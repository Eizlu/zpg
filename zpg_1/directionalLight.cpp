#include "directionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& dir, const glm::vec3& color, float intensity)
    : Light(color, intensity), direction(glm::normalize(dir)) {
}

void DirectionalLight::setDirection(const glm::vec3& dir) { direction = glm::normalize(dir); notifyObservers(); }

void DirectionalLight::applyToShader(ShaderProgram& shader, int index) const {
    shader.setUniform("lights[" + std::to_string(index) + "].type", 1);
    shader.setUniform("lights[" + std::to_string(index) + "].color", color);
    shader.setUniform("lights[" + std::to_string(index) + "].intensity", intensity);
    shader.setUniform("lights[" + std::to_string(index) + "].direction", direction);
}
