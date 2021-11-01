#ifndef Moon_h
#define Moon_h

#include <GL/glew.h>

GLfloat vertices_moon[] =  //用作月亮的小立方体
{
	//position               //color
	-0.5f,-0.5f,-0.5f,       1.0f,1.0f,0.0f,
	0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,

	-0.5f,-0.5f,0.5f,		 1.0f,1.0f,0.0f,
	0.5f,-0.5f,0.5f,		 1.0f,1.0f,0.0f,
	0.5f,0.5f,0.5f,			 1.0f,1.0f,0.0f,
	0.5f,0.5f,0.5f,			 1.0f,1.0f,0.0f,
	-0.5f,0.5f,0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,-0.5f,0.5f,		 1.0f,1.0f,0.0f,

	-0.5f,0.5f,0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,-0.5f,0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,0.5f,0.5f,		 1.0f,1.0f,0.0f,

	0.5f,0.5f,0.5f,			 1.0f,1.0f,0.0f,
	0.5f,0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,-0.5f,0.5f,		 1.0f,1.0f,0.0f,
	0.5f,0.5f,0.5f,			 1.0f,1.0f,0.0f,

	-0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,-0.5f,0.5f,		 1.0f,1.0f,0.0f,
	0.5f,-0.5f,0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,-0.5f,0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,-0.5f,-0.5f,		 1.0f,1.0f,0.0f,

	-0.5f,0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,0.5f,-0.5f,		 1.0f,1.0f,0.0f,
	0.5f,0.5f,0.5f,			 1.0f,1.0f,0.0f,
	0.5f,0.5f,0.5f,			 1.0f,1.0f,0.0f,
	-0.5f,0.5f,0.5f,		 1.0f,1.0f,0.0f,
	-0.5f,0.5f,-0.5f,		 1.0f,1.0f,0.0f,
};

class Moon
{
public:
	Moon() {
		this->update();
	}
	void Draw(Shader& shader) {
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
private:
	GLuint VAO, VBO;
	void update() {
		//传入数据
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		//绑定VAO和VBO
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		//传输数据
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_moon), vertices_moon, GL_STATIC_DRAW);
		//设置VAO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); //位置
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); //位置
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑
		glBindVertexArray(0);//解绑
	}
};

#endif // !Moon_h
