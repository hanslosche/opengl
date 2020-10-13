#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light { 

    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float k0;
    float k1;
    float k2;
};

 out vec4 FragColor;

 in vec3 FragPos;
 in vec3 Normal;
 in vec2 TexCoord;

 uniform Material material;
 uniform Light light;

 uniform vec3 viewPos;

void main(){
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize( light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoord)));

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoord)));

    // calc attenuation
    float dist = length(light.position - FragPos);
    float attenuation = 1.0 / (light.k0 + light.k1 * dist * light.k2 * (dist * dist));

    // apply attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    FragColor = vec4(vec3(ambient + diffuse + specular), 1.0);

}