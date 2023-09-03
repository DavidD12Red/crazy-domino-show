#pragma once
#include "BasicActors.h"
#include "PhysicsEngine.h"
#include "Extras/Renderer.h"

#include <vector>


namespace PhysicsEngine
{
	class Ball
	{
	private:
		const PxVec3 color = PxVec3(46.f / 255.f, 9.f / 255.f, 39.f / 255.f);

	public:
		Sphere* ball;
		PxMaterial* material;
		PxVec3* originalPosition;
		PxReal ballForce = 20;

		Ball(Scene* scene, PxVec3* position, float size);
		~Ball();
		void Reset();
		void addForce(PxVec3 force);
	};

	class DominoPiece
	{
	private:
		const PxVec3 color = PxVec3(217.f / 255.f, 0.f / 255.f, 0.f / 255.f);

	public:
		Box* piece;
		PxMaterial* material;
		PxVec3* piecePosition;
		PxQuat pieceRotation;

		DominoPiece(Scene* scene, PxVec3* position);
		~DominoPiece();
		void Reset();
	};

	class PlatformTile
	{
	public:
		Box* tile;
		PxMaterial* material;

		PlatformTile(Scene* scene, PxVec3* position, PxVec3* scale, PxVec3 color);
		~PlatformTile();
	};

	class WreckingBall
	{
	private:
		const PxVec3 color1 = PxVec3(255.f / 255.f, 45.f / 255.f, 0.f / 255.f);
		const PxVec3 color2 = PxVec3(255.f / 255.f, 140.f / 255.f, 54.f / 255.f);

	public:
		float moveSpeed = 0.975f;
		float linkDistance = 1.5f;
		PxReal ballMass = 15.f;
		vector<PxVec3> originalPositions;
		vector<PxQuat> originalRotations;
		vector<Box*> boxes;
		vector<RevoluteJoint*> joints;
		bool isMove = false;
		bool isReset = false;
		bool isStart = false;
		bool isReverse = false;

		WreckingBall(Scene* scene, PxVec3* position, int links, bool reverse);
		~WreckingBall();
		void Update();
		void Reset();
	};
}

