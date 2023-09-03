#include "AdvancedActors.h"

namespace PhysicsEngine
{
	DominoPiece::DominoPiece(Scene* scene, PxVec3* position)
	{
		piece = new Box(PxTransform(PxVec3(position->x, position->y, position->z)), PxVec3(1.f, 3.f, 0.3f));
		material = scene->Get()->getPhysics().createMaterial(0.f, 1.f, 0.f);
		piece->Color(color);
		piece->Material(material);
		piece->SetMass(10.f);
		piecePosition = position;
		pieceRotation = piece->GetRotation();

		scene->Add(piece);
	}

	DominoPiece::~DominoPiece()
	{
		delete piece;
	}

	void DominoPiece::Reset()
	{
		piece->GetRigidBody()->setLinearVelocity(PxVec3(0.f, 0.f, 0.f));
		piece->GetRigidBody()->setAngularVelocity(PxVec3(0.f, 0.f, 0.f));
		piece->SetPosition(PxVec3(piecePosition->x, piecePosition->y, piecePosition->z));
		piece->SetRotation(pieceRotation);
	}
}
