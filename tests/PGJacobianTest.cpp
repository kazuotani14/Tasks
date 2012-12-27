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

// includes
// std
#include <iostream>
#include <tuple>

// boost
#define BOOST_TEST_MODULE PGJacobianTest
#include <boost/test/unit_test.hpp>
#include <boost/math/constants/constants.hpp>

// eigen3
#include <Eigen/Core>
#include <Eigen/Geometry>

// SpaceVecAlg
#include <SpaceVecAlg/SpaceVecAlg>

// RBDyn
#include <MultiBody.h>
#include <MultiBodyConfig.h>
#include <MultiBodyGraph.h>
#include <Jacobian.h>

// Tasks
#include "PGJacobian.h"


const double TOL = 1e-8;


std::vector<double> randomFree()
{
	using namespace Eigen;
	Quaterniond q(Vector4d::Random());
	q.normalize();
	Vector3d p(Vector3d::Random());

	return {q.w(), q.x(), q.y(), q.z(), p.x(), p.y(), p.z()};
}


std::tuple<rbd::MultiBody, rbd::MultiBodyConfig> makFreeXArm()
{
	using namespace Eigen;
	using namespace sva;
	using namespace rbd;

	MultiBodyGraph mbg;

	double mass = 1.;
	Matrix3d I = Matrix3d::Identity();
	Vector3d h = Vector3d::Zero();

	RBInertia rbi(mass, h, I);

	Body b0(rbi, 0, "b0");
	Body b1(rbi, 1, "b1");

	mbg.addBody(b0);
	mbg.addBody(b1);

	Joint j0(Joint::RevX, true, 0, "j0");

	mbg.addJoint(j0);

	//  Root     j0
	//  ---- b0 ---- b1
	//  Free     X


	PTransform to(Vector3d(0., 0.5, 0.));
	PTransform from(Vector3d(0., 0., 0.));


	mbg.linkBodies(0, PTransform::Identity(), 1, from, 0);

	MultiBody mb = mbg.makeMultiBody(0, false);

	MultiBodyConfig mbc(mb);

	mbc.q = {{1., 0., 0., 0., 0., 0., 0.}, {0.}};
	mbc.alpha = {{0., 0., 0., 0., 0., 0.}, {0.}};
	mbc.alphaD = {{0., 0., 0., 0., 0., 0.}, {0.}};
	mbc.jointTorque = {{0., 0., 0., 0., 0., 0.}, {0.}, {0.}, {0.}};
	ForceVec f0(Vector6d::Zero());
	mbc.force = {f0, f0};

	return std::make_tuple(mb, mbc);
}



BOOST_AUTO_TEST_CASE(angularVelToQuatVelVSquatVelToAngularVel)
{
	using namespace Eigen;
	using namespace sva;
	using namespace rbd;
	using namespace tasks;
	namespace cst = boost::math::constants;

	for(int i = 0; i < 10; ++i)
	{
		std::vector<double> q = randomFree();
		BOOST_REQUIRE_EQUAL(pg::angularVelToQuatVel(q).transpose()*2.,
			pg::quatVelToAngularVel(q)*0.5);
		BOOST_REQUIRE_EQUAL(pg::angularVelToQuatVel(q)*2.,
			pg::quatVelToAngularVel(q).transpose()*0.5);
	}

	for(int i = 0; i < 10; ++i)
	{
		std::vector<double> q = randomFree();
		Vector3d av = Vector3d::Random();
		Vector4d qv = pg::angularVelToQuatVel(q)*av;
		Vector3d av2 = pg::quatVelToAngularVel(q)*qv;

		BOOST_REQUIRE_SMALL((av - av2).norm(), TOL);
	}

	for(int i = 0; i < 10; ++i)
	{
		std::vector<double> q = randomFree();
		Vector3d av = Vector3d::Random();
		Vector4d qv = pg::angularVelToQuatVel(q)*av;
		Vector3d av2 = pg::quatVelToAngularVel(q)*qv;
		Vector4d qv2 = pg::angularVelToQuatVel(q)*av2;

		BOOST_REQUIRE_SMALL((qv - qv2).norm(), TOL);
	}
}
