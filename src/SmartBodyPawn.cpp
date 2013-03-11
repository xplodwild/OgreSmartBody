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
#include <CT/SmartBodyPawn.h>
#include <CT/SmartBodyManager.h>

#include <sb/SBPawn.h>

namespace CT
{
//================================
SmartBodyPawn::SmartBodyPawn(SmartBody::SBPawn* _pawn,
	SmartBodyEnums::PawnShape _shape) :
	m_pPawn(_pawn), m_pAttachedNode(nullptr)
{
	setShape(_shape);
}
//================================
SmartBodyPawn::~SmartBodyPawn()
{

}
//================================
void SmartBodyPawn::setAttachedSceneNode(Ogre::SceneNode* _sceneNode)
{
	m_pAttachedNode = _sceneNode;
}
//================================
void SmartBodyPawn::update()
{
	// Update position only if we have an attached node
	if (!m_pAttachedNode)
		return;

	Ogre::Vector3 pos = m_pAttachedNode->_getDerivedPosition();
	Ogre::Quaternion rot = m_pAttachedNode->_getDerivedOrientation();
	Ogre::Vector3 scale = m_pAttachedNode->_getDerivedScale();

	m_pPawn->setPosition(SrVec(pos.x,pos.y,pos.z));
	m_pPawn->setOrientation(SrQuat(rot.w,rot.x,rot.y,rot.z));
	m_pPawn->setDoubleAttribute("meshScale", scale.x); // TODO: Mesh scale on multiple axis?
}
//================================
void SmartBodyPawn::setPosition(const Ogre::Vector3& _pos)
{
	m_pPawn->setPosition(SrVec(_pos.x,_pos.y,_pos.z));
}
//================================
void SmartBodyPawn::setPositionSmooth(const Ogre::Vector3& _pos, float _smoothTime)
{
	m_pPawn->setPositionSmooth(SrVec(_pos.x,_pos.y,_pos.z), _smoothTime);
}
//================================
void SmartBodyPawn::setOrientation(const Ogre::Quaternion& _quat)
{
	m_pPawn->setOrientation(SrQuat(_quat.w, _quat.x, _quat.y, _quat.z));
}
//================================
void SmartBodyPawn::setShape(SmartBodyEnums::PawnShape _shape)
{
	switch (_shape)
	{
	case SmartBodyEnums::PAWNSHAPE_NULL:
		m_pPawn->setStringAttribute("collisionShape", "null");
		break;

	case SmartBodyEnums::PAWNSHAPE_SPHERE:
		m_pPawn->setStringAttribute("collisionShape", "sphere");
		break;

	case SmartBodyEnums::PAWNSHAPE_BOX:
		m_pPawn->setStringAttribute("collisionShape", "box");
		break;

	case SmartBodyEnums::PAWNSHAPE_CAPSULE:
		m_pPawn->setStringAttribute("collisionShape", "capsule");
		break;
	}
}
//================================
void SmartBodyPawn::setShapeDimensions(const Ogre::Vector3& _size)
{
	m_pPawn->setVec3Attribute("collisionShape", _size.x, _size.y, _size.z);
}
//================================
const std::string& SmartBodyPawn::getName() const
{
	return m_pPawn->getName();
}
//================================
};
