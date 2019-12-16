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

	p2DynArray <Primitive> ramp_1 = App->physics->AddRamp({ 5, 14 , 0 }, 16, 12, false);

	for (int i = 0; i < ramp_1.Count(); i++)
	{
		scene_elements.PushBack(ramp_1[i]);
	}

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->physics->AddRamp({ 5, 28 , 0 }, 30, 8);
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
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();


	for (int i = 0; i < scene_elements.Count(); i++)
	{
		scene_elements[i].axis = true;
		scene_elements[i].Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

