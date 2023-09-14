#include <iostream>
#include <vector>
using namespace std;
class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {

    if (nums.size() == 1) {
      if (nums[0] >= target) {
        return 1;
      } else {
        return 0;
      }
    }
    
    int myresult = 0;
    int i = 0;
    int j = 1;
    int sum = nums[0] + nums[1];
    if (nums[0] >= target) {
      return 1;
    }


    while (i < nums.size() && j < nums.size() && j >= i) {
      if (sum >= target) {
        if (myresult == 0) {
          myresult = j - i + 1;
        } else if (myresult > j - i + 1) {
          myresult = j - i + 1;
        } else {
        }
        sum -= nums[i];
        i++;
      } else {
        j++;
        if (j < nums.size()) sum += nums[j];
      }
    }
    return myresult;
  }
};

int main() {
  Solution a;
  vector<int> test = {10, 2, 3};
  cout << a.minSubArrayLen(6, test);
  return 0;
}
