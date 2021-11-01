#version 330 core //片段着色器
out vec4 color;
in vec3 vertexColor;
in vec2 ourTextCoord;
uniform float time;
uniform vec4 ourColor;
uniform sampler2D texture0;//第二次
uniform sampler2D texture1;//第二次
void main()
{
color = vec4(vertexColor,1.0f);
//color = ourColor; //第一次作业
//color = texture(texture0,ourTextCoord);//第二次
}