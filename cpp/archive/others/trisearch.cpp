int trisearch(int nums[], int begin, int end, int k) {
  // 在begin和end之间检索结果k并且返回下标 如果没有找到就返回-1

  // 递归出口
  // 因为是三分 除到最后可能会余0 1 2 所以有三个
  if (begin == end) {
    if (nums[begin] == k)
      return begin;
    else
      return -1;
  } else if (end == begin + 1) {
    if (nums[begin] == k) return begin;
    if (nums[end] == k) return end;
    return -1;
  } else if (end == begin + 2) {
    for (int i = begin; i <= begin + 2; i++) {
      if (nums[i] == k) return i;
    }
    return -1;
  }

  int mid1 = end / 3;
  int mid2 = 2 * end / 3;

  // 消除端点的问题
  if (nums[mid1] == k) return mid1;
  if (nums[mid2] == k) return mid2;

  // 三个判断 判断k可能在三段里面的哪一段 递归
  if (k < nums[mid1]) {
    int result1 = trisearch(nums, begin, mid1, k);
    if (result1 != -1) return result1;
  } else if (nums[mid1] < k < nums[mid2]) {
    int result2 = trisearch(nums, mid1, mid2, k);
    if (result2 != -1) return result2;
  } else {
    int result3 = trisearch(nums, mid2, end, k);
    if (result3 != -1) return result3;
  }

  return -1;
}
