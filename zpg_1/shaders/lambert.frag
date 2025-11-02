#version 400
#define MAX_LIGHTS 4

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
    float attenuation;
};

in vec3 worldNorm;
in vec3 worldPos;
out vec4 fragColor;

uniform Light lights[MAX_LIGHTS];
uniform int numLights;

float calculateAttenuation(float distance, float attenuation) {
    if (attenuation <= 0.0) return 1.0;
    return 1.0 / (1.0 + attenuation * distance);
}

void main() {
    vec3 norm = normalize(worldNorm);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 result = ambient;

    for(int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - worldPos);
        float distance = length(lights[i].position - worldPos);
        float att = calculateAttenuation(distance, lights[i].attenuation);
        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = diff * vec4(lights[i].color * lights[i].intensity, 1.0) * att;
        result += diffuse * objectColor;
    }

    fragColor = result;
}
