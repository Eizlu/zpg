#pragma once
#include "light.h"

class SpotLight : public Light {
private:
    glm::vec3 position;
    glm::vec3 direction;
    float attenuation;
    float cutoff; // cos(úhel kužele)
    bool enabled;

public:
    SpotLight(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& color,
        float intensity, float attenuation, float cutoff);

    void setDirection(const glm::vec3& dir);
    void setPosition(const glm::vec3& pos);
    void setEnabled(bool e);
    bool isEnabled() const;

    void applyToShader(ShaderProgram& shader, int index) const override;
};
