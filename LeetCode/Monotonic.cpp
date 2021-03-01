
#include <iostream>
#include<vector>
using std::vector;
using namespace std;
class Solution {
public:
	bool isMonotonic(vector<int>& A) {
		return isIncrease(A) || isDecrease(A);
	}
	bool isIncrease(vector<int>& A) {
		int N = A.size();
		for (int i = 1; i < N; ++i) {
			if (A[i] < A[i - 1])
				return false;
		}
		return true;
	}

	bool isDecrease(vector<int>& A) {
		int N = A.size();
		for (int i = 1; i < N; ++i) {
			if (A[i] > A[i - 1])
				return false;
		}
		return true;
	}
};


int main()
{
	int n,i;
	cin >> n;
	vector<int> A(n);
	Solution justify;
	for (i = 0; i < n; i++) {
		cin >> A[i];
	}
	if (justify.isMonotonic(A) == true)
		cout << "true";
	else
		cout << "false";
}


