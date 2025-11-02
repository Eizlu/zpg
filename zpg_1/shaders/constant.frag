#version 400
in vec3 worldNorm;
in vec3 worldPos;
out vec4 fragColor;

uniform vec3 objectColor;

void main() {
    fragColor = vec4(objectColor, 1.0);
}
