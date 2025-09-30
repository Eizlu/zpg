/**
 * @file triangle.h
 *
 * @brief triangle declaration
 *
 * @author �esl�rov� Eli�ka CES0022
  **/
#pragma once
#include "Shape.h"

class Triangle : public Shape {
private:
	static const Vertex vertices[3];
public:
	Triangle();
};