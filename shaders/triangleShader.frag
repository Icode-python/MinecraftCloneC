#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
	// linearly interpolate between both textures (60% container, 40% awesomeface)
	FragColor = texture(texture1, TexCoord);
}