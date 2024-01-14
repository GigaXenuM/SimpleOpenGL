#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texturePosition;
layout (location = 2) in vec3 normal;

out vec2 _texturePosition;
out vec3 _normal;
out vec3 _fragmentPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    _texturePosition = texturePosition;
    _normal = normal;
    _fragmentPosition = vec3(model * vec4(position, 1.0f));

    gl_Position = projection * view * model * vec4(position, 1.0);
}
