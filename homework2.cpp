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
	{   //position           //color               //��������
		0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,       1.0f,1.0f,                 //����
		0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,      1.0f,0.0f,                 //����
		-0.5f,-0.5f,0.0f,      1.0f,0.0f,0.0f,     0.0f,0.0f,                 //����
		-0.5f,0.5f,0.0f,      1.0f,0.0f,0.0f,      0.0f,1.0f,                 //����
	};

	//������Ϣ
	unsigned int indices[] =
	{
		0,1,3,//��һ��������
		1,2,3//�ڶ���
	};

	//��������
	GLuint VAO, VBO; //�������ж��󣨸���������ݣ������㻺�����(������)���ɶԳ���
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//��VAO��VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//����VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); //λ��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); //��ɫ
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); //��ɫ
	glEnableVertexAttribArray(2);

	GLuint EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//���
	glBindVertexArray(0);//���

	GLuint texture;//��������
	int width, height;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//�����������ʱ��С
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//����С������ʱ�Ŵ�

	unsigned char* image = SOIL_load_image("res/images/01.jpg",&width,&height,0,SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,image);//ͼƬ�����������
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);//���


	GLuint texture1;//��������
	int width1, height1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//�����������ʱ��С
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//����С������ʱ�Ŵ�

	unsigned char* image1 = SOIL_load_image("res/images/02.jpg", &width1, &height1, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);//ͼƬ�����������
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);//���


	//����ѭ��
	while (!glfwWindowShouldClose(window)) { //���ڲ��ر�ÿһ֡��ˢ�»�ͼ
		float time = glfwGetTime();
		glViewport(0, 0, screenWidth, screenHeight);//�����½�λ�ã�0��0���������ĳ��͸�
		glfwPollEvents();//��ȡ��Ҫ��λ�ñ����Ϣ,�������̵�
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//RGBA
		glClear(GL_COLOR_BUFFER_BIT);//����ɫ���г�ʼ����ֵ
		ourShader.Use();
		glActiveTexture(GL_TEXTURE0);//�����һ����������
		
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
		glfwSwapBuffers(window);//˫�������

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