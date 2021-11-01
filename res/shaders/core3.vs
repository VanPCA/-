#version 330 core  //顶点着色器版本
layout(location = 0) in vec3 position;   //从显存里获取数据映射到position
layout(location = 1) in vec3 ourColor;   //获取颜色
layout(location = 2) in vec3 normal;     //获取法向量

out vec3 vertexColor; //传给片段着色器
out vec3 Normal;
out vec3 FragPos; //观测点位置
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
void main()
{
    gl_Position = projection * view * transform * vec4(position, 1.0f);  //最终顶点信息四维向量
    FragPos = vec3(transform*vec4(position,1.0f));
    vertexColor = ourColor;
    Normal = mat3(transpose(inverse(transform)))*normal;
}