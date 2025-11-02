#pragma once
#include "light.h"

class AmbientLight : public Light {
public:
    AmbientLight(const glm::vec3& color, float intensity);
    void applyToShader(ShaderProgram& shader, int index) const override;
};
