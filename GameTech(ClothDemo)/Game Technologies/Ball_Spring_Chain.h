#pragma once
#include "Renderer.h"
#include "../../nclgl/Vector3.h"
#include "../../nclgl/Matrix4.h"
#include "PhysicsNode.h"

//////////////////////////////////////////////

//gravity acceleration
const static float g			=	-0.1f;
const static int GravityMul		=	1;		// Gravity Multipiler.
//mass
const static float mass			=	5.0f;

//spring parameter in hook's law.
const static float ks			=	1.7f;

//velocity damping paramrter.
const static float kd			=	0.1f;

//time slice
const static float dt			=	0.01f;

const static int ballsqr		=	30;
const static int maxnumballs	=	90;

//////////////////////////////////////////

const static int clothSize		=	1000;
const static float dist_apart	=	clothSize / (ballsqr-1);
static float offset				=	100.0f;
//TODO: Few more things. Check back later. 

class springdemo_c{

	PhysicsNode**	pNode;
	Vector3			maxXYZ;
	Vector3			minXYZ;

public:
	PhysicsNode**	GetPhysicsNodeList() { return pNode;}

	springdemo_c(){
	

		//Creating balls.
		pNode = new PhysicsNode*[ballsqr];

		for(int i = 0; i < ballsqr; i++) {
			pNode[i] = new PhysicsNode[ballsqr];
		}

		//creating balls - Setting init values for the balls.
		for (int i = 0; i < ballsqr; i++) {
			for(int j = 0; j < ballsqr; j++) {
				pNode [i][j].m_position = Vector3(0 , 0, 0);
				pNode [i][j].m_force = Vector3(0, 0, 0);
				pNode [i][j].m_linearVelocity = Vector3(0, 0, 0);
				pNode [i][j].m_colli_radius =	dist_apart;
				pNode [i][j].SetInverseMass(1.0f);
				float inertia = 2 * 3.14 * (dist_apart * dist_apart)/5;
				pNode [i][j].m_invInertia.SetScalingVector(Vector3(inertia, inertia, inertia));
			}

		}

		//Setting the position of the balls. 
		for( int i = 0; i < ballsqr; i++){
			for(int j = 0; j < ballsqr; j++){
				pNode[i][j].m_position.x = i * clothSize/(ballsqr-1);
				pNode[i][j].m_position.z = j * clothSize/(ballsqr-1);
				//Hmm.. Could be intresting.
				//pNode[i][j].m_position. x = Renderer::RandomFloat(0 ,800);
				//pNode[i][j].m_position. y = Renderer::RandomFloat(0 ,800);
			}
		}

		//Register with the physics system
		for( int i = 0; i < ballsqr; i++){
			for(int j = 0; j < ballsqr; j++){
				PhysicsNode* temp = &pNode[i][j];
				//TODO - Why not modify - AddNode? -- Modified. Try to simplify later.
				PhysicsSystem::GetPhysicsSystem().AddNode(temp, 1);
			}
		}
	}


	~springdemo_c(){
		for(int i = 0; i < ballsqr;i++){
			delete [] pNode[i];
		}
		delete [] pNode;
	};

void SetFixPoint(){
		// Fix first ball
			//Fix the edge
		//for (int i =0; i < ballsqr; i++){
			
			//Bottom
			//pNode[i][0].m_position.x = i * clothSize/(ballsqr-1)+offset;
			//pNode[i][0].m_position.y = 0;
			//pNode[i][0].m_position.z = 0 +offset;

			//Staic pos - Left
			//pNode[0][i].m_position. x = 0+offset;
			//pNode[0][i].m_position.y = 0;
			//pNode[0][i].m_position. z = i * clothSize/(ballsqr-1)+ offset;

			//Static pos - Top
			//pNode[i][ballsqr-1].m_position. x = i * clothSize/(ballsqr-1)+ offset;
			//pNode[i][ballsqr-1].m_position.y = clothSize+offset;
			//pNode[i][ballsqr-1].m_position. z = clothSize+offset;				

			//Staic Pos - Right
			//pNode[ballsqr-1][i].m_position. x = clothSize+offset;
			//pNode[ballsqr-1][i].m_position.y = 0;
			//pNode[ballsqr-1][i].m_position. z = (i * clothSize/(ballsqr-1))+ offset;		
		//}

		//pNode[0][0].m_position.x = offset;
		//pNode[0][0].m_position.y = offset;
		//pNode[0][0].m_position.z = 0;

		//Mid Hanger.
		pNode[(ballsqr/2)-1][ballsqr-1].m_position.x = 0+offset;
		pNode[(ballsqr/2)-1][ballsqr-1].m_position.y = clothSize+offset;
		pNode[(ballsqr/2)-1][ballsqr-1].m_position.z = 0;

		//pNode[0][ballsqr-1].m_position.x = 0+offset;
		//pNode[0][ballsqr-1].m_position.y = clothSize+offset;
		//pNode[0][ballsqr-1].m_position.z = 0;
		
	}

void DrawBalls() {


	for( int i = 0; i < ballsqr; i++){
		for( int j = 0; j < ballsqr; j++){
			Renderer::GetRenderer().DrawDebugCircle(DEBUGDRAW_PERSPECTIVE, pNode[i][j].m_position,10.0f, Vector3(1,0,0));
		}
	}

	//Draw springs
	for( int i = 0; i < ballsqr; i++){
		for(int j = 0; j < ballsqr; j++){
			if(j+1 < ballsqr){
				Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, pNode[i][j].m_position,pNode[i][j+1].m_position, Vector3(1,1,1), Vector3(1,1,1));
			}
			if(i+1< ballsqr){
				Renderer::GetRenderer().DrawDebugLine(DEBUGDRAW_PERSPECTIVE, pNode[i][j].m_position,pNode[i+1][j].m_position, Vector3(1,1,1), Vector3(1,1,1));
			}
		}
	}
}

void AddForce(int i){
		if(i == 0){
			cout << "0" <<endl;
			for ( int i = 0; i < ballsqr; i++) {
				pNode[i][ballsqr-1].m_position.z = pNode[i][ballsqr-1].m_position.z - 3.0f;
				//pNode[ballsqr-1][i].m_position.z = pNode[ballsqr-1][i].m_position.z - 1.0f;
				pNode[i][ballsqr-1].m_position.z = pNode[i][ballsqr-1].m_position.z - 1.0f;

			}

			//pNode[(int)(ballsqr-1)/2][(ballsqr-1)/2].m_position.z = pNode[(int)(ballsqr-1)/2][(int)(ballsqr-1)/2].m_position.z - 25.0f;
		}
		//if(i == 1){
		//	wa
		//	cout << "1" <<endl;
		//	pNode[(ballsqr-1)/2][(ballsqr-1)/2].m_position.z = pNode[(int)(ballsqr-1)/2][(int)(ballsqr-1)/2].m_position.z + 5.0f;
		//}
		//if(i == 2){
		//	
		//	cout << "2" <<endl;
		//	pNode[(ballsqr-1)/2][(ballsqr-1)/2].m_position.y = pNode[(int)(ballsqr-1)/2][(int)(ballsqr-1)/2].m_position.y - 5.0f;
		//}
		//if(i == 3){
		//	
		//	cout << "3" <<endl;
		//	pNode[(ballsqr-1)/2][(ballsqr-1)/2].m_position.y = pNode[(int)(ballsqr-1)/2][(int)(ballsqr-1)/2].m_position.y + 5.0f;
		//}
		//if(i == 4){
		//	
		//	cout << "4" <<endl;
		//	pNode[(ballsqr-1)/2][(ballsqr-1)/2].m_position.x = pNode[(int)(ballsqr-1)/2][(int)(ballsqr-1)/2].m_position.x - 5.0f;
		//}
		//if(i == 5){
		//	
		//	cout << "5" <<endl;
		//	pNode[ballsqr-1/2][ballsqr-1/2].m_position.x = pNode[(int)(ballsqr-1)/2][(int)(ballsqr-1)/2].m_position.x + 5.0f;
		//}
	}

void RecalculateBallPosition() {

	// Directional force.
	for(int i = 0; i < ballsqr; i++){
		for(int j = 0; j < ballsqr; j++){
			Vector3	force0	=	Vector3(0, 0, 0);
			Vector3	force1	=	Vector3(0, 0, 0);
			Vector3	force2	=	Vector3(0, 0, 0);
			Vector3	force3	=	Vector3(0, 0, 0);
			//if(pNode[i][j].hit == false && true){
				if(j+1 < ballsqr){
					force3 = (pNode[i][j].m_position - pNode[i][j+1].m_position + Vector3(0, dist_apart, 0));
				}
				if(j-1 >= 0){
					force2 = (pNode[i][j].m_position - pNode[i][j-1].m_position - Vector3(0, dist_apart, 0));
				}
				if(i+1 < ballsqr){
					force1 = (pNode[i][j].m_position - pNode[i+1][j].m_position + Vector3(dist_apart, 0, 0));
				}
				if(i-1 >= 0){
					force0 = (pNode[i][j].m_position - pNode[i-1][j].m_position - Vector3(dist_apart, 0, 0));
				}
			//	}

			Vector3 F = -(Vector3(ks,ks,ks)*(force0 + force1 + force2 + force3));

			pNode[i][j].m_force		=	F - Vector3(kd,kd,kd) * pNode[i][j].m_linearVelocity;
			pNode[i][j].m_force.y	+=	pNode[i][j].GetMass()* g * GravityMul;
		}
	}


	// Setting balls again - Check.
	for(int i = 0; i < ballsqr; i++){
		for(int j = 0; j < ballsqr; j++){

			//Acceleration.
			Vector3	acc	= pNode[i][j].m_force * (1.0f/mass);

			//Velocity.
			pNode[i][j].m_linearVelocity += acc * dt;

			//Position.
			pNode[i][j].m_position += pNode[i][j].m_linearVelocity * dt;

 			SetFixPoint();

			pNode[i][j].s1->m_pos		= pNode[i][j].m_position;

			pNode[i][j].s1->m_radius	= dist_apart;
		}
	}

}

void springdemo_c::Draw(){

		RecalculateBallPosition();

		DrawBalls();
}

};