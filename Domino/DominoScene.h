#pragma once
#include "BasicActors.h"
#include "AdvancedActors.h"

#include <vector>

namespace PhysicsEngine
{

	class DominoScene : public Scene
	{
	private:
		const PxVec3 tileColor = PxVec3(4.f / 255.f, 117.f / 255.f, 111.f / 255.f);

		static PxFilterFlags CustomFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
			PxFilterObjectAttributes attributes1, PxFilterData filterData1,
			PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);

	public:
		Ball* ball;
		vector<WreckingBall*> wreckingBalls;
		vector<DominoPiece*> dominoPieces;
		vector<PlatformTile*> platformTiles;

		DominoScene();
		~DominoScene();
		void SetVisualisation();
		virtual void CustomInit();
		virtual void CustomUpdate();
	};
}

