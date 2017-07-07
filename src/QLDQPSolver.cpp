// Copyright 2012-2016 CNRS-UM LIRMM, CNRS-AIST JRL
//
// This file is part of Tasks.
//
// Tasks is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tasks is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Tasks.  If not, see <http://www.gnu.org/licenses/>.

// associated header
#include "QLDQPSolver.h"

// includes
// Tasks
#include "GenQPUtils.h"
#include "QPSolver.h"


namespace tasks
{

namespace qp
{


QLDQPSolver::QLDQPSolver():
	qld_(),
	Aeq_(),Aineq_(),
	beq_(), bineq_(),
	XL_(),XU_(),
	Q_(),C_(),
	nrAeqLines_(0), nrAineqLines_(0),
	last_Q_(), last_C_(), last_mats_available(false)
{
    std::cout << "QLDQPSolver init" << std::endl;

}


void QLDQPSolver::updateSize(int nrVars, int nrEq, int nrInEq, int nrGenInEq)
{
	int maxAeqLines = nrEq;
	int maxAineqLines = nrInEq + nrGenInEq*2;

	Aeq_.resize(maxAeqLines, nrVars);
	Aineq_.resize(maxAineqLines, nrVars);

	beq_.resize(maxAeqLines);
	bineq_.resize(maxAineqLines);

	XL_.resize(nrVars);
	XU_.resize(nrVars);

	Q_.resize(nrVars, nrVars);
	C_.resize(nrVars);

	qld_.problem(nrVars, maxAeqLines, maxAineqLines);
}


void QLDQPSolver::updateMatrix(
	const std::vector<Task*>& tasks,
	const std::vector<Equality*>& eqConstr,
	const std::vector<Inequality*>& inEqConstr,
	const std::vector<GenInequality*>& genInEqConstr,
	const std::vector<Bound*>& boundConstr)
{
	Aeq_.setZero();
	Aineq_.setZero();
	beq_.setZero();
	bineq_.setZero();
	XL_.fill(-std::numeric_limits<double>::infinity());
	XU_.fill(std::numeric_limits<double>::infinity());
	Q_.setZero();
	C_.setZero();

	const int nrVars = int(Q_.rows());

	// std::cout << "size(eqConstr): " << eqConstr.size() << std::endl;
	// std::cout << "size(inEqConstr): " << inEqConstr.size() << std::endl;
	// std::cout << "size(genInEqConstr): " << genInEqConstr.size() << std::endl;

	nrAeqLines_ = 0;
	nrAeqLines_ = fillEq(eqConstr, nrVars, nrAeqLines_, Aeq_, beq_);
	nrAineqLines_ = 0;
	nrAineqLines_ = fillInEq(inEqConstr, nrVars, nrAineqLines_, Aineq_, bineq_);
	nrAineqLines_ = fillGenInEq(genInEqConstr, nrVars, nrAineqLines_, Aineq_, bineq_);

	// std::cout << "nrAeqLines_: " << nrAeqLines_ << " , nrAineqLines_: " << nrAineqLines_ << std::endl;

	fillBound(boundConstr, XL_, XU_);
	fillQC(tasks, nrVars, Q_, C_);

	if(!last_mats_available)
	{
		last_mats_available = true;
	}
	else
	{
		Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
		// std::cout << "Q-Qlast" << "\n" << Q_ - last_Q_ << std::endl;
		// std::cout << "C-Clast" << "\n" << C_ - last_C_ << std::endl;
	}
	last_Q_ = Q_;
	last_C_ = C_;

}


bool QLDQPSolver::solve()
{
	bool success = qld_.solve(Q_, C_,
		Aeq_.block(0, 0, nrAeqLines_, int(Aeq_.cols())), beq_.segment(0, nrAeqLines_),
		Aineq_.block(0, 0, nrAineqLines_, int(Aineq_.cols())), bineq_.segment(0, nrAineqLines_),
		XL_, XU_, 1e-6);

	return success;
}


const Eigen::VectorXd& QLDQPSolver::result() const
{
	return qld_.result();
}


std::ostream& QLDQPSolver::errorMsg(
	const std::vector<rbd::MultiBody>& /* mbs */,
	const std::vector<Task*>& /* tasks */,
	const std::vector<Equality*>& /* eqConstr */,
	const std::vector<Inequality*>& /* inEqConstr */,
	const std::vector<GenInequality*>& /* genInEqConstr */,
	const std::vector<Bound*>& /* boundConstr */,
	std::ostream& out) const
{
	return out;
}


} // namespace qp

} // namespace tasks
