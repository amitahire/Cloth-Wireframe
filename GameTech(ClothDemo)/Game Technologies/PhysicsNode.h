/******************************************************************************
Class:PhysicsNode
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk> and YOU!
Description: This class represents the physical properties of your game's
entities - their position, orientation, mass, collision volume, and so on.
Most of the first few tutorials will be based around adding code to this class
in order to add correct physical integration of velocity / acceleration etc to
your game objects. 


In addition to the tutorial code, this class contains a pointer to a SceneNode.
This pointer is to the 'graphical' representation of your game object, just 
like the SceneNode's used in the graphics module. However, instead of 
calculating positions etc as part of the SceneNode, it should instead be up
to your 'physics' representation to determine - so we calculate a transform
matrix for your SceneNode here, and apply it to the pointer. 

Your SceneNode should still have an Update function, though, in order to
update any graphical effects applied to your object - anything that will end
up modifying a uniform in a shader should still be the job of the SceneNode. 

Note that since the SceneNode can still have children, we can represent our
entire CubeRobot with a single PhysicsNode, and a single SceneNode 'root'.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////


#pragma once

#include "../../nclgl/Quaternion.h"
#include "../../nclgl/Vector3.h"
#include "../../nclgl/Matrix4.h"
#include "../../nclgl/SceneNode.h"
#include "../../nclgl/Plane.h"
//
#include "PhysicsSystem.h"
#include "CollisionSphere.h"

class PhysicsSystem;

class PhysicsNode	{
public:
	PhysicsNode(void);
	PhysicsNode(Quaternion orientation, Vector3 position);
	~PhysicsNode(void);

	void				SetPosition(Vector3 pos)			{ m_position = pos;}
	Vector3				GetPosition()						{ return m_position;}

	void				SetLinearVelocity(Vector3 l_vel)	{ m_linearVelocity = l_vel;} 
	Vector3				GetLinearVelocity()					{ return m_linearVelocity;}
	
	void				SetInverseMass(float m)				{ m_invMass = m; }
	float				GetInverseMass()					{ return m_invMass;}
	float				GetMass()							{ return 1/m_invMass;}

	void				SetOrientation(Quaternion q)		{ m_orientation = q;}
	Quaternion			GetOrientation()					{ return m_orientation;}


	void				SetAngularVelocity(Vector3 a_vel)	{ m_angularVelocity = a_vel; }
	Vector3				GetAngularVelocity()				{ return m_angularVelocity;}

	Matrix4				BuildTransform();

	virtual void		Update(float msec);

	void				SetTarget(SceneNode *s)				{ target = s;}
	//void				IntergrateGravity(float dt);

	void				AddForce(Vector3 f) 				{ m_force	+= f;}
	Vector3				GetForce()							{ return m_force;}

	void				AddTorque(Vector3 t)				{ m_torque	+= t;}
	Vector3				GetTorque()							{ return m_torque;}

	//SPHERE
	void				SetSphereRadius(float r)			{ radius = r;}
	float				GetSphereRadius()					{return radius;}

	//CUBOID.
	//Removed H, L, W - You can get it in SetModelScale - I think that should be enough.
	//void				SetInvMass(float m)					{ m_invMass = m;}
	//float				GetInvMass()						{ return m_invMass;}

	Matrix4				GetInvInertia()						{ return m_invInertia;}
	
	// A New Plane.
	float				GetYaw()							{ return yaw; }
	float				GetPitch()							{ return pitch;}

	Vector3				GetDimension()						{ return m_dimension;}
	void				SetDimension(Vector3 d)				{ m_dimension = d; }
	
	//bool				isPlane;
	//bool				isMissile;
	//bool				isShip;
	//bool				isHit;
	//bool				m_HasHit;
	//bool				isBackFire;
	

	SceneNode*		target;
	///////////////////////////FOR SOFTBODY///////////////////////////////
	//Set Collision Sphere Radius
	float m_colli_radius;
	//Colli Used
	void			SetColliRadius(float radius){ m_colli_radius = radius;}
	float			GetColliRadius()			{ return m_colli_radius;}
	///////////////////////////////////////////////////////////////////////


	//<---------LINEAR-------------->
	Vector3		m_position;
	Vector3		m_linearVelocity;
	Vector3		m_force;
	Vector3		m_acce;
	float		m_invMass;

	//<----------ANGULAR--------------->
	Quaternion  m_orientation;
	Vector3		m_angularVelocity;
	Vector3		m_angularAcce; 
	Vector3		m_torque;
	Matrix4     m_invInertia;

	bool hit;

//protected:
	bool		isLinear;
	bool		isSphere;
	bool		isCuboid;



	 
	PhysicsSystem*	psys;
	Plane*			pla;

	// Change it and add it above.
	float radius; //Collision Radius?
	float yaw;
	float pitch;

	Vector3		m_dimension;
		//Collision Sphere.
	CollisionSphere		*s1;
};

