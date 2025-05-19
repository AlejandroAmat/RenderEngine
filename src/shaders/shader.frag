#version 330

in vec4 vCol;
in vec2 TexCoord;

struct light{
	vec3 color;
	vec3 pos;
	float ambient;
};

out vec4 colour;
uniform sampler2D theTexture;
uniform light directional;

void main(){
	vec4 ambient_col = vec4(directional.color, 1.0f)* directional.ambient;
	colour =  texture(theTexture, TexCoord) * ambient_col;
}
