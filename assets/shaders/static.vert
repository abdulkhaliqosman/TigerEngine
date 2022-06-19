#version 330 core

uniform mat4 model;
uniform mat4 view;       // camera
uniform mat4 projection; // frustum

uniform bool hasPose;
uniform mat4 jointTransform [128];

in vec3 position;
in vec3 normal;
in vec2 texCoord;

in ivec4 joints;
in vec4 weights;

out vec3 fragNormal;
out vec3 fragPosition;
out vec2 uv;

void main() 
{

	fragPosition = vec3(model * vec4(position, 1.0));
	fragNormal = vec3(model * vec4(normal, 0.0f));
	uv = texCoord;

	if(hasPose)
	{
		mat4 skin = weights.x * jointTransform[joints.x] 
				+ weights.y * jointTransform[joints.y]
				+ weights.z * jointTransform[joints.z]
				+ weights.w * jointTransform[joints.w];

		fragPosition = vec3(model * skin * vec4(position, 1.0));
		fragNormal = vec3(model * skin * vec4(normal, 0.0f));

		gl_Position = projection * view * model * skin * vec4(position, 1.0);
	}
	else
	{
		gl_Position = projection * view * model * vec4(position, 1.0);
	}
}