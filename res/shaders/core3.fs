#version 330 core //片段着色器
out vec4 color;
in vec3 vertexColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 LightPos; //世界坐标系下光源位置
uniform vec3 ViewPos;  //世界坐标系下相机位置

struct Material
{
    float diffuse;
    float specular;
};

uniform Material material;

void main()
{
//color = vec4(vertexColor,1.0f);//开启混合测试调整透明度才有效果
    vec3 lightDirection = normalize(LightPos-FragPos); //光照方向
    vec3 viewDirection = normalize(ViewPos - FragPos); //视野方向
    vec3 norm = normalize(Normal);

    //环境部分
    vec3 ambient = 0.5f * vertexColor;

    //漫反射
    float diff = material.diffuse * max(dot(norm,lightDirection),0.0f);
    vec3 diffuse = diff * vertexColor;
    //镜面反射
    vec3 halfAngle = normalize(viewDirection + lightDirection);
    float spec = material.specular * pow(max(dot(norm,halfAngle),0.0f),64.0f);
    vec3 specular = spec * vertexColor;

    color = vec4(ambient + diffuse + specular,1.0f);
}