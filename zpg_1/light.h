#pragma once
#include <glm/ext/vector_float3.hpp>
#include "subject.h"
#include "shaderProgram.h"

class Light : public Subject {
protected:
    glm::vec3 color;
    float intensity;

public:
    Light(const glm::vec3& color, float intensity);
    virtual ~Light() = default;

    glm::vec3 getColor() const { return color; }
    float getIntensity() const { return intensity; }

    void setColor(const glm::vec3& c);
    void setIntensity(float i);

    virtual void applyToShader(ShaderProgram& shader, int index) const = 0;
};
