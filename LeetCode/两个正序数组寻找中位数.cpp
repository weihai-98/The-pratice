#include <iostream>
#include<vector>
using std::vector;
using namespace std;
class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		vector<int> nums;
		int size1 = nums1.size(), size2 = nums2.size();
		int n = size1 + size2;
		nums.resize(n);

		//i1为数组nums1下标，i2为数组nusm2下标，i为数组nums下标
		int i1 = 0, i2 = 0, i = 0;

		//归并排序
		while (i1 < size1 || i2 < size2) {
			//nums1首元素小于nums2或i2已遍历到末尾
			if (i2 >= size2 || (i1 < size1 && nums1[i1] <= nums2[i2])) {
				nums[i++] = nums1[i1++];
			}
			//nums2首元素小于nums1或i1已遍历到末尾
			else {
				nums[i++] = nums2[i2++];
			}
		}

		//根据长度奇偶情况决定返回单个数还是两个数的平均值
		return n % 2 == 0 ? ((double)nums[n / 2 - 1] + (double)nums[n / 2]) / 2 : (double)nums[n / 2];
	}
};
int main() {
	int m, n;
	cin >> m >> n;
	Solution solution;
	vector<int> nums1(m), nums2(n);
	for (int i = 0; i < m; i++)
		cin >> nums1[i];
	for (int i = 0; i < n; i++)
		cin >> nums2[i];
	cout << solution.findMedianSortedArrays(nums1, nums2);
}
