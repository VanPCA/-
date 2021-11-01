#version 330 core  //顶点着色器版本
layout(location = 0) in vec3 position;   //从显存里获取数据映射到position
layout(location = 1) in vec3 ourColor;   //获取颜色
//layout(location = 2) in vec2 textCoord;   //获取纹理
out vec3 vertexColor; //传给片段着色器
out vec2 ourTextCoord;
void main()
{
    gl_Position = vec4(position, 1.0f);  //最终顶点信息四维向量
    vertexColor = ourColor;
    //ourTextCoord = vec2(textCoord.x,1-textCoord.y);//上下颠倒 第二次
}