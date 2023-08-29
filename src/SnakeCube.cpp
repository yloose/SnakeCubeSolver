/*
 * SnakeCube.cpp
 *
 *  Created on: Mar 24, 2023
 *      Author: yloose
 */

#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "SnakeCube.h"
#include "util.h"

using namespace std;

static int cubeSize = -1;

Cube::Cube(CubeDirection _direction) {
	this->direction = _direction;
}

void Cube::rotate() {
	if (this->prev == NULL) {
		int x = this->rot.x + this->rot.y + this->rot.z == 0 ? 1 : this->rot.y;
		int y = this->rot.z;
		this->rot.z = this->rot.x;
		this->rot.x = x;
		this->rot.y = y;
		return;
	}

	if (this->direction == Angled) {
		int idx = 1 - abs(this->prev->rot.x), idy = 1 - abs(this->prev->rot.y), idz = 1 - abs(this->prev->rot.z);

		int x = this->rot.x + this->rot.y + this->rot.z == 0 ? this->prev->rot.y : ((this->rot.y * idy == -1 || this->rot.z * idz == -1) ? 1 : this->rot.x == 1 ? -1 : 0) * idx;
		int y = this->rot.x + this->rot.y + this->rot.z == 0 ? this->prev->rot.z : ((this->rot.z * idz == -1 || this->rot.x * idx == -1) ? 1 : this->rot.y == 1 ? -1 : 0) * idy;
		int z = this->rot.x + this->rot.y + this->rot.z == 0 ? this->prev->rot.x : ((this->rot.x * idx == -1 || this->rot.y * idy == -1) ? 1 : this->rot.z == 1 ? -1 : 0) * idz;

		this->rot.x = x;
		this->rot.y = y;
		this->rot.z = z;

	} else {
		// A straight cube can adopt the rotation of the previous cube as it does not matter.
		this->rot = this->prev->rot;
	}
}

void Cube::calcNextCube() {
	// Calculate position of next cube
	if (next != NULL) {
		this->next->pos.x = this->pos.x + this->rot.x;
		this->next->pos.y = this->pos.y + this->rot.y;
		this->next->pos.z = this->pos.z + this->rot.z;
	}
}

bool validateCube(Cube *cube) {

	// Check if the first (new) cube is out of bounds
	if (cube->pos.x < 0 || cube->pos.y < 0 || cube->pos.z < 0 || cube->pos.x >= cubeSize || cube->pos.y >= cubeSize || cube->pos.z >= cubeSize) {
		return false;
	}

	// Check if the first cube is in a already occupied place
	Cube *prevCube = cube->prev;
	while (prevCube != NULL) {
		if (prevCube->pos.x == cube->pos.x && prevCube->pos.y == cube->pos.y && prevCube->pos.z == cube->pos.z) {
			return false;
		}
		prevCube = prevCube->prev;
	}

	return true;
}

void solve(Cube *cube) {

	if (cube->next == NULL) {
		cout << "Solved: " << endl;
		printCube(cube);
		exit(0);
	}

	// Rotate the cube until the next cube is in a valid position
	for (size_t i = 0; i < 4; i++) {
		cube->rotate();
		cube->calcNextCube();
		if (!validateCube(cube->next)) {
			continue;
		}
		solve(cube->next);
	}
}

int main(int argc, char **argv) {

	// Create class based doubly linked list of cubes.
	Cube *snakeCube;

	while (cubeSize < 0 || cubeSize > 10) {
		cout << "Input cube size: ";
		cin >> cubeSize;
	}

	Cube *head = snakeCube = new Cube(Angled);
	for (size_t i = 1; i < pow((float) cubeSize, 3) - 1; i++) {
		char input;
		cout << "Is cube " << i << " straight or angled relative to the following one? (s/a): ";
		cin >> input;
		switch (input) {
		case 'a':
			head = addCube(head, new Cube(Angled));
			break;
		case 's':
			head = addCube(head, new Cube(Straight));
			break;
		default:
			i--;
			break;
		}
	}
    head = addCube(head, new Cube(Angled));

	solve(snakeCube);

	cout << "Could not solve." << endl;

	return 0;
}
