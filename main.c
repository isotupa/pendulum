#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define G 1 
#define PI 3.14
#define height 100
#define width 30

double x, y = 0;
double ang = PI/2;
double vel, acc = 0;
double L = 15;
double drag = 0.995;

int originx = 40;
int originy = 5;

char grid[height][width]; 

void init_grid(void);
void update(void);
void draw_grid(void);
void ball(void);

int main() {
	init_grid();

	while (1) {
		printf("\x1b[2J");
		update();
		ball();
		draw_grid();
		printf("x: %f,  y: %f, sin(ang)=%f, cos(ang)=%f\nang=%f, vel=%f, acc=%f\n", x, y,sin(ang), cos(ang), ang, vel, acc);
		usleep(90000);
	}
}


void update() {

	x = L*sin(ang) + originx;
	y = L*cos(ang) + originy;

	acc = (-1 * G / L) * sin(ang);
	vel += acc;

	vel *= drag;
	ang += vel;

}

void init_grid() {
	int a, b;
	for (a = 0; a < width; ++a) {
		for (b = 0; b < height; ++b) {
			grid[b][a] = ' ';
		}
	}
}

void draw_grid() {
	int a, b;

	for (a = 0; a < width; ++a) {
		for (b = 0; b < height; ++b) {
			printf("%c", grid[b][a]);
		}
		printf("\n");
	}
}

void ball() {
	int a, b;

	for (a = 0; a < width; ++a) {
		for (b = 0; b < height; ++b) {
			if (grid[b][a] == '@') grid[b][a] = 'o';
			else if (grid[b][a] == 'o') grid[b][a] = '.';
			else if (grid[b][a] == '.') grid[b][a] = ' ';

			if (a == originy && b == originx) grid[b][a] = '+';
			if (a == (int) y && b == (int) x) grid[b][a] = '@';
		}
	}
}

