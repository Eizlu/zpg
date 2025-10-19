#pragma once
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include "lightObserver.h"


class Light
{
private:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;

	std::vector<LightObserver*> observers;
public:	
	Light();
	Light(const glm::vec3& position, const glm::vec3& color, float intensity);

	void setPosition(const glm::vec3& position);
	void setColor(const glm::vec3& color);
	void setIntensity(float intensity);

	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;
	float getIntensity() const;

	void addObserver(LightObserver* observer);
	void removeObserver(LightObserver* observer);
	void notifyObservers();
};