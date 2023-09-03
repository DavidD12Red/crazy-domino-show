#include "AdvancedActors.h"

namespace PhysicsEngine
{
	WreckingBall::WreckingBall(Scene* scene, PxVec3* position, int links, bool reverse)
	{
		isReverse = reverse;

		for (auto i = 0; i < links; i++)
		{
			boxes.push_back(new Box(PxTransform(PxVec3(position->x, position->y - (1.5f * i), position->z))));
			originalRotations.push_back(boxes[i]->GetRotation());
			originalPositions.push_back(boxes[i]->GetPosition());

			if (i != 0)
			{
				boxes[i]->Color(color1);

				if (i == links - 1)
				{
					joints.push_back(new RevoluteJoint(boxes[i - 1], PxTransform(PxVec3(0.f, -linkDistance - 0.5f, 0.f)), boxes[i], PxTransform(PxVec3(0.f, 0.f, 0.f))));
					boxes[i]->GetShape()->setGeometry(PxBoxGeometry(2.f, 2.f, 2.f));
					boxes[i]->SetMass(ballMass);
				}
				else
				{
					if ((i % 2) == 0 && i != 2)
						joints.push_back(new RevoluteJoint(boxes[i - 1], PxTransform(PxVec3(0.f, -linkDistance, 0.f)), boxes[i], PxTransform(PxVec3(0.f, 0.f, 0.f))));
					else
						joints.push_back(new RevoluteJoint(boxes[i - 1], PxTransform(PxVec3(0.f, -linkDistance, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))), boxes[i], PxTransform(PxVec3(0.f, 0.f, 0.f))));
				}
			}
			else
			{
				boxes[i]->Color(color2);
				boxes[i]->SetKinematic(true);
			}

			scene->Add(boxes[i]);
		}
	}

	WreckingBall::~WreckingBall()
	{
		for (auto* box : boxes)
		{
			delete box;
		}

		for (auto* joint : joints)
		{
			delete joint;
		}
	}

	void WreckingBall::Update()
	{
		if (isMove)
		{
			if (boxes[1]->GetRotation().z > 0.5f)
				joints[0]->DriveVelocity(moveSpeed);
			else if (boxes[1]->GetRotation().z < -0.5f)
				joints[0]->DriveVelocity(-moveSpeed);

			isReset = false;
		}
		else if (isStart)
		{
			if (isReverse)
				joints[0]->DriveVelocity(-moveSpeed);
			else
				joints[0]->DriveVelocity(moveSpeed);

			isStart = false;
			isMove = true;
		}
		else
		{
			Reset();
		}

	}

	void WreckingBall::Reset()
	{
		joints[0]->DriveVelocity(0.f);

		for (unsigned i = 0; i < boxes.size(); i++)
		{
			boxes[i]->SetPosition(originalPositions[i]);
			boxes[i]->SetRotation(originalRotations[i]);
		}

		isReset = true;
		isStart = false;
		isMove = false;
	}
}

