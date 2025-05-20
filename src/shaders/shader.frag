#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct light{
	vec3 color;
	vec3 dir;
	float ambient;
	float diffuse;
	vec3 pos;
};

out vec4 colour;
uniform sampler2D theTexture;
uniform light directional;
uniform vec3 view_pos;

void main(){
	vec4 ambient_col = vec4(directional.color, 1.0f)* directional.ambient;

	float diffuseFactor = max(dot(normalize(Normal), normalize(directional.dir)),0);
	vec4 diffuseColor = vec4(directional.color, 1.0f) * diffuseFactor * directional.diffuse;

	//specular
	vec4 specular_comp = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	if (diffuseFactor>0.0f){
		vec3 vec_specular = normalize(view_pos - FragPos);
		vec3 reflected = normalize(reflect(-directional.dir, normalize(Normal)));

		float spec = pow(max(dot(vec_specular, reflected), 0.0f), 8);
		specular_comp = vec4(directional.color, 1.0f) * spec;
	}
	


	colour =  texture(theTexture, TexCoord) * (ambient_col + diffuseColor + specular_comp);



}
