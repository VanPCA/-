/* #include <iostream>
#include<Windows.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader2.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//副版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//作用是画opengl，版本是CORE_PROFILE
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//向前兼容，苹果必须
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止窗口调整大小

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "B19030235PCA", nullptr, nullptr);

	if (nullptr == window) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//对于高清屏,获取实际占用现显存
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);//获得窗口对应显存大小

	glfwMakeContextCurrent(window);//把窗口设为当前窗口
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initilize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	Shader ourShader = Shader("res/shaders/core2.vs", "res/shaders/core2.fs");
	//顶点信息
	
	GLfloat vertices[] =
	{     //position          //color
		//第一个三角形
		0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,
		-0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,
		//第二个
		0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,
		-0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,
	};

	//传入数据
	GLuint VAO, VBO; //顶点阵列对象（负责解释数据），顶点缓存对象(负责传输)，成对出现
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//绑定VAO和VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//传输数据
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//设置VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); //位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat))); //颜色
	glEnableVertexAttribArray(1);

	//GLuint EBO;
	//glGenBuffers(1,&EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑
	glBindVertexArray(0);//解绑


	//绘制循环
	while (!glfwWindowShouldClose(window)) { //窗口不关闭每一帧都刷新画图
		float time = glfwGetTime();
		if ((int)time % 2 == 0)
			glUniform4f(glGetUniformLocation(ourShader.Program, "ourColor"), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			glUniform4f(glGetUniformLocation(ourShader.Program, "ourColor"), 0.0f, 1.0f, 0.0f, 1.0f);

		glViewport(0,0,screenWidth,screenHeight);//最左下角位置（0，0），画画的长和高
		glfwPollEvents();//获取重要的位置标记信息,如鼠标键盘等
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//RGBA
		glClear(GL_COLOR_BUFFER_BIT);//对颜色进行初始化赋值
		ourShader.Use();
		//glUseProgram(shaderProgram);
		glUniform1f(glGetUniformLocation(ourShader.Program,"time"), time);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glfwSwapBuffers(window);//双缓存机制
        
	}
	glfwTerminate();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1,&VBO);
	//glDeleteProgram(shaderProgram);
	return 0;
}
*/