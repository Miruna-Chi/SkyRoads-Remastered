#pragma once
#include <Component/SimpleScene.h>
#include <Laboratoare/Laborator5/LabCamera.h>
#include <Laboratoare/Laborator4/Transform3D.h>
#include <Laboratoare/Laborator3/Transform2D.h>
#include <Laboratoare/Laborator6/Laborator6.h>
#include "Podium.h"
#include "HP.h"
#include "Game.h"
#include "Powerbar.h"

#define NUM_POD 50
#define NUM_PLATFORMS 5

class Skyroads : public SimpleScene
{
	public:
		Skyroads();
		~Skyroads();

		void Init() override;
		void InitVar();

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

		std::vector<bool> NecessaryPodImpossibleJump(int prev_pod);

		void GenerateNextPod();
		std::vector<std::string> GeneratePodColor(int prev_pod);
		void GeneratePlatforms();
		void RenderPlatforms(float deltaTime);

		void RenderUFO(float deltaTime);

		void isPlayerMoving(float deltaTime);
		int CollisionCheck();

		void UFOfall(float deltaTime);

		void AddHP();
		void RenderHP(float deltaTime);

		void AddPowerbar();
		void RenderPowerbar(float deltaTime);

	protected:
		glm::vec3 RED = glm::vec3(1, 0.12, 0.12);
		glm::vec3 YELLOW = glm::vec3(0.9, 0.9, 0.2);
		glm::vec3 WHITE = glm::vec3(1, 1, 1);
		glm::vec3 TURQOISE = glm::vec3(0, 0.7, 0.7);
		glm::vec3 GRAY = glm::vec3(0.4, 0.4, 0.4);
		glm::vec3 PINK = glm::vec3(1, 0.7, 0.8);
		glm::vec3 GREEN = glm::vec3(0.02, 0.9, 0.24);
		glm::vec3 ORANGE = glm::vec3(1.00, 0.55, 0.10);


		int window_h = 720;
		int window_w = 1280;

		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		float xmin = -4, xmax = 4, ymin = -4, ymax = 4, fov = 45, znear = 1, zfar = 100, aspect = 1.8;

		float Z_Space = -90, Y_Space_Offset = -5.5, Z_Space_Offset = -90;
		float game_speed = 5; // standard_speed

		float ufo_angle = 0;
		float fall_angle = 0;

		glm::vec3 center = { 0, 0, 0 };

		std::vector<std::vector<Podium>> platforms;

		float X_offset_pod1 = -2;
		float X_offset_pod2 = -1;
		float X_offset_pod3 = 0;
		float X_offset_pod4 = 1;
		float X_offset_pod5 = 2;
		
		float Y_offset_pod = 0.5f;
		float Z_offset_pod = 3.0f;
		
		float jump_length = 2;
		float jump_counter = 0;

		float pod_sf = 0.01f;
		float ufo_sf = 0.01f;
		float Y_offset_ufo = 0.6;
		float X_UFO = 0, Y_UFO = 0.60, Z_UFO = 0.5;
		float jump_over = 0;


		// Player

		int playerPos = 2; // center, 0 - left, 2 - right
		bool playerIsMoving = false;
		std::string direction;
		bool up = true;

		bool first_frame = true; // deltaTime is huge;

		int HP_UFO = 5;

		float power_fill = 1;
		float power_up_down = 0.2; // percentage of power gained/drained on impact

		int force_speed = 5;
		int speed_lock = 0;
		float speed_timer = 0;

		float safe_zone_timer = 0;

		int UFOaffliction = 0;
		float affliction_timer = 0;
		int isUFO = 0;

		int framerate = 50;
		int frame_counter = 0;

		float randDrugs = 0;

		glm::vec3 rgb;

};
