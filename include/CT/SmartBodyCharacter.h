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

#ifndef _CAKAOTWO_SMARTBODYCHARACTER_H_
#define _CAKAOTWO_SMARTBODYCHARACTER_H_

#include <CT/Prerequisites.h>

#include <OgreSceneNode.h>
#include <memory>

namespace SmartBody
{
	class SBCharacter;
	class SBJoint;
};

namespace CT
{
class SmartBodyManager;

/**
 * A SmartBody scene can be populated with characters that interacts with pawns
 * You shouldn't create a SmartBodyCharacter directly, use SmartBodyManager::createCharacter
 */
class SmartBodyCharacter
{
public:
	/**
	 * ctor
	 * @param _mesh The mesh that is used as character. It will try to grab and convert
	 * the skeleton to SmartBody format automatically.
	 */
	SmartBodyCharacter(Ogre::Entity* _mesh, SmartBody::SBCharacter* _char);

	// dtor
	~SmartBodyCharacter();

	/**
	 * Manually set the position of the character
	 * This position is overwritten by update calls if a SceneNode
	 * is attached.
	 */
	void setPosition(const Ogre::Vector3& _pos);
	void setPositionSmooth(const Ogre::Vector3& _pos, float _smoothTime);

	/**
	 * Manually set the orientation of the character
	 * This orientation is overwritten by update calls if a SceneNode
	 * is attached.
	 */
	void setOrientation(const Ogre::Quaternion& _quat);

	/**
	 * Returns the Ogre entity
	 */
	Ogre::Entity* getEntity() const;

	/**
	 * Returns the internal SmartBody name of the character
	 */
	const std::string& getName() const;

protected:
	friend class SmartBodyManager;
	void _update();
	void _makeValidBonesMap();

protected:
	SmartBody::SBCharacter* m_pCharacter;
	Ogre::Entity* m_pEntity;
	std::unordered_map<std::string, bool> m_mValidBones;
};

};

#endif
