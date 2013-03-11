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
#include <CT/SmartBodyManager.h>
#include <CT/SmartBodyPawn.h>
#include <CT/SmartBodyCharacter.h>
#include <CT/SmartBodyTools.h>

#include <sb/SBScene.h>
#include <sb/SBPawn.h>
#include <sb/SBCharacter.h>
#include <sb/SBSkeleton.h>
#include <sb/SBJointMapManager.h>
#include <sb/SBJointMap.h>
#include <sb/SBGestureMapManager.h>
#include <sb/SBGestureMap.h>
#include <sb/SBSimulationManager.h>
#include <sb/SBBmlProcessor.h>
#include <sb/SBVHMsgManager.h>
#include <sb/SBSteerManager.h>
#include <sb/SBSteerAgent.h>
#include <sb/SBMotion.h>
#include <sb/SBRetargetManager.h>
#include <sb/SBRetarget.h>

#include <OgreSkeleton.h>

namespace CT
{

std::list<SmartBody::SBJoint*> walkJoints(SmartBody::SBJoint* root)
{
	std::list<SmartBody::SBJoint*> liste;
	liste.push_back(root);

	for (int i = 0; i < root->getNumChildren(); i++)
	{
		liste.merge(walkJoints(root->getChild(i)));
	}

	return liste;
}

//===============================================
SmartBodyManager::SmartBodyManager() :
	m_pScene(nullptr), m_pNameGenerator(nullptr)
{
	initialize();
}
//===============================================
SmartBodyManager::~SmartBodyManager()
{
	if (m_pScene)
		delete m_pScene;

	if (m_pNameGenerator)
		delete m_pNameGenerator;
}
//===============================================
void SmartBodyManager::initialize()
{
	m_pScene = SmartBody::SBScene::getScene();
	m_pScene->getVHMsgManager()->setEnableLogging(true);
	m_pNameGenerator = new Ogre::NameGenerator("SmartBody/");

	// Start the simulation. It will be stepped in update(...) method
	m_pScene->start();
}
//===============================================
void SmartBodyManager::update(float _timeDelta)
{
	// Step forward the SB simulation
	SmartBody::SBSimulationManager* sim = m_pScene->getSimulationManager();
	sim->setTime(Ogre::Root::getSingleton().getTimer()->getMilliseconds() / 1000.0f);
	m_pScene->update();

	// Update characters bones and positions
	for (auto it = m_mCharacters.begin(); it != m_mCharacters.end(); ++it)
	{
		(*it).second->_update();
	}
}
//===============================================
void SmartBodyManager::addAssetPath(const std::string& _type, const std::string& _path)
{
	m_pScene->addAssetPath(_type, _path);
	m_pScene->loadAssetsFromPath(_path);
}
//===============================================
SmartBodyPawnPtr SmartBodyManager::createPawn(SmartBodyEnums::PawnShape _shape)
{
	SmartBody::SBPawn* pawn = m_pScene->createPawn(m_pNameGenerator->generate());
	SmartBodyPawn* ogPawn = new SmartBodyPawn(pawn, _shape);

	SmartBodyPawnPtr sharedPtr = SmartBodyPawnPtr(ogPawn);
	m_mPawns[pawn->getName()] = sharedPtr;
	return sharedPtr;
}
//===============================================
SmartBodyCharacterPtr SmartBodyManager::createCharacter(Ogre::Entity* _entity, const std::string& _skelName)
{
	std::string charName = m_pNameGenerator->generate();

	SmartBody::SBGestureMapManager* gmm = m_pScene->getGestureMapManager();
	SmartBody::SBGestureMap* gMap = gmm->createGestureMap(charName);

	/*
	==> TODO: Gesture mapping
	gMap->addGestureMapping("ChrUtah_IndicateThereLeft001", "DEICTIC", "YOU", "LEFT_HAND", "", "ChrUtah_Idle003");
	gMap->addGestureMapping("ChrUtah_IndicateThereRight001", "DEICTIC", "YOU", "LEFT_HAND", "", "ChrUtah_Idle003");
	gMap->addGestureMapping("ChrUtah_IndicateThereLeft001", "DEICTIC", "LEFT", "LEFT_HAND", "", "ChrUtah_Idle003");
	gMap->addGestureMapping("ChrUtah_IndicateThereRight001", "DEICTIC", "RIGHT", "RIGHT_HAND", "", "ChrUtah_Idle003");*/

	/*
	===> Do we need to do this for locomotion?
	SmartBody::SBJointMapManager* jmm = m_pScene->getJointMapManager();
	SmartBody::SBJointMap* jointMap = jmm->createJointMap(_skelName);
	jointMap->guessMapping(m_pScene->getSkeleton(_skelName), false);
	jointMap->applySkeleton(m_pScene->getSkeleton(_skelName));

	jointMap->applyMotion(m_pScene->getMotion("ChrUtah_Run001"));
	jointMap->applyMotion(m_pScene->getMotion("ChrUtah_Walk001"));
	jointMap->applyMotion(m_pScene->getMotion("ChrUtah_Turn90Lf01"));
	jointMap->applyMotion(m_pScene->getMotion("ChrUtah_Jog001"));*/

	// Create the character
	SmartBody::SBCharacter* character = m_pScene->createCharacter(charName, "");
	SmartBodyCharacter* ogChar = new SmartBodyCharacter(_entity, character);

	// Retarget motions, and setup locomotion
	SmartBodyTools::retargetStandardMotions(_skelName);

	SmartBodyTools::locomotionSetup(_skelName, "base", "", "");
	SmartBodyTools::startingSetup(_skelName, "base", "", "");
	SmartBodyTools::idleTurnSetup(_skelName, "base", "", "");
	SmartBodyTools::stepSetup(_skelName, "base", "", "");
	SmartBodyTools::transitionSetup("", "");

	// Apply skeleton to character, set face def
	SmartBody::SBSkeleton* skel = m_pScene->getSkeleton(_skelName);
	character->setSkeleton(skel);
	character->createStandardControllers();
	character->setStringAttribute("gestureMap", charName);
	character->setFaceDefinition(SmartBodyTools::getDefaultFaceDefinition());

	// Enable steering on the character
	m_pScene->getSteerManager()->setEnable(false);
	SmartBodyTools::setupSteerAgent(charName, "");
	character->setBoolAttribute("steering.pathFollowingMode", false);
	m_pScene->getSteerManager()->setEnable(true);

	// Setup lipsyncing
	character->setStringAttribute("diphoneSetName", "default");
	character->setBoolAttribute("useDiphone", true);
	character->setBoolAttribute("bmlRequest.autoGestureTransition", true);
	m_pScene->getBmlProcessor()->execBML("*", "<saccade mode=\"talk\" />");
	character->setVoice("");

	// Store the character locally
	SmartBodyCharacterPtr sharedPtr = SmartBodyCharacterPtr(ogChar);
	m_mCharacters[character->getName()] = sharedPtr;
	return sharedPtr;
}
//===============================================
SmartBody::SBScene* SmartBodyManager::getSBScene() const
{
	return m_pScene;
}
//===============================================
void SmartBodyManager::executeBML(const std::string& _char, const std::string& _cmd)
{
	m_pScene->getBmlProcessor()->execBML(_char, _cmd);
}
//===============================================
void SmartBodyManager::executeBMLat(float _time, const std::string& _char, const std::string& _cmd)
{
	m_pScene->getBmlProcessor()->execBMLAt(_time, _char, _cmd);
}
//===============================================
void SmartBodyManager::executeBMLin(float _time, const std::string& _char, const std::string& _cmd)
{
	m_pScene->getBmlProcessor()->execBMLAt(
		Ogre::Root::getSingleton().getTimer()->getMilliseconds() / 1000.0f + _time, _char, _cmd);
}
//===============================================

};
