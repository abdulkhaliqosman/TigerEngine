#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;
in vec2 uv;

uniform vec3 lightPos;
uniform sampler2D tex0;

out vec4 FragColor;

void blinn_phong();

void main() 
{
	//FragColor = vec4(1.0f, 0.2f, 0.5f, 1.0f);

	vec4 diffuseColor = texture(tex0, uv);
	// vec3 n = normalize(normal);
	// vec3 l = normalize(light);

	// float diffuseIntensity = clamp(dot(n, l), 0, 1);
	// FragColor = diffuseColor * diffuseIntensity;
	// FragColor = diffuseColor + vec4(0.2f, 0.2f, 0.2f, 1.0f);

	blinn_phong();
}

void blinn_phong()
{
	// material
	float specPower = 32.0f;
	float ambient = 0.2f;

	vec4 color = vec4(0.3f, 0.3f, 0.3f, 1.0f); //texture(tex0, uv);

	vec3 n = normalize(fragNormal);
	vec3 v = normalize(-fragPosition);
	vec3 l = normalize(lightPos - fragPosition);
	vec3 h = normalize(v+l);


	float diffuse = max(dot(n, l), 0.0f);

	float spec = pow(max(dot(n, h), 0.0f), specPower);

	FragColor = vec4( (ambient + diffuse) * color.rgb + spec * vec3(0.5,0.5,0.5), 1.0f);
}