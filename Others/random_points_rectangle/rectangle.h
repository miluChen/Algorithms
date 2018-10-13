#ifndef __CPLUS_GEOMETRY__
#define __CPLUS_GEOMETRY__

#include <iostream>
#include <map>
#include <set>
#include <vector>

#define EPS 0.00001 // threshold to determine whether two float number is the same

struct Point {
	float x, y;
	Point(float _x, float _y): x(_x), y(_y) {}
};

struct Rectangle {
	float x, y;				// the left bottom coordinate
	float width, height;	// width and height of the rectangle

	Rectangle(): x(0), y(0), width(0), height(0) {}
	Rectangle(float _x, float _y, float _w, float _h): x(_x), y(_y), width(_w), height(_h) {}
	Rectangle(const Rectangle &that) { x = that.x; y = that.y; width = that.width; height = that.height; }
	inline float area() { return width * height; }
	inline void Print() { std::cout << x << "\t" << y << "\t" << width << "\t" << height << std::endl; }
};

struct EndPoint {
	bool isLeft;
	Rectangle * rect_ptr;

	bool operator<(const EndPoint &that) const {
		if (Value() != that.Value())
			return Value() < that.Value();
		return !isLeft; // if the value is the same, right end point is put before left end point
	}
	inline float Value() const { return isLeft ? rect_ptr->x : rect_ptr->x + rect_ptr->width; }
};

/* truncate the overlapping rectangles into non-overlapping rectangles
 * invariant:
 *	1. the rectangles extracted do not overlap
 *	2. active retangles in the bst (based on Y axis) do not overlap
 */
std::vector<Rectangle> truncateRectangle(std::vector<Rectangle> rects);

// generate a random point from a rectangle that aligns with x, y axes
Point randPointOneRectangle(Rectangle &rect);
// generate a random point from many non-overlapping rectangles that align with x, y axes
std::vector<Point> randPointNonOverlapRectangles(std::vector<Rectangle> &rects, int num);
// generate a random point from overlapping rectangles that align with x, y axes
std::vector<Point> randPointRectangles(std::vector<Rectangle> rects, int num);
// generate "num" rectangles with left bottom point in "rect", and width and height in specific ranges
std::vector<Rectangle> generateRectangle(Rectangle rect, float width_low, float width_up, float height_low, float height_up, int num_rect);

// read in rectangles from a file, assume each line is rectangle with x, y, width, and height
std::vector<Rectangle> readRectangle(char *fname);
// write rectangles into file
void writeRect(std::vector<Rectangle> &rects, char *fname);

// test whether rectangles overlap
bool isOverlap(Rectangle &r1, Rectangle &r2);
bool isOverlap(std::vector<Rectangle> &rects);

// helper functions
void printEndPoints(std::multiset<EndPoint> &endpoints);
void printActiveRects(std::map<float, Rectangle *> &active_rects);

#endif
