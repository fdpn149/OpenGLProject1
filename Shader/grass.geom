#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 12) out;

in int type[];

out vec2 texCoord;
out float colorVariation;

uniform mat4 projection;
uniform mat4 view;
uniform sampler2D wind;
uniform float time;

const float PI = 3.14;
const float MIN_SIZE = 0.4f;
const int NUM_OCTAVES = 5;

// UTILS Prototypes
mat4 rotationX(float angle);
mat4 rotationY(float angle);
mat4 rotationZ(float angle);
float random (vec2 st);
float noise (vec2 st);
float fbm (vec2 st);

// Main functions
float grassSize;

void createQuad(vec3 basePos, mat4 crossModel)
{
    vec4 vertexPosition[4];
	vertexPosition[0] = vec4(-0.25, 0.0, 0.0, 0.0); 	// down left
	vertexPosition[1] = vec4( 0.25, 0.0, 0.0, 0.0);		// down right
	vertexPosition[2] = vec4(-0.25, 0.5, 0.0, 0.0);		// up left
	vertexPosition[3] = vec4( 0.25, 0.5, 0.0, 0.0);		// up right

    vec2 texCoords[4];

	vec2 grass1TexCoords[4];
	grass1TexCoords[0] = vec2( 0.0f, 0.5f);	// down left
	grass1TexCoords[1] = vec2(0.25f, 0.5f);	// down right
	grass1TexCoords[2] = vec2( 0.0f, 0.0f);	// up left
	grass1TexCoords[3] = vec2(0.25f, 0.0f);	// up right

	
	vec2 grass2TexCoords[4];
	grass2TexCoords[0] = vec2(0.25f, 0.5f);	// down left
	grass2TexCoords[1] = vec2( 0.5f, 0.5f);	// down right
	grass2TexCoords[2] = vec2(0.25f, 0.0f);	// up left
	grass2TexCoords[3] = vec2( 0.5f, 0.0f);	// up right

	vec2 grass3TexCoords[4];
	grass3TexCoords[0] = vec2( 0.5f, 0.5f);	// down left
	grass3TexCoords[1] = vec2(0.75f, 0.5f);	// down right
	grass3TexCoords[2] = vec2( 0.5f, 0.0f);	// up left
	grass3TexCoords[3] = vec2(0.75f, 0.0f);	// up right

	vec2 grass4TexCoords[4];
	grass4TexCoords[0] = vec2(0.75f, 0.5f);	// down left
	grass4TexCoords[1] = vec2( 1.0f, 0.5f);	// down right
	grass4TexCoords[2] = vec2(0.75f, 0.0f);	// up left
	grass4TexCoords[3] = vec2( 1.0f, 0.0f);	// up right

	vec2 flower1TexCoords[4];
	flower1TexCoords[0] = vec2( 0.0f, 1.0f);	// down left
	flower1TexCoords[1] = vec2(0.25f, 1.0f);	// down right
	flower1TexCoords[2] = vec2( 0.0f, 0.5f);	// up left
	flower1TexCoords[3] = vec2(0.25f, 0.5f);	// up right

	vec2 flower2TexCoords[4];
	flower2TexCoords[0] = vec2(0.25f, 1.0f);	// down left
	flower2TexCoords[1] = vec2( 0.5f, 1.0f);	// down right
	flower2TexCoords[2] = vec2(0.25f, 0.5f);	// up left
	flower2TexCoords[3] = vec2( 0.5f, 0.5f);	// up right

	vec2 flower3TexCoords[4];
	flower3TexCoords[0] = vec2( 0.5f, 1.0f);	// down left
	flower3TexCoords[1] = vec2(0.75f, 1.0f);	// down right
	flower3TexCoords[2] = vec2( 0.5f, 0.5f);	// up left
	flower3TexCoords[3] = vec2(0.75f, 0.5f);	// up right

	vec2 flower4TexCoords[4];
	flower4TexCoords[0] = vec2(0.75f, 1.0f);	// down left
	flower4TexCoords[1] = vec2( 1.0f, 1.0f);	// down right
	flower4TexCoords[2] = vec2(0.75f, 0.5f);	// up left
	flower4TexCoords[3] = vec2( 1.0f, 0.5f);	// up right

	switch(type[0])
	{
		case 1:
			texCoords = grass1TexCoords;
			break;
		case 2:
			texCoords  = grass2TexCoords;
			break;
		case 3:
			texCoords  = grass3TexCoords;
			break;
		case 4:
			texCoords  = grass4TexCoords;
			break;
		case 5:
			texCoords  = flower1TexCoords;
			break;
		case 6:
			texCoords  = flower2TexCoords;
			break;
		case 7:
			texCoords  = flower3TexCoords;
			break;
		case 8:
			texCoords  = flower4TexCoords;
			break;
	}


	// wind
	vec2 windDirection = vec2(1.0, 1.0); 
	float windStrength = 0.15f;

	vec2 uv = basePos.xz / 10.0f + windDirection * windStrength * time * 0.25;
	uv.x = mod(uv.x, 1.0f);
	uv.y = mod(uv.y, 1.0f);

	vec4 wind = texture(wind, uv);

	mat4 modelWind = (rotationX(wind.x * PI * 0.75f - PI * 0.25f) * rotationZ(wind.y * PI * 0.75f - PI * 0.25f));

    mat4 modelRandY = rotationY(random(basePos.zx) * PI);

	mat4 modelWindApply = mat4(1.0f);

    for(int iii = 0; iii < 4; ++iii) 
    {
		if(iii == 2) 
		{
			modelWindApply = modelWind;
		}

        gl_Position = projection * view * (gl_in[0].gl_Position + modelWindApply * modelRandY * crossModel * vertexPosition[iii] * grassSize);
        texCoord = texCoords[iii];
        EmitVertex();
    }

    EndPrimitive();
}

void createGrass()
{
    mat4 model0, model45, modeln45;
    model0 = mat4(1.0f);
    model45 = rotationY(radians(45.0f));
    modeln45 = rotationY(radians(-45.0f));

    createQuad(gl_in[0].gl_Position.xyz, model0);
    createQuad(gl_in[0].gl_Position.xyz, model45);
    createQuad(gl_in[0].gl_Position.xyz, modeln45);
}

void main()
{
    // set grass size
    grassSize = random(gl_in[0].gl_Position.xz * (1.0f - MIN_SIZE) + MIN_SIZE);

    // create grass
    createGrass();

	// color variation
	colorVariation = fbm(gl_in[0].gl_Position.xz);
}

// UTIL Defs
mat4 rotationX(float angle) 
{
	return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}
 
mat4 rotationY(float angle)
{
	return mat4(	cos(angle),		0,		sin(angle),	0,
			 				0,		1.0,			 0,	0,
					-sin(angle),	0,		cos(angle),	0,
							0, 		0,				0,	1);
}
 
mat4 rotationZ(float angle) 
{
	return mat4(	cos(angle),		-sin(angle),	0,	0,
			 		sin(angle),		cos(angle),		0,	0,
							0,				0,		1,	0,
							0,				0,		0,	1);
}

float random (vec2 st) 
{
    return fract(sin(dot(st.xy,vec2(12.9898,78.233))) * 43758.5453123);
}

float noise (vec2 st) {
	vec2 i = floor(st);
	vec2 f = fract(st);
 
	// Four corners in 2D of a tile
	float a = random(i);
	float b = random(i + vec2(1.0, 0.0));
	float c = random(i + vec2(0.0, 1.0));
	float d = random(i + vec2(1.0, 1.0));
 
	// Smooth Interpolation
 
	// Cubic Hermine Curve.  Same as SmoothStep()
	vec2 u = f*f*(3.0-2.0*f);
	// u = smoothstep(0.,1.,f);
 
	// Mix 4 coorners percentages
	return mix(a, b, u.x) +
	(c - a)* u.y * (1.0 - u.x) +
	(d - b) * u.x * u.y;
}

float fbm (vec2 st)
{
	float v = 0.0;
	float a = 0.5;
	vec2 shift = vec2(100.0);

	// Rotate to reduce axial bias
	mat2 rot = mat2(cos(0.5), sin(0.5), -sin(0.5), cos(0.50));

	for (int iii = 0; iii < NUM_OCTAVES; ++iii) 
	{
		v += a * noise(st);

		st = rot * st * 2.0 + shift;

		a *= 0.5;
	}

	return v;
}