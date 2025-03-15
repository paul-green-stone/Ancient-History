#include "../include/shapes.h"
#include <stdlib.h>
#include <stdio.h>

// rounding helper, simplified version of the function I use
static int roundUpToMultipleOfEight(int v) {
	return (v + (8 - 1)) & -8;
}

void draw_circle(SDL_Renderer *renderer, Vector2D center, int radius, SDL_Color color) {

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// 35 / 49 is a slightly biased approximation of 1/sqrt(2)
	const int arrSize = roundUpToMultipleOfEight(radius * 8 * 35 / 49);
	SDL_Point *points = (SDL_Point *)calloc(arrSize, sizeof(SDL_Point));
	int drawCount = 0;

	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y) {

		// Each of the following renders an octant of the circle
		points[drawCount + 0] = (SDL_Point){center.x + x, center.y - y};
		points[drawCount + 1] = (SDL_Point){center.x + x, center.y + y};
		points[drawCount + 2] = (SDL_Point){center.x - x, center.y - y};
		points[drawCount + 3] = (SDL_Point){center.x - x, center.y + y};
		points[drawCount + 4] = (SDL_Point){center.x + y, center.y - x};
		points[drawCount + 5] = (SDL_Point){center.x + y, center.y + x};
		points[drawCount + 6] = (SDL_Point){center.x - y, center.y - x};
		points[drawCount + 7] = (SDL_Point){center.x - y, center.y + x};

		drawCount += 8;

		if (error <= 0) {

			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0) {

			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

	SDL_RenderDrawPoints(renderer, points, drawCount);
	free(points);
}
