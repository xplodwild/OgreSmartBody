/****************************************************************
 * OgreSmartBody wrapper
 * Copyright (C) 2013 Guillaume Lesniak

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************/

#ifndef _CAKAOTWO_SMARTBODYTOOLS_H_
#define _CAKAOTWO_SMARTBODYTOOLS_H_

#include <CT/Prerequisites.h>

namespace SmartBody
{
	class SBJoint;
	class SBJointMap;
	class SBSteerAgent;
	class SBFaceDefinition;
};

namespace CT
{

/**
 * This class mimics some of the core SmartBody python scripts, but in C++
 */
class SmartBodyTools
{
public:
	static SmartBody::SBJointMap* makeZebra2Map();
	static void retargetStandardMotions(const std::string& _target);
	static SmartBody::SBFaceDefinition* getDefaultFaceDefinition();


	// stateAllLocomotion.py
	static void locomotionSetup(const std::string& skeletonName, const std::string& baseJoint,
		const std::string& preFix, const std::string& statePreFix);

	// stateAllStarting.py
	static void startingSetup(const std::string& skeletonName, const std::string& baseJoint,
		const std::string& preFix, const std::string& statePreFix);

	// stateAllIdleTurn.py
	static void idleTurnSetup(const std::string& skeletonName, const std::string& baseJoint,
		const std::string& preFix, const std::string& statePreFix);

	// stateAllStep.py
	static void stepSetup(const std::string& skeletonName, const std::string& baseJoint,
		const std::string& preFix, const std::string& statePreFix);

	// motion-retarget.py
	static void retargetCharacter(const std::string& charName, const std::string& targetSkelName,
		bool reach = true);
	static void retargetSetup(const std::string& targetSkelName);
	static std::vector<std::string> getStandardGestureMotions(const std::string& preFix);
	static std::vector<std::string> getStandardLocoMotions(const std::string& preFix);
	static std::vector<std::string> getStandardReachMotions(const std::string& preFix);
	static void retargetMotion(const std::string& motionName, const std::string& srcSkelName,
		const std::string& tgtSkelName);

	// transitions.py
	static void transitionSetup(const std::string& preFix, const std::string& statePrefix);

	// init-steer-agents
	static void setupSteerAgent(const std::string& charName, const std::string& prefix);

private:
	static bool m_bBradMotionRT;
};

};


#endif // _CAKAOTWO_SMARTBODYTOOLS_H_
