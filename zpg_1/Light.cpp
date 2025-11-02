#include "light.h"

Light::Light(const glm::vec3& color, float intensity)
    : color(color), intensity(intensity) {
}

void Light::setColor(const glm::vec3& c) { color = c; notifyObservers(); }
void Light::setIntensity(float i) { intensity = i; notifyObservers(); }
