#pragma once

#include "PxPhysicsAPI.h"
#include "Exception.h"
#include "Extras\UserData.h"
#include <string>
#include <vector>

namespace PhysicsEngine
{
	using namespace physx;
	using namespace std;
	
	///Initialise PhysX framework
	void PxInit();

	///Release PhysX resources
	void PxRelease();

	///Get the PxPhysics object
	PxPhysics* GetPhysics();

	///Get the cooking object
	PxCooking* GetCooking();

	///Get the specified material
	PxMaterial* GetMaterial(PxU32 index=0);

	///Create a new material
	PxMaterial* CreateMaterial(PxReal sf=.0f, PxReal df=.0f, PxReal cr=.0f);

	static const PxVec3 default_color(.8f,.8f,.8f);

	///Abstract Actor class
	///Inherit from this class to create your own actors
	class Actor
	{
	protected:
		PxActor* actor;
		std::vector<PxVec3> colors;
		std::string name;
		PxReal mass;

	public:
		///Constructor
		Actor()
			: actor(0)
		{
		}

		PxActor* Get();

		// Set color
		void Color(PxVec3 new_color, PxU32 shape_index=-1);

		// Get color
		const PxVec3* Color(PxU32 shape_indx=0);

		void Actor::Name(const string& name);

		string Actor::Name();

		// Set Material
		void Material(PxMaterial* new_material, PxU32 shape_index=-1);

		PxShape* GetShape(PxU32 index=0);

		std::vector<PxShape*> Actor::GetShapes(PxU32 index=-1);

		virtual void CreateShape(const PxGeometry& geometry, PxReal density) {}

		void SetTrigger(bool value, PxU32 index=-1);

		void SetupFiltering(PxU32 filterGroup, PxU32 filterMask, PxU32 shape_index=-1);

		void SetMass(PxReal mass);

		PxReal GetMass();

		void SetPosition(PxVec3 position);

		PxVec3 GetPosition();

		void SetRotation(PxQuat rotation);

		PxQuat GetRotation();

		PxVec3 GetVelocity();

		PxRigidBody* GetRigidBody();
	};

	class DynamicActor : public Actor
	{
	public:
		DynamicActor(const PxTransform& pose);

		~DynamicActor();

		void CreateShape(const PxGeometry& geometry, PxReal density);

		void SetKinematic(bool value, PxU32 index=-1);
	};

	class StaticActor : public Actor
	{
	public:
		StaticActor(const PxTransform& pose);

		~StaticActor();

		void CreateShape(const PxGeometry& geometry, PxReal density=0.f);
	};

	///Generic scene class
	class Scene
	{
	protected:
		//a PhysX scene object
		PxScene* px_scene;
		//pause simulation
		bool pause;
		//selected dynamic actor on the scene
		PxRigidDynamic* selected_actor;
		//original and modified colour of the selected actor
		std::vector<PxVec3> sactor_color_orig;
		//custom filter shader
		PxSimulationFilterShader filter_shader;

		void HighlightOn(PxRigidDynamic* actor);

		void HighlightOff(PxRigidDynamic* actor);

	public:
		Scene(PxSimulationFilterShader custom_filter_shader=PxDefaultSimulationFilterShader) : filter_shader(custom_filter_shader) {}

		///Init the scene
		void SceneInit();

		///User defined initialisation
		virtual void CustomInit() {}

		///Perform a single simulation step
		void SceneUpdate(PxReal dt);

		///User defined update step
		virtual void CustomUpdate() {}

		///Add actors
		void Add(Actor* actor);

		///Get the PxScene object
		PxScene* Get();

		///Reset the scene
		void Reset();

		///Set pause
		void Pause(bool value);

		///Get pause
		bool Pause();

		///Get the selected dynamic actor on the scene
		PxRigidDynamic* GetSelectedActor();

		///Switch to the next dynamic actor
		void SelectNextActor();

		///a list with all actors
		std::vector<PxActor*> GetAllActors();
	};

	///Generic Joint class
	class Joint
	{
	protected:
		PxJoint* joint;

	public:
		Joint() : joint(0) {}

		PxJoint* Get() { return joint; }
	};


}

