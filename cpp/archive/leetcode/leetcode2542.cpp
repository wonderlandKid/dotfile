#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <stdexcept>
#include <vector>
using namespace std;

class Solution {
   public:
    struct myPair {
        // 使用第一个表示下标 第二个表示数值
        int downindex;
        int data;

        bool operator<(myPair const& other) const{

        }

        bool operator>(myPair const& other) const{

        }
        bool operator==(myPair const& other) const{

        }

    };

    void printf_vec(vector<myPair> const& x) {
        for (auto const& i : x) {
            printf("{%d %d}", i.downindex, i.data);
        }
        printf("\n");
    }

    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        // 先保留下标信息 然后对nums2 进行递减排序 一次遍历即可
        vector<myPair> infor_nums2;

        // infor_nums2.reserve(nums2.size());

        for (int i = 0; i < nums2.size(); i++) {
            infor_nums2.push_back(myPair{i, nums2[i]});
        }

        // printf_vec(infor_nums2);

        // 然后对其进行排序
        // sort(infor_nums2.begin(), infor_nums2.end(), greater_op());
        sort(infor_nums2.begin(), infor_nums2.end(), [](myPair x, myPair y) { return x.data > y.data; });

        // printf("排序之后的结果\n");
        // printf_vec(infor_nums2);

        // 然后开始遍历
        // 新建一个小根堆
        priority_queue<int, vector<int>, greater<int>> heap_queue;

        // 用来记录前k个最大的数字和
        long long cur_priority_queue_sum = 0;

        long long max_result = 0;

        // 先建立一个k-1大小的优先队列
        for (int i = 0; i < k - 1; i++) {
            heap_queue.push(nums1[infor_nums2[i].downindex]);
            // heap_queue.push(nums1.at(infor_nums2.at(i).x1));
            cur_priority_queue_sum += nums1[infor_nums2[i].downindex];
        }

        for (int i = k - 1; i < infor_nums2.size(); i++) {
            if (i == k - 1) {
                heap_queue.push(nums1[infor_nums2[i].downindex]);
                cur_priority_queue_sum += nums1[infor_nums2[i].downindex];
                max_result = cur_priority_queue_sum * infor_nums2[i].data;
                continue;
            }

            // 要是确实很小就别push了
            if (nums1[infor_nums2[i].downindex] < heap_queue.top()) continue;

            heap_queue.push(nums1[infor_nums2[i].downindex]);
            cur_priority_queue_sum += nums1[infor_nums2[i].downindex];

            int deleted_elem = heap_queue.top();
            cur_priority_queue_sum -= deleted_elem;
            heap_queue.pop();

            // 保持前k个
            max_result = max(cur_priority_queue_sum * infor_nums2[i].data, max_result);
        }
        return max_result;
    }
};

int main(int argc, char* argv[]) {
    vector<int> nums1(20, 1);
    vector<int> nums2(20, 1);
    // nums2.at(19) = 2;
    cout << Solution().maxScore(nums1, nums2, 2);
}
