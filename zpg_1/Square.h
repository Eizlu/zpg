/**
 * @file square.h
 *
 * @brief square declaration
 *
 * @author Èeslárová Eliška CES0022
  **/
#pragma once
#include "Shape.h"

class Square : public Shape {
private:
	static const Vertex vertices[6];
public:
	Square();
};
