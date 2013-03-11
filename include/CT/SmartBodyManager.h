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

#ifndef _CAKAOTWO_SMARTBODYMANAGER_H_
#define _CAKAOTWO_SMARTBODYMANAGER_H_

#include <CT/Prerequisites.h>
#include <CT/Singleton.h>
#include <CT/SmartBodyEnums.h>
#include <memory>


// Forward declare to avoid shitstorm of dependencies...
namespace SmartBody
{
	class SBScene;
};

namespace CT
{
class SmartBodyPawn;
class SmartBodyCharacter;

typedef std::shared_ptr<SmartBodyPawn> SmartBodyPawnPtr;
typedef std::shared_ptr<SmartBodyCharacter> SmartBodyCharacterPtr;

/**
 * Host class for SmartBody system. Manages the big things
 */
class SmartBodyManager :
	public Singleton<SmartBodyManager>
{
protected:
	friend class Singleton<SmartBodyManager>;
	// ctor
	SmartBodyManager();

	// dtor
	~SmartBodyManager();

public:
	/**
	 * Updates SmartBody simulation of one step.
	 * Call this once per frame.
	 */
	void update(float _timeDelta);

	/**
	 * Add an asset path to the Scene Manager
	 * Types:
	 * - motion - Location of animation and skeleton assets.
	 * - script - Location of Python scripts.
	 * - audio - Location of audio files used for text-to-speech or
	 *         prerecorded audio.
	 * - mesh - Location of geometry, smooth binding/skinning
	 *        information, and textures
	 */
	void addAssetPath(const std::string& _type, const std::string& _path);

	/**
	 * Create a SmartBody Pawn
	 * @see CT::SmartBodyPawn
	 */
	SmartBodyPawnPtr createPawn(SmartBodyEnums::PawnShape _shape);

	/**
	 * Create a SmartBody Character
	 * @see CT::SmartBodyPawn
	 */
	SmartBodyCharacterPtr createCharacter(Ogre::Entity* _entity, const std::string& _skelName);

	/**
	 * Returns the SmartBody scene
	 */
	SmartBody::SBScene* getSBScene() const;

	/**
	 * Execute a BML command immediately on the SB engine
	 * @param _char The character name
	 * @param _cmd The BML command (xml)
	 */
	 void executeBML(const std::string& _char, const std::string& _cmd);

	 /**
	  * Execute a BML command at the specified time on the SB engine.
	  * Note that SmartBodyManager uses Ogre Timer (Ogre::Root::getSingleton().getTimer()->
	  * getMiliseconds())
	  * @param _time The time.
	  * @param _char The character name
	  * @param _cmd The BML command (xml)
	  */
	 void executeBMLat(float _time, const std::string& _char, const std::string& _cmd);

	 /**
	  * Execute a BML command in _time seconds in the future.
	  * @param _time Delay until the command starts.
	  * @param _char The character name
	  * @param _cmd The BML command (xml)
	  */
	 void executeBMLin(float _time, const std::string& _char, const std::string& _cmd);



protected:
	void initialize();

	SmartBody::SBScene* m_pScene;
	Ogre::NameGenerator* m_pNameGenerator;

	std::unordered_map<std::string, SmartBodyPawnPtr> m_mPawns;
	std::unordered_map<std::string, SmartBodyCharacterPtr> m_mCharacters;
};


};

#endif // _CAKAOTWO_SMARTBODYMANAGER_H_
