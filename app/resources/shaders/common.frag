#version 330 core

out vec4 color;

in vec2 _texturePosition;
in vec3 _normal;
in vec3 _fragmentPosition;

vec3 objectColor = vec3(0.0f, 1.0f, 0.0f);
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

uniform vec3 lightPosition;

void main()
{    
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(_normal);
    vec3 lightDir = normalize(lightPosition - _fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0f);
}
