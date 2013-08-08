#include "PhysicsSystem.h"
#include "Renderer.h"

PhysicsSystem* PhysicsSystem::instance = 0;


PhysicsSystem::PhysicsSystem(void)	{

	pla = new Plane(Vector3(0,-1,0), 10, true); // Normal , Distance from origin and Normalise. //REMOVE

/*
	// Adding some basic forces/Vectors - Just like that.
	// STEP :
	//	1.	 Resolve all forces on an object into a single force.
	//	2.	 Calculate the acceleration caused by that force from F = ma.
	//	3.	 Integrate the acceleration over time to calculate the velocity.
	//	4.	 Integrate the velocity over time to calculate the position.

*/
}

PhysicsSystem::~PhysicsSystem(void)	{

	delete pla;

}


void	PhysicsSystem::Update(float msec) {	


	//BroadPhaseCollisions();
	//NarrowPhaseCollisions();
	//DeleteCollided();
	for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		(*i)->Update(msec);
	}
}

void	PhysicsSystem::BroadPhaseCollisions() {

//	//DO IT by sorting by type of the object.
//
//	//Why should you create it everytime.. Cant you just create it in the constructor? DOESNT WORK!!
//	//Plane* pla = new Plane(Vector3(0,0,-1), -500, true);
//	// Doing the SphereSphereCollision detection and responce here.
//	//int shipIndex = 0;
//	//for(vector<PhysicsNode*>::iterator i = allNodes.begin() + 1 ; i != allNodes.end(); ++i, shipIndex++) {
//
//	//	if((*i)->isPlane)
//	//	{
//	//		for(vector<PhysicsNode*>::iterator j = i; j != allNodes.end(); ++j) 
//	//		{
//	//			if(*i != *j)
//	//			{
//	//				c_Sphere*		c2 = new c_Sphere((*j)->GetPosition(), 50);
//	//				CollisionData*	cd = new CollisionData();
//	//				if(SphereInPlane((*j)->GetPosition(), c2->m_radius, *c2, cd))
//	//				{
//	//					AddCollImpulse2(*j, *cd);
//	//				}
//	//			}
//	//		}
//
//	//	}
//
//	//	for(vector<PhysicsNode*>::iterator j = i; j != allNodes.end(); ++j) {
//	//		if(*i != *j){
//	//				c_Sphere*		c1 = new c_Sphere((*i)->GetPosition(), 50);
//	//				c_Sphere*		c2 = new c_Sphere((*j)->GetPosition(), 50);
//
//	//				CollisionData*	cd = new CollisionData();
//	//				if(SphereSphereCollision(*c1, *c2, cd) == true){
//	//					AddCollisionImpulse(*i, *j, *cd);
//	//					
//	//					//for(int k =0; k < 8; k++){
//	//					//	(*i)->m_HasHit = true;
//
//	//						//allNodes.erase(i);
//	//						//delArray[k] = (*i);
//	//					//}
//
//	//					if((*i)->isShip){
//	//						((*i))->isHit = true;
//	//						score += 100; 
//	//						pos = ((*i))->GetPosition();
//	//					}
//
//	//					if ((*j)->isMissile) {
//	//						delete *j;
//	//						
//	//						allNodes.erase(j);
//	//						i = j = allNodes.begin();
//	//						continue;
//	//					}
//
//
//	//				/*	if((*j)->isMissile == true){
//	//						allNodes.erase(j);
//	//					}*/
//	//				}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//					
//
/////////////////////////////////////////OLD WAY - BACK UP PLAN/////////////////////////////////////////////////////////////
//
//		//AI - ooh aah!
//		for(vector<PhysicsNode*>::iterator i = allNodes.begin()  ; i != allNodes.end(); ++i) {
//
//		if((*i)->isPlane)
//		{
//			for(vector<PhysicsNode*>::iterator j = i; j != allNodes.end(); ++j) 
//			{
//				if(*i != *j)
//				{
//					c_Sphere		c2 =  c_Sphere((*j)->GetPosition(), 50);
//					CollisionData	cd =  CollisionData();
//					if(SphereInPlane((*j)->GetPosition(), c2.m_radius, c2, &cd))
//					{
//						AddCollImpulse2(*j, cd);
//						//(*j)->SetLinearVelocity((*j)->GetLinearVelocity());
//						//Vector3 temp = (*j)->GetLinearVelocity();
//						//temp.y = -temp.y;
//						//(*j)->SetLinearVelocity(temp);
//
//					}
//
//					//c2 is gone
//					//cd is gone
//
//				}
//			}
//
//		}
//
//		//Getting the position from and making the spaceship backfire.
//		if(((*i))->isShip && (*i)->isHit == false) 
//		{
//			RandPos = (*i)->GetPosition();// + Vector3(100, 100, 100);
//			//hitCount++;
//		}
//
//		//Check if hit the player/camera.
//		if((*i)->isBackFire)
//		{
//			cubeAABB a = cubeAABB((*i)->GetPosition(), Vector3(100,100,100));
//			cubeAABB b = cubeAABB(CamPos, Vector3(300, 300, 300));
//
//			if(AABBCollision(a, b)){
//				lifes -= 1;
//				jitter = true;
//
//			}
//		}
//
//
//		for(vector<PhysicsNode*>::iterator j = i; j != allNodes.end(); ++j) {
//			if(*i != *j)
//			{
//					c_Sphere		c1 =  c_Sphere((*i)->GetPosition(), 50);
//					c_Sphere		c2 =  c_Sphere((*j)->GetPosition(), 50);
//
//					CollisionData	cd =  CollisionData();
//					if(SphereSphereCollision(c1, c2, &cd) == true){
//						AddCollisionImpulse(*i, *j, cd);
//						(*i)->m_HasHit = true;
//						if((*i)->isShip == true)
//						{
//							//In order to remove the ship.
//							//if(((*i))->GetPosition().y == 0)
//							//{
//								((*i))->isHit = true;
//
//							//}
//							
//								score += 100; 
//								pos = ((*i))->GetPosition();
//						}
//						//if((*j)->isMissile = true){
//						//	allNodes.erase(j);
//						//}
//					}
//
//			
//					// AI - Ooh aah!!
//					if (AI){
//
//						if((*i)->isShip && (*j)->isMissile)
//						{
//							if(*i != *j)
//							{
//
//								Vector3 a = (*i)->GetPosition();
//								Vector3 b = (*j)->GetPosition();
//								float diffX = abs(a.x-b.x);
//								float diffY = abs(a.y-b.y);
//								float diffZ = abs(a.z-b.z);
//								Vector3 diff = Vector3(diffX, diffY, diffZ);
//								float sep;
//								sep = (AIlevel == 0) ? 100.0 : 150.0f; 
//								if(diff.x <= 100)
//								{
//									if(diff.y <= 100)
//									{
//										if(diff.z <= 100)
//										{
//										
//											(*i)->SetPosition((*i)->GetPosition() + Vector3(100, 100, 100));
//											RandPos = (*i)->GetPosition() + Vector3(100, 100, 100);
//
//											}
//
//											//or add force or velo or acce -- check.
//										}
//									}
//								}
//							}
//						}
//
//					}
//				}
//
//		//if(((*i))->isHit) 
//		//{
//		//	std::remove(allNodes.begin(), allNodes.end(), ((*i))), allNodes.end();
//		//	delete *i;
//		//}
//
//			 }
	}

void	PhysicsSystem::NarrowPhaseCollisions() {
	CollisionData *newData = new CollisionData();
	//cout << allNodes.size() <<endl;
	int ccount = 0;
	int icount = 0;
	//cout << "Current System N^2 Calculations:" << allNodes.size() << " Total:" << allNodes.size() * allNodes.size() <<endl;
	for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		for(vector<PhysicsNode*>::iterator j = i; j != allNodes.end(); ++j) {
			if(i != j){
				PhysicsNode *n1 = (*i);			
				PhysicsNode *n2 = (*j);				

				//Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE, n1->GetPosition(),n1->GetColliRadius(), Vector3(0,1,0));
				//Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE,n1->GetPosition(),n1->GetColliRadius()*2, Vector3(0,1,0));
				//Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE, n2->GetPosition(),n2->GetColliRadius(), Vector3(0,1,0));
				//Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE, n2->GetPosition(),n2->GetColliRadius()*2, Vector3(0,1,0));
				
				if(SphereSphereCollision(*n1->s1,*n2->s1,newData)){
					//cout << "Collided!" <<endl;
					// cout << "Before" << n1->m_position <<":" << n1->m_linearVelocity << endl;
					AddCollisionImpulse(*n1,*n2,newData->m_point,newData->m_normal,newData->m_penetration);
					//cout << newData->m_point <<":"<< newData->m_normal <<":"<< newData->m_penetration <<endl;
					//cout << "After" << n1->m_position <<":" << n1->m_linearVelocity << endl;
					ccount++;
				} else {
					//cout << "--------"<<endl;
				}
				icount++;
			}
		}				
	}

	delete newData;

	float ccountf = ccount/100;
	//cout << icount <<endl;
	//cout << fps <<endl;
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_ORTHO, Vector3(0,30,0),Vector3(ccountf,30,0), Vector3(1,0,0), Vector3(1,0,0));
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_ORTHO, Vector3(60,20,0),Vector3(60,40,0), Vector3(0,0,1), Vector3(1,1,0));
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_ORTHO, Vector3(120,20,0),Vector3(120,40,0), Vector3(0,0,1), Vector3(1,1,0));
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_ORTHO, Vector3(200,20,0),Vector3(200,40,0), Vector3(0,0,1), Vector3(1,1,0));
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_ORTHO, Vector3(350,20,0),Vector3(350,40,0), Vector3(0,0,1), Vector3(1,1,0));
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_ORTHO, Vector3(500,20,0),Vector3(500,40,0), Vector3(0,0,1), Vector3(1,1,0));
}	
	//for (int k = 0; k < 8; k++){
	//	allNodes.erase(delArray[k]);
	//}
	



//void	PhysicsSystem::DeleteCollided(){
//
//	for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
//		if((*i)->m_HasHit = true) {
//			allNodes.erase(i);
//
//
//
//			return;
//		}
//	}
//
//}



void	PhysicsSystem::AddNode(PhysicsNode* n, int which) {
	if(which == 0){
		allNodes.push_back(n);
	}else if(which == 1){
		clothNodes.push_back(n);
	}
}

void	PhysicsSystem::RemoveNode(PhysicsNode* n) {
	for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		if((*i) == n) {
			allNodes.erase(i);
			return;
		}
	}

	for(vector<PhysicsNode*>::iterator j = clothNodes.begin(); j != clothNodes.end(); ++j) {
		if((*j) == n) {
			clothNodes.erase(j);
			return;
		}
	}
}


bool	PhysicsSystem::SphereSphereCollision(const CollisionSphere &s0, const CollisionSphere &s1, CollisionData *collisionData) const {
	
	const float distSq = LengthSq(s0.m_pos - s1.m_pos);
	//DBG_ASSERT (distSq > 0.00001f);
	
	const float sumRadius	= (s0.m_radius + s1.m_radius);

	if( distSq < sumRadius*sumRadius && distSq > 0.001f){
		if(collisionData){
			collisionData->m_penetration	= sumRadius - sqrtf(distSq);
			collisionData->m_normal			= s0.m_pos - s1.m_pos;
			collisionData->m_normal.Normalise();
			//Vector3 NormVec = (s0.m_pos - s1.m_pos);
			//NormVec.Normalise();
			//collisionData->m_normal			= NormVec; 
			collisionData->m_point			= s0.m_pos - collisionData->m_normal * (s0.m_radius - collisionData->m_penetration * 0.5f );
		}
		//cout << "TRUE" << endl;
		return true; // A Hit! - Collision
	}
	//system("cls");
	//cout << "FAL" << endl;
	return false;
}

bool	PhysicsSystem::AABBCollision(const CollisionAABB &cube0, const CollisionAABB &cube1, CollisionData *collisionData) const{

	////Testing along the x-axis.
	//float dist	= abs(cube0.pos.x - cube1.pos.x);
	//float sum	= (cube0.halfdims.x + cube1.halfdims.x);

	////If the distance is less than the sum, we have a overlap.
	//if( dist <= sum) {
	//	dist	= abs(cube0.pos.y - cube1.pos.y);
	//	sum		= (cube0.halfdims.y + cube1.halfdims.y);
	//	if(dist <= sum){
	//		float dist	= abs(cube0.pos.z - cube1.pos.z);
	//		float sum	= (cube0.halfdims.z + cube1.halfdims.z);
	//		if( dist <= sum) {
	//			//Overlap in all three axes so there is an intersection.
	//			return true;
	//		}
	//	}
	//}
	//return false;
	float maxX0 = cube0.pos.x+cube0.halfdims.x;
	float minX0 = cube0.pos.x-cube0.halfdims.x;
	float maxY0 = cube0.pos.y+cube0.halfdims.y;
	float minY0 = cube0.pos.y-cube0.halfdims.y;
	float maxZ0 = cube0.pos.z+cube0.halfdims.z;
	float minZ0 = cube0.pos.z-cube0.halfdims.z;

	float maxX1 = cube1.pos.x+cube1.halfdims.x;
	float minX1 = cube1.pos.x-cube1.halfdims.x;
	float maxY1 = cube1.pos.y+cube1.halfdims.y;
	float minY1 = cube1.pos.y-cube1.halfdims.y;
	float maxZ1 = cube1.pos.z+cube1.halfdims.z;
	float minZ1 = cube1.pos.z-cube1.halfdims.z;
	
	//Test along the x axis
	float dist = abs(cube0.pos.x - cube1.pos.x);
	float sum = (cube0.halfdims . x + cube1 . halfdims . x );
	//cout << "X:"<<dist <<":" << sum <<endl;
	if ( dist <= sum ) {
		dist = abs(cube0.pos . y - cube1.pos . y) ;
		sum = ( cube0.halfdims.y + cube1 . halfdims . y );
		//cout << "Y:"<<dist <<":" << sum <<endl;
		if ( dist <= sum ){
			dist = abs( cube0.pos . z - cube1 . pos . z );
			sum = ( cube0 . halfdims . z + cube1 . halfdims . z );
			//cout << "Z:"<<dist <<":" << sum <<endl;
			if ( dist <= sum ){
			// Overlap in all three axes so there is an intersection
				Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,cube0.pos,cube1.pos, Vector3(1,1,0), Vector3(1,1,0));	
				if ( collisionData ){
					//collisionData -> m_penetration = sumRadius - sqrtf ( distSq );
					collisionData -> m_normal =  cube0.pos - cube1.pos;
					collisionData -> m_normal.Normalise(); 
					collisionData -> m_point = cube1.pos;

				}
				if(true){
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,maxZ0),Vector3(maxX0,minY0,minZ0), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,maxY0,maxZ0),Vector3(maxX0,maxY0,minZ0), Vector3(1,0,0), Vector3(1,0,0));	
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,minZ0),Vector3(maxX0,maxY0,minZ0), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,maxZ0),Vector3(maxX0,maxY0,maxZ0), Vector3(1,0,0), Vector3(1,0,0));	

					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX0,minY0,maxZ0),Vector3(minX0,minY0,minZ0), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX0,maxY0,maxZ0),Vector3(minX0,maxY0,minZ0), Vector3(1,0,0), Vector3(1,0,0));	
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX0,minY0,minZ0),Vector3(minX0,maxY0,minZ0), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX0,minY0,maxZ0),Vector3(minX0,maxY0,maxZ0), Vector3(1,0,0), Vector3(1,0,0));	

					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,maxZ0),Vector3(minX0,minY0,maxZ0), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,maxY0,minZ0),Vector3(minX0,maxY0,minZ0), Vector3(1,0,0), Vector3(1,0,0));	
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,minZ0),Vector3(minX0,minY0,minZ0), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,maxY0,maxZ0),Vector3(minX0,maxY0,maxZ0), Vector3(1,0,0), Vector3(1,0,0));	
				}
				if(true){
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,maxZ1),Vector3(maxX1,minY1,minZ1), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,maxY1,maxZ1),Vector3(maxX1,maxY1,minZ1), Vector3(1,0,0), Vector3(1,0,0));	
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,minZ1),Vector3(maxX1,maxY1,minZ1), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,maxZ1),Vector3(maxX1,maxY1,maxZ1), Vector3(1,0,0), Vector3(1,0,0));	

					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX1,minY1,maxZ1),Vector3(minX1,minY1,minZ1), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX1,maxY1,maxZ1),Vector3(minX1,maxY1,minZ1), Vector3(1,0,0), Vector3(1,0,0));	
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX1,minY1,minZ1),Vector3(minX1,maxY1,minZ1), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX1,minY1,maxZ1),Vector3(minX1,maxY1,maxZ1), Vector3(1,0,0), Vector3(1,0,0));	

					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,maxZ1),Vector3(minX1,minY1,maxZ1), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,maxY1,minZ1),Vector3(minX1,maxY1,minZ1), Vector3(1,0,0), Vector3(1,0,0));	
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,minZ1),Vector3(minX1,minY1,minZ1), Vector3(1,0,0), Vector3(1,0,0));		
					Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,maxY1,maxZ1),Vector3(minX1,maxY1,maxZ1), Vector3(1,0,0), Vector3(1,0,0));	
				}
				Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE,cube0.pos,100.0f,Vector3(1,1,0));
				return true ;
			}			
		}
	}
	if(true){
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,maxZ0),Vector3(maxX0,minY0,minZ0), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,maxY0,maxZ0),Vector3(maxX0,maxY0,minZ0), Vector3(0,1,0), Vector3(0,1,0));	
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,minZ0),Vector3(maxX0,maxY0,minZ0), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,maxZ0),Vector3(maxX0,maxY0,maxZ0), Vector3(0,1,0), Vector3(0,1,0));	

		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX0,minY0,maxZ0),Vector3(minX0,minY0,minZ0), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX0,maxY0,maxZ0),Vector3(minX0,maxY0,minZ0), Vector3(0,1,0), Vector3(0,1,0));	
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX0,minY0,minZ0),Vector3(minX0,maxY0,minZ0), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX0,minY0,maxZ0),Vector3(minX0,maxY0,maxZ0), Vector3(0,1,0), Vector3(0,1,0));	

		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,maxZ0),Vector3(minX0,minY0,maxZ0), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,maxY0,minZ0),Vector3(minX0,maxY0,minZ0), Vector3(0,1,0), Vector3(0,1,0));	
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,minY0,minZ0),Vector3(minX0,minY0,minZ0), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX0,maxY0,maxZ0),Vector3(minX0,maxY0,maxZ0), Vector3(0,1,0), Vector3(0,1,0));	
	}
	if(true){
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,maxZ1),Vector3(maxX1,minY1,minZ1), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,maxY1,maxZ1),Vector3(maxX1,maxY1,minZ1), Vector3(0,1,0), Vector3(0,1,0));	
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,minZ1),Vector3(maxX1,maxY1,minZ1), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,maxZ1),Vector3(maxX1,maxY1,maxZ1), Vector3(0,1,0), Vector3(0,1,0));	

		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX1,minY1,maxZ1),Vector3(minX1,minY1,minZ1), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX1,maxY1,maxZ1),Vector3(minX1,maxY1,minZ1), Vector3(0,1,0), Vector3(0,1,0));	
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX1,minY1,minZ1),Vector3(minX1,maxY1,minZ1), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(minX1,minY1,maxZ1),Vector3(minX1,maxY1,maxZ1), Vector3(0,1,0), Vector3(0,1,0));	

		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,maxZ1),Vector3(minX1,minY1,maxZ1), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,maxY1,minZ1),Vector3(minX1,maxY1,minZ1), Vector3(0,1,0), Vector3(0,1,0));	
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,minY1,minZ1),Vector3(minX1,minY1,minZ1), Vector3(0,1,0), Vector3(0,1,0));		
		Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,Vector3(maxX1,maxY1,maxZ1),Vector3(minX1,maxY1,maxZ1), Vector3(0,1,0), Vector3(0,1,0));	
	}
	Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE,cube0.pos,cube1.pos, Vector3(1,0,0), Vector3(1,0,0));	
	return false;
}

bool	PhysicsSystem::PointInConvexPolygon(const Vector3 testPosition, Vector3 * convexShapePoints, int numPointsL) const {

	//Check if our test point is inside our convex shape.
	for(int i =0; i<numPointsL; ++i){
		const int i0 = i;
		const int i1 = (i+1) % numPointsL;

		const Vector3& p0 = convexShapePoints[i0];
		const Vector3& p1 = convexShapePoints[i1];


		//Required things - a point on the edge and the normal.
		Vector3 normal = p0 - p1;
		normal.Normalise();
		const Vector3 n = Vector3::Cross(Vector3(0,0,1), normal);

		//Using the point equation to calculate d and determine if our point 
		//is on the positive or negative side of the plane (edge).
		const float d = Vector3::Dot( n, p0);

		//Calculate whihc side out test points is..
		//+ve = inside ; -ve = outside; 0 = on plane.
		const float s = d - Vector3::Dot(n, testPosition);

		if(s < 0.0f) {
			//Failed - so skip rest of the test.
			return false;
		}

	}
	return true;
}


bool	PhysicsSystem::LineLineIntersection(const Line_c& l0, const Line_c& l1, float* t0, float* t1, float* t2){

	const Vector3& p0 = l0.m_p0;
	const Vector3& p1 = l0.m_p1;
	const Vector3& p2 = l1.m_p0;
	const Vector3& p3 = l1.m_p1;

	const float div = (p3.y-p2.y) * (p1.x-p0.x) - (p3.x-p2.x) * (p1.y - p0.y);

	//Nearly parallel lines.
	if(abs(div) < 0.000001f)	{ return false;}

	const float ta = ((p3.x-p2.x) * (p0.y-p2.y) - (p3.y - p2.y) * (p0.x-p2.x)) /div;
	if( ta < 0 || ta > 1.0f) {
		return false;
	}

	const float tb = ((p1.x-p0.x)*(p0.y-p2.y) - (p1.y-p0.y)*(p0.x-p2.x)) / div;
	if(tb < 0 || tb > 1.0f){
		return false;
	}

	if (t0)		(*t0) = ta;
	if (t1)		(*t1) = tb;

	return true;

}

bool	PhysicsSystem::InsideConcaveShape(const Vector3* shapePoints, const int numPoints, const Vector3& testPoint){

	int intersectionCount = 0;
	//Counting hom many times we cross the line.
	for( int i = 0; i < numPoints; ++i){
		const int i0 = i;
		const int i1 = (i+1)%numPoints;

		const Vector3& p0 = shapePoints[i0];
		const Vector3& p1 = shapePoints[i1];

		bool intersect = LineLineIntersection(Line_c(p0,p1), Line_c(testPoint, testPoint + Vector3(1000,1000,0)));

		if (intersect){
			intersectionCount++;
		}
	}

	//Even = false;
	if(intersectionCount % 2 == 0){
		return false;
	}
	else {return true;}
}


///////////////SphereInPlane///////////////////////////////////

bool	PhysicsSystem::SphereInPlane(const Vector3 &position, float radius, c_Sphere &s0, CollisionData* collData) const {


	//Debug boxes
	//Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE, Vector3(0,0,-400), Vector3(100,100,100), Vector3(1,0,0));
	//float seperation = Vector3::Dot(position,normal) + distance;
	Vector3 normal = pla->GetNormal();
	float seperation = Vector3::Dot(position, normal) + pla->GetDistance();
	if ( seperation <= -radius) {
		return false;
	}else
	{
		if(collData) {
			collData->m_penetration = radius + seperation;
			collData->m_normal = -pla->GetNormal();
			collData->m_point = s0.m_pos - normal * collData->m_penetration;
		}
	}

	return true;

}


///////////////////////////////////////////////////////////////

//Impulse Method.
void	PhysicsSystem::AddCollisionImpulse( PhysicsNode & c0 ,PhysicsNode & c1 ,const Vector3 & hitPoint ,const Vector3 & normal ,float penetration){

	////Some simple check code.
	//float invMass0 = (c0->GetInverseMass() > 1000.0f) ? 0.0f : (1.0f/c0->GetInverseMass());
	//float invMass1 = (c1->GetInverseMass() > 1000.0f) ? 0.0f : (1.0f/c1->GetInverseMass());

	///*invMass0 = (!c0.m_awake) ? 0.0f : invMass0;
	//invMass1 = (!c1.m_awake) ? 0.0f : invMass1;*/

	//const Matrix4 worldInvInertia0	= c0->GetInvInertia();
	//const Matrix4 worldInvInertia1	= c1->GetInvInertia();

	////Both objects are non movable.
	//if((invMass0 + invMass1) == 0.0) return;

	////Assuming m_c is the center.
	//Vector3 r0 = cd.m_point - c0->GetPosition();
	////Vector3 r1 = cd.m_point - c1.m_c;
	//Vector3 r1 = cd.m_point - c1->GetPosition();

	//Vector3 v0 = c0->GetLinearVelocity() + Vector3::Cross(c0->GetAngularVelocity(), r0);
	//Vector3 v1 = c1->GetLinearVelocity() + Vector3::Cross(c1->GetAngularVelocity(), r1);

	////Relative Velocity.
	//Vector3 dv = v0 - v1;

	////If the objects are moving away from each other
	////we dont need to apply an impulse.
	//float relativeMovement	=	-(Vector3::Dot(dv, cd.m_normal));
	//if(relativeMovement < -0.01f)		{ return; }


	////NORMAL Impulse.///////////////////////////////////////////////////////////////
	//{
	//	//Coefficient Of Restitution.
	//	float e = 0.5f;

	//	float normDiv	= Vector3::Dot(cd.m_normal, cd.m_normal) * ((invMass0 + invMass1) + Vector3::Dot(cd.m_normal, Vector3::Cross(PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal), worldInvInertia0), r0)
	//					  + Vector3::Cross(PhysicsSystem::Transform(Vector3::Cross(r1, cd.m_normal), worldInvInertia1), r1)));

	//	float jn		= -1 * (1+e) * Vector3::Dot(dv, cd.m_normal) / normDiv;

	//	//Hack fix to stop sinking.
	//	//Bias impulse proportional to penetration distance.
	//	jn				= jn + (cd.m_penetration * 1.5f);

	//	//OLD - //c0->m_linearVelocity += cd.m_normal * invMass0 * jn;
	//	c0->SetLinearVelocity(c0->GetLinearVelocity() + cd.m_normal * invMass0 * jn);
	//	c0->SetAngularVelocity(c0->GetAngularVelocity() + PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal * jn), worldInvInertia0));

	//	c1->SetLinearVelocity(c1->GetLinearVelocity() - cd.m_normal * invMass1 * jn);
	//	c1->SetAngularVelocity(c1->GetAngularVelocity() - PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal * jn), worldInvInertia1));

	//}

	////TANGENT Impusle Code///////////////////////////////////////////////////////////
	//{
	//	//Work out the tangent vector, Which is perpendicular to the collision normal.
	//	Vector3 tangent = Vector3(0, 0, 0);
	//	tangent			= dv - (cd.m_normal * Vector3::Dot(dv, cd.m_normal) ); //TODO - Make sure - We are talking the SAME normals here - CHECK 
	//	tangent.Normalise();

	//	//tangent			= Vector3::Normalise(tangent);

	//	float tangDiv	= invMass0 + invMass1 + Vector3::Dot(tangent, Vector3::Cross((c0->GetInvInertia() * Vector3::Cross(r0, tangent) ), r0)
	//		+ Vector3::Cross((c1->GetInvInertia() * Vector3::Cross(r1, tangent)), r1));

	//	float jt		= -1 * Vector3::Dot(dv, tangent) / tangDiv;

	//	//Clamp main/max tangental component
	//	//Apply contact impulse.
	//	c0->SetLinearVelocity(c0->GetLinearVelocity() + tangent * invMass0 * jt);
	//	c0->SetAngularVelocity((c0->GetAngularVelocity() + PhysicsSystem::Transform(Vector3::Cross(r0, tangent * jt), worldInvInertia0)) * 2);
	//	//c0.m_linVelocity += tangent * invMass0  * jt;
	//	//c0.m_angVelocity += PhysicsSystem::Transform(Vector3::Cross(r0, tangent * jt), worldInvInertia0);
	//	
	//	c1->SetLinearVelocity(c1->GetLinearVelocity() - tangent * invMass1  * jt);
	//	c1->SetAngularVelocity(c1->GetAngularVelocity() - PhysicsSystem::Transform(Vector3::Cross(r1, tangent * jt), worldInvInertia1));
	//	//c1.m_linVelocity -= tangent * invMass1  * jt;
	//	//c1.m_angVelocity -= PhysicsSystem::Transform(Vector3::Cross(r1, tangent * jt), worldInvInertia1);

	//}
	//////////////////////////////////////////////////////////////////////////////////
	float invMass0 = c0.m_invMass;
	float invMass1 = c1.m_invMass;
	
	const Matrix4 worldInvInertia0 = c0 . m_invInertia ;
	const Matrix4 worldInvInertia1 = c1 . m_invInertia ;
	
	//cout << c1 . m_position<<":==" <<invMass0 << ":" <<worldInvInertia0.GetScalingVector() <<endl;
	if ( ( invMass0 + invMass1 )== 0.0 ) return ;

	Vector3 r0 = hitPoint - c0 . m_position ;
	Vector3 r1 = hitPoint - c1 . m_position ;

	Vector3 v0 = c0 . m_linearVelocity + Vector3::Cross ( c0 . m_angularVelocity , r0 );

	Vector3 v1 = c1 . m_linearVelocity + Vector3::Cross ( c1 . m_angularVelocity , r1 );

	Vector3 dv = v0 - v1 ;

	float relativeMovement = - Vector3::Dot ( dv , normal );

	if ( relativeMovement < -0.01f ) {return ;} 

	
		// Coefficient of Restitution
		float e = 0.0f ;
		float normDiv = 0;

		// n.n(1/ma + 1/mb)
		normDiv = normDiv + Vector3::Dot( normal , normal ) * ((invMass0 + invMass1)); 

		//[(Ia^-1(Ra x n)x ra ].n
		Vector3 raxn = Vector3::Cross(r0,normal);
		Vector3 Inva = worldInvInertia0.GetScalingVector();		
		Inva.x = 1.0f/Inva.x;
		Inva.y = 1.0f/Inva.y;
		Inva.z = 1.0f/Inva.z;

		Vector3 InvaXraxn = Vector3::Cross(raxn,Inva);
		Vector3 temp = Vector3::Cross(InvaXraxn,r0);
		float Result = Vector3::Dot(temp,normal);

		normDiv = normDiv + Result;

		//[(Ib^-1(Rb x n)x rb ].n		
		Vector3 rbxn = Vector3::Cross(r1,normal);
		Vector3 Invb = worldInvInertia1.GetScalingVector();		
		Invb.x = 1.0f/Invb.x;
		Invb.y = 1.0f/Invb.y;
		Invb.z = 1.0f/Invb.z;

		Vector3 InvbXrbxn = Vector3::Cross(rbxn,Invb);
		Vector3 temp1 = Vector3::Cross(InvaXraxn,r1);
		float Result1 = Vector3::Dot(temp1,normal);

		normDiv = normDiv + Result1;

		float jn = -1*(1+ e )* Vector3::Dot ( dv , normal ) / normDiv ;

		//cout << jn << endl;

		 //Hack fix to stop sinking
		 // bias impulse proportional to penetration distance
		 jn = jn + ( penetration *1.5f );

		 c0 . m_linearVelocity += Vector3(invMass0) * normal *  Vector3(jn)  ;
		// cout << c0 . m_linearVelocity <<endl;
		// c0 . m_angularVelocity +=  Vector3::Cross ( r0 , (normal *  Vector3(jn))) ;//, worldInvInertia0 );
		 //c0 . m_angularVelocity += (r0*Vector3(jn))*worldInvInertia0.GetScalingVector()*Vector3(0.00001);

		c0.m_angularVelocity += (r0 * Vector3(jn)) * worldInvInertia0.GetScalingVector() * Vector3(0.00001);

		c1 . m_linearVelocity -=  (Vector3(invMass1)  * normal * Vector3(jn));//*Vector3(10,10,10)  ;
		 // cout << c1 . m_linearVelocity <<endl;
		// c1 . m_angularVelocity -=  Vector3::Cross ( r1 , (normal *  Vector3(jn))) ;//, worldInvInertia1 );
		c1 . m_angularVelocity -= (r1*Vector3(jn))*worldInvInertia1.GetScalingVector()*Vector3(0.00001);
	 
	 //{
		 /*
		 Vector3 tangent = Vector3(0,0,0);
		 tangent = dv - Vector3::Cross(Vector3::Dot ( dv , normal ),normal );
		 tangent.Normalise();

		 float tangDiv = invMass0 + invMass1 
			 + Vector3::Dot (tangent , Vector3::Cross (Vector3::Cross ( Vector3::Cross ( r0 , tangent ) , c0.m_invInertia.GetScalingVector()) , r0 ));
			// + Vector3::Cross (Vector3::Cross( Vector3::Cross(r1,tangent),c1.m_invInertia.GetScalingVector()) , r1 );

		// float jt = -1 * Vector3:Dot ( dv , tangent ) / tangDiv ;
		//// Clamp min /max tangental component

		// // Apply contact impulse
		// c0 . m_linearVelocity += invMass0 * tangent * jt ;
		// c0 . m_angularVelocity += Vector3::Transform ( Cross ( r0 , tangent * jt ) , worldInvInertia0 );

		// c1 . m_linearVelocity -= invMass1 * tangent * jt ;
		// c1 . m_angularVelocity -= Vector3::Transform ( Cross ( r1 , tangent * jt ) , worldInvInertia1 );
	 //}*/
}

//////////////////////////////Collision Responce for SphereInPlane./////////////////
void	PhysicsSystem::AddCollImpulse2( PhysicsNode* c0, const CollisionData& cd){

	//Some simple check code.
	float invMass0 = (c0->GetInverseMass() > 1000.0f) ? 0.0f : (1.0f/c0->GetInverseMass());

	/*invMass0 = (!c0.m_awake) ? 0.0f : invMass0;
	invMass1 = (!c1.m_awake) ? 0.0f : invMass1;*/

	const Matrix4 worldInvInertia0	= c0->GetInvInertia();

	//Both objects are non movable.
	if((invMass0) == 0.0) return;

	//Assuming m_c is the center.
	Vector3 r0 = cd.m_point - c0->GetPosition();

	Vector3 v0 = c0->GetLinearVelocity() + Vector3::Cross(c0->GetAngularVelocity(), r0);

	//Relative Velocity.
	Vector3 dv = v0;

	//If the objects are moving away from each other
	//we dont need to apply an impulse.
	float relativeMovement	=	-(Vector3::Dot(dv, cd.m_normal));
	if(relativeMovement < -0.01f)		{ return; }


	//NORMAL Impulse.///////////////////////////////////////////////////////////////
	{
		//Coefficient Of Restitution.
		float e = 0.5f;

		float normDiv	= Vector3::Dot(cd.m_normal, cd.m_normal) * ((invMass0) + Vector3::Dot(cd.m_normal, Vector3::Cross(PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal), worldInvInertia0), r0)));

		float jn		= -1 * (1+e) * Vector3::Dot(dv, cd.m_normal) / normDiv;

		//Hack fix to stop sinking.
		//Bias impulse proportional to penetration distance.
		jn				= jn + (cd.m_penetration * 1.5f);

		//OLD - //c0->m_linearVelocity += cd.m_normal * invMass0 * jn;
		c0->SetLinearVelocity(c0->GetLinearVelocity() + cd.m_normal * invMass0 * jn);
		c0->SetAngularVelocity(c0->GetAngularVelocity() + PhysicsSystem::Transform(Vector3::Cross(r0, cd.m_normal * jn), worldInvInertia0));


	}

	//TANGENT Impusle Code///////////////////////////////////////////////////////////
	{
		//Work out the tangent vector, Which is perpendicular to the collision normal.
		Vector3 tangent = Vector3(0, 0, 0);
		tangent			= dv - (cd.m_normal * Vector3::Dot(dv, cd.m_normal) ); //TODO - Make sure - We are talking the SAME normals here - CHECK 
		tangent.Normalise();

		float tangDiv	= invMass0 + Vector3::Dot(tangent, Vector3::Cross((c0->GetInvInertia() * Vector3::Cross(r0, tangent) ), r0));

		float jt		= -1 * Vector3::Dot(dv, tangent) / tangDiv;

		//Clamp main/max tangental component
		//Apply contact impulse.
		c0->SetLinearVelocity(c0->GetLinearVelocity() + tangent * invMass0 * jt);
		c0->SetAngularVelocity(c0->GetAngularVelocity() + PhysicsSystem::Transform(Vector3::Cross(r0, tangent * jt), worldInvInertia0));

	}
}

////////////////////////////////////////////////////////////////////////////////////////////

void	PhysicsSystem::SoftBodyCollision() {
	CollisionData *newData = new CollisionData();
	for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		PhysicsNode *n1 = (*i);	
		for(vector<PhysicsNode*>::iterator j = clothNodes.begin(); j != clothNodes.end(); ++j) {	
				PhysicsNode *n2 = (*j);			
				//Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE, n1->GetPosition(),n1->GetColliRadius(), Vector3(0,1,0));
				//Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE,n1->GetPosition(),n1->GetColliRadius()*2, Vector3(0,1,0));
				//Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE, n2->GetPosition(),n2->GetColliRadius()+1, Vector3(0,1,0));
				//Renderer::GetRenderer().DrawDebugBox(DEBUGDRAW_PERSPECTIVE, n2->GetPosition(),n2->GetColliRadius()*2, Vector3(0,1,0));	
				if(SphereSphereCollision(*n1->s1,*n2->s1,newData)){
					//cout << "Collided!" <<endl;
					//cout << clothNodes.size() << ":" << allNodes.size() <<endl;
					//cout << newData->m_normal << ":" << newData->m_penetration <<":" << newData ->m_point <<endl;
					AddCollisionImpulse(*n1,*n2,newData->m_point,newData->m_normal,newData->m_penetration);
					n2->hit = true;

				} else {
					//cout << "--------"<<endl;
				}
			
		}
	}
	delete newData;
}

void	PhysicsSystem::SoftBodyCollision_AABB() {
		for(vector<PhysicsNode*>::iterator i = allNodes.begin(); i != allNodes.end(); ++i) {
		PhysicsNode *n1 = (*i);	
		CollisionAABB *b1 = new CollisionAABB(n1->GetPosition(),Vector3(n1->GetColliRadius(),n1->GetColliRadius(),n1->GetColliRadius()));
		int maxX = 0.0f;				
		int minX = 0.0f;				
		int maxY = 0.0f;				
		int minY = 0.0f;				
		int maxZ = 0.0f;
		int minZ = 0.0f;
		for(vector<PhysicsNode*>::iterator j = clothNodes.begin(); j != clothNodes.end(); j++) {				
			PhysicsNode *n2 = (*j);		
			if(j == clothNodes.begin()){
				maxX =  n2->m_position.x;
				minX =  n2->m_position.x;
				maxY =  n2->m_position.y;
				minY =  n2->m_position.y;
				maxZ =  n2->m_position.z;
				minZ =  n2->m_position.z;
			}
			if(n2->GetPosition().x > maxX){
				maxX = n2->m_position.x;
			}
			if(n2->GetPosition().x < minX){
				minX =  n2->m_position.x;
			}				
			if(n2->GetPosition().y > maxY){
				maxY =  n2->m_position.y;
			} 
			if(n2->GetPosition().y < minY){
				minY =  n2->m_position.y;
			}
			if(n2->GetPosition().z > maxZ){
				maxZ =  n2->m_position.z;
			}
			if(n2->GetPosition().z < minZ){
				minZ =  n2->m_position.z;
			}
		}

		float originX = (maxX-(maxX-minX)/4);
		float originY = (maxY-(maxY-minY)/4);
		float originZ = (maxZ-(maxZ-minZ)/4);

		float lengthX = (maxX-minX)/4;
		float lengthY = (maxY-minY)/2;
		float lengthZ = (maxZ-minZ)/4;

		CollisionAABB *b2 = new CollisionAABB(Vector3(maxX-lengthX,maxY-lengthY,maxZ-lengthZ),Vector3(lengthX,lengthY,lengthZ));
		CollisionAABB *b3 = new CollisionAABB(Vector3(maxX-3*lengthX,maxY-lengthY,maxZ-3*lengthZ),Vector3(lengthX,lengthY,lengthZ));		
		CollisionAABB *b4 = new CollisionAABB(Vector3(maxX-3*lengthX,maxY-lengthY,maxZ-lengthZ),Vector3(lengthX,lengthY,lengthZ));		
		CollisionAABB *b5 = new CollisionAABB(Vector3(maxX-lengthX,maxY-lengthY,maxZ-3*lengthZ),Vector3(lengthX,lengthY,lengthZ));

		CollisionData *d0 = new CollisionData();

		if(AABBCollision(*b1,*b2,d0)){
		//	cout << "Collided:"<<endl;			
		} else {
			if(AABBCollision(*b1,*b3,d0)){
		//		cout << "Collided:"<<endl;			
			} else {
				if(AABBCollision(*b1,*b4,d0)){
			//	cout << "Collided:"<<endl;			
				} else {
					if(AABBCollision(*b1,*b5,d0)){
			//		cout << "Collided:"<<endl;			
					} else {
				//		cout << "--------"<<endl;
					}	
				}	
			}		
		
		}
		
		delete b1;
		delete b2;
		delete d0;
	}
}