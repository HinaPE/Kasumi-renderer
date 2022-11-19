#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform bool has_diffuse_texture;
uniform bool has_specular_texture;
uniform bool has_normal_texture;
uniform bool has_height_texture;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_normal;
uniform sampler2D texture_height;

void main()
{
    vec4 color = vec4(57.f / 255.9f, 197.f / 255.9f, 187.f / 255.9f, 1.0f);
    if (has_diffuse_texture)
    {
        color = texture(texture_diffuse, TexCoords);
    }
    FragColor = color;
}
