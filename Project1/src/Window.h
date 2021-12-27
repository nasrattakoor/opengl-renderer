#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Window
{
public:
	// TODO: implement some proper error handling with exceptions, callbacks (GLFW), etc.
	Window(const std::string& name, int width, int height, GLFWmonitor* monitorForFullScreen)
	{
		if (glfwInit() == GLFW_FALSE)
		{
			std::cerr << "Failed to initialize GLFW\n";
			exit(-1);
		}
		
		//std::cout << glGetString(GL_VERSION) << std::endl;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		

		handle = glfwCreateWindow(width, height, name.c_str(), monitorForFullScreen, nullptr);
		if (!handle)
		{
			std::cerr << "Failed to create GLFW window\n";
			glfwTerminate();
			exit(-1);
		}

		//glfwMaximizeWindow(handle);

		glfwMakeContextCurrent(handle);
		glfwSwapInterval(1); // V-Sync
		GLCall(glViewport(0, 0, width, height));
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to initialize GLEW\n";
			glfwDestroyWindow(handle);
			glfwTerminate();
			exit(-1);
		}

		// ImGUI stuff
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(GetHandle(), true);
		// we need OpenGL v4.6 to use preprocessor directive "version 460"
		assert(GLSLVersion460());
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	~Window()
	{
		glfwDestroyWindow(handle);
		ImGui_ImplGlfw_Shutdown();
		glfwTerminate();
	}

	GLFWwindow* GetHandle() const
	{
		return handle;
	}

	bool GLSLVersion460() const
	{
		return versionMajor == 4 && versionMinor == 6;
	}

private:
	GLFWwindow* handle;
	int width, height;
	std::string name;
	int versionMajor = 4, versionMinor = 6;
};