#include "AdvancedActors.h"

namespace PhysicsEngine
{
	Ball::Ball(Scene* scene, PxVec3* position, float size)
	{
		originalPosition = position;
		ball = new Sphere(PxTransform(PxVec3(position->x, position->y, position->z)), size, 15.f);
		material = scene->Get()->getPhysics().createMaterial(0.f, 10.f, 0.8f);
		ball->Material(material);
		ball->Color(color);
		ball->SetMass((5.f));
		scene->Add(ball);
	}

	Ball::~Ball()
	{
		delete ball;
	}

	void Ball::Reset()
	{
		ball->SetPosition(PxVec3(originalPosition->x, originalPosition->y, originalPosition->z));
		ball->GetRigidBody()->setLinearVelocity(PxVec3(0, 0, 0));
		ball->GetRigidBody()->setAngularVelocity(PxVec3(0, 0, 0));
	}

	void Ball::addForce(PxVec3 force)
	{
		ball->GetRigidBody()->addForce(ballForce * force);
	}
}

