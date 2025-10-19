#include "light.h"

Light::Light()
	: position(0.0f, 0.0f, 0.0f), color(1.0f, 1.0f, 1.0f), intensity(1.0f)
{
}

Light::Light(const glm::vec3& position, const glm::vec3& color, float intensity)
	: position(position), color(color), intensity(intensity)
{
}

void Light::setPosition(const glm::vec3& position)
{
	this->position = position;
	notifyObservers();
}

void Light::setColor(const glm::vec3& color)
{
	this->color = color;
	notifyObservers();
}

void Light::setIntensity(float intensity)
{
	this->intensity = intensity;
	notifyObservers();
}

glm::vec3 Light::getPosition() const
{
	return position;
}	

glm::vec3 Light::getColor() const
{
	return color;
}

float Light::getIntensity() const
{
	return intensity;
}

void Light::addObserver(LightObserver* observer)
{
	observers.push_back(observer);
}

void Light::removeObserver(LightObserver* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Light::notifyObservers()
{
	for (auto observer : observers) {
		observer->onLightChanged(*this);
	}
}