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
// std
#include <vector>

// Eigen
#include <Eigen/Core>

// Tasks
#include "QPSolver.h"


namespace tasks
{

namespace qp
{


// Value add to the diagonal to ensure positive matrix
static const double DIAG_CONSTANT = 1e-4;


/**
	* Fill the \f$ Q \f$ matrix and the \f$ c \f$ vector based on the
	* task list.
	*/
inline void fillQC(const std::vector<Task*>& tasks, int nrVars,
	Eigen::MatrixXd& Q, Eigen::VectorXd& C)
{
	for(std::size_t i = 0; i < tasks.size(); ++i)
	{
		const Eigen::MatrixXd& Qi = tasks[i]->Q();
		const Eigen::VectorXd& Ci = tasks[i]->C();
		std::pair<int, int> b = tasks[i]->begin();

		int r = static_cast<int>(Qi.rows());
		int c = static_cast<int>(Qi.cols());

		Q.block(b.first, b.second, r, c) += tasks[i]->weight()*Qi;
		C.segment(b.first, r) += tasks[i]->weight()*Ci;

        // std::cout << "dim(Qi): " << Qi.rows() << " " << Qi.cols() << std::endl;
	}

	// try to transform Q_ to a positive matrix
	// we just add a small value to the diagonal since
	// the first necessary condition is to have
	// Q_(i,i) > 0
	// may be we can try to check the second
	// condition in a near future
	// Q_(i,i) + Q_(j,j) > 2·Q_(i,j) for i≠j
	for(int i = 0; i < nrVars; ++i)
	{
		if(std::abs(Q(i, i)) < DIAG_CONSTANT)
		{
			Q(i, i) += DIAG_CONSTANT;
		}
	}
}


// general qp form


/**
	* Fill the \f$ A \f$ matrix and the \f$ L \f$ and \f$ U \f$ bounds vectors
	* based on the equality constaint list.
	*/
inline int fillEq(const std::vector<Equality*>& eq, int nrVars,
	int nrALines, Eigen::MatrixXd& A, Eigen::VectorXd& AL, Eigen::VectorXd& AU)
{
	for(std::size_t i = 0; i < eq.size(); ++i)
	{
		// ineq constraint can return a matrix with more line
		// than the number of constraint
		int nrConstr = eq[i]->nrEq();
		const Eigen::MatrixXd& Ai = eq[i]->AEq();
		const Eigen::VectorXd& bi = eq[i]->bEq();

		A.block(nrALines, 0, nrConstr, nrVars) = Ai.block(0, 0, nrConstr, nrVars);
		AL.segment(nrALines, nrConstr) = bi.head(nrConstr);
		AU.segment(nrALines, nrConstr) = bi.head(nrConstr);

		nrALines += nrConstr;
	}

	return nrALines;
}


/**
	* Fill the \f$ A \f$ matrix and the \f$ L \f$ and \f$ U \f$ bounds vectors
	* based on the inequality constaint list.
	*/
inline int fillInEq(const std::vector<Inequality*>& inEq, int nrVars,
	int nrALines, Eigen::MatrixXd& A, Eigen::VectorXd& AL, Eigen::VectorXd& AU)
{
	for(std::size_t i = 0; i < inEq.size(); ++i)
	{
		// ineq constraint can return a matrix with more line
		// than the number of constraint
		int nrConstr = inEq[i]->nrInEq();
		const Eigen::MatrixXd& Ai = inEq[i]->AInEq();
		const Eigen::VectorXd& bi = inEq[i]->bInEq();

		A.block(nrALines, 0, nrConstr, nrVars) = Ai.block(0, 0, nrConstr, nrVars);
		AL.segment(nrALines, nrConstr).fill(-std::numeric_limits<double>::infinity());
		AU.segment(nrALines, nrConstr) = bi.head(nrConstr);

		nrALines += nrConstr;
	}

	return nrALines;
}


/**
	* Fill the \f$ A \f$ matrix and the \f$ L \f$ and \f$ U \f$ bounds vectors
	* based on the general inequality constaint list.
	*/
inline int fillGenInEq(const std::vector<GenInequality*>& genInEq, int nrVars,
	int nrALines, Eigen::MatrixXd& A, Eigen::VectorXd& AL, Eigen::VectorXd& AU)
{
	for(std::size_t i = 0; i < genInEq.size(); ++i)
	{
		// ineq constraint can return a matrix with more line
		// than the number of constraint
        // std::cout << genInEq[i]->nameGenInEq() << std::endl;

		int nrConstr = genInEq[i]->nrGenInEq();
		const Eigen::MatrixXd& Ai = genInEq[i]->AGenInEq();
		const Eigen::VectorXd& ALi = genInEq[i]->LowerGenInEq();
		const Eigen::VectorXd& AUi = genInEq[i]->UpperGenInEq();

		A.block(nrALines, 0, nrConstr, nrVars) =
			Ai.block(0, 0, nrConstr, nrVars);
		AL.segment(nrALines, nrConstr) = ALi.head(nrConstr);
		AU.segment(nrALines, nrConstr) = AUi.head(nrConstr);

		nrALines += nrConstr;
	}

	return nrALines;
}


// standard qp form


/**
	* Fill the \f$ A \f$ matrix and the \f$ b \f$ vectors
	* based on the equality constaint list.
	*/
inline int fillEq(const std::vector<Equality*>& eq, int nrVars,
	int nrALines, Eigen::MatrixXd& A, Eigen::VectorXd& b)
{
	for(std::size_t i = 0; i < eq.size(); ++i)
	{
		// std::cout << eq[i]->nameEq() << std::endl;

		// ineq constraint can return a matrix with more line
		// than the number of constraint
		int nrConstr = eq[i]->nrEq();
		const Eigen::MatrixXd& Ai = eq[i]->AEq();
		const Eigen::VectorXd& bi = eq[i]->bEq();

		A.block(nrALines, 0, nrConstr, nrVars) =
			Ai.block(0, 0, nrConstr, nrVars);
		b.segment(nrALines, nrConstr) = bi.head(nrConstr);

		nrALines += nrConstr;
	}

	return nrALines;
}


/**
	* Fill the \f$ A \f$ matrix and the \f$ b \f$ vectors
	* based on the inequality constaint list.
	*/
inline int fillInEq(const std::vector<Inequality*>& inEq, int nrVars,
	int nrALines, Eigen::MatrixXd& A, Eigen::VectorXd& b)
{
	for(std::size_t i = 0; i < inEq.size(); ++i)
	{
		// std::cout << inEq[i]->nameInEq() << std::endl;

		// ineq constraint can return a matrix with more line
		// than the number of constraint
		int nrConstr = inEq[i]->nrInEq();
		const Eigen::MatrixXd& Ai = inEq[i]->AInEq();
		const Eigen::VectorXd& bi = inEq[i]->bInEq();

		A.block(nrALines, 0, nrConstr, nrVars) =
			Ai.block(0, 0, nrConstr, nrVars);
		b.segment(nrALines, nrConstr) = bi.head(nrConstr);

		nrALines += nrConstr;
	}

	return nrALines;
}


/**
	* Fill the \f$ A \f$ matrix and the \f$ b \f$ vectors
	* based on the general inequality constaint list.
	*/
inline int fillGenInEq(const std::vector<GenInequality*>& genInEq, int nrVars,
	int nrALines, Eigen::MatrixXd& A, Eigen::VectorXd& b)
{
	for(std::size_t i = 0; i < genInEq.size(); ++i)
	{
		// std::cout << genInEq[i]->nameGenInEq() << std::endl;

		// ineq constraint can return a matrix with more line
		// than the number of constraint
		int nrConstr = genInEq[i]->nrGenInEq();
		const Eigen::MatrixXd& Ai = genInEq[i]->AGenInEq();
		const Eigen::VectorXd& ALi = genInEq[i]->LowerGenInEq();
		const Eigen::VectorXd& AUi = genInEq[i]->UpperGenInEq();

		A.block(nrALines, 0, nrConstr, nrVars) =
			-Ai.block(0, 0, nrConstr, nrVars);
		b.segment(nrALines, nrConstr) = -ALi.head(nrConstr);

		nrALines += nrConstr;

		A.block(nrALines, 0, nrConstr, nrVars) =
			Ai.block(0, 0, nrConstr, nrVars);
		b.segment(nrALines, nrConstr) = AUi.head(nrConstr);

		nrALines += nrConstr;
	}

	return nrALines;
}


/**
	* Fill the \f$ L \f$  and \f$ U \f$ bounds vectors
	* based on the bound constaint list.
	*/
inline void fillBound(const std::vector<Bound*>& bounds,
	Eigen::VectorXd& XL, Eigen::VectorXd& XU)
{

	for(std::size_t i = 0; i < bounds.size(); ++i)
	{
		// std::cout << bounds[i]->nameBound() << std::endl;

		const Eigen::VectorXd& XLi = bounds[i]->Lower();
		const Eigen::VectorXd& XUi = bounds[i]->Upper();
		int bv = bounds[i]->beginVar();

		XL.segment(bv, XLi.size()) = XLi;
		XU.segment(bv, XUi.size()) = XUi;
	}
}


// print of a constraint at a given line
template<typename T>
std::ostream& printConstr(const Eigen::VectorXd& result, T* constr, int line,
	std::ostream& out);

template<>
inline std::ostream& printConstr(const Eigen::VectorXd& result, Equality* constr,
	int line, std::ostream& out)
{
	out << constr->AEq().row(line)*result <<" = " <<
				 constr->bEq()(line);
	return out;
}

template<>
inline std::ostream& printConstr(const Eigen::VectorXd& result, Inequality* constr,
	int line, std::ostream& out)
{
	out << constr->AInEq().row(line)*result <<" <= " <<
				 constr->bInEq()(line);
	return out;
}

template<>
inline std::ostream& printConstr(const Eigen::VectorXd& result, GenInequality* constr,
	int line, std::ostream& out)
{
	out << constr->LowerGenInEq()(line) << " <= " <<
				 constr->AGenInEq().row(line)*result <<" <= " <<
				 constr->UpperGenInEq()(line);
	return out;
}


template <typename T>
inline std::ostream& constrErrorMsg(const std::vector<rbd::MultiBody>& mbs,
	const Eigen::VectorXd& result,
	int ALine, const std::vector<T*>& constr, int& start, int& end,
	std::ostream& out)
{
	for(T* e: constr)
	{
		end += constr_traits<T>::nrLines(e);
		if(ALine >= start && ALine < end)
		{
			int line = ALine - start;
			out << constr_traits<T>::name(e) << " violated at line: " << line << std::endl;
			out << constr_traits<T>::desc(e, mbs, line) << std::endl;
			printConstr(result, e, line, out) << std::endl;
			start = end;
			break;
		}
		start = end;
	}
	return out;
}


} // namespace qp

} // namespace tasks
