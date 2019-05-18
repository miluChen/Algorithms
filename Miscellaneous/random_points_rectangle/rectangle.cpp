#include "rectangle.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <cassert>
#include <map>
#include <set>
#include <unordered_set>

#define EPS 0.00001

using namespace std;

// read in rectangles from a file, assume each line is rectangle with x, y, width, and height
vector<Rectangle> readRectangle(char *fname) {
	cout << "Reading rectangles from " << fname << endl;
	vector<Rectangle> ans;
	ifstream in (fname);
	assert(in.is_open());

	int n; // number of rectangles
	in >> n;
	assert (n > 0);
	while (n--) {
		Rectangle rect;
		in >> rect.x; in >> rect.y;
		in >> rect.width; in >> rect.height;
		assert(rect.width > 0 && rect.height > 0);
		ans.push_back(rect);
	}
	return ans;
}

/* truncate the overlapping rectangles into non-overlapping rectangles
 * invariant:
 *	1. the rectangles extracted do not overlap
 *	2. active retangles in the bst (based on Y axis) do not overlap
 */
vector<Rectangle> truncateRectangle(vector<Rectangle> rects) {
	vector<Rectangle> ans;
	// if rectangle is in the "visited" set, skip it
	unordered_set<Rectangle *> visited;
	// build the end points and sort the end points
	vector<Rectangle *> rects_ptrs;
	multiset<EndPoint> endpoints;
	for (int i=0; i<rects.size(); i++) {
		rects_ptrs.push_back(new Rectangle(rects[i]));
		endpoints.insert(EndPoint{true, rects_ptrs.back()});
		endpoints.insert(EndPoint{false, rects_ptrs.back()});
	}
	// printEndPoints(endpoints);
	// y axis: bst structure that holds rectangles. It is ordered by "rect_ptr->y"
	map<float, Rectangle *> active_rects;
	// scan endpoints from left to right; insertion on set does not affect the iterators or references
	for (auto it = endpoints.begin(); it != endpoints.end(); ) {
		if (visited.find(it->rect_ptr) != visited.end()) {
			auto tmp = active_rects.find(it->rect_ptr->y);
			if (tmp != active_rects.end() && tmp->second == it->rect_ptr)
				active_rects.erase(it->rect_ptr->y);
			it++;
			continue;
		}
		if (!it->isLeft) { // encountered a right end point
			ans.push_back(*(it->rect_ptr));
			visited.insert(it->rect_ptr);
			// erase the correponding left side in the bst
			if (active_rects.find(it->rect_ptr->y) != active_rects.end())
				active_rects.erase(it->rect_ptr->y);
			it++;
		}
		else { // encountered a left end point
			auto iter = active_rects.upper_bound(it->rect_ptr->y);
			if (iter != active_rects.begin())
				iter--;
			bool add_flag = true; // a flag to indicate whether we need to insert "it" in the Y bst
			while (iter != active_rects.end() && (iter->first < it->rect_ptr->y + it->rect_ptr->height)) {
				// printRect(ans);
				auto curr = iter->second;
				if (curr->y + curr->height > it->rect_ptr->y) { // have a intersection
					// case 1: "it" overlaps with "curr". The y axis of "it" is in "curr" => "curr" is the only overlap
					if (curr->y + curr->height >= it->rect_ptr->y + it->rect_ptr->height && curr->y <= it->rect_ptr->y) {
						// case 1a: "it" is completely in "curr" => skip "it"
						if (curr->x + curr->width >= it->rect_ptr->x + it->rect_ptr->width) {
							visited.insert(it->rect_ptr);
							it++;
						}
						// case 1b: the y axis of "it" is in "curr", but the x axis of "it" is not completely in "curr" => truncate "it"
						else {
							set<EndPoint>::iterator prev_it = endpoints.end();
							if (it != endpoints.begin())
								prev_it = prev(it);
							auto rect_ptr = it->rect_ptr;
							endpoints.erase(it);
							rect_ptr->width = rect_ptr->x + rect_ptr->width - curr->x - curr->width;
							rect_ptr->x     = curr->x + curr->width;
							endpoints.insert(EndPoint{true, rect_ptr});
							// it = next_it;
							if (prev_it == endpoints.end())
								it = endpoints.begin();
							else {
								it = next(prev_it);
							}
						}
						add_flag = false;
						break;
					}
					// case 2: "it" partially overlap with "curr" from bottom => "curr" is the only overlap
					else if (curr->y + curr->height >= it->rect_ptr->y + it->rect_ptr->height && curr->y > it->rect_ptr->y) {
						// case 2a: the x axis of "it" is completely in "curr" => truncate "it"
						if (curr->x + curr->width >= it->rect_ptr->x + it->rect_ptr->width) {
							it->rect_ptr->height = curr->y - it->rect_ptr->y;
							assert(it->rect_ptr->height > 0);
							// insert into the active_rects
							active_rects[it->rect_ptr->y] = it->rect_ptr;
						}
						// case 2b: both x and y axes of "it" partially overlap "curr" => truncate "curr"
						else {
							if (it->rect_ptr->x > curr->x)
								ans.push_back(Rectangle(curr->x, curr->y, it->rect_ptr->x - curr->x, it->rect_ptr->y + it->rect_ptr->height - curr->y));
							curr->height = curr->y + curr->height - it->rect_ptr->y - it->rect_ptr->height;
							curr->y      = it->rect_ptr->y + it->rect_ptr->height;
							active_rects.erase(iter);
							if (curr->height > 0)
								active_rects[curr->y] = curr;
							else
								visited.insert(curr);
							active_rects[it->rect_ptr->y] = it->rect_ptr;
						}
						it++;
						add_flag = false;
						break;
					}
					// case 3: "it" partially overlap with "curr" from top
					else if (curr->y + curr->height < it->rect_ptr->y + it->rect_ptr->height && curr->y <= it->rect_ptr->y) {
						// case 3a: "it" partially overlap with "curr" from top, the axis of "it" completely in "curr" => truncate "it"
						if (curr->x + curr->width >= it->rect_ptr->x + it->rect_ptr->width) {
							it->rect_ptr->height = it->rect_ptr->y + it->rect_ptr->height - curr->y - curr->height;
							assert(it->rect_ptr->height > 0);
							it->rect_ptr->y      = curr->y + curr->height;
							iter++;
						}
						// case 3b: both x and y axes of "it" partially overlap with "curr": truncate "curr"
						else {
							if (it->rect_ptr->x > curr->x)
								ans.push_back(Rectangle(curr->x, it->rect_ptr->y, it->rect_ptr->x - curr->x, curr->y + curr->height - it->rect_ptr->y));
							curr->height = it->rect_ptr->y - curr->y;
							if (curr->height > 0)
								iter++;
							else { // curr->height == 0
								visited.insert(curr);
								auto next_iter = next(iter);
								active_rects.erase(iter);
								iter = next_iter;
							}
						}
						continue;
					}
					// case 4: "it" spreads across "curr"
					else if (curr->y > it->rect_ptr->y && curr->y + curr->height < it->rect_ptr->y + it->rect_ptr->height) {
						// case 4a: x axis of "it" is completely inside "curr": truncate "it"
						if (curr->x + curr->width >= it->rect_ptr->x + it->rect_ptr->width) {
							rects_ptrs.push_back(new Rectangle(it->rect_ptr->x, it->rect_ptr->y, it->rect_ptr->width, curr->y - it->rect_ptr->y));
							active_rects[it->rect_ptr->y] = rects_ptrs.back();
							endpoints.insert(EndPoint{false, rects_ptrs.back()});
							it->rect_ptr->height = it->rect_ptr->y + it->rect_ptr->height - curr->y - curr->height;
							it->rect_ptr->y      = curr->y + curr->height;
							assert(it->rect_ptr->height > 0);
							iter++;
						}
						// case 4b: x axis of "it" partially overlaps with "curr": truncate "curr"
						else {
							if (it->rect_ptr->x > curr->x)
								ans.push_back(Rectangle(curr->x, curr->y, it->rect_ptr->x - curr->x, curr->height));
							visited.insert(curr);
							auto next_iter = next(iter);
							active_rects.erase(iter);
							iter = next_iter;
						}
					}
					else {
						cout << "error intersection" << endl;
					}
				}
				else { // "it" does not intersect with "curr"
					iter++;
				}
			}
			if (add_flag) {
				active_rects[it->rect_ptr->y] = it->rect_ptr;
				it++;
			}
		}
	}
	// free up the space
	for (int i=0; i<rects_ptrs.size(); i++)
		delete rects_ptrs[i];

	writeRect(ans, "_truncated_rects_");
	return ans;
}

// generate a random point from a rectangle that aligns with x, y axes
Point randPointOneRectangle(Rectangle &rect) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distX(rect.x, rect.x + rect.width);
	std::uniform_real_distribution<float> distY(rect.y, rect.y + rect.height);

	return Point(distX(gen), distY(gen));
}

// generate a random point from many non-overlapping rectangles that align with x, y axes
vector<Point> randPointNonOverlapRectangles(vector<Rectangle> &rects, int num) {
	vector<Point> ans;
	float sumArea = 0;
	for (int i=0; i<rects.size(); i++) {
		float area = rects[i].area();
		if (area == 0) {
			cout << "area of rects is 0! " << endl;
			assert(false);
		}
		sumArea += area;
	}
	vector<float> buckets(rects.size());
	cout << "buckets: " << endl;
	for (int i=0; i<rects.size(); i++) {
		buckets[i] = rects[i].area() / sumArea;
		if (i > 0)
			buckets[i] += buckets[i-1]; 
		cout << buckets[i] << ", ";
	}
	cout << endl;
	// generate random points by first determine which rectangle to use every time
	// std::default_random_engine gen;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(0, 1);
	for (int i=0; i<num; i++) {
		float pivot = distribution(gen);
		int idx = 0;
		for (int j=0; j<buckets.size(); j++) {
			if (buckets[j] >= pivot) {
				idx = j;
				break;
			}
		}
		ans.push_back(randPointOneRectangle(rects[idx]));
	}
	return ans;
}

// generate a random point from overlapping rectangles that align with x, y axes
vector<Point> randPointRectangles(vector<Rectangle> rects, int num) {
	vector<Rectangle> nonoverlap_rects = truncateRectangle(rects);
	return randPointNonOverlapRectangles(nonoverlap_rects, num);
}

// generate "num" rectangles with left bottom point in "rect", and width and height in specific ranges
vector<Rectangle> generateRectangle(Rectangle rect, float width_low, float width_up, float height_low, float height_up, int num_rect) {
	vector<Rectangle> ans;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distWidth(width_low, width_up);
	std::uniform_real_distribution<float> distHeight(height_low, height_up);

	for (int i=0; i<num_rect; i++) {
		Point p = randPointOneRectangle(rect);
		ans.push_back(Rectangle(p.x, p.y, distWidth(gen), distHeight(gen)));
	}
	return ans;
}

void printRect(vector<Rectangle> &rects) {
	for (int i=0; i<rects.size(); i++)
		cout << rects[i].x << "\t" << rects[i].y << "\t" << rects[i].width << "\t" << rects[i].height << "\n";
}

void writeRect(vector<Rectangle> &rects, char *fname) {
	ofstream f (fname);
	assert(f.is_open());
	for (int i=0; i<rects.size(); i++)
		f << rects[i].x << "\t" << rects[i].y << "\t" << rects[i].width << "\t" << rects[i].height << "\n";
}

bool isOverlap(Rectangle &r1, Rectangle &r2) {
	if (r1.x >= r2.x + r2.width - EPS || r2.x >= r1.x + r1.width - EPS)
		return false;
	if (r1.y >= r2.y + r2.height - EPS || r2.y >= r1.y + r1.height - EPS)
		return false;
	return true;
}

bool isOverlap(vector<Rectangle> &rects) {
	if (rects.size() <= 1)
		return false;
	for (int i=0; i<rects.size()-1; i++) {
		for (int j=i+1; j<rects.size(); j++) {
			if (isOverlap(rects[i], rects[j])) {
				rects[i].Print();
				rects[j].Print();
				return true;
			}
		}
	}
	return false;
}

void printEndPoints(multiset<EndPoint> &endpoints) {
	cout << "EndPoints: " << endpoints.size() << endl;
	for (auto tmp = endpoints.begin(); tmp != endpoints.end(); tmp++)
		cout << tmp->Value() << ", ";
	cout << endl;
	for (auto tmp = endpoints.begin(); tmp != endpoints.end(); tmp++)
		tmp->rect_ptr->Print();
	cout << endl;
}

void printActiveRects(map<float, Rectangle *> &active_rects) {
	cout << "Active Rectangles: " <<active_rects.size() << endl;
	for (auto tmp = active_rects.begin(); tmp != active_rects.end(); tmp++) {
		auto rect = tmp->second;
		cout << rect->x << "\t" << rect->y << "\t" << rect->width << "\t" << rect->height << "\n";
	}
	cout << endl;
}

