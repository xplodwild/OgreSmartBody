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

#include "stdafx.h"
#include <CT/SmartBodyTools.h>
#include <CT/SmartBodyManager.h>

#include <sb/SBScene.h>
#include <sb/SBSkeleton.h>
#include <sb/SBJoint.h>
#include <sb/SBJointMap.h>
#include <sb/SBJointMapManager.h>
#include <sb/SBSteerManager.h>
#include <sb/SBSteerAgent.h>
#include <sb/SBRetarget.h>
#include <sb/SBRetargetManager.h>
#include <sb/SBMotion.h>
#include <sb/SBFaceDefinition.h>
#include <sb/SBAnimationState.h>
#include <sb/SBAnimationStateManager.h>
#include <sb/SBAnimationTransition.h>

namespace CT
{

bool SmartBodyTools::m_bBradMotionRT = false;

//======================================================
SmartBody::SBJointMap* SmartBodyTools::makeZebra2Map()
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBJointMapManager* jmm = scene->getJointMapManager();

	// Mapping from Zebra2 skeleton to SmartBody skeleton
	SmartBody::SBJointMap* zebra2Map = jmm->getJointMap("zebra2");
	if (!zebra2Map)
		zebra2Map = jmm->createJointMap("zebra2");

	// Core
	zebra2Map->setMapping("JtRoot", "base");
	zebra2Map->setMapping("JtSpineA", "spine1");
	zebra2Map->setMapping("JtSpineB", "spine2");
	zebra2Map->setMapping("JtSpineC", "spine3");
	zebra2Map->setMapping("JtNeckA", "spine4");
	zebra2Map->setMapping("JtNeckB", "spine5");
	zebra2Map->setMapping("JtSkullA", "skullbase");

	// Arm, left
	zebra2Map->setMapping("JtClavicleLf", "l_sternoclavicular");
	zebra2Map->setMapping("JtShoulderLf", "l_shoulder");
	zebra2Map->setMapping("JtUpperArmTwistALf", "l_upperarm1");
	zebra2Map->setMapping("JtUpperArmTwistBLf", "l_upperarm2");
	zebra2Map->setMapping("JtElbowLf", "l_elbow");
	zebra2Map->setMapping("JtForearmTwistALf", "l_forearm1");
	zebra2Map->setMapping("JtForearmTwistBLf", "l_forearm2");
	zebra2Map->setMapping("JtWristLf", "l_wrist");
	zebra2Map->setMapping("JtThumbALf", "l_thumb1");
	zebra2Map->setMapping("JtThumbBLf", "l_thumb2");
	zebra2Map->setMapping("JtThumbCLf", "l_thumb3");
	zebra2Map->setMapping("JtThumbDLf", "l_thumb4");
	zebra2Map->setMapping("JtIndexALf", "l_index1");
	zebra2Map->setMapping("JtIndexBLf", "l_index2");
	zebra2Map->setMapping("JtIndexCLf", "l_index3");
	zebra2Map->setMapping("JtIndexDLf", "l_index4");
	zebra2Map->setMapping("JtMiddleALf", "l_middle1");
	zebra2Map->setMapping("JtMiddleBLf", "l_middle2");
	zebra2Map->setMapping("JtMiddleCLf", "l_middle3");
	zebra2Map->setMapping("JtMiddleDLf", "l_middle4");
	zebra2Map->setMapping("JtRingALf", "l_ring1");
	zebra2Map->setMapping("JtRingBLf", "l_ring2");
	zebra2Map->setMapping("JtRingCLf", "l_ring3");
	zebra2Map->setMapping("JtRingDLf", "l_ring4");
	zebra2Map->setMapping("JtLittleALf", "l_pinky1");
	zebra2Map->setMapping("JtLittleBLf", "l_pinky2");
	zebra2Map->setMapping("JtLittleCLf", "l_pinky3");
	zebra2Map->setMapping("JtLittleDLf", "l_pinky4");

	// Arm, right
	zebra2Map->setMapping("JtClavicleRt", "r_sternoclavicular");
	zebra2Map->setMapping("JtShoulderRt", "r_shoulder");
	zebra2Map->setMapping("JtUpperArmTwistARt", "r_upperarm1");
	zebra2Map->setMapping("JtUpperArmTwistBRt", "r_upperarm2");
	zebra2Map->setMapping("JtElbowRt", "r_elbow");
	zebra2Map->setMapping("JtForearmTwistARt", "r_forearm1");
	zebra2Map->setMapping("JtForearmTwistBRt", "r_forearm2");
	zebra2Map->setMapping("JtWristRt", "r_wrist");
	zebra2Map->setMapping("JtThumbARt", "r_thumb1");
	zebra2Map->setMapping("JtThumbBRt", "r_thumb2");
	zebra2Map->setMapping("JtThumbCRt", "r_thumb3");
	zebra2Map->setMapping("JtThumbDRt", "r_thumb4");
	zebra2Map->setMapping("JtIndexARt", "r_index1");
	zebra2Map->setMapping("JtIndexBRt", "r_index2");
	zebra2Map->setMapping("JtIndexCRt", "r_index3");
	zebra2Map->setMapping("JtIndexDRt", "r_index4");
	zebra2Map->setMapping("JtMiddleARt", "r_middle1");
	zebra2Map->setMapping("JtMiddleBRt", "r_middle2");
	zebra2Map->setMapping("JtMiddleCRt", "r_middle3");
	zebra2Map->setMapping("JtMiddleDRt", "r_middle4");
	zebra2Map->setMapping("JtRingARt", "r_ring1");
	zebra2Map->setMapping("JtRingBRt", "r_ring2");
	zebra2Map->setMapping("JtRingCRt", "r_ring3");
	zebra2Map->setMapping("JtRingDRt", "r_ring4");
	zebra2Map->setMapping("JtLittleARt", "r_pinky1");
	zebra2Map->setMapping("JtLittleBRt", "r_pinky2");
	zebra2Map->setMapping("JtLittleCRt", "r_pinky3");
	zebra2Map->setMapping("JtLittleDRt", "r_pinky4");

	// Leg, left
	zebra2Map->setMapping("JtHipLf", "l_hip");
	zebra2Map->setMapping("JtKneeLf", "l_knee");
	zebra2Map->setMapping("JtAnkleLf", "l_ankle");
	zebra2Map->setMapping("JtBallLf", "l_forefoot");
	zebra2Map->setMapping("JtToeLf", "l_toe");

	// Leg, right
	zebra2Map->setMapping("JtHipRt", "r_hip");
	zebra2Map->setMapping("JtKneeRt", "r_knee");
	zebra2Map->setMapping("JtAnkleRt", "r_ankle");
	zebra2Map->setMapping("JtBallRt", "r_forefoot");
	zebra2Map->setMapping("JtToeRt", "r_toe");

	// Head, left
	zebra2Map->setMapping("JtEyeLf", "eyeball_left");
	zebra2Map->setMapping("JtEyelidUpperLf", "upper_eyelid_left");
	zebra2Map->setMapping("JtEyelidLowerLf", "lower_eyelid_left");

	// Head, right
	zebra2Map->setMapping("JtEyeRt", "eyeball_right");
	zebra2Map->setMapping("JtEyelidUpperRt", "upper_eyelid_right");
	zebra2Map->setMapping("JtEyelidLowerRt", "lower_eyelid_right");

	return zebra2Map;
}
//======================================================
void SmartBodyTools::retargetStandardMotions(const std::string& _target)
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBSkeleton* bradSkel = scene->getSkeleton("ChrBrad.sk");

	// If we haven't yet setup the initial retargetted motion, do it
	if (!m_bBradMotionRT)
	{
		m_bBradMotionRT = true;
		SmartBody::SBJointMap* zebra2Map = makeZebra2Map();
		zebra2Map->applySkeleton(bradSkel);
		zebra2Map->applyMotionRecurse("Data/SmartBody/ChrBrad");

		std::list<std::string> motions;
		motions.push_back("ChrBrad@Guitar01");
		motions.push_back("ChrBrad@Idle01");
		motions.push_back("ChrBrad@Idle02");
		motions.push_back("ChrBrad@Idle03");

		for (auto it = motions.begin(); it != motions.end(); ++it)
		{
			SmartBody::SBMotion* motion = scene->getMotion(*it);
			motion->setMotionSkeletonName("ChrBrad.sk");
		}
	}

	// Then retarget on the target skeleton
	SmartBody::SBRetargetManager* rtm = scene->getRetargetManager();
	SmartBody::SBRetarget* retarget = rtm->createRetarget("ChrBrad.sk", _target);

	std::vector<std::string> endJoints;
	endJoints.push_back("l_forefoot");
	endJoints.push_back("l_toe");
	endJoints.push_back("l_wrist");
	endJoints.push_back("r_forefoot");
	endJoints.push_back("r_toe");
	endJoints.push_back("r_wrist");

	std::vector<std::string> relativeJoints;
	relativeJoints.push_back("spine1");
	relativeJoints.push_back("spine2");
	relativeJoints.push_back("spine3");
	relativeJoints.push_back("spine4");
	relativeJoints.push_back("spine5");
	relativeJoints.push_back("r_sternoclavicular");
	relativeJoints.push_back("l_sternoclavicular");

	retarget->initRetarget(endJoints, relativeJoints);
}
//======================================================
SmartBody::SBFaceDefinition* SmartBodyTools::getDefaultFaceDefinition()
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBFaceDefinition* facedef = scene->getFaceDefinition("_SB_DefaultFaceDef");

	if (!facedef)
	{
		facedef = scene->createFaceDefinition("_SB_DefaultFaceDef");

		facedef->setFaceNeutral("utah_face_neutral");

		facedef->setAU(1,  "left",  "utah_001_inner_brow_raiser_lf");
		facedef->setAU(1,  "right", "utah_001_inner_brow_raiser_rt");
		facedef->setAU(2,  "left",  "utah_002_outer_brow_raiser_lf");
		facedef->setAU(2,  "right", "utah_002_outer_brow_raiser_rt");
		facedef->setAU(2,  "both",  "utah_002_outer_brow_raiser");
		facedef->setAU(4,  "left",  "utah_004_brow_lowerer_lf");
		facedef->setAU(4,  "right", "utah_004_brow_lowerer_rt");
		facedef->setAU(5,  "both",  "utah_005_upper_lid_raiser");
		facedef->setAU(6,  "both",  "utah_006_cheek_raiser");
		facedef->setAU(7,  "both",  "utah_007_lid_tightener");
		facedef->setAU(9,  "both",  "utah_009_nose_wrinkler");
		facedef->setAU(10, "both",  "utah_010_upper_lip_raiser");
		facedef->setAU(12, "left",  "utah_012_lip_corner_puller_lf");
		facedef->setAU(12, "right", "utah_012_lip_corner_puller_rt");
		facedef->setAU(12, "both",  "utah_012_lip_corner_puller");
		facedef->setAU(20, "left",  "utah_020_lip_stretcher_lf");
		facedef->setAU(20, "right", "utah_020_lip_stretcher_rt");
		facedef->setAU(20, "both",  "utah_020_lip_stretcher");
		facedef->setAU(23, "both",  "utah_023_lip_tightener");
		facedef->setAU(25, "both",  "utah_025_lips_part");
		facedef->setAU(26, "both",  "utah_026_jaw_drop");
		facedef->setAU(27, "both",  "utah_027_mouth_stretch");
		facedef->setAU(37, "both",  "utah_037_1_4");
		facedef->setAU(38, "both",  "utah_038_nostril_dilator");
		facedef->setAU(39, "both",  "utah_039_nostril_compressor");
		facedef->setAU(45, "left",  "utah_045_blink_lf");
		facedef->setAU(45, "right", "utah_045_blink_rt");

		facedef->setViseme("ao",      "utah_ao");
		facedef->setViseme("bmp",     "utah_bmp");
		facedef->setViseme("d",       "utah_d");
		facedef->setViseme("ee",      "utah_ee");
		facedef->setViseme("er",      "utah_er");
		facedef->setViseme("f",       "utah_f");
		facedef->setViseme("ih",      "utah_ih");
		facedef->setViseme("j",       "utah_j");
		facedef->setViseme("kg",      "utah_kg");
		facedef->setViseme("ng",      "utah_ng");
		facedef->setViseme("oh",      "utah_oh");
		facedef->setViseme("oo",      "utah_oo");
		facedef->setViseme("r",       "utah_r");
		facedef->setViseme("th",      "utah_th");
		facedef->setViseme("z",       "utah_z");
	}

	return facedef;
}
//======================================================
void SmartBodyTools::locomotionSetup(const std::string& skeletonName, const std::string& baseJoint,
		const std::string& preFix, const std::string& statePreFix)
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBAnimationBlendManager* stateManager = scene->getBlendManager();
	std::string stateName = statePreFix+"Locomotion";

	if (stateManager->getBlend(stateName) != nullptr) // don't create duplicate
	{
		printf("%s: duplicate!\n", __FUNCTION__);
		return;
	}

	SmartBody::SBAnimationBlend3D* state = stateManager->createBlend3D(stateName);

	// add motions
	std::vector<std::string> motions;
	motions.push_back(preFix+"ChrUtah_Walk001");
	motions.push_back(preFix+"ChrUtah_Idle001");
	motions.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn360Lf01");
	motions.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn360Rt01");
	motions.push_back(preFix+"ChrUtah_Meander01");
	motions.push_back(preFix+"ChrUtah_Shuffle01");
	motions.push_back(preFix+"ChrUtah_Jog001");
	motions.push_back(preFix+"ChrUtah_Run001");
	motions.push_back(preFix+"ChrUtah_WalkInCircleLeft001");
	motions.push_back(preFix+"ChrUtah_WalkInCircleRight001");
	motions.push_back(preFix+"ChrUtah_WalkInTightCircleLeft001");
	motions.push_back(preFix+"ChrUtah_WalkInTightCircleRight001");
	motions.push_back(preFix+"ChrUtah_RunInCircleLeft001");
	motions.push_back(preFix+"ChrUtah_RunInCircleRight001");
	motions.push_back(preFix+"ChrUtah_RunInTightCircleLeft01");
	motions.push_back(preFix+"ChrUtah_RunInTightCircleRight01");
	motions.push_back(preFix+"ChrUtah_StrafeSlowRt01");
	motions.push_back(preFix+"ChrUtah_StrafeSlowLf01");
	motions.push_back(preFix+"ChrUtah_StrafeFastRt01");
	motions.push_back(preFix+"ChrUtah_StrafeFastLf01");

	for (auto it = motions.begin(); it != motions.end(); ++it)
		state->addMotion((*it), 0, 0, 0);


	// correspondance points
	double floatarray[] = {0, 0.811475, 1.34262, 2.13333, 0, 0.698851, 1.37931, 2.13333, 0, 0.82023, 1.30207, 2.12966, 0, 0.812874, 1.35356, 2.12966, 0, 0.988525, 1.87377, 3.06667, 0, 0.713115, 1.29836, 2.13333, 0, 0.501639, 0.92459, 1.6, 0, 0.422951, 0.772131, 1.33333, 0, 0.840984, 1.39672, 2.13333, 0, 0.840984, 1.29836, 2.13333, 0, 0.845902, 1.30328, 2.13333, 0, 0.880328, 1.33279, 2.13333, 0, 0.437705, 0.811475, 1.33333, 0, 0.452459, 0.791803, 1.33333, 0, 0.462295, 0.757377, 1.33333, 0, 0.452459, 0.796721, 1.33333, 0, 0.90000, 1.41000, 2.13000, 0.72, 1.38, 1.92, 0.72, 0, 0.473684, 0.920079, 1.6, 0.4, 0.893233, 1.28421, 0.4};
	int numCorrespondancePoints = 4;
	/*if (len(floatarray) != 4 * len(motions)):
		print "**Correspondance points input wrong"*/
		
	for (int i = 0; i < numCorrespondancePoints; i++)
	{
		std::vector<double> points;
		for (int j = 0; j < motions.size(); j++)
		{
			points.push_back(floatarray[j * numCorrespondancePoints + i]);
		}

		state->addCorrespondencePoints(motions, points);
	}
		
	// reset parameters (because it needs context of correspondance points, extract parameters from motion)
	SmartBody::SBSkeleton* skeleton = scene->getSkeleton(skeletonName);
	SmartBody::SBJoint* joint = skeleton->getJointByName(baseJoint);

	int travelDirection[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, -90, 90, -90};

	for (int i  = 0; i < motions.size(); i++)
	{
		SmartBody::SBMotion* motion = scene->getMotion(motions[i]);

		if (!motion)
		{
			printf("Unknown motion: %s\n", motions[i].c_str());
			continue;
		}

		motion->connect(skeleton);
		std::vector<double> correspondancePoints = state->getCorrespondencePoints(i);
		int lenCorrespondancePoints = correspondancePoints.size();
		float speed = motion->getJointSpeed(joint, correspondancePoints[0], correspondancePoints[lenCorrespondancePoints - 1]);
		float omega = motion->getJointAngularSpeed(joint, correspondancePoints[0], correspondancePoints[lenCorrespondancePoints - 1]);
		int direction = travelDirection[i];
		state->setParameter(motions[i], speed, omega, direction);
		motion->disconnect();
	}
										 
	// add tetrahedrons (need automatic way to generate)
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_WalkInTightCircleLeft001", preFix+"ChrUtah_StrafeSlowRt01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_WalkInTightCircleLeft001", preFix+"ChrUtah_StrafeSlowLf01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_WalkInTightCircleRight001", preFix+"ChrUtah_StrafeSlowRt01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_WalkInTightCircleRight001", preFix+"ChrUtah_StrafeSlowLf01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Walk001", preFix+"ChrUtah_Jog001", preFix+"ChrUtah_WalkInCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Walk001", preFix+"ChrUtah_Jog001", preFix+"ChrUtah_WalkInCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Jog001", preFix+"ChrUtah_Run001", preFix+"ChrUtah_RunInCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Jog001", preFix+"ChrUtah_Run001", preFix+"ChrUtah_RunInCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_WalkInCircleLeft001", preFix+"ChrUtah_RunInCircleLeft001", preFix+"ChrUtah_Jog001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_WalkInCircleRight001", preFix+"ChrUtah_RunInCircleRight001", preFix+"ChrUtah_Jog001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_WalkInCircleLeft001", preFix+"ChrUtah_WalkInTightCircleLeft001", preFix+"ChrUtah_RunInCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_WalkInCircleRight001", preFix+"ChrUtah_WalkInTightCircleRight001", preFix+"ChrUtah_RunInCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_WalkInTightCircleLeft001", preFix+"ChrUtah_RunInCircleLeft001", preFix+"ChrUtah_RunInTightCircleLeft01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_WalkInTightCircleRight001", preFix+"ChrUtah_RunInCircleRight001", preFix+"ChrUtah_RunInTightCircleRight01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_Walk001", preFix+"ChrUtah_WalkInCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_WalkInCircleLeft001", preFix+"ChrUtah_WalkInTightCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_Walk001", preFix+"ChrUtah_WalkInCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_WalkInCircleRight001", preFix+"ChrUtah_WalkInTightCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Walk001", preFix+"ChrUtah_Jog001", preFix+"ChrUtah_WalkInCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Walk001", preFix+"ChrUtah_Jog001", preFix+"ChrUtah_WalkInCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Jog001", preFix+"ChrUtah_Run001", preFix+"ChrUtah_RunInCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Jog001", preFix+"ChrUtah_Run001", preFix+"ChrUtah_RunInCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_WalkInCircleLeft001", preFix+"ChrUtah_RunInCircleLeft001", preFix+"ChrUtah_Jog001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_WalkInCircleRight001", preFix+"ChrUtah_RunInCircleRight001", preFix+"ChrUtah_Jog001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_WalkInCircleLeft001", preFix+"ChrUtah_WalkInTightCircleLeft001", preFix+"ChrUtah_RunInCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_WalkInCircleRight001", preFix+"ChrUtah_WalkInTightCircleRight001", preFix+"ChrUtah_RunInCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_WalkInTightCircleLeft001", preFix+"ChrUtah_RunInCircleLeft001", preFix+"ChrUtah_RunInTightCircleLeft01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_WalkInTightCircleRight001", preFix+"ChrUtah_RunInCircleRight001", preFix+"ChrUtah_RunInTightCircleRight01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_Walk001", preFix+"ChrUtah_WalkInCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_WalkInCircleLeft001", preFix+"ChrUtah_WalkInTightCircleLeft001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_Walk001", preFix+"ChrUtah_WalkInCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Meander01", preFix+"ChrUtah_WalkInCircleRight001", preFix+"ChrUtah_WalkInTightCircleRight001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_StrafeFastRt01", preFix+"ChrUtah_RunInCircleRight001", preFix+"ChrUtah_RunInTightCircleRight01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_StrafeFastRt01", preFix+"ChrUtah_RunInCircleRight001", preFix+"ChrUtah_Run001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_StrafeFastRt01", preFix+"ChrUtah_RunInCircleLeft001", preFix+"ChrUtah_RunInTightCircleLeft01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_StrafeFastRt01", preFix+"ChrUtah_RunInCircleLeft001", preFix+"ChrUtah_Run001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_StrafeFastLf01", preFix+"ChrUtah_RunInCircleRight001", preFix+"ChrUtah_RunInTightCircleRight01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_StrafeFastLf01", preFix+"ChrUtah_RunInCircleRight001", preFix+"ChrUtah_Run001");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_StrafeFastLf01", preFix+"ChrUtah_RunInCircleLeft001", preFix+"ChrUtah_RunInTightCircleLeft01");
	state->addTetrahedron(preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_StrafeFastLf01", preFix+"ChrUtah_RunInCircleLeft001", preFix+"ChrUtah_Run001");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_WalkInTightCircleLeft001", preFix+"ChrUtah_Idle01_ToWalk01_Turn360Lf01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_WalkInTightCircleRight001", preFix+"ChrUtah_Idle01_ToWalk01_Turn360Rt01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Idle001", preFix+"ChrUtah_Idle01_ToWalk01_Turn360Lf01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_StrafeSlowLf01", preFix+"ChrUtah_Idle001", preFix+"ChrUtah_Idle01_ToWalk01_Turn360Rt01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_WalkInTightCircleLeft001", preFix+"ChrUtah_Idle01_ToWalk01_Turn360Lf01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_WalkInTightCircleRight001", preFix+"ChrUtah_Idle01_ToWalk01_Turn360Rt01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Idle001", preFix+"ChrUtah_Idle01_ToWalk01_Turn360Lf01");
	state->addTetrahedron(preFix+"ChrUtah_Shuffle01", preFix+"ChrUtah_StrafeSlowRt01", preFix+"ChrUtah_Idle001", preFix+"ChrUtah_Idle01_ToWalk01_Turn360Rt01");
}
//======================================================
void SmartBodyTools::setupSteerAgent(const std::string& charName, const std::string& prefix)
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBSteerManager* steerManager = scene->getSteerManager();
	steerManager->removeSteerAgent(charName);
	SmartBody::SBSteerAgent* steerAgent = steerManager->createSteerAgent(charName);
	steerAgent->setSteerStateNamePrefix(prefix);
	steerAgent->setSteerType("basic");
}
//======================================================
void SmartBodyTools::startingSetup(const std::string& skeletonName, const std::string& baseJoint,
		const std::string& preFix, const std::string& statePreFix)
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBAnimationBlendManager* stateManager = scene->getBlendManager();

	SmartBody::SBMotion* mirrorMotion = scene->getMotion(preFix+"ChrUtah_StopToWalkRt01");
	mirrorMotion->mirror(preFix+"ChrUtah_StopToWalkLf01", skeletonName);
	
	SmartBody::SBMotion* mirrorMotion1 = scene->getMotion(preFix+"ChrUtah_Idle01_ToWalk01_Turn90Lf01");
	mirrorMotion1->mirror(preFix+"ChrUtah_Idle01_ToWalk01_Turn90Rt01", skeletonName);
	SmartBody::SBMotion* mirrorMotion2 = scene->getMotion(preFix+"ChrUtah_Idle01_ToWalk01_Turn180Lf01");
	mirrorMotion2->mirror(preFix+"ChrUtah_Idle01_ToWalk01_Turn180Rt01", skeletonName);

	std::string startLefStateName = statePreFix+"StartingLeft";
	std::vector<double> points1;
	std::vector<double> points2;
	std::vector<double> points3;

	if (stateManager->getBlend(startLefStateName) == nullptr) // don't create duplicate state
	{
		SmartBody::SBAnimationBlend1D* state1 = stateManager->createBlend1D(statePreFix+"StartingLeft");
		std::vector<std::string> motions1;
		motions1.push_back(preFix+"ChrUtah_StopToWalkLf01");
		motions1.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn90Lf01");
		motions1.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn180Lf01");
		std::vector<double> params1;
		params1.push_back(0);
		params1.push_back(-90);
		params1.push_back(-180);

		for (int i = 0; i < motions1.size(); i++)
			state1->addMotion(motions1[i], params1[i]);

		
		points1.push_back(0);
		points1.push_back(0);
		points1.push_back(0);
		state1->addCorrespondencePoints(motions1, points1);

		points2.push_back(0.57541);
		points2.push_back(1.2);
		points2.push_back(1.35);
		state1->addCorrespondencePoints(motions1, points2);

		points3.push_back(0.943716);
		points3.push_back(1.41);
		points3.push_back(1.6);
		state1->addCorrespondencePoints(motions1, points3);
	}

	std::string startRightStateName = statePreFix+"StartingRight";
	if (stateManager->getBlend(startRightStateName) == nullptr)
	{
		SmartBody::SBAnimationBlend1D* state2 = stateManager->createBlend1D(statePreFix+"StartingRight");
		std::vector<std::string> motions2;
		motions2.push_back(preFix+"ChrUtah_StopToWalkRt01");
		motions2.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn90Rt01");
		motions2.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn180Rt01");
		std::vector<double> params2;
		params2.push_back(0);
		params2.push_back(90);
		params2.push_back(180);

		for (int i = 0; i < motions2.size(); i++)
			state2->addMotion(motions2[i], params2[i]);

		// Since the right is symetric with the left, so the correspondance points are the same
		state2->addCorrespondencePoints(motions2, points1);
		state2->addCorrespondencePoints(motions2, points2);
		state2->addCorrespondencePoints(motions2, points3);
	}
}
//======================================================
void SmartBodyTools::idleTurnSetup(const std::string& skeletonName, const std::string& baseJoint,
		const std::string& preFix, const std::string& statePreFix)
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBAnimationBlendManager* stateManager = scene->getBlendManager();
	std::string stateName = statePreFix+"IdleTurn";
	if (stateManager->getBlend(stateName) != nullptr) 
	{
		// don't create duplicate state
		printf("%s: duplicate!\n", __FUNCTION__);
		return;
	}

	SmartBody::SBAnimationBlend1D* state = stateManager->createBlend1D(stateName);
	std::vector<std::string> motions;
	motions.push_back(preFix+"ChrUtah_Idle001");
	motions.push_back(preFix+"ChrUtah_Turn90Lf01");
	motions.push_back(preFix+"ChrUtah_Turn180Lf01");
	motions.push_back(preFix+"ChrUtah_Turn90Rt01");
	motions.push_back(preFix+"ChrUtah_Turn180Rt01");
	std::vector<double> params;
	params.push_back(0);
	params.push_back(-90);
	params.push_back(-180);
	params.push_back(90);
	params.push_back(180);

	for (int i = 0; i < motions.size(); i++)
		state->addMotion(motions[i], params[i]);

	std::vector<double> points1;
	points1.push_back(0);
	points1.push_back(0);
	points1.push_back(0);
	points1.push_back(0);
	points1.push_back(0);
	state->addCorrespondencePoints(motions, points1);
	std::vector<double> points2;
	points2.push_back(0.255738);
	points2.push_back(0.762295);
	points2.push_back(0.87541);
	points2.push_back(0.757377);
	points2.push_back(0.821311);
	state->addCorrespondencePoints(motions, points2);
	std::vector<double> points3;
	points3.push_back(0.633333);
	points3.push_back(1.96667);
	points3.push_back(2.46667);
	points3.push_back(1.96667);
	points3.push_back(2.46667);
	state->addCorrespondencePoints(motions, points3);
}
//======================================================
void SmartBodyTools::stepSetup(const std::string& skeletonName, const std::string& baseJoint,
		const std::string& preFix, const std::string& statePreFix)
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBAnimationBlendManager* stateManager = scene->getBlendManager();

	std::string stateName = statePreFix+"Step";
	if (stateManager->getBlend(stateName) != nullptr) // don't create duplicate state
		return;

	SmartBody::SBAnimationBlend2D* state = stateManager->createBlend2D(stateName);
	// add motions
	std::vector<std::string> motions;
	motions.push_back(preFix+"ChrUtah_Idle001");
	motions.push_back(preFix+"ChrUtah_Idle01_StepBackwardRt01");
	motions.push_back(preFix+"ChrUtah_Idle01_StepForwardRt01");
	motions.push_back(preFix+"ChrUtah_Idle01_StepSidewaysRt01");
	motions.push_back(preFix+"ChrUtah_Idle01_StepBackwardLf01");
	motions.push_back(preFix+"ChrUtah_Idle01_StepForwardLf01");
	motions.push_back(preFix+"ChrUtah_Idle01_StepSidewaysLf01");
	for (int i = 0; i < motions.size(); i++)
		state->addMotion(motions[i], 0, 0);

	// add correspondance points
	std::vector<double> points1;
	points1.push_back(0);
	points1.push_back(0);
	points1.push_back(0);
	points1.push_back(0);
	points1.push_back(0);
	points1.push_back(0);
	points1.push_back(0);
	state->addCorrespondencePoints(motions, points1);
	std::vector<double> points2;
	points2.push_back(0.556322);
	points2.push_back(0.556322);
	points2.push_back(0.543678);
	points2.push_back(0.482989);
	points2.push_back(0.395402);
	points2.push_back(0.531034);
	points2.push_back(0.473563);
	state->addCorrespondencePoints(motions, points2);
	std::vector<double> points3;
	points3.push_back(1.46414);
	points3.push_back(1.46414);
	points3.push_back(1.46414);
	points3.push_back(1.46414);
	points3.push_back(1.33333);
	points3.push_back(1.33333);
	points3.push_back(1.33103);
	state->addCorrespondencePoints(motions, points3);

	// reset parameters (because it needs context of correspondance points)
	SmartBody::SBSkeleton* skeleton = scene->getSkeleton(skeletonName);
	SmartBody::SBJoint* joint = skeleton->getJointByName(baseJoint);
	for (int i = 0; i < motions.size(); i++)
	{
		SmartBody::SBMotion* motion = scene->getMotion(motions[i]);
		motion->connect(skeleton);
		std::vector<double> correspondancePoints = state->getCorrespondencePoints(i);
		int lenCorrespondancePoints = correspondancePoints.size();
		std::vector<float> jointTransition = motion->getJointTransition(joint, correspondancePoints[0], correspondancePoints[lenCorrespondancePoints - 1]);
		state->setParameter(motions[i], jointTransition[0], jointTransition[2]);
		motion->disconnect();
	}

	// add triangles
	state->addTriangle(preFix+"ChrUtah_Idle001", preFix+"ChrUtah_Idle01_StepBackwardLf01", preFix+"ChrUtah_Idle01_StepSidewaysLf01");
	state->addTriangle(preFix+"ChrUtah_Idle001", preFix+"ChrUtah_Idle01_StepForwardLf01", preFix+"ChrUtah_Idle01_StepSidewaysLf01");
	state->addTriangle(preFix+"ChrUtah_Idle001", preFix+"ChrUtah_Idle01_StepBackwardRt01", preFix+"ChrUtah_Idle01_StepSidewaysRt01");
	state->addTriangle(preFix+"ChrUtah_Idle001", preFix+"ChrUtah_Idle01_StepForwardRt01", preFix+"ChrUtah_Idle01_StepSidewaysRt01");
}
//======================================================
void SmartBodyTools::transitionSetup(const std::string& preFix, const std::string& statePrefix)
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBAnimationBlendManager* stateManager = scene->getBlendManager();

	if (stateManager->getTransition(statePrefix+"StartingLeft", statePrefix+"Locomotion") == nullptr)
	{
		SmartBody::SBAnimationTransition* transition1 = stateManager->createTransition(statePrefix+"StartingLeft", statePrefix+"Locomotion");
		transition1->setEaseInInterval(preFix+"ChrUtah_Meander01", 0.4, 0.78);
		transition1->addEaseOutInterval(preFix+"ChrUtah_StopToWalkLf01", 0.54, 0.83);
	}
		
	if (stateManager->getTransition(statePrefix+"StartingRight", statePrefix+"Locomotion") == nullptr)
	{
		SmartBody::SBAnimationTransition*transition2 = stateManager->createTransition(statePrefix+"StartingRight", statePrefix+"Locomotion");
		transition2->setEaseInInterval(preFix+"ChrUtah_Meander01", 1.1, 1.5);
		transition2->addEaseOutInterval(preFix+"ChrUtah_StopToWalkRt01", 0.54, 0.83);
	}
}
//======================================================
void SmartBodyTools::retargetCharacter(const std::string& charName, const std::string& targetSkelName, bool reach /* = true */)
{
	retargetSetup(targetSkelName);

	// setup standard locomotion
	locomotionSetup(targetSkelName,"base","",targetSkelName);
	startingSetup(targetSkelName,"base","",targetSkelName);
	idleTurnSetup(targetSkelName,"base","",targetSkelName);
	stepSetup(targetSkelName,"base","",targetSkelName);
	transitionSetup("","");

	if (reach)
	{
		printf("todo: reach\n");
	}

	setupSteerAgent(charName,targetSkelName);
}
//======================================================
void SmartBodyTools::retargetSetup(const std::string& targetSkelName)
{
	std::vector<std::string> gestureMotions = getStandardGestureMotions("");
	std::vector<std::string> reachMotions = getStandardReachMotions("");
	std::vector<std::string> locoMotions = getStandardLocoMotions("");

	for (auto it = gestureMotions.begin(); it != gestureMotions.end(); ++it)
		retargetMotion((*it), "common.sk", targetSkelName);

	for (auto it = reachMotions.begin(); it != reachMotions.end(); ++it)
		retargetMotion((*it), "common.sk", targetSkelName);

	for (auto it = locoMotions.begin(); it != locoMotions.end(); ++it)
		retargetMotion((*it), "common.sk", targetSkelName);

}
//======================================================
std::vector<std::string> SmartBodyTools::getStandardGestureMotions(const std::string& preFix)
{
	std::vector<std::string> gestureMotions;

	gestureMotions.push_back(preFix+"HandsAtSide_Motex");
	gestureMotions.push_back(preFix+"HandsAtSide_Arms_Sweep");
	gestureMotions.push_back(preFix+"HandsAtSide_Motex_Softened");
	gestureMotions.push_back(preFix+"HandsAtSide_RArm_GestureYou");
	gestureMotions.push_back(preFix+"HandsAtSide_Transition_LHandOnHip");
	gestureMotions.push_back(preFix+"LHandOnHip_Arms_GestureWhy");
	gestureMotions.push_back(preFix+"LHandOnHip_Motex");
	gestureMotions.push_back(preFix+"LHandOnHip_RArm_GestureOffer");
	gestureMotions.push_back(preFix+"LHandOnHip_RArm_SweepRight");
	gestureMotions.push_back(preFix+"LHandOnHip_Transition_HandsAtSide");

	return gestureMotions;
}
//======================================================
std::vector<std::string> SmartBodyTools::getStandardReachMotions(const std::string& preFix)
{
	std::vector<std::string> reachMotions;

	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachRtHigh");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachRtMidHigh");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachRtMidLow");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachLfLow");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachLfHigh");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachLfMidHigh");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachRtMidLow");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachRtLow");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachMiddleHigh");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachMiddleMidHigh");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachMiddleMidLow");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachMiddleLow");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachClose_Lf");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachClose_Rt");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachClose_MiddleHigh");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachClose_MiddleLow");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachClose_MiddleMidHigh");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachClose_MiddleMidLow");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachBehind_High1");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachBehind_High2");	
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachBehind_Low1");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachBehind_Low2");	
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachBehind_MidHigh1");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachBehind_MidHigh2");	
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachBehind_MidLow1");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_ArmReachBehind_MidLow2");	
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_HandGraspSmSphere_Grasp");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_HandGraspSmSphere_Reach");
	reachMotions.push_back(preFix+"ChrHarmony_Relax001_HandGraspSmSphere_Release");

	return reachMotions;
}
//======================================================
std::vector<std::string> SmartBodyTools::getStandardLocoMotions(const std::string& preFix)
{
	std::vector<std::string> locoMotions;
	locoMotions.push_back(preFix+"ChrUtah_Walk001");
	locoMotions.push_back(preFix+"ChrUtah_Idle001");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn360Lf01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn360Rt01");
	locoMotions.push_back(preFix+"ChrUtah_Meander01");
	locoMotions.push_back(preFix+"ChrUtah_Shuffle01");
	locoMotions.push_back(preFix+"ChrUtah_Jog001");
	locoMotions.push_back(preFix+"ChrUtah_Run001");
	locoMotions.push_back(preFix+"ChrUtah_WalkInCircleLeft001");
	locoMotions.push_back(preFix+"ChrUtah_WalkInCircleRight001");
	locoMotions.push_back(preFix+"ChrUtah_WalkInTightCircleLeft001");
	locoMotions.push_back(preFix+"ChrUtah_WalkInTightCircleRight001");
	locoMotions.push_back(preFix+"ChrUtah_RunInCircleLeft001");
	locoMotions.push_back(preFix+"ChrUtah_RunInCircleRight001");
	locoMotions.push_back(preFix+"ChrUtah_RunInTightCircleLeft01");
	locoMotions.push_back(preFix+"ChrUtah_RunInTightCircleRight01");
	locoMotions.push_back(preFix+"ChrUtah_StrafeSlowRt01");
	locoMotions.push_back(preFix+"ChrUtah_StrafeSlowLf01");
	locoMotions.push_back(preFix+"ChrUtah_StrafeFastRt01");
	locoMotions.push_back(preFix+"ChrUtah_StrafeFastLf01");
	locoMotions.push_back(preFix+"ChrUtah_Idle001");
	locoMotions.push_back(preFix+"ChrUtah_Turn90Lf01");
	locoMotions.push_back(preFix+"ChrUtah_Turn180Lf01");
	locoMotions.push_back(preFix+"ChrUtah_Turn90Rt01");
	locoMotions.push_back(preFix+"ChrUtah_Turn180Rt01");
	locoMotions.push_back(preFix+"ChrUtah_StopToWalkRt01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn90Lf01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_ToWalk01_Turn180Lf01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_StepBackwardRt01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_StepForwardRt01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_StepSidewaysRt01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_StepBackwardLf01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_StepForwardLf01");
	locoMotions.push_back(preFix+"ChrUtah_Idle01_StepSidewaysLf01");	

	return locoMotions;
}
//======================================================
void SmartBodyTools::retargetMotion(const std::string& motionName, const std::string& srcSkelName, const std::string& tgtSkelName)
{
	SmartBody::SBScene* scene = SmartBodyManager::getSingleton().getSBScene();
	SmartBody::SBSkeleton* remapSkel = scene->getSkeleton(srcSkelName);
	SmartBody::SBJointMapManager* jointMapManager = scene->getJointMapManager();
	SmartBody::SBJointMap* jointMap = jointMapManager->getJointMap(srcSkelName);

	if (jointMap == nullptr)
	{
		jointMap = jointMapManager->createJointMap(srcSkelName);
		jointMap->guessMapping(remapSkel, false);
	}

	jointMap->applySkeleton(remapSkel);

	SmartBody::SBMotion* remapMotion = scene->getMotion(motionName);
	if (remapMotion == nullptr)
		return;
	
	jointMap->applyMotion(remapMotion);
	remapMotion->setMotionSkeletonName(srcSkelName);

	SmartBody::SBRetargetManager* rtm = scene->getRetargetManager();
	SmartBody::SBRetarget* retarget = rtm->getRetarget(srcSkelName, tgtSkelName);
	if (!retarget)
		retarget = rtm->createRetarget(srcSkelName, tgtSkelName);

	std::vector<std::string> endJoints;
	endJoints.push_back("l_forefoot");
	endJoints.push_back("l_toe");
	endJoints.push_back("l_wrist");
	endJoints.push_back("r_forefoot");
	endJoints.push_back("r_toe");
	endJoints.push_back("r_wrist");

	std::vector<std::string> relativeJoints;
	relativeJoints.push_back("spine1");
	relativeJoints.push_back("spine2");
	relativeJoints.push_back("spine3");
	relativeJoints.push_back("spine4");
	relativeJoints.push_back("spine5");
	relativeJoints.push_back("r_sternoclavicular");
	relativeJoints.push_back("l_sternoclavicular");

	retarget->initRetarget(endJoints, relativeJoints);
}
//======================================================


};
