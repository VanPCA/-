#version 330 core //Ƭ����ɫ��
out vec4 color;
in vec3 vertexColor;
in vec2 ourTextCoord;
uniform float time;
uniform vec4 ourColor;
uniform sampler2D texture0;//�ڶ���
uniform sampler2D texture1;//�ڶ���
void main()
{
color = vec4(vertexColor,1.0f);
//color = ourColor; //��һ����ҵ
//color = texture(texture0,ourTextCoord);//�ڶ���
}