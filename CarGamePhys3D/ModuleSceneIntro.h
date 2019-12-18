#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"


struct PhysBody3D;
struct PhysMotor3D;
class btQuaternion;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateMap();
	void CreateTerrain();
	void CreateRamps();
	void CreateScorePoints(vec3 starting_position, uint num_points, uint pos_incr);
	void CreateAllScorePoints();
	void ResetScorePoints();
	void DestroyScorePoint(PhysBody3D* point);
	void CreateCheckPoint(vec3 pos, vec3 size, btQuaternion rotation);
	int GetTotalScore();
	void Win();
	void Lose();
	void Restart();
	bool on_win_scene = false;

private:

	uint score = 0;
	Cube floor;
	unsigned int coin_fx;
	unsigned int win_fx;

	p2DynArray <Cube> scene_terrain;
	p2DynArray <Cube> scene_points;
	p2DynArray <PhysBody3D*> scene_points_pb;
	p2DynArray <Sphere> scene_spheres;
	p2DynArray <Cylinder> scene_cylinders;

	p2DynArray <Cube> stars;
	PhysBody3D* endsensor;

	Timer* total_time = nullptr;
	Uint32 max_time_per_level = 110;
	Uint32 time_left = 0;

	vec3 player_start_pos = { -175, 0, 190 };
	bool score_points_full = false;

};
