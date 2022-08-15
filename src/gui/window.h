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

#include <spindulys/math/vec2.h>
#include <spindulys/buffer.h>

#include <render/renderManager.h>
#include <render/cpuRenderManager.h>

#include "spindulysGUI.h"

#include "opengl/glshader.h"

GUI_NAMESPACE_OPEN_SCOPE

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
		void MouseCallback(ImGuiIO &guiIO, Vec2f mousePos);

		void RenderToScreenTexture(int width, int height, const Buffer3f& buffer);
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

		GLFWwindow* window;
		CPURenderManager renderManager;
		RenderManager::RenderGlobals renderGlobals;

		Buffer3f frontBuffer = Buffer3f(renderGlobals.width, renderGlobals.height);
		Buffer3f backBuffer  = Buffer3f(renderGlobals.width, renderGlobals.height);

		Vec2f prevMousePos = Vec2f(renderGlobals.width / 2.0f, renderGlobals.height / 2.0f);

		GLuint screenQuadVAO;
		GLuint screenQuadVBO;
		GLuint screenTextureID;

		GLShader screenQuadShader;
};

GUI_NAMESPACE_CLOSE_SCOPE

#endif // WINDOW_H
