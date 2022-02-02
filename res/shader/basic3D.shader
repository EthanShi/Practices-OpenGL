#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 viewport;

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * viewport * vec4(aPos, 1.0f);
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_TexCoord);
};