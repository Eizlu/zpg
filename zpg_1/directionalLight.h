#pragma once
#include "light.h"

class DirectionalLight : public Light {
private:
    glm::vec3 direction;

public:
    DirectionalLight(const glm::vec3& dir, const glm::vec3& color, float intensity);

    glm::vec3 getDirection() const { return direction; }
    void setDirection(const glm::vec3& dir);

    void applyToShader(ShaderProgram& shader, int index) const override;
};
