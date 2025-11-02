#pragma once
#include "light.h"

class PointLight : public Light {
private:
    glm::vec3 position;
    float attenuation;

public:
    PointLight(const glm::vec3& pos, const glm::vec3& color, float intensity, float attenuation);

    glm::vec3 getPosition() const { return position; }
    float getAttenuation() const { return attenuation; }

    void setPosition(const glm::vec3& pos);
    void setAttenuation(float att);

    void applyToShader(ShaderProgram& shader, int index) const override;
};
