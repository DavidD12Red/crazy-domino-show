#include "AdvancedActors.h"

namespace PhysicsEngine
{
	PlatformTile::PlatformTile(Scene* scene, PxVec3* position, PxVec3* scale, PxVec3 color)
	{
		tile = new Box(PxTransform(PxVec3(position->x, position->y, position->z), PxQuat(0.f, PxVec3(0.f, 1.f, 0.f))), PxVec3(scale->x, scale->y, scale->z));
		tile->SetKinematic(true);
		tile->Color(color);
		material = scene->Get()->getPhysics().createMaterial(0, 1.f, 0);
		tile->Material(material);

		scene->Add(tile);
	}

	PlatformTile::~PlatformTile()
	{
		delete tile;
	}
}