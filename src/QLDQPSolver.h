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

#pragma once

// includes
// eigen-qld
#include <eigen-qld/QLD.h>

// Tasks
#include "GenQPSolver.h"


namespace tasks
{

namespace qp
{


/**
	* GenQPSolver interface implementation with the QLD QP solver.
	*/
class TASKS_DLLAPI QLDQPSolver : public GenQPSolver
{
public:
	QLDQPSolver();

	virtual void updateSize(int nrVars, int nrEq, int nrInEq, int nrGenInEq);
	virtual void updateMatrix(const std::vector<Task*>& tasks,
		const std::vector<Equality*>& eqConstr,
		const std::vector<Inequality*>& inEqConstr,
		const std::vector<GenInequality*>& genInEqConstr,
		const std::vector<Bound*>& boundConstr);
	virtual bool solve();
	virtual const Eigen::VectorXd& result() const;
	virtual std::ostream& errorMsg(const std::vector<rbd::MultiBody>& mbs,
		const std::vector<Task*>& tasks,
		const std::vector<Equality*>& eqConstr,
		const std::vector<Inequality*>& inEqConstr,
		const std::vector<GenInequality*>& genInEqConstr,
		const std::vector<Bound*>& boundConstr,
		std::ostream& out) const override;

    Eigen::MatrixXd Q_;
    Eigen::VectorXd C_;
	Eigen::MatrixXd last_Q_;
	Eigen::VectorXd last_C_;
	bool last_mats_available;

private:
	Eigen::QLD qld_;

	Eigen::MatrixXd Aeq_, Aineq_;
	Eigen::VectorXd beq_, bineq_;

	Eigen::VectorXd XL_;
	Eigen::VectorXd XU_;


	int nrAeqLines_;
	int nrAineqLines_;
};


} // namespace qp

} // namespace tasks
