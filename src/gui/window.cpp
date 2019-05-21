#include "window.h"


Window::Window()
{
    
}


int Window::renderWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Tracer", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    gladLoadGL();

    ImGui_ImplGlfwGL3_Init(window, true);

    scene.loadScene("res/scenes/cupandsaucer.usdz");

    camera.setResolution(Vector2(width, height));
    camera.initCameraData();

    frontBuffer.initBuffer(width, height);
    backBuffer.initBuffer(width, height);

    renderer.setupScreenQuad(width, height);
    renderer.setupIntegrator(integratorID);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //--------------
        // GUI setting & callbacks
        //--------------
        setupGUI();
        ImGuiIO guiIO = ImGui::GetIO();

        keyboardCallback(guiIO);

        ImVec2 currentMousePos = ImGui::GetMousePos();

        if (lastPosX != currentMousePos.x ||
            lastPosY != currentMousePos.y)
            mouseCallback(guiIO, currentMousePos.x, currentMousePos.y);

        // TODO: Will make use of Qt's callback system once the GUI will be revamped.
        if (renderer.setupIntegrator(integratorID))
        {
            renderReset = true;
        }

        //--------------
        // CPU Rendering
        //--------------
        if (!pauseBool)
        {
            // If anything in camera or scene data has changed, we flush the data and reinit them again
            if (renderReset)
                resetRenderer();

            frame++;


            // Progressive rendering
            renderer.trace(width,
                height,
                samples,
                depth,
                frame,
                frontBuffer.getBufferData(),
                camera,
                scene);
            renderer.renderToScreenTexture(width,
                height,
                frontBuffer.getBufferData());
        }

        renderer.drawScreenQuad();

        //----------------
        // GUI rendering
        //----------------
        renderGUI();

        glfwSwapBuffers(window);
    }

    //---------
    // Cleaning
    //---------
    stopGUI();

    glfwTerminate();

    return 0;
}

void Window::resetRenderer()
{
    frame = 0;
    frontBuffer.cleanBufferData(width, height);

    renderReset = false;
}

void Window::fpsWindow(bool& guiOpen)
{
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 160, 30), 1);

    ImGui::Begin("FPS Counter",
        &guiOpen,
        ImGuiWindowFlags_NoTitleBar
        |ImGuiWindowFlags_NoResize
        |ImGuiWindowFlags_AlwaysAutoResize
        |ImGuiWindowFlags_NoMove
        |ImGuiWindowFlags_NoSavedSettings);

    ImGui::Text("Framerate %.2f FPS", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

    ImGui::End();
}

void Window::aboutWindow(bool& guiOpen)
{
    ImGui::Begin("About", &guiOpen);

    ImGui::Text("Tracer by Joshua Senouf\n\nEmail: joshua.senouf@gmail.com\nTwitter: @JoshuaSenouf");

    ImGui::End();
}

void Window::renderConfigWindow(bool& guiOpen)
{
    ImGui::Begin("Render Config", &guiOpen);

    ImGui::InputInt("Width", &width);
    ImGui::InputInt("Height", &height);
    ImGui::InputInt("Samples", &samples);
    ImGui::InputInt("Depth", &depth);

    ImGui::Separator();

    if (!swapBool)
    {
        if (ImGui::Button("Save To Back Buffer"))
        {
            backBuffer.cleanBufferData(width, height);
            backBuffer.setBufferData(frontBuffer.getBufferData());
        }
    }
    if (ImGui::Button("Swap Buffers"))
    {
        frontBuffer.swapBufferData(backBuffer.getBufferData());
        renderer.renderToScreenTexture(width, height, frontBuffer.getBufferData());

        swapBool = !swapBool;
        pauseBool = true;
    }

    ImGui::End();
}

void Window::setupGUI()
{
    ImGui_ImplGlfwGL3_NewFrame();

    if (fpsBool)
        fpsWindow(fpsBool);
    if (aboutBool)
        aboutWindow(aboutBool);
    if (renderConfigBool)
        renderConfigWindow(renderConfigBool);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("Render to..."))
            {
                if (ImGui::MenuItem("PPM"))
                {
                    Buffer outputBuffer;
                    outputBuffer.initBuffer(width, height);

                    renderer.trace(width,
                        height,
                        samples,
                        depth,
                        1,
                        outputBuffer.getBufferData(),
                        camera,
                        scene);

                    exportToPPM(width,
                        height,
                        outputBuffer.getBufferData());
                }

                if (ImGui::MenuItem("EXR"))
                {
                    Buffer outputBuffer;
                    outputBuffer.initBuffer(width, height);
                    
                    renderer.trace(width,
                        height,
                        samples,
                        depth,
                        1,
                        outputBuffer.getBufferData(),
                        camera,
                        scene);

                    exportToEXR(width,
                        height,
                        outputBuffer.getBufferData());
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Export to..."))
            {
                if (ImGui::MenuItem("PPM"))
                {
                    exportToPPM(width, height, frontBuffer.getBufferData());
                }

                if (ImGui::MenuItem("EXR"))
                {
                    exportToEXR(width, height, frontBuffer.getBufferData());
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Rendering"))
        {
            if (ImGui::BeginMenu("Integrator"))
            {
                ImGui::RadioButton("UDPT", &integratorID, 0);
                ImGui::RadioButton("Diffuse", &integratorID, 1);
                ImGui::RadioButton("Occlusion", &integratorID, 2);
                ImGui::RadioButton("Debug", &integratorID, 3);

                ImGui::EndMenu();
            }

            ImGui::MenuItem("Config", NULL, &renderConfigBool);

            if (!swapBool)
            {
                ImGui::Separator();
                ImGui::Checkbox("Pause Render", &pauseBool);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::BeginMenu("Load..."))
            {
                if (ImGui::MenuItem("Cup and Saucer"))
                {
                    scene.loadScene("res/scenes/usd/cupandsaucer.usdz");
                    camera.initCameraData();

                    renderReset = true;
                }

                if (ImGui::MenuItem("Stormtroopers"))
                {
                    scene.loadScene("res/scenes/usd/stormtroopers.usdc");
                    camera.initCameraData();

                    renderReset = true;
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Profiling", NULL, &fpsBool);
            ImGui::Separator();
            ImGui::MenuItem("About", NULL, &aboutBool);

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void Window::renderGUI()
{
    ImGui::Render();
}

void Window::stopGUI()
{
    ImGui_ImplGlfwGL3_Shutdown();
}

void Window::keyboardCallback(ImGuiIO& guiIO)
{
    if (guiIO.KeysDown[GLFW_KEY_ESCAPE])
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (guiIO.KeysDown[GLFW_KEY_W])
    {
        camera.keyboardCall(FORWARD, deltaTime);
        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_S])
    {
        camera.keyboardCall(BACKWARD, deltaTime);
        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_A])
    {
        camera.keyboardCall(LEFT, deltaTime);
        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_D])
    {
        camera.keyboardCall(RIGHT, deltaTime);
        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_KP_ADD])
    {
        if (guiIO.KeysDown[GLFW_KEY_LEFT_CONTROL])
            camera.setFocalDistance(camera.getFocalDistance() + 0.1f);
        else
            camera.setApertureRadius(camera.getApertureRadius() + 0.005f);

        renderReset = true;
    }
    if (guiIO.KeysDown[GLFW_KEY_KP_SUBTRACT])
    {
        if (guiIO.KeysDown[GLFW_KEY_LEFT_CONTROL])
        {
            camera.setFocalDistance(camera.getFocalDistance() - 0.1f);
        }
        else
        {
            camera.setApertureRadius(camera.getApertureRadius() - 0.005f);
        }
        renderReset = true;
    }
}

void Window::mouseCallback(ImGuiIO& guiIO,
    float mousePosX,
    float mousePosY)
{
    if (firstMouse)
    {
        lastPosX = mousePosX;
        lastPosY = mousePosY;
        firstMouse = false;
    }

    float offsetX = mousePosX - lastPosX;
    float offsetY = mousePosY - lastPosY;

    lastPosX = mousePosX;
    lastPosY = mousePosY;

    if (guiIO.MouseDown[GLFW_MOUSE_BUTTON_RIGHT])
    {
        if (offsetX != 0 || offsetY != 0)
        {
            camera.mouseCall(offsetX, offsetY, true);
            renderReset = true;
        }
    }
}
