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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//���汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//�����ǻ�opengl���汾��CORE_PROFILE
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//��ǰ���ݣ�ƻ������
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//��ֹ���ڵ�����С

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "B19030235PCA", nullptr, nullptr);

	if (nullptr == window) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//���ڸ�����,��ȡʵ��ռ�����Դ�
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);//��ô��ڶ�Ӧ�Դ��С

	glfwMakeContextCurrent(window);//�Ѵ�����Ϊ��ǰ����
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initilize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	Shader ourShader = Shader("res/shaders/core2.vs", "res/shaders/core2.fs");
	//������Ϣ
	
	GLfloat vertices[] =
	{     //position          //color
		//��һ��������
		0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,
		-0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,
		//�ڶ���
		0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,
		-0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,
	};

	//��������
	GLuint VAO, VBO; //�������ж��󣨸���������ݣ������㻺�����(������)���ɶԳ���
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//��VAO��VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//��������
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//����VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); //λ��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat))); //��ɫ
	glEnableVertexAttribArray(1);

	//GLuint EBO;
	//glGenBuffers(1,&EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//���
	glBindVertexArray(0);//���


	//����ѭ��
	while (!glfwWindowShouldClose(window)) { //���ڲ��ر�ÿһ֡��ˢ�»�ͼ
		float time = glfwGetTime();
		if ((int)time % 2 == 0)
			glUniform4f(glGetUniformLocation(ourShader.Program, "ourColor"), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			glUniform4f(glGetUniformLocation(ourShader.Program, "ourColor"), 0.0f, 1.0f, 0.0f, 1.0f);

		glViewport(0,0,screenWidth,screenHeight);//�����½�λ�ã�0��0���������ĳ��͸�
		glfwPollEvents();//��ȡ��Ҫ��λ�ñ����Ϣ,�������̵�
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//RGBA
		glClear(GL_COLOR_BUFFER_BIT);//����ɫ���г�ʼ����ֵ
		ourShader.Use();
		//glUseProgram(shaderProgram);
		glUniform1f(glGetUniformLocation(ourShader.Program,"time"), time);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glfwSwapBuffers(window);//˫�������
        
	}
	glfwTerminate();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1,&VBO);
	//glDeleteProgram(shaderProgram);
	return 0;
}
*/