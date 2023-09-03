#include "DominoScene.h"

namespace PhysicsEngine
{
	// A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	PxFilterFlags DominoScene::CustomFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
	{
		// Let triggers through
		if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		// Enable continous collision detection
		pairFlags = PxPairFlag::eSOLVE_CONTACT;
		pairFlags |= PxPairFlag::eDETECT_DISCRETE_CONTACT;
		pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT;

		// Trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			// Trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
		}

		return PxFilterFlags();
	};

	DominoScene::DominoScene() : Scene(CustomFilterShader)
	{
	}

	DominoScene::~DominoScene()
	{
		// Delete movable ball
		delete ball;

		// Delete wrecking balls
		for (auto* wball : wreckingBalls)
		{
			delete wball;
		}

		// Delete platform tiles
		for (auto* tile : platformTiles)
		{
			delete tile;
		}

		// Delete dominos
		for (auto* domino : dominoPieces)
		{
			delete domino;
		}
	}

	void DominoScene::SetVisualisation()
	{
		// Scale and shape
		px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.f);
		px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.f);

		// Cloth
		px_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_HORIZONTAL, 1.f);
		px_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_VERTICAL, 1.f);
		px_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_BENDING, 1.f);
		px_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_SHEARING, 1.f);
	}

	void DominoScene::CustomInit()
	{
		SetVisualisation();

		// Enable customised collision detection
		px_scene->setFlag(PxSceneFlag::eENABLE_CCD, true);

		// Create a movable ball
		ball = new Ball(this, new PxVec3(0.f, 3.f, 0.f), 2.f);

		// Create wrecking balls
		float wreckingBallPositionZ = -50.f;
		for (unsigned i = 0; i < 20; i++)
		{
			// Check if number is even
			if (i % 2 == 0)
			{
				wreckingBalls.push_back(new WreckingBall(this, new PxVec3(5.f, 15.f, wreckingBallPositionZ), 7, false));
			}
			else
			{
				wreckingBalls.push_back(new WreckingBall(this, new PxVec3(-5.f, 15.f, wreckingBallPositionZ), 7, true));
			}

			wreckingBallPositionZ -= 8.f;
		}

		// Create floor tiles
		float gap = -18.f;
		for (unsigned i = 0; i < 20; i++)
		{
			platformTiles.push_back(new PlatformTile(this, new PxVec3(-12.f, 0.3f, i * gap), new PxVec3(6.f, 0.5, 9.f), tileColor));
			platformTiles.push_back(new PlatformTile(this, new PxVec3(0.f, 0.3f, i * gap), new PxVec3(6.f, 0.5, 9.f), tileColor));
			platformTiles.push_back(new PlatformTile(this, new PxVec3(12.f, 0.3f, i * gap), new PxVec3(6.f, 0.5, 9.f), tileColor));
		}

		// Create the domino pieces
		float dominoPositionZ = -50.f;
		for (unsigned i = 0; i < 30; i++)
		{
			dominoPieces.push_back(new DominoPiece(this, new PxVec3(0.f, 5.f, dominoPositionZ)));
			dominoPositionZ -= 5.f;
		}
	}

	void DominoScene::CustomUpdate()
	{
		for (int i = 0; i < wreckingBalls.size(); i++)
		{
			wreckingBalls[i]->Update();
		}
	}
}
