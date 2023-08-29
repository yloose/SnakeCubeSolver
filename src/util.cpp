/*
 * util.cpp
 *
 *  Created on: Mar 24, 2023
 *      Author: yloose
 */

#include <iostream>

#include "util.h"
#include "SnakeCube.h"

using namespace std;

void printCube(Cube *cube) {
	int i = 0;
	while (cube != NULL) {
		cout << "Cube " << i << " at (" << cube->pos.x << ", " << cube->pos.y << ", " << cube->pos.z << ")." << endl;
		cube = cube->prev;
		i++;
	}
}

Cube* addCube(Cube *head, Cube *newCube) {
	head->next = newCube;
	newCube->prev = head;
	return newCube;
}
