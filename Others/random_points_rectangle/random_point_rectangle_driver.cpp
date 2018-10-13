/*
 * This driver program generates random points within given rectangles
 * The given rectangles are aligned with x, y axes
 * The given rectangles may overlap
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include "rectangle.h"

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 3 && argc != 8) {
		cout << "ERROR: ./a.out filename NumberOfPoints" << endl;
		cout << "ERROR: ./a.out filename NumberOfPoints width_low width_up height_low height_up NumberOfRectangles" << endl;
		return -1;
	}

	vector<Rectangle> rects;
	if (argc == 3)
		rects = readRectangle(argv[1]);
	else {
		float width_low  = stof(argv[3]);
		float width_up   = stof(argv[4]);
		float height_low = stof(argv[5]);
		float height_up  = stof(argv[6]);
		int num_rect     = stoi(argv[7]);
		assert(width_low > 0 && width_up > 0 && width_up > width_low);
		assert(height_low > 0 && height_up > 0 && height_up > height_low);
		rects = generateRectangle(readRectangle(argv[1]).back(), width_low, width_up, height_low, height_up, num_rect);
	}
	writeRect(rects, "_original_rects_");
	vector<Rectangle> nonoverlap_rects = truncateRectangle(rects);
	if (isOverlap(nonoverlap_rects)) {
		cout << "Truncated rectangles overlap" << endl;
	}

	int num = stoi(argv[2]);
	assert(num > 0);
	vector<Point> randpoints = randPointNonOverlapRectangles(nonoverlap_rects, num);

	// write the points into two files
	ofstream xf ("_XXX_"), yf ("_YYY_");
	assert(xf.is_open() && yf.is_open());
	for (int i=0; i<randpoints.size(); i++) {
		xf << randpoints[i].x << "\n";
		yf << randpoints[i].y << "\n";
	}
	return 0;
}
