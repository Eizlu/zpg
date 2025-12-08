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

struct Material {
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Ns;
};

in vec3 worldPos;
in vec3 worldNorm;
in vec2 textCoord;
out vec4 fragColor;

uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform vec3 viewPos;  // Přidáno pro viewDir
uniform Material material;

uniform sampler2D diffuseMap;    // <-- textura
uniform bool hasTexture;

float calculateAttenuation(float distance, float attenuation) {
    if (attenuation <= 0.0) return 1.0;
    return 1.0 / (1.0 + attenuation * distance);
}

void main() {
    vec3 norm = normalize(worldNorm);
    vec3 viewDir = normalize(viewPos - worldPos);
    vec3 baseColor;
    if (hasTexture) {
        baseColor = texture(diffuseMap, textCoord).rgb;
    }
    else if (material.Kd != vec3(0.0)) {
    	baseColor = material.Kd;
    }
    else {
    	baseColor = vec3(0.8, 0.8, 0.8); // světle šedá
    }
    vec3 result = vec3(0.0);

    for(int i = 0; i < numLights; i++) {
    if(lights[i].type == 0) { // ambient
        result += baseColor  * lights[i].color * lights[i].intensity;
        continue;
    }

    vec3 lightDir;
    float attenuation = 1.0;

    if(lights[i].type == 1) { // directional
        lightDir = normalize(-lights[i].direction);
    } 
    else { // point nebo spot
        vec3 toLight = lights[i].position - worldPos;
        float distance = length(toLight);
        lightDir = normalize(toLight);
        attenuation = calculateAttenuation(distance, lights[i].attenuation);

    	if(lights[i].type == 3) { // spot
	    if(lights[i].enabled == 0)       // <---- TADY JE TVOJE CHYBĚJÍCÍ PODMÍNKA
            continue;

	    float theta = dot(lightDir, normalize(-lights[i].direction));
            if(theta < lights[i].cutoff) continue;
	}
    }
    

    float NdotL = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = baseColor  * NdotL * lights[i].color * lights[i].intensity * attenuation;

    vec3 reflectDir = reflect(-lightDir, norm);
    float specAngle = max(dot(viewDir, reflectDir), 0.0);
    float specFactor = pow(specAngle, max(material.Ns, 1.0));

    vec3 specular = material.Ks * specFactor * lights[i].color * lights[i].intensity * attenuation;

    result += diffuse + specular;
    }

    fragColor =  vec4(result, 1.0);
}
