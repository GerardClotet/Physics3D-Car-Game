#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	CreateMap();

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->physics->AddRamp({ 20, 9.6f , 0 }, 11, 12);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	for (int i = 0; i < scene_terrain.Count(); i++)
	{
		scene_terrain[i].Render();
	}

	for (int i = 0; i < scene_points.Count(); i++)
	{
		scene_points[i].Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->active && body2->active)
	{
		switch (body2->GetType())
		{
		case PhysBody3D::type::POINT:
			DestroyScorePoint(body2);
			App->physics->DestroyBody(body2);
			LOG("LUL");
			break;
		default:
			break;
		}
	}
}

void ModuleSceneIntro::CreateMap()
{

	p2DynArray <Cube> ramp_1 = App->physics->AddRamp({ -180, 48 , 140 }, 50, 9, false);

	for (int i = 0; i < ramp_1.Count(); i++)
	{
		scene_terrain.PushBack(ramp_1[i]);
	}

	p2DynArray <Cube> reception_1 = App->physics->AddRamp({ -180, 68 , 30 }, 70, 8, false, 1, 20, 3, 7);

	for (int i = 0; i < reception_1.Count(); i++)
	{
		scene_terrain.PushBack(reception_1[i]);
	}

	p2DynArray <Cube> ramp_2 = App->physics->AddRamp({ -180, 16 , 0 }, 18, 87, true);

	for (int i = 0; i < ramp_2.Count(); i++)
	{
		scene_terrain.PushBack(ramp_2[i]);
	}

	p2DynArray <Cube> ramp_3 = App->physics->AddRamp({ -0, 48 , 0 }, 50, 500, true);

	for (int i = 0; i < ramp_3.Count(); i++)
	{
		scene_terrain.PushBack(ramp_3[i]);
	}

	CreateScorePoints({ -180, 1, 120 }, 4, 15);
	CreateScorePoints({ -180, 1, -15 }, 3, 15);

	Cube way1(20, 0, 400);
	way1.color.Set(128, 0, 0, 1.F);
	way1.SetPos(-180, 0, 0);
	scene_terrain.PushBack(way1);



	floor = { 400, -1, 400 };
	floor.color.Set(125, 125, 125, 0.25F);
	scene_terrain.PushBack(floor);
}

void ModuleSceneIntro::CreateScorePoints(vec3 starting_position, uint num_points, uint pos_incr)
{
	for (int i = 0; i < num_points; i++)
	{
		Cube points(2, 2, 2);
		points.color.Set(128, 128, 0, 1.F);
		points.SetPos(starting_position.x, starting_position.y, starting_position.z + pos_incr);
		scene_points.PushBack(points);
		PhysBody3D* sensor = App->physics->AddBody(points, 0);
		sensor->SetAsSensor(true);
		pos_incr += 15;
		sensor->SetType(PhysBody3D::type::POINT);
		scene_points_pb.PushBack(sensor);
	}
}

void ModuleSceneIntro::DestroyScorePoint(PhysBody3D* point)
{
	for (int i = 0; i < scene_points_pb.Count(); i++)
	{
		if (scene_points_pb[i] == point)
		{
			scene_points.Pop(scene_points[i]);
			scene_points_pb.Pop(scene_points_pb[i]);
		}
	}
}