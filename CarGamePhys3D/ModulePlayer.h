#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "glmath.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 250.0f
#define MAX_VELOCITY 200.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	vec3 GetSavedPosition();
	void SetSavedPosition(vec3 pos);
	btQuaternion GetSavedRotation();
	void SetSavedRotation(btQuaternion rotation);
	void SetPosition(int x, int y, int z);
	void SetRotation(btQuaternion rot);
	float GetVehicleSpeed();
	vec3 GetPosition();
	vec3 GetUpwardPosition();
	PhysBody3D* GetVehicle();

public:

	float max_height = 0;
private:
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	float offset_x = 0;
	float speed;
	vec3 saved_position = { -175, 1, 190 };
	btQuaternion saved_rotation;
};