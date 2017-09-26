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
#include "LSSOLQPSolver.h"

// includes
// Tasks
#include "GenQPUtils.h"
#include "QPSolver.h"


namespace tasks
{

namespace qp
{


LSSOLQPSolver::LSSOLQPSolver():
	lssol_(),
	A_(),AL_(),AU_(),
	XL_(),XU_(),
	Q_(),C_(),
	nrALines_(0)
{
	std::cout << "starting LSSOLQPSolver" << std::endl;
	lssol_.warm(true);
	lssol_.feasibilityTol(1e-6);
}


void LSSOLQPSolver::updateSize(int nrVars, int nrEq, int nrInEq, int nrGenInEq)
{
	int maxALines = nrEq + nrInEq + nrGenInEq;
	A_.resize(maxALines, nrVars);
	AL_.resize(maxALines);
	AU_.resize(maxALines);

	XL_.resize(nrVars);
	XU_.resize(nrVars);

	Q_.resize(nrVars, nrVars);
	C_.resize(nrVars);

	lssol_.problem(nrVars, maxALines);
}


void LSSOLQPSolver::updateMatrix(
	const std::vector<Task*>& tasks,
	const std::vector<Equality*>& eqConstr,
	const std::vector<Inequality*>& inEqConstr,
	const std::vector<GenInequality*>& genInEqConstr,
	const std::vector<Bound*>& boundConstr)
{
	A_.setZero();
	AL_.setZero();
	AU_.setZero();
	XL_.fill(-std::numeric_limits<double>::infinity());
	XU_.fill(std::numeric_limits<double>::infinity());
	Q_.setZero();
	C_.setZero();

	const int nrVars = int(Q_.rows());

	nrALines_ = 0;
	nrALines_ = fillEq(eqConstr, nrVars, nrALines_, A_, AL_, AU_);
	nrALines_ = fillInEq(inEqConstr, nrVars, nrALines_, A_, AL_, AU_);
	nrALines_ = fillGenInEq(genInEqConstr, nrVars, nrALines_, A_, AL_, AU_);

	fillBound(boundConstr, XL_, XU_);
	fillQC(tasks, nrVars, Q_, C_);
}


bool LSSOLQPSolver::solve()
{

	bool success = lssol_.solve(Q_, C_,
		A_.block(0, 0, nrALines_, int(A_.cols())), int(A_.rows()),
		AL_.segment(0, nrALines_), AU_.segment(0, nrALines_), XL_, XU_);
	return success;
}


const Eigen::VectorXd& LSSOLQPSolver::result() const
{
	return lssol_.result();
}


std::ostream& LSSOLQPSolver::errorMsg(
	const std::vector<rbd::MultiBody>& mbs,
	const std::vector<Task*>& /* tasks */,
	const std::vector<Equality*>& eqConstr,
	const std::vector<Inequality*>& inEqConstr,
	const std::vector<GenInequality*>& genInEqConstr,
	const std::vector<Bound*>& boundConstr,
	std::ostream& out) const
{
	const int nrVars = int(Q_.rows());

	out << "lssol output: " << lssol_.fail() << std::endl;
	const Eigen::VectorXi& istate = lssol_.istate();
	// check bound constraint
	for(int i = 0; i < nrVars; ++i)
	{
		if(istate(i) < 0)
		{
			for(Bound* b: boundConstr)
			{
				int start = b->beginVar();
				int end = start + int(b->Lower().rows());
				if(i >= start && i < end)
				{
					int line = i - start;
					out << b->nameBound() << " violated at line: " << line << std::endl;
					out << b->descBound(mbs, line) << std::endl;
					out << XL_(i) << " <= " << lssol_.result()(i) << " <= " << XU_(i) << std::endl;
					break;
				}
			}
		}
	}

	// check inequality constraint
	for(int i = 0; i < nrALines_; ++i)
	{
		int iInIstate = i + nrVars;
		if(istate(iInIstate) < 0)
		{
			int start = 0;
			int end = 0;

			constrErrorMsg(mbs, lssol_.result(), i, eqConstr, start, end, out);
			constrErrorMsg(mbs, lssol_.result(), i, inEqConstr, start, end, out);
			constrErrorMsg(mbs, lssol_.result(), i, genInEqConstr, start, end, out);
			out << std::endl;
		}
	}
	return out;
}


} // namespace qp

} // namespace tasks
