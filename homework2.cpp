/*#include <iostream>
#include<Windows.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader2.h"

#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"

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
	{   //position           //color               //纹理坐标
		0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,       1.0f,1.0f,                 //右上
		0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,      1.0f,0.0f,                 //右下
		-0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,     0.0f,0.0f,                 //左下
		-0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,      0.0f,1.0f,                 //左上
	};

	//链接信息
	unsigned int indices[] =
	{
		0,1,3,//第一个三角形
		1,2,3//第二个
	};

	//传入数据
	GLuint VAO, VBO; //顶点阵列对象（负责解释数据），顶点缓存对象(负责传输)，成对出现
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//绑定VAO和VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//传输数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//设置VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); //位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); //颜色
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); //颜色
	glEnableVertexAttribArray(2);

	GLuint EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑
	glBindVertexArray(0);//解绑

	GLuint texture;//生成纹理
	int width, height;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//纹理大于物体时缩小
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//纹理小于物体时放大

	unsigned char* image = SOIL_load_image("res/images/01.jpg",&width,&height,0,SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,image);//图片导入纹理缓冲池
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);//解绑


	GLuint texture1;//生成纹理
	int width1, height1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//纹理大于物体时缩小
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//纹理小于物体时放大

	unsigned char* image1 = SOIL_load_image("res/images/02.jpg", &width1, &height1, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);//图片导入纹理缓冲池
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);//解绑


	//绘制循环
	while (!glfwWindowShouldClose(window)) { //窗口不关闭每一帧都刷新画图
		float time = glfwGetTime();
		glViewport(0, 0, screenWidth, screenHeight);//最左下角位置（0，0），画画的长和高
		glfwPollEvents();//获取重要的位置标记信息,如鼠标键盘等
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//RGBA
		glClear(GL_COLOR_BUFFER_BIT);//对颜色进行初始化赋值
		ourShader.Use();
		glActiveTexture(GL_TEXTURE0);//激活第一个纹理区域
		
		if ((int)time % 2 == 0)
		{
           glBindTexture(GL_TEXTURE_2D,texture);
		   glUniform1i(glGetUniformLocation(ourShader.Program, "texture0"), 0);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(ourShader.Program, "texture1"), 0);
		}
		
		glUniform1f(glGetUniformLocation(ourShader.Program, "time"), time);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glfwSwapBuffers(window);//双缓存机制

	}
	glfwTerminate();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);
	//glDeleteProgram(shaderProgram);
	return 0;
}
*/