#version 330
in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;


struct BaseLight {
    vec3 color;
    float ambient;
    float diffuse;
}; 

struct DirectionalLight {
    BaseLight light;
    vec3 dir;
}; 

struct PointLight {
    BaseLight light;
    vec3 pos;
    float constant;
    float linear;
    float exp;
}; 

out vec4 colour;

uniform sampler2D theTexture;
uniform DirectionalLight directional;
uniform PointLight point;
uniform vec3 view_pos;

vec3 DirectionalLighting(BaseLight light, vec3 dir);
vec3 PointLighting();

void main() {

    vec3 lightResult = vec3(0.0f, 0.0f, 0.0f);

    lightResult += DirectionalLighting(directional.light, directional.dir);
    lightResult += PointLighting();

    vec4 text = texture(theTexture, TexCoord);
    colour = vec4(text.rgb * lightResult, text.a);
}


vec3 DirectionalLighting(BaseLight light, vec3 dir) {
    
    vec3 ambient_col = light.color * light.ambient;
    
    float diffuseFactor = max(dot(normalize(Normal), normalize(dir)), 0.0);
    
    vec3 diffuseColor = light.color * diffuseFactor * light.diffuse;
    
    vec3 specular_comp = vec3(0.0f, 0.0f, 0.0f);
    if (diffuseFactor > 0.0f) {
        vec3 vec_specular = normalize(view_pos - FragPos);
        vec3 reflected = normalize(reflect(-dir, normalize(Normal)));
        float spec = pow(max(dot(vec_specular, reflected), 0.0f), 8);
        specular_comp = light.color * spec;
    }
    
    vec3 lightResult = ambient_col + diffuseColor + specular_comp;
    return lightResult;
}

vec3 PointLighting(){
    vec3 dir = point.pos - FragPos;
    float distance = length(dir);
    dir = normalize(dir);

    vec3 dir_contribution = DirectionalLighting(point.light, dir);
    float att = 1.0/(point.constant + point.linear * distance + point.exp * distance * distance);

    return att*dir_contribution;
}