/******************************************************************************
Class:PhysicsSystem
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk> and YOU!
Description: A very simple physics engine class, within which to implement the
material introduced in the Game Technologies module. This is just a rough 
skeleton of how the material could be integrated into the existing codebase -
it is still entirely up to you how the specifics should work. Now C++ and
graphics are out of the way, you should be starting to get a feel for class
structures, and how to communicate data between systems.

It is worth poinitng out that the PhysicsSystem is constructed and destructed
manually using static functions. Why? Well, we probably only want a single
physics system to control the entire state of our game world, so why allow 
multiple systems to be made? So instead, the constructor / destructor are 
hidden, and we 'get' a single instance of a physics system with a getter.
This is known as a 'singleton' design pattern, and some developers don't like 
it - but for systems that it doesn't really make sense to have multiples of, 
it is fine!

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////


#pragma once

#include "PhysicsNode.h"
#include "../../nclgl/Vector3.h"
#include <vector>
#include "CollisionSphere.h"


using std::vector;

/*
Rich: 
There are a few ways of integrating the collision volumes
discussed in this module into your little physics engine.
You could keep pointers to all types inside a physics node,
and check to see which ones are NULL. Or you could make all
collision volumes inherit from a base class, so we only need
a single pointer inside each Physics Node. We can then either
use a process of dynamic casting to determine which exact type
of volume the pointer is, or just cheat and use an enum member
variable (I do this in my own work, you can do whichever you
feel comfortable with!).

enum CollisionVolumeType {
	COLLISION_SPHERE,
	COLLISION_AABB,
	COLLISION_PLANE
}


class CollisionVolume {
public:
	CollisionVolumeType GetType() { return type;}


protected:
	CollisionVolumeType type;
};

*/

//

class c_Sphere {
public:
	c_Sphere(){};
	c_Sphere(const Vector3& p, float r) //Position and radius.
	{
		m_pos = p;
		m_radius = r;
	}
	Vector3 m_pos;
	float m_radius;

	//More elements.#
	float	m_mass;
	Vector3 m_c;			//Centre.
	Matrix4	m_invInertia;	//--> Also in PhysicsNode.
	Vector3 m_linVelocity;
	Vector3 m_angVelocity;

};

class Line_c{
public:
	Line_c(const Vector3& p0, const Vector3& p1){
		m_p0 = p0;
		m_p1 = p1;
	}
	Vector3 m_p0;
	Vector3 m_p1;
};


class CollisionAABB {
public:
	CollisionAABB(){}; //Temp.
	CollisionAABB(const Vector3& p, const Vector3& hd){
		pos = p;
		halfdims = hd;
	}
	Vector3 pos;
	Vector3	halfdims;

	//float	m_mass;
	////float	m_awake; //--> What is it??
	//Vector3 m_c;			//Centre.
	//Matrix4	m_invInertia;	//--> Also in PhysicsNode.
	//Vector3 m_linVelocity;
	//Vector3 m_angVelocity;


};

class CollisionData {
public:
	Vector3		m_point;
	Vector3		m_normal;
	float		m_penetration;
};


class PhysicsSystem	{
public:
	friend class GameClass;
	friend class PhysicsNode;
	Plane*			pla;
	c_Sphere		cs0;
	c_Sphere		cs1;
	CollisionData	cd;
	CollisionAABB		cAB0;
	CollisionAABB		cAB1;
	//For Impulse.
	CollisionAABB		c0;
	CollisionAABB		c1;


	void		Update(float msec);

	void		BroadPhaseCollisions();
	void		NarrowPhaseCollisions();
	void		DeleteCollided();

	//Statics
	static void Initialise() {
		instance = new PhysicsSystem();
	}

	static void Destroy() {
		delete instance;
	}

	static PhysicsSystem& GetPhysicsSystem() {
		return *instance;
	}

	void	AddNode(PhysicsNode* n, int which);

	void	RemoveNode(PhysicsNode* n);

	static inline Vector3 Transform(const Vector3 v, const Matrix4 m){ return m * v; }

	//An array to delete the things off.
	PhysicsNode*	delArray[8];


protected:
	PhysicsSystem(void);
	~PhysicsSystem(void);

	bool SphereSphereCollision(const CollisionSphere &s0, const CollisionSphere &s1, CollisionData *collisionData = NULL) const;
	bool AABBCollision(const CollisionAABB &cube0, const CollisionAABB &cube1, CollisionData *collisionData) const;

	bool SphereInPlane(const Vector3 &position, float radius, c_Sphere &s0, CollisionData* collData) const;

	//bool SphereAABBCollision(const CollisionSphere &sphere, const CollisionAABB &cube, CollisionData *collisionData = NULL) const; //Research!!!! :-)


	//Sphere plane collisions we started in the previous module, and expand upon via the Plane class..

	bool PointInConvexPolygon(const Vector3 testPosition, Vector3 * convexShapePoints, int numPointsL) const;

	bool LineLineIntersection(const Line_c& l0, const Line_c& l1, float* t0 = NULL, float* t1 = NULL, float* t2 = NULL);

	bool InsideConcaveShape(const Vector3* shapePoints, const int numPoints, const Vector3& testPoint);

	//Collision Method - Impulse Method.

	//Was static. Why?
	void AddCollisionImpulse( PhysicsNode & c0 ,PhysicsNode & c1 ,const Vector3 & hitPoint ,const Vector3 & normal ,float penetration);

	void AddCollImpulse2( PhysicsNode* c0, const CollisionData& cd);

	void SoftBodyCollision();

	void SoftBodyCollision_AABB();
	
	float	LengthSq(Vector3 d) const		{
			float x = d.x;
			float y = d.y;
			float z = d.z;
			return (x*x)+(y*y)+(z*z);	
	} 
	//Statics
	static PhysicsSystem* instance;

	vector<PhysicsNode*> allNodes;

	vector<PhysicsNode*> clothNodes;
};

