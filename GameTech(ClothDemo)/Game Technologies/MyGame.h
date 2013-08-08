/******************************************************************************
Class:MyGame
Implements:GameEntity
Author:Rich Davison	<richard.davison4@newcastle.ac.uk> and YOU!
Description: This is an example of a derived game class - all of your game 
specific things will go here. Such things would include setting up the game 
environment (level, enemies, pickups, whatever), and keeping track of what the
gameplay state is (Is the player dead? Has he/she won the game? And so on).

To get you started, there's a few static functions included that will create 
create some simple game objects - ideally your game object loading would be
handled by config files or somesuch, but for a simple demo game, these 
functions are a good start. Don't be afraid to modify/delete/add more of these!

Finally, there's some calls to the OGLRenderer debug draw functions that have
been added to the course this year. These are really useful for debugging the
state of your game in a graphical way - i.e drawing a line from a character
to the item it is aiming at, or pointing in the direction it is moving, or
for drawing debug bounding volumes to see when objects collide. Feel free
to add more of these debug functions - how they are implemented is covered
in the code definitions for them, and also in the extra introduction 
document on the research website.

Have fun!


-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////



#pragma once
#include "GameEntity.h"
#include "GameClass.h"
#include "../nclgl/Camera.h"
#include "../nclgl/CubeRobot.h"
#include "FirstProjectile.h"
#include "MoveCube.h"
#include "MoveSphere.h"
#include "Cube.h"
#include "CubeBox0.h"
#include "CubeBox1.h"
#include "MoveSpherePhy.h"
#include "KPAXPhysicsNode.h"
#include "../../nclgl/HeightMap.h"
#include "../../nclgl/KPAXNode.h"

#include "Ball_Spring_Chain.h"


class MyGame : public GameClass	{
public:
	MyGame();
	~MyGame(void);

	virtual void UpdateGame(float msec);

protected:
	GameEntity*		BuildRobotEntity();

	GameEntity*		BuildCubeEntity(float size);

	GameEntity*		BuildCube2(float size);

	//GameEntity*		BuildSphereEntity(float radius);

	//GameEntity*		BuildQuadEntity(float size);
	//
	//GameEntity*		BuildQuadEntity2(float size);


	//GameEntity*		DrawMyAnything();
	//GameEntity*		ShotProjectile(float msec);

	//GameEntity*		BuildHeightMap();
	//GameEntity*		BuildSpaceShip(Vector3 pos);

	//GameEntity*		BackFire(Vector3 pos);




	MoveCube*	cubeObj;
	//MoveCube*	cubeObj2;							// Check if using.

	CubeBox0*	cB0;
	CubeBox1*	cB1;

	MoveSphere*	sphereObj;
	//MoveSphere*	spObj[10];

	Mesh*	heightMap2;
	Vector3		position;

	springdemo_c* sd;

	Mesh* cube;
	Mesh* quad;
	Mesh* sphere;
	Mesh* sphere2;
	Mesh* missile1;
};

