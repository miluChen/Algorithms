/*
 * Given a sorted array of integers without duplicates.
 * Between the first and last number, all missing numbers form an array.
 * Find the kth number (k > 0) in this array constructed by the missing numbers; if not exist, return -1.
 * For example:
 *	nums = [2, 4, 7, 8, 9, 15], k = 2
 *	array by missing numbers = [3, 5, 6, 10, 11, 12, 13, 14]
 *	=> 5
 */

#include <iostream>
#include <vector>

using namespace std;

int kth_missing_num(vector<int> nums, int k) {
	if (nums.size() < 2 || k <= 0)
		return -1;
	if (nums.back() - nums.front() - nums.size() + 1 < k)
		return -1;
	// binary search
	int left = 0, right = nums.size() - 1;
	while (left < right-1) {
		int mid = left + (right - left) / 2;
		int mis_left = nums[mid] - nums[left] - mid + left;
		if (mis_left >= k)
			right = mid;
		else {
			left = mid;
			k -= mis_left;
		}
	}
	return nums[left] + k;
}

int main(int argc, char *argv[]) {
	vector<int> nums = {2, 4, 7, 8, 9, 15};
	cout << kth_missing_num(nums, stoi(argv[1])) << endl;
	return 0;
}
