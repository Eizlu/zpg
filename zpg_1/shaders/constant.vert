#version 400
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 worldPos;
out vec3 worldNorm;

void main() {
    worldPos = vec3(model * vec4(vp, 1.0));
    worldNorm = mat3(transpose(inverse(model))) * vn;
    gl_Position = projection * view * model * vec4(vp, 1.0);
}
