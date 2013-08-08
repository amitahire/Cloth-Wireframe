#include "PhysicsNode.h"
#define DAMP_FACTOR 0.9995

PhysicsNode::PhysicsNode(void)	{
	target = NULL;
	m_colli_radius = 1.0f;
	s1 = new CollisionSphere(m_position,m_colli_radius);
	hit = false;
	//isMissile		= false;
	//isShip			= false;
	//isHit			= false;
	//m_HasHit		= false;
	//isBackFire		= false;
}

PhysicsNode::PhysicsNode(Quaternion orientation, Vector3 position) {
	m_orientation	= orientation;
	m_position		= position;
	m_colli_radius  = 1.0f;	
	s1 = new CollisionSphere(m_position,m_colli_radius);
	hit = false;
	//isPlane			= false;
	//isMissile		= false;
	//isShip			= false;
	//isHit			= false;
	//m_HasHit		= false;
	//isBackFire		= false;

	yaw -= (Window::GetMouse()->GetRelativePosition().x);
	pitch -= (Window::GetMouse()->GetRelativePosition().y);
	pitch = min(pitch,90.0f);
	pitch = max(pitch,-90.0f);

	if(yaw < 0) {
		yaw += 360.0f;
	}
	if(yaw > 360.0f) {
		yaw -= 360.0f;
	}
}

PhysicsNode::~PhysicsNode(void)	{

	//delete pla;
	//delete target;
	//delete psys;
	delete s1;

}

//You will perform your per-object physics integration, here!
//I've added in a bit that will set the transform of the
//graphical representation of this object, too.
void	PhysicsNode::Update(float msec) {
	//FUN GOES HERE
/*
	// Adding some basic forces/Vectors - Just like that.
	// STEP :
	//	1.	 Resolve all forces on an object into a single force.
	//	2.	 Calculate the acceleration caused by that force from F = ma.
	//	3.	 Integrate the acceleration over time to calculate the velocity.
	//	4.	 Integrate the velocity over time to calculate the position.
*/
	//////////////// COMMON SECTION. ///////////////////////////////
//	msec *= 0.001f;
//
//	//////////////// LINEAR CALCULATION. ///////////////////////////
//	if( isLinear) {
//
//		m_invMass = 1.0;
//		//m_force = Vector3(0, 10, 10);
//		m_acce = (m_force * m_invMass);
//		//if(m_force != Vector3(0, 0, 0)) { 
//		//	cout<< "Test" << endl;
//		//}
//
//
//		// Using the Symplectic Euler Integration.
//		/*NextVelocity = ThisVelocity + ThisAcceleration * msec;
//		NextPosition = ThisPosition + NextVelocity * msec;*/	
//
//		//m_linearVelocity = ThisVelocity + ThisAcceleration * msec;
//		m_linearVelocity = m_linearVelocity + m_acce * msec;
//		m_position = m_position + m_linearVelocity * msec;
//		m_force.ToZero();
//
//		//Damping Factor.
//		m_linearVelocity = m_linearVelocity * DAMP_FACTOR;
//		
//		//TODO - How the do I add friction?
//	//	if(m_linearVelocity.x < 15 ) { m_linearVelocity.x = 0; }
//	//	if(m_linearVelocity.z < 15 ) { m_linearVelocity.z = 0; }
//
//
//		if(m_position.y < 0)
//		{
//			m_position.y = 0;
//			//this->m_linearVelocity = -this->m_linearVelocity * (0.4);
//
//		}
//	}
///*	///////////////////CHECKING FOR COLLISION - SPHERE-SPHERE//////////
//	//cout << &psys->cd.m_point << endl;
//	PhysicsSystem* psys = &PhysicsSystem::GetPhysicsSystem();
//	//cout << psys->cs0.m_pos << endl;
//	//cout << psys->cs1.m_pos << endl;
//	//cout << psys->cs0.m_radius<< endl;
//	//cout << psys->cs1.m_radius << endl;
//	psys->cs0.m_radius = 50.0f;
//	psys->cs1.m_radius = 50.0f;
//	bool hit = false;
//	hit = psys->SphereSphereCollision(psys->cs0, psys->cs1, &psys->cd);
//	if(hit) {cout << "SSC : " << hit << endl;}
//	//if (hit = false) { cout << "ITS FALSE" << endl; }
//	/////////////////////////////////////////////////////////////////
//
//	/////////////////////////////////////////////////////////////////
//	//////////////////SPHERE IN PLANE COLLISION./////////////////////
//
//	//collPlane = Plane(Vector3::Cross(Vector3(1,0,0),Vector3(0,1,0)), 500, true); // Normal , Distance and Normalise.
//	Plane* pla = new Plane(Vector3(0,0,-1), -500, true); // Normal , Distance and Normalise.
//	//collPlane.sp.m_radius = 50.0f;
//	pla->sp.m_radius = 50.0f;
//	pla->sp.m_pos = Vector3(0, 0, -510);
//
//	bool hitpla = false;
//	//hitpla = collPlane.SphereInPlane(collPlane.sp.m_pos, collPlane.sp.m_radius, collPlane.sp, collPlane.cd);
//	//cout << pla->sp.m_pos << endl;
//	//hitpla = pla->SphereInPlane(pla->sp.m_pos, pla->sp.m_radius, pla->sp, &pla->cd);
//	//if (hitpla) {cout << "SIP :" << hitpla << endl;}
//
//	///////////////////AABB-COLLISION////////////////////////////////
//
//	//Note : Giving the dimension for the cube explicitly - Too lazy to have a pointer and stuff. (Actually dont wanna make it messy.)
//	psys->cAB0.halfdims = Vector3(20, 10, 10);
//	psys->cAB1.halfdims = Vector3(10, 20, 20);
//	bool hitAABB = false;
//	hitAABB = psys->AABBCollision(psys->cAB0, psys->cAB1);
//	if (hitAABB) {cout << "AABB :" << hitAABB << endl;}
//	
//*/
//	//////////////////ANGULAR CALCULATION.///////////////////////////
//
////	if(isSphere) {
//
//		//m_angularVelocity = Vector3(0, 0, 0);
//		m_torque = Vector3(0, 1, 0);
//		
//
//		//Solid Sphere.
//		float Iner = (2 * PI * (radius) * (radius)) / 5;
//
//		m_invInertia = Matrix4();
//		m_invInertia.values[0] = Iner;
//		m_invInertia.values[5] = Iner;
//		m_invInertia.values[10] = Iner;
//		m_invInertia.Inverse();
//
//		m_angularAcce = m_invInertia * m_torque; /* invIner * torque */
//		m_orientation = m_orientation * m_orientation.EulerAnglesToQuaternion(m_angularVelocity.x*msec, m_angularVelocity.y*msec, m_angularVelocity.z*msec);
//
////	}
//
//
//	/////////////////////////////////////CUBOID CALCULATIONS/////////////////////////
//	/////////////////////////////////////////////////////////////////////////////////
//	////if(isCuboid) {
//
//	//	//For Solid Cuboid.
//	//	m_angularVelocity = Vector3(0, 0, 0);
//	//	m_torque = Vector3(10, 0, 0);
//
//	//	/*float Inxx = 1/12 * mass * (height*height + width*width);
//	//	float Inyy = 1/12 * mass * (lenght*lenght + width*width);
//	//	float Inzz = 1/12 * mass * (height*height + lenght*lenght);*/
//	//	
//	//	//Trying with some basic test values.
//	//	float Inxx = 3333;
//	//	float Inyy = 3333;
//	//	float Inzz = 3333;
//
//	//	m_invInertia = Matrix4();
//	//	m_invInertia.values[0] = Inxx;
//	//	m_invInertia.values[5] = Inyy;
//	//	m_invInertia.values[10] = Inzz;
//	//	m_invInertia.Inverse();
//
//	//	m_angularAcce = m_invInertia * m_torque; /* invIner * torque */
//
//	//	m_angularVelocity = m_angularVelocity + m_angularAcce * msec;
//	//	//m_position = m_position;
//
//	//	// Vector3 halfAngularSpin = m_angularVelocity*msec*0.5; -- Next method.
//	//	// Interchange x and y.
//	//	m_orientation = m_orientation * m_orientation.EulerAnglesToQuaternion(m_angularVelocity.x*msec, m_angularVelocity.y*msec, m_angularVelocity.z*msec);
//	//
//	//
//	//
//	//	//m_orientation = m_orientation * m_orientation.EulerAnglesToQuaternion(m_position.x, m_position.y, m_position.z);
//	//	//m_orientation = m_orientation + m_orientation*Quaternion(halfAngularSpin.x, halfAngularSpin.y, halfAngularSpin.z, 0);
//	////}
//
//
//	///////////////////////////////////////////////////////////////////
//
//		m_angularAcce -= m_angularAcce  * 0.4;
//
//
//		IntergrateGravity(msec);

		if(target) {
			target->SetTransform(BuildTransform());
		}
}


//void PhysicsNode::IntergrateGravity(float dt)
//{
//	
//	//Gravity & Friction.
//	m_linearVelocity = m_linearVelocity + (Vector3(0, -9.81, 0)) * dt;
//	m_position = m_position + m_linearVelocity *dt; //* msec;
//
//	//m_linearVelocity = m_linearVelocity * DAMP_FACTOR;
//
//	if(m_position.y < 0)
//	{
//		m_position.y = 0;
//		//m_linearVelocity = m_linearVelocity - (Vector3(10,10,10) * dt);
//		//m_linearVelocity.x = m_linearVelocity.x * 0.6;
//		//m_linearVelocity.z = m_linearVelocity.z * 0.6;
//	}
//
//}

/*
This function simply turns the orientation and position
of our physics node into a transformation matrix, suitable
for plugging into our Renderer!

It is cleaner to work with matrices when it comes to rendering,
as it is what shaders expect, and allow us to keep all of our
transforms together in a single construct. But when it comes to
physics processing and 'game-side' logic, it is much neater to
have seperate orientations and positions.

*/
Matrix4		PhysicsNode::BuildTransform() {
	Matrix4 m = m_orientation.ToMatrix();

	m.SetPositionVector(m_position);

	return m;
}