/**
 * @file triangle.cpp
 *
 * @brief triangle definiition
 *
 * @author Èeslárová Eliška CES0022
  **/
#include "Triangle.h"


const Vertex Triangle::vertices[3] = {
	{{0.0f , 0.3f , 0.0f ,1.f},{ 0, 1, 0, 1 }},
	{{0.3f , -0.3f , 0.0, 1.f},{ 1, 0, 0, 1 }},
	{{ -0.3f , -0.3f , 0.0f, 1.f },{ 0, 0, 0, 1 }}
};

Triangle::Triangle()
	:Shape(vertices, 3)
{
}