/**
 * @file square.cpp
 *
 * @brief square definition
 *
 * @author Èeslárová Eliška CES0022
  **/

#include "Square.h"

const Vertex Square::vertices[6] = {
	{{ -0.2f, 0.2f, 0.0f, 1.0f},{0,1,1,1}},
	{{0.2f, 0.2f, 0.0f, 1.0f},{0,0,0,1}},
	{{-0.2f,  -0.2f, 0.0f, 1.0f},{0,0,0,1}},
	{{0.2f,  0.2f, 0.0f, 1.0f},{0,0,0,1}},
	{{-0.2f, -0.2f, 0.0f, 1.0f},{0,0,0,1}},
	{{0.2f,  -0.2f, 0.0f, 1.0f},{1,0,1,1}}
};

Square::Square()
	:Shape(vertices, 6)
{
}