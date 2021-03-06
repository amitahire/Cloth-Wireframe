#include "GameEntity.h"
#include "Renderer.h"
#include "PhysicsSystem.h"

GameEntity::GameEntity(void)	{
	renderNode	= NULL;
	physicsNode = NULL;
}

GameEntity::GameEntity(SceneNode* s, PhysicsNode* p) {
	renderNode	= s;
	physicsNode = p;


}

GameEntity::~GameEntity(void)	{
	DisconnectFromSystems();

	delete renderNode;
	delete physicsNode;
}

void	GameEntity::Update(float msec) {

			//if(((*i))->isHit) 
		//{
		//	std::remove(allNodes.begin(), allNodes.end(), ((*i))), allNodes.end();
		//	delete *i;
		//}

}

void	GameEntity::ConnectToSystems() {
	if(renderNode) {
		Renderer::GetRenderer().AddNode(renderNode);
	}

	if(physicsNode) {
		PhysicsSystem::GetPhysicsSystem().AddNode(physicsNode,0);
	}

	if(renderNode && physicsNode) {
		physicsNode->SetTarget(renderNode);
	}
	
	
}

void	GameEntity::DisconnectFromSystems() {
	if(renderNode) {
		Renderer::GetRenderer().RemoveNode(renderNode);
	}

	if(physicsNode) {
		PhysicsSystem::GetPhysicsSystem().RemoveNode(physicsNode);
	}
}