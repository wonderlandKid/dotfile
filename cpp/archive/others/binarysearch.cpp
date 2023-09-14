int binary_search(int nums[], int begin, int end, int k) {
  // 在begin和end之间检索结果k并且返回下标 如果没有找到就返回-1
  // 假设递增排序

  // 递归出口
  if (begin == end) {
    if (nums[begin] == k) return begin;
    return -1;
  }

  if (end == begin + 1) {
    if (nums[begin] == k) return begin;
    if (nums[end] == k) return end;
    return -1;
  }

  int mid = (begin + end) / 2;
  if (k == nums[mid])
    return mid;
  else if (k > nums[mid]) {
    int right_result = binary_search(nums, mid, end, k);
    if (right_result != -1) return right_result;
  } else {
    int left_result = binary_search(nums, begin, mid, k);
    if (left_result != -1) return left_result;
  }

  return -1;
}
