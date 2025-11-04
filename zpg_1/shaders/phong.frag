#version 400
#define MAX_LIGHTS 16

struct Light {
    int type;        // 0=ambient, 1=directional, 2=point, 3=spot
    vec3 position;   
    vec3 direction;  
    vec3 color;
    float intensity;
    float attenuation; 
    float cutoff;      
    int enabled;
};


in vec3 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform vec3 viewPos;  // Přidáno pro viewDir

float calculateAttenuation(float distance, float attenuation) {
    if (attenuation <= 0.0) return 1.0;
    return 1.0 / (1.0 + attenuation * distance);
}

void main() {
    vec3 norm = normalize(worldNorm);
    vec3 viewDir = normalize(viewPos - worldPos);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 result = ambient * objectColor;

    for(int i = 0; i < numLights; i++) {
    if(lights[i].type == 0) { // ambient
        result += vec4(0.1,0.1,0.1,1.0) * objectColor * vec4(lights[i].color,1.0);
        continue;
    }

    vec3 lightDir;
    float attenuation = 1.0;
    if(lights[i].type == 1) { // directional
        lightDir = normalize(-lights[i].direction);
    } else if(lights[i].type == 2) { // point
        lightDir = normalize(lights[i].position - worldPos);
        float distance = length(lights[i].position - worldPos);
        attenuation = calculateAttenuation(distance, lights[i].attenuation);
    } else if(lights[i].type == 3) { // spot
	if(lights[i].enabled == 0) continue;
        lightDir = normalize(lights[i].position - worldPos);
        float distance = length(lights[i].position - worldPos);
        attenuation = calculateAttenuation(distance, lights[i].attenuation);
        float theta = dot(lightDir, normalize(-lights[i].direction));
        if(theta < lights[i].cutoff) continue;
    }

    float NdotL = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir),0.0),32);

    vec4 diffuse = vec4(NdotL * lights[i].color * lights[i].intensity * attenuation, 1.0);
    vec4 specular = vec4(spec * lights[i].color * lights[i].intensity * attenuation, 1.0);

    result += (diffuse + specular) * objectColor;
    }


    fragColor = result;
}
