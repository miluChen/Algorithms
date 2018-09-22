#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
	double x, y;
	double dist(Point &that) { return sqrt((this->x - that.x) * (this->x - that.x) + (this->y - that.y) * (this->y - that.y)); }
};

struct Segment {
	Point a, b;

	Segment(Point &_a, Point &_b) { a.x = _a.x, a.y = _a.y, b.x = _b.x, b.y = _b.y; }
	double length() { return a.dist(b); }
	bool intersect(Segment &that) { return true; }
	bool rightSide(Point &p) { return true; }
};

struct Polygon {
	int vertex;
	vector<Point> points;
};

// assume the input is in required format
Polygon readPolygon(char *fname) {
	ifstream in (fname);
	Polygon p;
	in >> p.vertex;
	for (int i=0; i<p.vertex; i++) {
		Point tmp;
		in >> tmp.x, in >> tmp.y;
		p.points.push_back(tmp);
	}
	return p;
}

// compute the longest straight line segment that fits inside the polygon
double landingStrip(Polygon &polygon) {
	vector<Segment> segs;
	for (int i=0; i<polygon.vertex-1; i++)
		segs.push_back(Segment(polygon.points[i], polygon.points[i+1]));
	segs.push_back(Segment(polygon.points.back(), polygon.points[0]));

	
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "INPUT ERROR: need input file" << endl;
		return -1;
	}
	Polygon polygon = readPolygon(argv[1]);

	cout << "answer: " << landingStrip(polygon) << endl;
	return 0;
}
