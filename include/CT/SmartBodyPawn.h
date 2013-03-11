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

#ifndef _CAKAOTWO_SMARTBODYPAWN_H_
#define _CAKAOTWO_SMARTBODYPAWN_H_

#include <CT/Prerequisites.h>
#include <CT/SmartBodyEnums.h>

#include <OgreSceneNode.h>
#include <memory>

namespace SmartBody
{
	class SBPawn;
};

namespace CT
{
class SmartBodyManager;

/**
 * A SmartBody scene can be populated with pawns (generally rigid objects or structures)
 * You shouldn't create a SmartBodyPawn directly, use SmartBodyManager::createPawn
 */
class SmartBodyPawn
{
public:

	// ctor
	SmartBodyPawn(SmartBody::SBPawn* _pawn, SmartBodyEnums::PawnShape _shape);

	// dtor
	~SmartBodyPawn();

	/**
	 * Sets the Ogre SceneNode this Pawn belongs to.
	 * It will keep the position synced with the node
	 */
	void setAttachedSceneNode(Ogre::SceneNode* _sceneNode);

	/**
	 * Manually set the position of the pawn
	 * This position is overwritten by update calls if a SceneNode
	 * is attached.
	 */
	void setPosition(const Ogre::Vector3& _pos);
	void setPositionSmooth(const Ogre::Vector3& _pos, float _smoothTime);

	/**
	 * Manually set the orientation of the pawn
	 * This orientation is overwritten by update calls if a SceneNode
	 * is attached.
	 */
	void setOrientation(const Ogre::Quaternion& _quat);

	/**
	 * Sets the shape of the pawn
	 */
	void setShape(SmartBodyEnums::PawnShape _shape);

	/**
	 * Sets the dimensions/size of the pawn shape
	 * The X/Y/Z axis of the _size parameters are used as this: for a sphere,
	 * 'x' is the radius. For a box, all three sizes are used to specify the x/y/z
	 * dimensions, and for a capsule, 'x' is the length and 'y' is the radius.
	 */
	void setShapeDimensions(const Ogre::Vector3& _size);

	/**
	 * Returns the internal SmartBody name of the pawn
	 */
	const std::string& getName() const;

	/**
	 * Updates the pawn
	 */
	void update();

protected:
	SmartBody::SBPawn* m_pPawn;
	Ogre::SceneNode* m_pAttachedNode;
};

};

#endif
