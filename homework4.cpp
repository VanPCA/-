#include <iostream>
#include<Windows.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader2.h"
#include "Camera2.h"
#include "Light2.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"

const GLint WIDTH = 800, HEIGHT = 600;
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);//键盘操作
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);//滚轮
void MouseCallback(GLFWwindow* window, double xPos, double yPos);//鼠标光标

void DoMovement();//键盘控制镜头

bool keys[1024];//所有键盘操作
Camera2 camera(glm::vec3(0.0f, 0.0f, 2.0f));
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat lastX = WIDTH / 2.0f; //上一个鼠标x位置
GLfloat lastY = HEIGHT / 2.0f; //上一个鼠标y位置
bool firstMouse = true; //是否鼠标首次移动

GLfloat objectX = 0.0f; //物体初始位置
GLfloat objectY = 0.0f;
GLfloat objectZ = -2.0f;
const GLfloat OBJECT_SPEED = 6.0f;

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
	glfwSetKeyCallback(window, KeyCallback);//在当前窗口注册键盘操作
	glfwSetCursorPosCallback(window, MouseCallback);//注册鼠标
	glfwSetScrollCallback(window, ScrollCallback);//注册滚轮

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initilize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);//开启深度测试
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);//开启混合测试
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader = Shader("res/shaders/core3.vs", "res/shaders/core3.fs");
	Shader lightShader = Shader("res/shaders/light2.vs", "res/shaders/light2.fs");

	Light2 lightModel = Light2();

	//顶点信息
	//立方体坐标
	GLfloat vertices[] =
	{
		//position                      //color               //法向量
		-0.5f,-0.5f,-0.5f,              1.0f,0.0f,0.0f,		  0.0f,0.0f,-1.0f,
		0.5f,-0.5f,-0.5f,               1.0f,0.0f,0.0f,		  0.0f,0.0f,-1.0f,
		0.5f,0.5f,-0.5f,                1.0f,0.0f,0.0f,		  0.0f,0.0f,-1.0f,
		0.5f,0.5f,-0.5f,                1.0f,0.0f,0.0f,		  0.0f,0.0f,-1.0f,
		-0.5f,0.5f,-0.5f,               1.0f,0.0f,0.0f,		  0.0f,0.0f,-1.0f,
		-0.5f,-0.5f,-0.5f,              1.0f,0.0f,0.0f,		  0.0f,0.0f,-1.0f,

		-0.5f,-0.5f,0.5f,               0.0f,1.0f,0.0f,		  0.0f,0.0f,1.0f,
		0.5f,-0.5f,0.5f,                0.0f,1.0f,0.0f,		  0.0f,0.0f,1.0f,
		0.5f,0.5f,0.5f,                 0.0f,1.0f,0.0f,		  0.0f,0.0f,1.0f,
		0.5f,0.5f,0.5f,                 0.0f,1.0f,0.0f,		  0.0f,0.0f,1.0f,
		-0.5f,0.5f,0.5f,                0.0f,1.0f,0.0f,		  0.0f,0.0f,1.0f,
		-0.5f,-0.5f,0.5f,               0.0f,1.0f,0.0f,		  0.0f,0.0f,1.0f,

		-0.5f,0.5f,0.5f,                0.0f,0.0f,1.0f,		  -1.0f,0.0f,0.0f,
		-0.5f,0.5f,-0.5f,               0.0f,0.0f,1.0f,		  -1.0f,0.0f,0.0f,
		-0.5f,-0.5f,-0.5f,              0.0f,0.0f,1.0f,		  -1.0f,0.0f,0.0f,
		-0.5f,-0.5f,-0.5f,              0.0f,0.0f,1.0f,		  -1.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.5f,               0.0f,0.0f,1.0f,		  -1.0f,0.0f,0.0f,
		-0.5f,0.5f,0.5f,                0.0f,0.0f,1.0f,		  -1.0f,0.0f,0.0f,

		0.5f,0.5f,0.5f,                1.0f,1.0f,0.0f,		   1.0f,0.0f,0.0f,
		0.5f,0.5f,-0.5f,               1.0f,1.0f,0.0f,		   1.0f,0.0f,0.0f,
		0.5f,-0.5f,-0.5f,              1.0f,1.0f,0.0f,		   1.0f,0.0f,0.0f,
		0.5f,-0.5f,-0.5f,              1.0f,1.0f,0.0f,		   1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.5f,               1.0f,1.0f,0.0f,		   1.0f,0.0f,0.0f,
		0.5f,0.5f,0.5f,                1.0f,1.0f,0.0f,		   1.0f,0.0f,0.0f,
																		  
		-0.5f,-0.5f,-0.5f,             1.0f,0.0f,1.0f,		   0.0f,-1.0f,0.0f,
		0.5f,-0.5f,-0.5f,              1.0f,0.0f,1.0f,		   0.0f,-1.0f,0.0f,
		0.5f,-0.5f,0.5f,               1.0f,0.0f,1.0f,		   0.0f,-1.0f,0.0f,
		0.5f,-0.5f,0.5f,               1.0f,0.0f,1.0f,		   0.0f,-1.0f,0.0f,
		-0.5f,-0.5f,0.5f,              1.0f,0.0f,1.0f,		   0.0f,-1.0f,0.0f,
		-0.5f,-0.5f,-0.5f,             1.0f,0.0f,1.0f,		   0.0f,-1.0f,0.0f,

		-0.5f,0.5f,-0.5f,             0.0f,1.0f,1.0f,		   0.0f,1.0f,0.0f,
		0.5f,0.5f,-0.5f,              0.0f,1.0f,1.0f,		   0.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,               0.0f,1.0f,1.0f,		   0.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,               0.0f,1.0f,1.0f,		   0.0f,1.0f,0.0f,
		-0.5f,0.5f,0.5f,              0.0f,1.0f,1.0f,		   0.0f,1.0f,0.0f,
		-0.5f,0.5f,-0.5f,             0.0f,1.0f,1.0f,		   0.0f,1.0f,0.0f,

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0); //位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); //颜色
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); //法向量
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑
	glBindVertexArray(0);//解绑


	glm::vec3 lightPos = glm::vec3(0.0f, 1.5f, 0.0f);//初始光源位置

	//绘制循环
	while (!glfwWindowShouldClose(window)) { //窗口不关闭每一帧都刷新画图
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glViewport(0, 0, screenWidth, screenHeight);//最左下角位置（0，0），画画的长和高
		glfwPollEvents();//获取重要的位置标记信息,如鼠标键盘等
		DoMovement();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//RGBA
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//对颜色、深度进行初始化赋值
		lightPos = glm::rotate(lightPos, glm::radians(0.03f), glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);//构造透视投影(视域、)
		glm::mat4 transform = glm::mat4(1.0f); //4*4矩阵,修改顶点位置信息
		transform = glm::translate(transform, lightPos);
		transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));

		lightShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		lightModel.Draw(lightShader);

		ourShader.Use();
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(objectX, objectY, objectZ));//平移
		//transform = glm::rotate(transform, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));//旋转变换
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));//缩放

		GLuint transLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));


		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3f(glGetUniformLocation(ourShader.Program, "ViewPos"),camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(ourShader.Program, "LightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(ourShader.Program, "material.diffuse"),0.8f);
		glUniform1f(glGetUniformLocation(ourShader.Program, "material.specular"), 0.6f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glfwSwapBuffers(window);//双缓存机制

	}
	glfwTerminate();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)//键盘操作
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { //按下esc
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	//记录按键
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}
}

void DoMovement()
{
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		objectY += deltaTime * OBJECT_SPEED; //向上
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		objectY -= deltaTime * OBJECT_SPEED; ////向下
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		objectX -= deltaTime * OBJECT_SPEED; //向左
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		objectX += deltaTime * OBJECT_SPEED; //向右
	}
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{

}
void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{

	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}