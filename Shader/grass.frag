#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in float colorVariation;

uniform sampler2D grassTex;

void main()
{
	vec4 color = texture(grassTex, texCoord);
	if (color.a < 0.25f ) discard;

	color.xyz = mix(color.xyz, 0.5 * color.xyz, colorVariation);

	FragColor = color;
}
