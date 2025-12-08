#version 400
in vec3 worldNorm;
in vec3 worldPos;
in vec2 textCoord;
out vec4 fragColor;

uniform vec3 objectColor;
uniform sampler2D diffuseMap;    
uniform bool hasTexture;

void main() {
    if (hasTexture) {
        fragColor = texture(diffuseMap, textCoord);
    } else {
        fragColor = vec4(objectColor, 1.0);
    }
}
