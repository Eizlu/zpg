#include "ambientLight.h"

AmbientLight::AmbientLight(const glm::vec3& color, float intensity)
    : Light(color, intensity) {
}

void AmbientLight::applyToShader(ShaderProgram& shader, int index) const {
    shader.setUniform("lights[" + std::to_string(index) + "].type", 0);
    shader.setUniform("lights[" + std::to_string(index) + "].color", color);
    shader.setUniform("lights[" + std::to_string(index) + "].intensity", intensity);
}
