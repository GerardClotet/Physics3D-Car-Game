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

	//total_time = new Timer();

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
			score += 150;
			break;
		case PhysBody3D::type::CHECKPOINT: {
			App->player->SetSavedPosition(body2->GetPos());
			btQuaternion rotation(body2->GetRotation().getAxis(), body2->GetRotation().getAngle());
			App->player->SetSavedRotation(rotation);
		}break;
		default:
			break;
		}
	}
}

void ModuleSceneIntro::CreateMap()
{

	Cube way1(50, 0.2F, 400);
	way1.color = White;
	way1.SetPos(-170, 0, 0);
	scene_terrain.PushBack(way1);

	Cube wall11(2, 6, 400);
	wall11.color = DarkGray;
	wall11.SetPos(-192, 3, 0);
	scene_terrain.PushBack(wall11);
	App->physics->AddBody(wall11, 0);

	Cube wall12(2, 6, 375);
	wall12.color = DarkGray;
	wall12.SetPos(-150, 3, 10);
	scene_terrain.PushBack(wall12);
	App->physics->AddBody(wall12, 0);

	btQuaternion rot({ 0, 1, 0 }, 0.5 * 3.14);
	CreateCheckPoint({ -145, 0, -189 }, { 20, 4, 5 }, rot);

	Cube way2(80, 0.2F, 25);
	way2.color = White;
	way2.SetPos(-165, 0, -187.5F);
	scene_terrain.PushBack(way2);

	Cube wall21(25, 6, 2);
	wall21.color = DarkGray;
	wall21.SetPos(-138, 3, -178);
	scene_terrain.PushBack(wall21);
	App->physics->AddBody(wall21, 0);

	Cube wall22(125, 6, 2);
	wall22.color = DarkGray;
	wall22.SetPos(-135, 3, -200);
	scene_terrain.PushBack(wall22);
	App->physics->AddBody(wall22, 0);

	Cube way3(50, 0.2F, 400);
	way3.color = White;
	way3.SetPos(-100, 0, 0);
	scene_terrain.PushBack(way3);

	Cube wall31(2, 6, 380);
	wall31.color = DarkGray;
	wall31.SetPos(-125, 3, 12);
	scene_terrain.PushBack(wall31);
	App->physics->AddBody(wall31, 0);

	Cube wall32(2, 6, 380);
	wall32.color = DarkGray;
	wall32.SetPos(-75, 3, -12);
	scene_terrain.PushBack(wall32);
	App->physics->AddBody(wall32, 0);

	rot.setRotation({ 0, 1, 0 }, 0);
	CreateCheckPoint({ -100, 0, 155 }, { 45, 4, 5 }, rot);

	Cube way4(100, 0.2F, 25);
	way4.color = White;
	way4.SetPos(-100, 0, 187.5F);
	scene_terrain.PushBack(way4);

	Cube wall41(25, 6, 2);
	wall41.color = DarkGray;
	wall41.SetPos(-63, 3, 178);
	scene_terrain.PushBack(wall41);
	App->physics->AddBody(wall41, 0);

	Cube wall42(125, 6, 2);
	wall42.color = DarkGray;
	wall42.SetPos(-63, 3, 200);
	scene_terrain.PushBack(wall42);
	App->physics->AddBody(wall42, 0);

	Cube way5(50, 0.2F, 400);
	way5.color = White;
	way5.SetPos(-30, 0, 0);
	scene_terrain.PushBack(way5);

	Cube wall51(2, 6, 380);
	wall51.color = DarkGray;
	wall51.SetPos(-55, 3, -12);
	scene_terrain.PushBack(wall51);
	App->physics->AddBody(wall51, 0);

	Cube wall52(2, 6, 380);
	wall52.color = DarkGray;
	wall52.SetPos(-5, 3, 12);
	scene_terrain.PushBack(wall52);
	App->physics->AddBody(wall52, 0);

	rot.setRotation({ 0, 1, 0 }, 0.5 * 3.14);
	CreateCheckPoint({ 0, 0, -189 }, { 20, 4, 5 }, rot);

	Cube way6(80, 0.2F, 25);
	way6.color = White;
	way6.SetPos(35, 0, -187.5F);
	scene_terrain.PushBack(way6);

	Cube wall61(25, 6, 2);
	wall61.color = DarkGray;
	wall61.SetPos(5, 3, -178);
	scene_terrain.PushBack(wall61);
	App->physics->AddBody(wall61, 0);

	Cube wall62(125, 6, 2);
	wall62.color = DarkGray;
	wall62.SetPos(7, 3, -200);
	scene_terrain.PushBack(wall62);
	App->physics->AddBody(wall62, 0);

	Cube way7(50, 0.2F, 400);
	way7.color = White;
	way7.SetPos(40, 0, 0);
	scene_terrain.PushBack(way7);

	Cube wall71(2, 6, 380);
	wall71.color = DarkGray;
	wall71.SetPos(15, 3, 12);
	scene_terrain.PushBack(wall71);
	App->physics->AddBody(wall71, 0);

	Cube wall72(2, 6, 380);
	wall72.color = DarkGray;
	wall72.SetPos(65, 3, -12);
	scene_terrain.PushBack(wall72);
	App->physics->AddBody(wall72, 0);

	//CreateCheckPoint({ 100, 0, 185 });

	Cube way8(100, 0.2F, 25);
	way8.color = White;
	way8.SetPos(100, 0, 187.5F);
	scene_terrain.PushBack(way8);

	Cube wall81(25, 6, 2);
	wall81.color = DarkGray;
	wall81.SetPos(78, 3, 178);
	scene_terrain.PushBack(wall81);
	App->physics->AddBody(wall81, 0);

	Cube wall82(200, 6, 2);
	wall82.color = DarkGray;
	wall82.SetPos(100, 3, 200);
	scene_terrain.PushBack(wall82);
	App->physics->AddBody(wall82, 0);

	Cube way9(200, 0.2F, 400);
	way9.color = White;
	way9.SetPos(100, 0, 0);
	scene_terrain.PushBack(way9);

	Cube wall91(2, 6, 380);
	wall91.color = DarkGray;
	wall91.SetPos(90, 3, -12);
	scene_terrain.PushBack(wall91);
	App->physics->AddBody(wall91, 0);

	Cube wall92(2, 6, 400);
	wall92.color = DarkGray;
	wall92.SetPos(200, 3, 0);
	scene_terrain.PushBack(wall92);
	App->physics->AddBody(wall92, 0);

	Cube wall10(200, 6, 2);
	wall10.color = DarkGray;
	wall10.SetPos(100, 3, -200);
	scene_terrain.PushBack(wall10);
	App->physics->AddBody(wall10, 0);

	floor = { 400, 0, 400 };
	floor.color = DarkGray;
	scene_terrain.PushBack(floor);

	p2DynArray <Cube> ramp_1 = App->physics->AddRamp({ -175, 48 , 140 }, 50, 9, false);

	for (int i = 0; i < ramp_1.Count(); i++)
	{
		scene_terrain.PushBack(ramp_1[i]);
	}

	p2DynArray <Cube> reception_1 = App->physics->AddRamp({ -175, 68 , 30 }, 70, 8, false, 1, 20, 3, 7);

	for (int i = 0; i < reception_1.Count(); i++)
	{
		scene_terrain.PushBack(reception_1[i]);
	}

	p2DynArray <Cube> ramp_2 = App->physics->AddRamp({ -175, 16.5F , -50 }, 18, 87, true);

	for (int i = 0; i < ramp_2.Count(); i++)
	{
		scene_terrain.PushBack(ramp_2[i]);
	}

	p2DynArray <Cube> ramp_3 = App->physics->AddRamp({ -100, 16.5F , -140 }, 18, 87, true);

	for (int i = 0; i < ramp_3.Count(); i++)
	{
		scene_terrain.PushBack(ramp_3[i]);
	}

	p2DynArray <Cube> ramp_4 = App->physics->AddRamp({ -100, 48 , -100 }, 50, 9, false, 1, 20, 3, 7);

	for (int i = 0; i < ramp_4.Count(); i++)
	{
		scene_terrain.PushBack(ramp_4[i]);
	}

	//p2DynArray <Cube> ramp_3 = App->physics->AddRamp({ -0, 48 , 0 }, 50, 500, true);

	//for (int i = 0; i < ramp_3.Count(); i++)
	//{
	//	scene_terrain.PushBack(ramp_3[i]);
	//}

	CreateScorePoints({ -175, 1, 120 }, 4, 15);
	CreateScorePoints({ -175, 1, -15 }, 3, 15);
	CreateScorePoints({ -175, 1, -70 }, 3, 15);
	CreateScorePoints({ -100, 40, -25 }, 3, 15);
	CreateScorePoints({ -25, 26, -25 }, 3, 15);
	CreateScorePoints({ 100, 1, 0 }, 3, 15);

	p2DynArray <Cube> reception_2 = App->physics->AddRamp({ -100, 68 , 70 }, 70, 7, false, 0, 40, 3, 5);

	for (int i = 0; i < reception_2.Count(); i++)
	{
		scene_terrain.PushBack(reception_2[i]);
	}

	p2DynArray <Cube> ramp_5 = App->physics->AddRamp({ -30, 48 , 70 }, 50, 7, false, 0, 40, 3, 5);

	for (int i = 0; i < ramp_5.Count(); i++)
	{
		scene_terrain.PushBack(ramp_5[i]);
	}

	p2DynArray <Cube> reception_3 = App->physics->AddRamp({ -30, 68 , -100 }, 70, 7, false, 1, 40, 3, 7);

	for (int i = 0; i < reception_3.Count(); i++)
	{
		scene_terrain.PushBack(reception_3[i]);
	}


	p2DynArray <Cube> ramp_6 = App->physics->AddRamp({ 40, 16.5F , -140 }, 18, 87, true);

	for (int i = 0; i < ramp_6.Count(); i++)
	{
		scene_terrain.PushBack(ramp_6[i]);
	}

	p2DynArray <Cube> ramp_7 = App->physics->AddRamp({ 40, 48 , -100 }, 50, 9, false, 1, 20, 3, 7);

	for (int i = 0; i < ramp_7.Count(); i++)
	{
		scene_terrain.PushBack(ramp_7[i]);
	}

	p2DynArray <Cube> reception_4 = App->physics->AddRamp({ 40, 68 , 70 }, 70, 7, false, 0, 40, 3, 5);

	for (int i = 0; i < reception_4.Count(); i++)
	{
		scene_terrain.PushBack(reception_4[i]);
	}

	p2DynArray <Cube> ramp_8 = App->physics->AddRamp({ 40, 16.5F , 120 }, 18, 87, true);

	for (int i = 0; i < ramp_8.Count(); i++)
	{
		scene_terrain.PushBack(ramp_8[i]);
	}

	p2DynArray <Cube> ramp_9 = App->physics->AddRamp({ 120, 69 , 160 }, 70, 25, false, 1, 160, 3, 7);

	for (int i = 0; i < ramp_9.Count(); i++)
	{
		scene_terrain.PushBack(ramp_9[i]);
	}

	p2DynArray <Cube> ramp_10 = App->physics->AddRamp({ 148, 69 , 70 }, 70, 12, false, 0, 100, 3, 5);

	for (int i = 0; i < ramp_10.Count(); i++)
	{
		scene_terrain.PushBack(ramp_10[i]);
	}

}

void ModuleSceneIntro::CreateTerrain()
{
}

void ModuleSceneIntro::CreateRamps()
{
}

void ModuleSceneIntro::CreateScorePoints(vec3 starting_position, uint num_points, uint pos_incr)
{
	for (int i = 0; i < num_points; i++)
	{
		Cube points(2, 2, 2);
		points.color = Yellow;
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

void ModuleSceneIntro::CreateCheckPoint(vec3 pos, vec3 size, btQuaternion rotation)
{
	PhysBody3D* checkpoint = App->physics->AddBody(Cube(size.x, size.y, size.z), 0);
	checkpoint->SetAsSensor(true);
	checkpoint->SetType(PhysBody3D::type::CHECKPOINT);
	checkpoint->SetPos(pos.x, pos.y, pos.z);
	checkpoint->SetRotation(rotation);
}