#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <cmath>
#define M_PI 3.1415926535f

#include "Renderer.h"
#include "Error.h"
#include "Shader.h"
#include "Window.h"
#include "VertexArray.h"
#include "VertexAttribute.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
/*****************************************/
#include "Model_2.h"
#include "Mesh.h"
/******************************************/

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <assimp/Importer.hpp>

int main()
{
	Window wnd("My Rendering Engine", 1440, 900, nullptr);
	Shader shader("res/shaders/basic.shader");
	shader.Use();

	GLCall(GLint location = glGetUniformLocation(shader.GetHandle(), "u_Color"));

	//const GLfloat square_vertices[] = {
	//	-0.8f, -0.8f, 0.0f, 0.0f,
	//	 0.8f, -0.8f, 1.0f, 0.0f,
	//	 0.8f,  0.8f, 1.0f, 1.0f,
	//	-0.8f,  0.8f, 0.0f, 1.0f
	//};

	const GLfloat cube_vertices[] = {
		-0.5f, -0.5f, -0.5f,  // 0 - front left bottom	
		 0.5f, -0.5f, -0.5f,  // 1 - front right bottom	
		 0.5f,  0.5f, -0.5f,  // 2 - front right top	
		-0.5f,  0.5f, -0.5f,   // 3 - front left top		
		-0.5f, -0.5f,  0.5f,  // 4 - back left bottom	
		 0.5f, -0.5f,  0.5f,  // 5 - back right bottom	
		 0.5f,  0.5f,  0.5f,  // 6 - back right top		
		-0.5f,  0.5f,  0.5f   // 7 - back left top		
	};

	const GLuint cube_indices[] = {
		0,1,2,
		2,3,0,
		3,2,7,
		7,6,2,
		2,1,5,
		5,6,2,
		3,0,4,
		4,7,3,
		7,4,5,
		5,6,7,
		0,1,4,
		4,5,1
	};

	Assimp::Importer importer;

	// this is to enable the z-buffer (depth testing for fragments)
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
	// this is to make transparent pixels work
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Mesh cube(cube_vertices, GL_FLOAT, sizeof cube_vertices / sizeof cube_vertices[0], cube_indices, sizeof cube_indices / sizeof cube_indices[0]);

	//// you have to make the vao before the vbo
	//VertexArray va;
	//VertexBuffer vbo(cube_vertices, GL_FLOAT, sizeof cube_vertices / sizeof cube_vertices[0]);
	//IndexBuffer ibo(cube_indices, sizeof cube_indices / sizeof cube_indices[0]);
	////VertexAttribute pos(0, 2, sizeof GLfloat * 2, 0);
	//BufferLayout layout;
	//layout.Push<float>(3); // position xyz
	////layout.Push<float>(2); // tex coord uv
	//va.AddBuffer(vbo, layout);

	Renderer renderer;
	
	//Texture texture("res/textures/eiffel.jpg");
	//constexpr int NT_SOME_TEXTURE_SLOT = 0;
	//texture.Bind(NT_SOME_TEXTURE_SLOT);
	//shader.SetUniform1i("u_Texture", NT_SOME_TEXTURE_SLOT);



	/************************************************************************/

	Model sniper;
	if (!sniper.LoadModel("./res/models/sniper_rifle/Sniper_Scope.obj"))
	{
		std::cerr << "Could not load sniper" << std::endl;
		return -1;
	}

	glm::vec3 translation(0.0f, 0.0f, 0.0f);
	glm::vec3 scale(1.0f, 1.0f, 1.0f);
	glm::mat4 model(1.0f);
	float angleOfRotation = 0.0f;
	model = glm::rotate(angleOfRotation, glm::vec3{ 0.0f, 1.0f, 0.0f });
	model = glm::translate(model, translation);
	model = glm::scale(model, scale);
	// give shader our projection matrix to transform vertices
	//glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f);
	glm::mat4 view = glm::lookAt(glm::vec3{ 0.0f,0.0f, 7.0f }, glm::vec3{ 0.0f,0.0f,0.0f }, glm::vec3{ 0.0f,1.0f,0.0f });
	glm::mat4 proj = glm::perspective(65.0f * M_PI / 180.0f, 1.6f / 0.9f, 0.1f, 100.0f);
	glm::mat4 static_mvp = proj * view * model;
	

	/************************************************************************/







	//glm::vec3 cube_translation(0.0f, 0.0f, 0.0f);
	//glm::vec3 cube_scale(1.0f, 1.0f, 1.0f);
	//glm::mat4 cube_model(1.0f);
	//float cube_angleOfRotation = 0.0f;
	//model = glm::rotate(angleOfRotation, glm::vec3{ 0.0f, 1.0f, 0.0f });
	//model = glm::translate(model, translation);
	//model = glm::scale(model, scale);
	//// give shader our projection matrix to transform vertices
	////glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f);
	//glm::mat4 view = glm::lookAt(glm::vec3{ 0.0f,0.0f, 7.0f }, glm::vec3{ 0.0f,0.0f,0.0f }, glm::vec3{ 0.0f,1.0f,0.0f });
	//glm::mat4 proj = glm::perspective(65.0f * M_PI / 180.0f, 1.6f/0.9f, 0.1f, 100.0f);
	glm::mat4 mvp = proj * view * model;

	unsigned int foo = 0;

	//// Our state
	//bool show_demo_window = true;
	//bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(wnd.GetHandle()))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		renderer.Clear(clear_color.x, clear_color.y, clear_color.z);

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                        // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			
			ImGui::Text("Translation");
			ImGui::SliderFloat("Position X", &translation.x, -10.0f, 10.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Position Y", &translation.y, -15.0f, 15.0f);
			ImGui::SliderFloat("Position Z", &translation.z, -10.0f, 10.0f);
			ImGui::NewLine();

			ImGui::Text("Rotation");
			ImGui::SliderFloat("Angle of Rotation", &angleOfRotation, -90.0f, 90.0f);
			ImGui::NewLine();

			ImGui::Text("Scaling");
			ImGui::SliderFloat("Scaling X", &scale.x, -20.0f, 20.0f);
			ImGui::SliderFloat("Scaling Y", &scale.y, -15.0f, 15.0f);
			ImGui::SliderFloat("Scaling Z", &scale.z, -10.0f, 10.0f);
			ImGui::NewLine();

			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))    // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		
		shader.SetUniformMat4f("u_MVP", static_mvp);
		sniper.RenderModel(renderer, shader);

		// glm::translate -> rotate -> scale
		// in reality this scales first, then rotates, then translates.
		// DO NOT CHANGE THE ORDER OF THESE 3 LINES. IF YOU WANT TO, THEN MAKE SURE THE FIRST
		// FUNCTION IS GIVEN IDENTITY MATRIX AND THE NEXT 2 ARE GIVEN THE MODEL MATRIX.
		model = glm::translate(glm::mat4(1.0f), translation);
		model = glm::rotate(model, angleOfRotation * M_PI / 180.0f, glm::vec3{ 0.0f,1.0f,0.0f });
		model = glm::scale(model, scale);

		mvp = proj * view * model;
		shader.SetUniformMat4f("u_MVP", mvp);
		cube.RenderMesh(renderer, shader);
		//renderer.Draw(va, ibo, shader);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(wnd.GetHandle());
	}
}