#include "Skyroads.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

#include "irrklang/irrKlang.h"
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();


using namespace std;

Skyroads::Skyroads()
{	
	ISound* music = SoundEngine->play2D("Source/Laboratoare/SkyroadsRemastered/The Saga Begins.mp3", false);

}

Skyroads::~Skyroads()
{
	SoundEngine->drop();
}

void Skyroads::InitVar() {
	Z_Space = -90, Y_Space_Offset = -5.5, Z_Space_Offset = -90;
	game_speed = 5; // standard_speed

	ufo_angle = 0;
	fall_angle = 0;

	center = { 0, 0, 0 };

	X_offset_pod1 = -2;
	X_offset_pod2 = -1;
	X_offset_pod3 = 0;
	X_offset_pod4 = 1;
	X_offset_pod5 = 2;

	Y_offset_pod = 0.5f;
	Z_offset_pod = 3.0f;

	jump_length = 2;
	jump_counter = 0;

	pod_sf = 0.01f;
	ufo_sf = 0.01f;
	Y_offset_ufo = 0.6;
	X_UFO = 0, Y_UFO = 0.60, Z_UFO = 0.5;
	jump_over = 0;

	// Player

	playerPos = 2; // center, 0 - left, 2 - right
	playerIsMoving = false;
	up = true;

	first_frame = true; // deltaTime is huge;

	HP_UFO = 5;

	power_fill = 1;
	power_up_down = 0.1; // percentage of power gained/drained on impact

	force_speed = 5;
	speed_lock = 0;
	speed_timer = 0;

	safe_zone_timer = 0;

	UFOaffliction = 0;
	affliction_timer = 0;
	isUFO = 0;

	framerate = 50;
	frame_counter = 0;

	randDrugs = 0;
}

void Skyroads::Init()
{
	renderCameraTarget = true;

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("space");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Skyroads/Podium/Space", "podium_space.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("ufo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Skyroads/UFO", "Low_poly_UFO.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	
	{
		Mesh* mesh = new Mesh("podium_blue");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Skyroads/Podium/Blue", "podium_blue.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("podium_green");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Skyroads/Podium/Green", "podium_green.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("podium_orange");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Skyroads/Podium/Orange", "podium_orange.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("podium_red");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Skyroads/Podium/Red", "podium_red.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("podium_yellow");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Skyroads/Podium/Yellow", "podium_yellow.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("podium_purple");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Skyroads/Podium/Purple", "podium_purple.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader* shader = new Shader("ShaderSkyroads");
		shader->AddShader("Source/Laboratoare/SkyroadsRemastered/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/SkyroadsRemastered/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	const string textureLoc = "Source/Laboratoare/SkyroadsRemastered/Textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "pluto.jpg").c_str(), GL_REPEAT);
		mapTextures["pluto"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "saturn.jpg").c_str(), GL_REPEAT);
		mapTextures["saturn"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "venus.jpg").c_str(), GL_REPEAT);
		mapTextures["venus"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "some_planet.jpg").c_str(), GL_REPEAT);
		mapTextures["some_planet"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "some_star.jpg").c_str(), GL_REPEAT);
		mapTextures["some_star"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "space.jpg").c_str(), GL_REPEAT);
		mapTextures["space"] = texture;
	}

	{
		Shader* shader = new Shader("DecorationShader");
		shader->AddShader("Source/Laboratoare/SkyroadsRemastered/Shaders/Decoration Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/SkyroadsRemastered/Shaders/Decoration Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	AddHP();
	AddPowerbar();
	GeneratePlatforms();

	AddPlanets();
	GeneratePlanets();

	AddSpace();

}

void Skyroads::AddSpace() {
	float z_start = -99.0f;
	float x_max = 150;
	float x_min = -150;
	float y_max = 100;
	float y_min = -100;
	// Create a simple quad
	vector<glm::vec3> vertices
	{
		glm::vec3(x_max, y_max, z_start),	// Top Right
		glm::vec3(x_max, y_min, z_start),	// Bottom Right
		glm::vec3(x_min, y_min, z_start),	// Bottom Left
		glm::vec3(x_min, y_max, z_start),	// Top Left
	};

	vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0)
	};

	// TODO : Complete texture coordinates for the square
	vector<glm::vec2> textureCoords
	{
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	};

	vector<unsigned short> indices =
	{
		0, 1, 3,
		1, 2, 3
	};


	Mesh* mesh = new Mesh("space");
	mesh->InitFromData(vertices, normals, textureCoords, indices);
	meshes[mesh->GetMeshID()] = mesh;
}

void Skyroads::AddPlanets() {
	Sphere sph(center, 100, 100, "sphere");
	meshes["sphere"] = sph.sphere;
}

void Skyroads::GenerateNextPlanet() {
	for (int j = 0; j < NUM_POD - 1; j++) {
		planets[j].texture = planets[j + 1].texture;
		planets[j].x = planets[j + 1].x;
		planets[j].y = planets[j + 1].y;
		planets[j].z = planets[j + 1].z;
		planets[j].sf = planets[j + 1].sf;
	}

	int rand_text = rand() % 6;
	std::string texture;
	if (rand_text == 0)
		texture = "pluto";
	else if (rand_text == 1)
		texture = "saturn";
	else if (rand_text == 2)
		texture = "venus";
	else if (rand_text == 3)
		texture = "some_star";
	else if (rand_text == 4)
		texture = "some_planet";
	else texture = "space";

	float x = rand() % 50; // 25 positive, 25 negative
	if (rand() % 2 == 0) // flip -> positive
		x += 5.0f;
	else x = -x - 5.0f;      // flip -> negative

	float sf = (rand() % 50) / 50.0f + 0.5;

	float y = rand() % 60;
	y -= 30;

	planets[NUM_POD - 1].x = x;
	planets[NUM_POD - 1].y = y;
	planets[NUM_POD - 1].z = -3 * NUM_POD;
	planets[NUM_POD - 1].texture = texture;
	planets[NUM_POD - 1].sf = sf;
}

void Skyroads::GeneratePlanets() {
	for (int i = 0; i < NUM_POD; i++) {
		int rand_text = rand() % 6;
		std::string texture;
		if (rand_text == 0)
			texture = "pluto";
		else if (rand_text == 1)
			texture = "saturn";
		else if (rand_text == 2)
			texture = "venus";
		else if (rand_text == 3)
			texture = "some_star";
		else if (rand_text == 4)
			texture = "some_planet";
		else texture = "space";

		float x = rand() % 50; // 25 positive, 25 negative
		if (rand() % 2 == 0) // flip -> positive
			x += 5.0f;
		else x = -x - 5.0f;      // flip -> negative

		float sf = (rand() % 50) / 50.0f + 0.5;

		float y = rand() % 60;
		y -= 30;

		Decoration decor(texture, x, y, -3 * i, sf);
		planets.push_back(decor);
	}
}

void Skyroads::RenderPlanets(float deltaTimeSeconds) {

	if (planets[0].z >= Z_offset_pod + 2) {
		GenerateNextPlanet();
	}

	for (int i = 0; i < NUM_POD; i++) {
		planets[i].z += game_speed * deltaTimeSeconds;

		if (planets[i].texture != "space") { // platform exists at given i

			glm::mat4 modelMatrix = glm::mat4(1);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(planets[i].x, planets[i].y, planets[i].z));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(planets[i].sf));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(1, 0, 0));

			std::string object = "podium_" + planets[i].texture;
			RenderMesh(meshes["sphere"], shaders["DecorationShader"], modelMatrix, "sphere",
				mapTextures[planets[i].texture]);
		}
	}
}

void Skyroads::AddHP() {
	HP hp(center, WHITE, PINK);
	AddMeshToList(hp.H);
	AddMeshToList(hp.P);
	AddMeshToList(hp.Life);
}

void Skyroads::AddPowerbar() {
	Powerbar power_bar("powerbar", center, TURQOISE);
	AddMeshToList(power_bar.emptybar);
	AddMeshToList(power_bar.fullbar);
}

void Skyroads::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Skyroads::GenerateNextPod() {
	for (int i = 0; i < NUM_PLATFORMS; i++)
		for (int j = 0; j < NUM_POD - 1; j++) {
			platforms[i][j].color = platforms[i][j + 1].color;
			platforms[i][j].collided = platforms[i][j + 1].collided;
			platforms[i][j].x = platforms[i][j + 1].x;
			platforms[i][j].y = platforms[i][j + 1].y;
			platforms[i][j].z = platforms[i][j + 1].z;
		}

	std::vector<std::string> colors = GeneratePodColor(NUM_POD - 2);

	for (int i = 0; i < NUM_PLATFORMS; i++) {
			platforms[i][NUM_POD - 1].color = colors[i];
			platforms[i][NUM_POD - 1].z = Z_offset_pod - 2 * (NUM_POD - 1);
	}
}

std::vector<bool> Skyroads::NecessaryPodImpossibleJump(int prev_pod) {

	std::vector<bool> nec_pod = { false, false, false, false, false };

	if (platforms[0][prev_pod].color == "space" || platforms[0][prev_pod].color == "yellow" || platforms[0][prev_pod].color == "red" || platforms[0][prev_pod].color == "orange") {
		nec_pod[rand() % 2] = true;
	}
	if (platforms[1][prev_pod].color == "space" || platforms[1][prev_pod].color == "yellow" || platforms[1][prev_pod].color == "red" || platforms[1][prev_pod].color == "orange") {
		nec_pod[rand() % 3] = true;
	}
	if (platforms[2][prev_pod].color == "space" || platforms[2][prev_pod].color == "yellow" || platforms[2][prev_pod].color == "red" || platforms[2][prev_pod].color == "orange") {
		nec_pod[rand() % 3 + 1] = true;
	}
	if (platforms[3][prev_pod].color == "space" || platforms[3][prev_pod].color == "yellow" || platforms[3][prev_pod].color == "red" || platforms[3][prev_pod].color == "orange") {
		nec_pod[rand() % 3 + 2] = true;
	}
	if (platforms[4][prev_pod].color == "space" || platforms[4][prev_pod].color == "yellow" || platforms[4][prev_pod].color == "red" || platforms[4][prev_pod].color == "orange") {
		nec_pod[rand() % 2 + 3] = true;
	}

	return nec_pod;
}

std::vector<std::string> Skyroads::GeneratePodColor(int prev_pod) {

	std::vector<std::string> colors = { "", "", "", "", "" };

	std::vector<bool> necessary_pod = NecessaryPodImpossibleJump(prev_pod);

	std::vector<string> prev_colors = { platforms[0][prev_pod].color, platforms[1][prev_pod].color, 
		 platforms[2][prev_pod].color, platforms[3][prev_pod].color,  platforms[4][prev_pod].color};

	for (int i = 0; i < NUM_PLATFORMS; i++) {
		if (necessary_pod[i]) {
			int color_chance = rand() % 2;

			if (color_chance == 0)
				colors[i] = "blue"; // simple pod
			else
				colors[i] = "green"; // fuel++

			continue;
		}
		int pod_chance = rand() % 20;
		if (pod_chance < 8) {
			
			if (prev_colors[i] == "space") {

				int color_chance = rand() % 5;

				if (color_chance == 0)
					colors[i] = "blue"; // simple pod
				else if (color_chance == 1)
					colors[i] = "green"; // fuel++
				else if (color_chance == 2)
					colors[i] = "yellow"; // fuel--
				else if (color_chance == 3)
					colors[i] = "orange"; // speedup X
				else if (color_chance == 4)
					colors[i] = "red"; // HP--
			}
			else colors[i] = prev_colors[i];
		}
		else {
			colors[i] = "space";
		}
	}
	
	return colors;
}

void Skyroads::GeneratePlatforms() {
	// safe zone (game start)
	std::vector<Podium> PodCol_1, PodCol_2, PodCol_3, PodCol_4, PodCol_5;

	for (int i = 0; i < NUM_POD / 3 + 1; i++) {
		Podium podium1("blue", X_offset_pod1, Y_offset_pod, Z_offset_pod - 2 * i);
		PodCol_1.push_back(podium1);

		Podium podium2("blue", X_offset_pod2, Y_offset_pod, Z_offset_pod - 2 * i);
		PodCol_2.push_back(podium2);

		Podium podium3("blue", X_offset_pod3, Y_offset_pod, Z_offset_pod - 2 * i);
		PodCol_3.push_back(podium3);

		Podium podium4("blue", X_offset_pod4, Y_offset_pod, Z_offset_pod - 2 * i);
		PodCol_4.push_back(podium4);

		Podium podium5("blue", X_offset_pod5, Y_offset_pod, Z_offset_pod - 2 * i);
		PodCol_5.push_back(podium5);
	}

	platforms.push_back(PodCol_1);
	platforms.push_back(PodCol_2);
	platforms.push_back(PodCol_3);
	platforms.push_back(PodCol_4);
	platforms.push_back(PodCol_5);

	// not safe anymore
	for (int i = NUM_POD / 3 + 1; i < NUM_POD; i++) {

		std::vector<std::string> colors = GeneratePodColor(i - 1);
		
		Podium podium1(colors[0], X_offset_pod1, Y_offset_pod, Z_offset_pod - 2 * i);
		platforms[0].push_back(podium1);

		Podium podium2(colors[1], X_offset_pod2, Y_offset_pod, Z_offset_pod - 2 * i);
		platforms[1].push_back(podium2);

		Podium podium3(colors[2], X_offset_pod3, Y_offset_pod, Z_offset_pod - 2 * i);
		platforms[2].push_back(podium3);

		Podium podium4(colors[3], X_offset_pod4, Y_offset_pod, Z_offset_pod - 2 * i);
		platforms[3].push_back(podium4);

		Podium podium5(colors[4], X_offset_pod5, Y_offset_pod, Z_offset_pod - 2 * i);
		platforms[4].push_back(podium5);
	}

}

void Skyroads::RenderPlatforms(float deltaTimeSeconds) {

	if (platforms[0][0].z >= Z_offset_pod + 2) {
		GenerateNextPod();
	}

	for (int i = 0; i < NUM_POD; i++)
		for (int j = 0; j < NUM_PLATFORMS; j++) {
			platforms[j][i].z += game_speed * deltaTimeSeconds;

			if (platforms[j][i].color != "space") { // platform exists at given i

				glm::mat4 modelMatrix = glm::mat4(1);

				modelMatrix = glm::translate(modelMatrix, glm::vec3(platforms[j][i].x, platforms[j][i].y, platforms[j][i].z));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(pod_sf, pod_sf, pod_sf));

				std::string object = "podium_" + platforms[j][i].color;
				RenderMesh(meshes[object], shaders["Simple"], modelMatrix);
			}
		}
}

void Skyroads::isPlayerMoving(float deltaTimeSeconds) {
	if (playerIsMoving) {
		if (direction == "left") {
			if (X_UFO + NUM_PLATFORMS / 2 > playerPos) {
				X_UFO -= game_speed * deltaTimeSeconds;
				if (!renderCameraTarget)
					camera->TranslateRight(-game_speed * deltaTimeSeconds);
			}
			else {
				X_UFO = playerPos - NUM_PLATFORMS / 2;
				playerIsMoving = false;
			}
		}
		else if (direction == "right") {
			if (X_UFO + NUM_PLATFORMS / 2 < playerPos) {
				X_UFO += game_speed * deltaTimeSeconds;
				if (!renderCameraTarget)
					camera->TranslateRight(game_speed * deltaTimeSeconds);
			}
			else {
				X_UFO = playerPos - NUM_PLATFORMS / 2;
				playerIsMoving = false;
			}
		}
		else {
			if (up) {
				Y_UFO += 1.0 / 2 * game_speed * deltaTimeSeconds;
				jump_counter += 1.0 / 2 * game_speed * deltaTimeSeconds;
				if (jump_counter >= jump_length / 2.0)
					up = false;
				if (!renderCameraTarget)
					camera->TranslateUpward(1.0 / 2 * game_speed * deltaTimeSeconds);
			}
			else if (jump_counter < jump_length) {
				Y_UFO -= 1.0 / 2 * game_speed * deltaTimeSeconds;
				jump_counter += 1.0 / 2 * game_speed * deltaTimeSeconds;
				if (!renderCameraTarget)
					camera->TranslateUpward(- 1.0 / 2 * game_speed * deltaTimeSeconds);
			}
			else {
				Y_UFO = Y_offset_ufo;
				jump_counter = 0;
				playerIsMoving = false;
			}
		}
	}
}

int Skyroads::CollisionCheck() {
	
	int i = playerPos;

	for (int j = 2; j <= 2; j++) {
		cout << platforms[i][j].z << " " << platforms[i][j + 1].z << " " << platforms[i][j + 2].z << " " << Z_UFO << endl;
		if (!platforms[i][j].collided && (platforms[i][j].z <= 1 + Z_UFO) && (platforms[i][j].z >= - 1 + Z_UFO)) {
			if (platforms[i][j].color != "space") {

				if (platforms[i][j].color == "red") {
					HP_UFO = 0;
					power_fill = 0;
					UFOaffliction = 1;
					rgb = RED;
				}
				else if (platforms[i][j].color == "yellow") {
					power_fill = std::max(power_fill - power_up_down, 0.0f);
					UFOaffliction = 1;
					rgb = YELLOW;
				}
				else if (platforms[i][j].color == "green") {
					power_fill = std::min(1.0f, power_fill + power_up_down);
					UFOaffliction = 1;
					rgb = GREEN;
				}
				else if (platforms[i][j].color == "orange") {
					game_speed += force_speed;
					speed_lock++;
					speed_timer += 2.0;
					UFOaffliction = 1;
					rgb = ORANGE;
				}


				if (platforms[i][j - 1].color == platforms[i][j].color)
					platforms[i][j - 1].color = "purple";
				for (int k = j + 1; k < NUM_POD; k++) {
					if (platforms[i][k].color == platforms[i][j].color) {
						platforms[i][k].color = "purple";
						platforms[i][k].collided = true;
					}
					else break;
				}
				cout << "Player collided: col " << i << " " << platforms[i][j].color << " " << platforms[i][j].z << " " << endl;
				platforms[i][j].color = "purple";
				platforms[i][j].collided = true;
				return 0; // player landed on platform
			}
			else if (platforms[i][j].color == "space") {
				cout << "Player fell " << playerPos << " " << platforms[i][j].z << " z.plat " << endl;
				platforms[i][j].collided = true;
				for (int k = j + 1; k < NUM_POD; k++) {
					if (platforms[i][k].color == "space") {
						platforms[i][k].collided = true;
					}
					else break;
				}
				return 1; // player lost HP (fell into space)
			}
		}
	}
	return 0;
}


void Skyroads::UFOfall(float deltaTimeSeconds) {
	if (Y_UFO > -100) { // if UFO on screen
		for (int i = 0; i < NUM_PLATFORMS; i++)
			for (int j = 0; j < NUM_POD; j++) {
				platforms[i][j].y += rand() % 10 * deltaTimeSeconds;
			}
		Y_UFO -= deltaTimeSeconds;
		ufo_sf -= deltaTimeSeconds / 1000;
		fall_angle += 100 * deltaTimeSeconds;
	}
}

void Skyroads::RenderHP(float deltaTimeSeconds) {
	//glDisable(GL_DEPTH_TEST);

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.97, 0.87, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0007, 0.0012, 1));

	RenderSimpleMesh(meshes["H"], shaders["ShaderSkyroads"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.92, 0.87, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0007, 0.0012, 1));

	RenderSimpleMesh(meshes["P"], shaders["ShaderSkyroads"], modelMatrix);

	if (HP_UFO >= 1) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.85, 0.87, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0007, 0.0012, 1));
		RenderSimpleMesh(meshes["Life"], shaders["ShaderSkyroads"], modelMatrix);

		if (HP_UFO >= 2) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.75, 0.87, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0007, 0.0012, 1));
			RenderSimpleMesh(meshes["Life"], shaders["ShaderSkyroads"], modelMatrix);

			if (HP_UFO >= 3) {
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.65, 0.87, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0007, 0.0012, 1));
				RenderSimpleMesh(meshes["Life"], shaders["ShaderSkyroads"], modelMatrix);
				
				if (HP_UFO >= 4) {
					modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.55, 0.87, 0));
					modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0007, 0.0012, 1));
					RenderSimpleMesh(meshes["Life"], shaders["ShaderSkyroads"], modelMatrix);
					
					if (HP_UFO >= 5) {
						modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.45, 0.87, 0));
						modelMatrix = glm::scale(modelMatrix, glm::vec3(0.0007, 0.0012, 1));
						RenderSimpleMesh(meshes["Life"], shaders["ShaderSkyroads"], modelMatrix);
					}
				}
			}
		}
	}

	//glEnable(GL_DEPTH_TEST);
}

void Skyroads::RenderPowerbar(float deltaTime) {

	glm::mat4 modelMatrix;
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.35, 0.9, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.003, 0.003, 1));
	RenderSimpleMesh(meshes["powerbar_empty"], shaders["ShaderSkyroads"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.35, 0.9, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(power_fill * 0.003, 0.003, 1));

	RenderSimpleMesh(meshes["powerbar_full"], shaders["ShaderSkyroads"], modelMatrix);
}

void Skyroads::RenderUFO(float deltaTimeSeconds) {

	if (ufo_angle < 360) {
		ufo_angle += 10 * game_speed * deltaTimeSeconds;
	}
	else ufo_angle = 0;
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(X_UFO, Y_UFO, Z_UFO));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(ufo_sf, ufo_sf, ufo_sf));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(ufo_angle), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(fall_angle), glm::vec3(1, 0, 0));

	RenderMesh(meshes["ufo"], shaders["Simple"], modelMatrix);
	if (!renderCameraTarget && fall_angle != 0) {
		camera->TranslateRight(-(playerPos - NUM_PLATFORMS / 2));
		camera->TranslateForward(-2.8);
		renderCameraTarget = !renderCameraTarget;
	}

	if (UFOaffliction == 1) {
		if (affliction_timer < 2) {
			affliction_timer += deltaTimeSeconds;

			isUFO = 1;

			if (!renderCameraTarget) {
				modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(- 0.7, 0.6, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f));
			}
			else {
				modelMatrix = glm::scale(modelMatrix, glm::vec3(5.0f));
			}

			RenderSimpleMesh(meshes["sphere"], shaders["ShaderSkyroads"], modelMatrix);

			isUFO = 0;

			if (affliction_timer >= 2) {
				UFOaffliction = 0;
				affliction_timer = 0;
			}
		}
	}

}

void Skyroads::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location1 = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	int location2 = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	int location3 = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Bonus
	float time = Engine::GetElapsedTime();
	int location_bonus = glGetUniformLocation(shader->program, "elapsed_time");
	glUniform1f(location_bonus, time);

	int location_affliction = glGetUniformLocation(shader->program, "UFOaffliction");
	glUniform1i(location_affliction, UFOaffliction);

	int location_isUFO = glGetUniformLocation(shader->program, "isUFO");
	glUniform1i(location_isUFO, isUFO);

	int location_cameraTarget = glGetUniformLocation(shader->program, "renderCameraTarget");
	glUniform1i(location_cameraTarget, renderCameraTarget);

	
	if (frame_counter == framerate) {
		randDrugs = rand() % 100;
		frame_counter = 0;
	}
	else {
		frame_counter++;
	}
	int location_randdrugs = glGetUniformLocation(shader->program, "rand_drugs");
	glUniform1f(location_randdrugs, randDrugs);

	int location_color = glGetUniformLocation(shader->program, "rgb");
	glUniform3fv(location_color, 1, glm::value_ptr(rgb));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Skyroads::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, std::string obj_name, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Bonus
	if (obj_name == "ufo" || obj_name == "sphere") {
		int isEarth = glGetUniformLocation(shader->program, "isEarth");
		glUniform1i(isEarth, 1);

		float time = Engine::GetElapsedTime();
		int location_bonus = glGetUniformLocation(shader->program, "elapsed_time");
		glUniform1f(location_bonus, time);
	}
	else {
		int isEarth = glGetUniformLocation(shader->program, "isEarth");
		glUniform1i(isEarth, 0);

		int location_bonus = glGetUniformLocation(shader->program, "elapsed_time");
		glUniform1f(location_bonus, 0);
	}

	if (texture1)
	{
		//TODO : activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		//TODO : Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2)
	{
		//TODO : activate texture location 1
		glActiveTexture(GL_TEXTURE1);
		//TODO : Bind the texture2 ID
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Skyroads::Update(float deltaTimeSeconds)
{
	{
		Z_Space += game_speed * deltaTimeSeconds;
		if (Z_Space >= -10) {
			Z_Space = Z_Space_Offset;
		}
		//SimpleScene::RenderMesh(meshes["space"], glm::vec3(0, Y_Space_Offset, Z_Space), glm::vec3(0.5f, 4.0f, 1.0f));
		glm::mat4 modelMatrix = glm::mat4(1);
		RenderMesh(meshes["space"], shaders["DecorationShader"], modelMatrix, "space", mapTextures["space"]);
	}
	
	if (first_frame) {
		first_frame = false;
		return;
	}

	if (speed_timer > 0) {
		speed_timer -= deltaTimeSeconds;
		if (speed_timer <= 0) {
			game_speed -= force_speed * speed_lock;
			speed_lock = 0;
		}
	}

	if (power_fill <= 0) {
		power_fill = 1;
		HP_UFO--;
	}

	if (HP_UFO > 0) {

		if (safe_zone_timer >= 20)
			power_fill -= game_speed * deltaTimeSeconds / 50.0;
		else safe_zone_timer += game_speed * deltaTimeSeconds;
		
		isPlayerMoving(deltaTimeSeconds);

		if (!playerIsMoving) {
			if (CollisionCheck() != 0)
			HP_UFO = 0;
		}
	}
	else {
		UFOfall(deltaTimeSeconds);
	}

	RenderPowerbar(deltaTimeSeconds);
	RenderHP(deltaTimeSeconds);
	RenderPlanets(deltaTimeSeconds);
	RenderUFO(deltaTimeSeconds);
	RenderPlatforms(deltaTimeSeconds);
}

void Skyroads::FrameEnd()
{
	// DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Skyroads::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Skyroads::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(cameraSpeed / 20);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-cameraSpeed / 20);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->TranslateForward(-cameraSpeed / 20);
			// TODO : translate the camera backwards
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(cameraSpeed / 20);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpward(-cameraSpeed / 20);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			camera->TranslateUpward(cameraSpeed / 20);
			// TODO : translate the camera up
		}


	}

	// fov++
	if (window->KeyHold(GLFW_KEY_1)) {
		fov += deltaTime;
		projectionMatrix = glm::perspective(fov, aspect, znear, zfar);
	}
	// fov--
	if (window->KeyHold(GLFW_KEY_2)) {
		fov -= deltaTime;
		projectionMatrix = glm::perspective(fov, aspect, znear, zfar);
	}
}

void Skyroads::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_A) {
		if (!playerIsMoving && playerPos > 0) {
			playerPos--;
			playerIsMoving = true;
			direction = "left";
			up = true;
		}
	}
	if (key == GLFW_KEY_D) {
		if (!playerIsMoving && playerPos < NUM_PLATFORMS - 1) {
			playerPos++;
			playerIsMoving = true;
			direction = "right";
			up = true;
		}
	}
	if (key == GLFW_KEY_SPACE) {
		if (!playerIsMoving) {
			direction = "none";
			playerIsMoving = true;
			up = true;
		}
	}
	
	if (key == GLFW_KEY_W && speed_lock == 0) {
		game_speed++;
	}
	if (key == GLFW_KEY_S && speed_lock == 0) {
		game_speed--;
	}

	if (key == GLFW_KEY_C)
	{
		renderCameraTarget = !renderCameraTarget;

		if (renderCameraTarget) { // switch to 3rd person
			camera->TranslateRight(- (playerPos - NUM_PLATFORMS / 2));
			camera->TranslateForward(- 2.8);
		}
		else { // switch to 1st person
			camera->TranslateRight(playerPos - NUM_PLATFORMS / 2);
			camera->TranslateForward(2.8);
		}
	}

	if (key == GLFW_KEY_R) {
		platforms.clear();
		InitVar();
		Init();
	}
	

}

void Skyroads::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Skyroads::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensitivityOX = 0.001f;
		float sensitivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-sensitivityOX * deltaY);
			camera->RotateFirstPerson_OY(-sensitivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-sensitivityOX * deltaY);
			camera->RotateThirdPerson_OY(-sensitivityOY * deltaX);
		}

	}
}

void Skyroads::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Skyroads::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Skyroads::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Skyroads::OnWindowResize(int width, int height)
{
}
