#include "SpotLight.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

SpotLight::SpotLight(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& color,
                     float intensity, float attenuation, float cutoff)
    : Light(color, intensity),
      position(pos),
      direction(glm::normalize(dir)),
      attenuation(attenuation),
      cutoff(glm::cos(glm::radians(cutoff))),
      enabled(false) {}

void SpotLight::setDirection(const glm::vec3& dir) { direction = glm::normalize(dir); notifyObservers(); }
void SpotLight::setPosition(const glm::vec3& pos) { position = pos; notifyObservers(); }
void SpotLight::setEnabled(bool e) { enabled = e; notifyObservers(); }
bool SpotLight::isEnabled() const { return enabled; }

void SpotLight::applyToShader(ShaderProgram& shader, int index) const {
    shader.setUniform("lights[" + std::to_string(index) + "].type", 3);
    shader.setUniform("lights[" + std::to_string(index) + "].position", position);
    shader.setUniform("lights[" + std::to_string(index) + "].direction", direction);
    shader.setUniform("lights[" + std::to_string(index) + "].color", color);
    shader.setUniform("lights[" + std::to_string(index) + "].intensity", intensity);
    shader.setUniform("lights[" + std::to_string(index) + "].attenuation", attenuation);
    shader.setUniform("lights[" + std::to_string(index) + "].cutoff", cutoff);
    shader.setUniform("lights[" + std::to_string(index) + "].enabled", enabled ? 1 : 0);
}
