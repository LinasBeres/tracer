#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <config.h>

#include <camera/camera.h>

#include <shapes/buffer.h>
#include <render/rendermanager.h>
#include <scene/scenemanager.h>

#include <utils/render_helper.h>

#include "opengl/glshader.h"

SPINDULYS_NAMESPACE_OPEN_SCOPE

class Window
{
	public:
		Window() = default;

		int RenderWindow();
		void ResetRenderer();
		void SetupGUI();
		void RenderGUI();
		void StopGUI();
		void RenderConfigWindow(bool &guiOpen);
		void ProfilingWindow(bool& guiOpen);
		void AboutWindow(bool &guiOpen);
		void KeyboardCallback(ImGuiIO &guiIO);
		void MouseCallback(ImGuiIO &guiIO,
				embree::Vec2fa mousePos);

		void RenderToScreenTexture(int width, int height, Buffer& buffer);
		void SetupScreenQuad(int width, int height);
		void CleanScreenQuad();
		void DrawScreenQuad();

	private:
		bool firstMouse = true;
		bool renderReset = false;
		bool renderConfigState = false;
		bool profilingState = true;
		bool aboutState = false;
		bool pauseState = false;
		bool swapState = false;
		int iterations = 0;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		Buffer frontBuffer;
		Buffer backBuffer;
		Camera camera;
		GLFWwindow* window;
		SceneManager sceneManager;
		RenderManager renderManager;
		RenderGlobals renderGlobals;

		embree::Vec2fa prevMousePos = embree::Vec2fa(renderGlobals.width / 2.0f, renderGlobals.height / 2.0f);

		GLuint screenQuadVAO;
		GLuint screenQuadVBO;
		GLuint screenTextureID;

		GLShader screenQuadShader;
};

SPINDULYS_NAMESPACE_CLOSE_SCOPE

#endif // WINDOW_H
