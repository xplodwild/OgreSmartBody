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
#include <CT/SmartBodyCharacter.h>
#include <CT/SmartBodyManager.h>

#include <sb/SBCharacter.h>
#include <sb/SBSkeleton.h>

namespace CT
{
//================================
SmartBodyCharacter::SmartBodyCharacter(Ogre::Entity* _mesh, SmartBody::SBCharacter* _char) :
	m_pCharacter(_char), m_pEntity(_mesh)
{
	// TODO: Load the skeleton
}
//================================
SmartBodyCharacter::~SmartBodyCharacter()
{

}
//================================
void SmartBodyCharacter::_update()
{
	// Update position only if we have an attached node
	Ogre::SceneNode* parentNode = m_pEntity->getParentSceneNode();
	if (parentNode)
	{
		SrVec pos = m_pCharacter->getPosition();
		SrQuat ori = m_pCharacter->getOrientation();

		parentNode->setPosition(pos.x, pos.y, pos.z);
		parentNode->setOrientation(ori.w, ori.x, ori.y, ori.z);
	}

	// Update joints
	SmartBody::SBSkeleton* sbSkel = m_pCharacter->getSkeleton();
	Ogre::Skeleton* meshSkel = m_pEntity->getSkeleton();

	if (m_mValidBones.size() == 0)
		_makeValidBonesMap();

	int numJoints = sbSkel->getNumJoints();
	for (int j = 0; j < numJoints; j++)
	{
		SmartBody::SBJoint* joint = sbSkel->getJoint(j);

		// Don't update this joint if the Ogre skeleton doesn't have it
		if (!m_mValidBones[joint->getName()])
			continue;

		try
		{
			Ogre::Bone* bone = meshSkel->getBone(joint->getName());
			bone->setManuallyControlled(true);

			SrQuat orientation = joint->quat()->value();

			Ogre::Vector3 posDelta(joint->getPosition().x, joint->getPosition().y, joint->getPosition().z);
			Ogre::Quaternion quatDelta(orientation.w, orientation.x, orientation.y, orientation.z);

			bone->setPosition(bone->getInitialPosition() + posDelta);
			bone->setOrientation(quatDelta);
		}
		catch (Ogre::ItemIdentityException& ex)
		{
			// Should not happen as we filtered using m_mValidBones
		}
	}
}
//================================
void SmartBodyCharacter::_makeValidBonesMap()
{
	Ogre::Skeleton* meshSkel = m_pEntity->getSkeleton();
	Ogre::Skeleton::BoneIterator boneIt = meshSkel->getBoneIterator();

	while (boneIt.hasMoreElements())
		m_mValidBones[boneIt.getNext()->getName()] = true;
}
//================================
void SmartBodyCharacter::setPosition(const Ogre::Vector3& _pos)
{
	m_pCharacter->setPosition(SrVec(_pos.x,_pos.y,_pos.z));
}
//================================
void SmartBodyCharacter::setPositionSmooth(const Ogre::Vector3& _pos, float _smoothTime)
{
	m_pCharacter->setPositionSmooth(SrVec(_pos.x,_pos.y,_pos.z), _smoothTime);
}
//================================
void SmartBodyCharacter::setOrientation(const Ogre::Quaternion& _quat)
{
	m_pCharacter->setOrientation(SrQuat(_quat.w, _quat.x, _quat.y, _quat.z));
}
//================================
Ogre::Entity* SmartBodyCharacter::getEntity() const
{
	return m_pEntity;
}
//================================
const std::string& SmartBodyCharacter::getName() const
{
	return m_pCharacter->getName();
}
//================================


};
