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

#include "buffer.h"
#include "camera.h"
#include "rendermanager.h"
#include "scenemanager.h"

#include "embree_helper.h"
#include "render_helper.h"


class Window
{
    public:
        Window();

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
        embree::Vec2fa prevMousePos = embree::Vec2fa(renderGlobals.width / 2.0f, renderGlobals.height / 2.0f);

        Buffer frontBuffer;
        Buffer backBuffer;
        Camera camera;
        GLFWwindow* window;
        SceneManager sceneManager;
        RenderManager renderManager;
        RenderGlobals renderGlobals;
};


#endif // WINDOW_H
