/*
 * SnakeCube.h
 *
 *  Created on: Mar 24, 2023
 *      Author: yloose
 */

#pragma once
#include<stdlib.h>

enum CubeDirection {
	Angled, Straight,
};

class Cube {
public:
	Cube *prev = NULL;
	Cube *next = NULL;

	// Denotes the position in 3d space
	struct {
		int x;
		int y;
		int z;
	} pos;

	// Denotes in which the cube is facing i.d. the relative position of the following cube
	struct {
		int x = 0;
		int y = 0;
		int z = 0;
	} rot;

	CubeDirection direction;

	Cube(CubeDirection _direction);
	// Rotate the cubes along the axis of the previous cube, thus only 4 different states of rotation are possible
	void rotate();
	//Calculate the position of the next cube and set it.
	void calcNextCube();
};
