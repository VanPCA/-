#version 330 core  //������ɫ���汾
layout(location = 0) in vec3 position;   //���Դ����ȡ����ӳ�䵽position
layout(location = 1) in vec3 ourColor;   //��ȡ��ɫ
//layout(location = 2) in vec2 textCoord;   //��ȡ����
out vec3 vertexColor; //����Ƭ����ɫ��
out vec2 ourTextCoord;
void main()
{
    gl_Position = vec4(position, 1.0f);  //���ն�����Ϣ��ά����
    vertexColor = ourColor;
    //ourTextCoord = vec2(textCoord.x,1-textCoord.y);//���µߵ� �ڶ���
}