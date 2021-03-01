#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
using std::string;
class Solution
{
public:
	int lengthOfLongestSubstring(string s)
	{
		int start(0), end(0), length(0), result(0);////s[start,end) 
		int s_Size = int(s.size());
		while (end < s_Size)
		{
			char tmpChar = s[end];
			for (int i = start; i < end; i++)
			{
				if (tmpChar == s[i])
				{
					start = i + 1;
					length = end - start;
					break;
				}
			}
			end++;
			length++;
			result = max(result, length);
		}
		return result;
	}
};
int main()
{
	string s;
	cin >> s;
	Solution ob;
	cout << ob.lengthOfLongestSubstring(s);
}
