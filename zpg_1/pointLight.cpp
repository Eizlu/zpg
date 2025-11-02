#include "pointLight.h"

PointLight::PointLight(const glm::vec3& pos, const glm::vec3& color, float intensity, float attenuation)
    : Light(color, intensity), position(pos), attenuation(attenuation) {
}

void PointLight::setPosition(const glm::vec3& pos) { position = pos; notifyObservers(); }
void PointLight::setAttenuation(float att) { attenuation = att; notifyObservers(); }

void PointLight::applyToShader(ShaderProgram& shader, int index) const {
    shader.setUniform("lights[" + std::to_string(index) + "].type", 2);
    shader.setUniform("lights[" + std::to_string(index) + "].position", position);
    shader.setUniform("lights[" + std::to_string(index) + "].color", color);
    shader.setUniform("lights[" + std::to_string(index) + "].intensity", intensity);
    shader.setUniform("lights[" + std::to_string(index) + "].attenuation", attenuation);
}
