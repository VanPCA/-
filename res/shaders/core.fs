#version 330 core
out vec4 color;
in vec3 vertexColor;
//in vec2 ourTextCoord;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 LightPos;
uniform vec3 ViewPos;
//uniform float time;
//uniform sampler2D texture0;

struct Material
{
float diffuse;
float specular;
};

uniform Material material;


void main()
{
   //color = vec4(vertexColor,1.0f);
  //color = texture(texture0,ourTextCoord);
  vec3 lightDirection = normalize(LightPos - FragPos);
  vec3 viewDirection = normalize(ViewPos-FragPos);
  vec3 norm = normalize(Normal);

      //ambient
      vec3 ambient = 0.2f * vertexColor;

      //diffuse
      float diff = material.diffuse * max( dot(norm,lightDirection),0.0f);
      vec3 diffuse = diff * vertexColor;

      //specular
      vec3 halfAngle = normalize(viewDirection + lightDirection);
      float spec= material.specular * pow ( max (dot(norm,halfAngle), 0.0f),64.0f);
      vec3 specular = spec * vertexColor;

      color = vec4(ambient + specular + diffuse, 1.0f);
};