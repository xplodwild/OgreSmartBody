OgreSmartBody
=============

OgreSmartBody is a SmartBody (http://smartbody.ict.usc.edu) wrapper for Ogre. 
It uses the native C++ interface (smartbody-lib) to interact with the SmartBody
engine and animate characters.

This is still pretty much a work in progress, but you can add the include/src files
in your project and start using it. I'm using it in the core of my engine and I haven't
yet cleaned the files, so you might need to remove <CT/Prerequisites.h> includes, stdafx.h,
etc.
It uses some C++11 keywords (auto for iterators, and std::shared_ptr), but those can be
easily replaced with the classic iterator declaration and boost::shared_ptr. I'll put
these by default once I cleaned the lib.

Example of use:
```c++
	// initialize the engine
	CT::SmartBodyManager* sbmgr = CT::SmartBodyManager::getSingletonPtr();
	sbmgr->initialize();
	sbmgr->addAssetPath("motion", "Data/SmartBody/ChrBrad");
	sbmgr->addAssetPath("mesh", "Data/SmartBody/mesh");
	sbmgr->addAssetPath("motion", "Data/SmartBody/sbm-common/common-sk");
	sbmgr->addAssetPath("script", "Data/SmartBody/sbm-common/scripts");

	// !!! In your FrameListener's frameStarted
	sbmgr->update(evt.timeSinceLastFrame);
	// !!!
	
	// create some pawns
	CT::SmartBodyPawnPtr pawn1 = sbmgr->createPawn(CT::SmartBodyEnums::PAWNSHAPE_SPHERE);
	pawn1->setPosition(Ogre::Vector3(100, 0, 0));

	CT::SmartBodyPawnPtr pawn2 = sbmgr->createPawn(CT::SmartBodyEnums::PAWNSHAPE_SPHERE);
	pawn2->setPosition(Ogre::Vector3(0, 100, 0));

	CT::SmartBodyPawnPtr pawn3 = sbmgr->createPawn(CT::SmartBodyEnums::PAWNSHAPE_SPHERE);
	pawn3->setPosition(Ogre::Vector3(-500, -100, 200));
	pawn3->setPositionSmooth(Ogre::Vector3(0, 500, -100), 18.0f);

	// setup a character
	Ogre::SceneNode* node = sceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* ent = sceneMgr->createEntity("Utah.mesh");
	node->attachObject(ent);
	CT::SmartBodyCharacterPtr character = sbmgr->createCharacter(ent, "test_utah.sk");
	
	// run some commands in the future for this character
	sbmgr->executeBMLin(2.0f, character->getName(), "<gaze target=\""+pawn1->getName()+"\"/>");
	sbmgr->executeBMLin(3.0f, character->getName(), "<head type=\"NOD\" amount=\"0.4\" repeats=\"1.0\" velocity=\"0.8\"/>");
	sbmgr->executeBMLin(5.0f, character->getName(), "<gaze target=\""+pawn2->getName()+"\"/>");
	sbmgr->executeBMLin(6.0f, character->getName(), "<gaze target=\""+pawn3->getName()+"\"/>");
	sbmgr->executeBMLin(8.0f, character->getName(), "<body posture=\"ChrBrad@Guitar01\"/>");
	sbmgr->executeBMLin(12.0f, character->getName(), "<body posture=\"ChrBrad@Idle03\"/>");
	sbmgr->executeBMLin(13.0f, character->getName(), "<head type=\"TOSS\" amount=\"0.6\" repeats=\"1.0\" velocity=\"0.8\"/>");
	sbmgr->executeBMLin(14.0f, character->getName(), "<face type=\"facs\" au=\"6\" amount=\"1\"/><face type=\"facs\" au=\"12\" amount=\"1\"/>");
	sbmgr->executeBMLin(16.0f, character->getName(), "<face type=\" facs\"  au=\" 1_left\"  amount=\" 0.6\" /><face type=\" facs\"  au=\" 1_right\"  amount=\" 0.6\" />" \
							  "<face type=\" facs\"  au=\" 5\"  amount=\" 0.7\" /><face type=\" facs\"  au=\" 26\"  amount=\" 0.25\" />" \
							  "<face type=\" facs\"  au=\" 38\"  amount=\" 1\" />");
```
