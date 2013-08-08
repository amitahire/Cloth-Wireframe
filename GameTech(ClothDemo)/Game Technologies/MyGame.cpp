#include "MyGame.h"
#include "../../nclgl/HeightMap.h"
#include <time.h>
/*
Creates a really simple scene for our game - A cube robot standing on
a floor. As the module progresses you'll see how to get the robot moving
around in a physically accurate manner, and how to stop it falling
through the floor as gravity is added to the scene. 

You can completely change all of this if you want, it's your game!

*/

MyGame::MyGame()	{

	srand((unsigned int)time(NULL));

	gameCamera = new Camera(-30.0f,0.0f,Vector3(0,450,850));

	Renderer::GetRenderer().SetCamera(gameCamera);

	sd = new springdemo_c();

	cube			= new OBJMesh("../../Meshes/cube.obj");
	quad			= Mesh::GenerateQuad();
	sphere			= new OBJMesh("../../Meshes/ico.obj");

}

MyGame::~MyGame(void)	{
	/*
	We're done with our assets now, so we can delete them
	*/
	delete cube;
	delete quad;
	delete sphere;
}

/*
Here's the base 'skeleton' of your game update loop! You will presumably
want your games to have some sort of internal logic to them, and this
logic will be added to this function.
*/
void MyGame::UpdateGame(float msec) {

	if( Window :: GetKeyboard () -> KeyDown ( KEYBOARD_J )) {
		//sphereNode[0]->AddForce(-msec,0,0);
		sd->AddForce(3);
	}

	if( Window :: GetKeyboard () -> KeyDown ( KEYBOARD_K )) {
		//sphereNode[0]->AddForce(0,0,msec);
		sd->AddForce(0);
	}


	sd->Draw();

	//////////////////////////////////////////////////////
	if(gameCamera) {
		gameCamera->UpdateCamera(msec);
		//CamPos = gameCamera->GetPosition();
	}

	for(vector<GameEntity*>::iterator i = allEntities.begin(); i != allEntities.end(); ++i) {
		(*i)->Update(msec);
	}


	//Spawn new Enemy.
	if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_R)){

		float x = rand()%2000 + 350;
		float y = rand()%1100 + 200;
		float z = rand()%2000 + 850;
	//	allEntities.push_back(BuildSpaceShip(Vector3(x, y , z)));
	}


	// Reference Lines - X, Y and Z.
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, Vector3(10000,0,0),Vector3(-10000,0,0), Vector3(1,0,0), Vector3(1,0,0));
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, Vector3(0,10000,0),Vector3(0,-10000,0), Vector3(0,1,0), Vector3(0,1,0));
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, Vector3(0,0,10000),Vector3(0,0,-10000), Vector3(0,0,1), Vector3(0,0,1));
}




