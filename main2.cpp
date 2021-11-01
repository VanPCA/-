/*#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
const GLint WIDTH = 800, HEIGHT = 600;
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
bool keys[1024];


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL B19030311", nullptr,
		nullptr);//创建
	// next two lines are for mac retina display
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);//获取所需显存
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Shader ourShader = Shader("res/shaders/core.vs", "res/shaders/core.fs");

	//GLfloat vertices[] =
	//{
	//	 0.5f,0.5f,0.0f,           1.0f,0.0f,0.0f,         //1.0f,1.0f,                 //top right
	//	 0.5f,-0.5f,0.0f,          1.0f,0.0f,0.0f,         //1.0f,0.0f,                 // bottom right
	//	 -0.5f,-0.5f,0.0f,         1.0f,0.0f,0.0f,         //0.0f,0.0f,                   //bottom left
	//	 -0.5f,0.5f,0.0f,          1.0f,0.0f,0.0f          //0.0f,1.0f                     //top left   先屏蔽纹理
	//};
	//unsigned int indices[] =
	//{
	//	0,1,3,
	//	1,2,3
	//};
	GLfloat vertices[] =
	{
		//position                    //color
		-0.5f,-0.5f,-0.5f,             1.0f,0.0f,0.0f,
		0.5f,-0.5f,-0.5f,              1.0f,0.0f,0.0f,
		0.5f,0.5f,-0.5f,               1.0f,0.0f,0.0f,
		0.5f,0.5f,-0.5f,               1.0f,0.0f,0.0f,
		-0.5f,0.5f,-0.5f,              1.0f,0.0f,0.0f,
		-0.5f,-0.5f,-0.5f,             1.0f,0.0f,0.0f,

		-0.5f,-0.5f,0.5f,             0.0f,1.0f,0.0f,
		0.5f,-0.5f,0.5f,              0.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,               0.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,               0.0f,1.0f,0.0f,
		-0.5f,0.5f,0.5f,              0.0f,1.0f,0.0f,
		-0.5f,-0.5f,0.5f,             0.0f,1.0f,0.0f,

		-0.5f,0.5f,0.5f,             0.0f,0.0f,1.0f,
		-0.5f,0.5f,-0.5f,            0.0f,0.0f,1.0f,
		-0.5f,-0.5f,-0.5f,           0.0f,0.0f,1.0f,
		-0.5f,-0.5f,-0.5f,           0.0f,0.0f,1.0f,
		-0.5f,-0.5f,0.5f,            0.0f,0.0f,1.0f,
		-0.5f,0.5f,0.5f,             0.0f,0.0f,1.0f,

		0.5f,0.5f,0.5f,             1.0f,1.0f,0.0f,
		0.5f,0.5f,-0.5f,            1.0f,1.0f,0.0f,
		0.5f,-0.5f,-0.5f,           1.0f,1.0f,0.0f,
		0.5f,-0.5f,-0.5f,           1.0f,1.0f,0.0f,
		0.5f,-0.5f,0.5f,            1.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,             1.0f,1.0f,0.0f,

		-0.5f,-0.5f,-0.5f,             1.0f,0.0f,1.0f,
		0.5f,-0.5f,-0.5f,              1.0f,0.0f,1.0f,
		0.5f,-0.5f,0.5f,               1.0f,0.0f,1.0f,
		0.5f,-0.5f,0.5f,               1.0f,0.0f,1.0f,
		-0.5f,-0.5f,0.5f,              1.0f,0.0f,1.0f,
		-0.5f,-0.5f,-0.5f,             1.0f,0.0f,1.0f,

		-0.5f,0.5f,-0.5f,            0.0f,1.0f,1.0f,
		0.5f,0.5f,-0.5f,              0.0f,1.0f,1.0f,
		0.5f,0.5f,0.5f,               0.0f,1.0f,1.0f,
		0.5f,0.5f,0.5f,               0.0f,1.0f,1.0f,
		-0.5f,0.5f,0.5f,              0.0f,1.0f,1.0f,
		-0.5f,0.5f,-0.5f,             0.0f,1.0f,1.0f,
	};



	GLuint VAO, VBO;//成对出现
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//链接VAO和VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		GL_STATIC_DRAW);

	//设置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);//(，，，，每次跳几个位置获得浮点量，从数组的什么位置取)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//GLuint texture0;
	//int width, height;
	//glGenTextures(1, &texture0);
	//glBindTexture(GL_TEXTURE_2D, texture0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//unsigned char* image = SOIL_load_image("res/images/1.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 0);

	while (!glfwWindowShouldClose(window)) {
		//float time = glfwGetTime();
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ourShader.Use();
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture0);
		//glUniform1i(glGetUniformLocation(ourShader.Program, "texture0"), 0);
		////glUseProgram(shaderProgram);
		//glUniform1f(glGetUniformLocation(ourShader.Program, "time"), time);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -2.0f));
		transform = glm::rotate(transform, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));


		GLuint transLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(VAO);
		/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
		//glBindVertexArray(0);
		//glBindTexture(GL_TEXTURE_2D, 0);
		//glfwSwapBuffers(window);
	//}
	//glfwTerminate();
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	/*glDeleteBuffers(1, &EBO);*/
	//glDeleteTextures(1, &texture0);
	//glDeleteProgram(shaderProgram);
	//return 0;
//}*/
/*
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if ((key == GLFW_KEY_SPACE) && (action = GLFW_PRESS)) {
		glfwSetWindowShouldClose(window, GL_TRUE);

	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}*/