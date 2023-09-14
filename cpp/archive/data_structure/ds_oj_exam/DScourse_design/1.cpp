#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;
int threshold;

// 表示递归限度
int depth_limit = 0;

//////////////////////////////////////////////////////////////所有自定义工具函数
void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
/**
 * 维护堆的性质
 * @param arr 存储堆的数组
 * @param len 数组长度
 * @param i 待维护节点的下标
 */
void heapify(int heap[], int len, int i) {
    // 0 - len-1
    int max = i;
    int lson = i * 2 + 1;
    int rson = i * 2 + 2;

    if (lson < len && heap[max] < heap[lson]) max = lson;
    if (rson < len && heap[max] < heap[rson]) max = rson;

    if (max != i) {
        swap(heap[max], heap[i]);
        heapify(heap, len, max);
    }
}
int Partition(int R[], int m, int n) {
    int i = m, j = n + 1, K = R[m];
    while (i < j) {
        while (++i <= n && R[i] <= K)
            ;
        while (R[--j] > K)
            ;
        if (i < j) swap(R[i], R[j]);
    }
    swap(R[m], R[j]);
    return j;
}

////////////////////////////////////////////////////////排序函数
void heap_sort(int arr[], int m, int n) {
    // 对arr[]的m到n区间进行堆排序 递增排序
    if (m == n) {
        cout << "数组长度是0!!!!" << endl;
    }
    int *heap = new int[n - m + 1]{0};
    int len = n - m + 1;  // 堆的数组的长度
    for (int i = 0; i < len; i++) {
        heap[i] = arr[i + m];
    }

    // 待排序的存入heap[] 建堆
    for (int i = len / 2 - 1; i >= 0; i--) {
        heapify(heap, len, i);
    }
    // 建堆完成

    cout << "Heap:";
    for (int i = 0; i < len; i++) {
        cout << heap[i] << ' ';
    }
    cout << endl;
    // 排序
    for (int i = len - 1; i >= 1; i--) {
        swap(heap[i], heap[0]);
        heapify(heap, i, 0);
    }

    // 归还给原来的数组
    for (int i = m; i <= n; i++) {
        arr[i] = heap[i - m];
    }

    delete[] heap;
    return;
}
void QuickSort(int R[], int m, int n, int recursive) {
    if (m >= n) {
        // cout << "直接返回" << endl;
        return;
    }
    // for (int i = 1; i <= 10; i++) cout << R[i] << ' ';
    // cout << endl;
    // printf("本排序正在对数组的第%d到%d进行排序\n\n", m, n);

    if (n - m + 1 <= threshold) {
        // 插入排序
        // 这个子区间数量太少 不排序
        return;
    } else if (recursive >= depth_limit) {
        // 此时对R数组的m到n位进行堆排序
        heap_sort(R, m, n);
    } else {
        if (m < n) {
            int j = Partition(R, m, n);
            // for (int i = 1; i <= 10; i++) cout << R[i] << ' ';
            // cout << endl;
            QuickSort(R, m, j - 1, recursive + 1);
            QuickSort(R, j + 1, n, recursive + 1);
        }
    }
}

void sort(int *R, int n) {
    depth_limit = int(2 * log2(n));
    cout << "depth_limit:" << depth_limit << endl;
    // 排序下标从1到n
    QuickSort(R, 1, n, 0);
    cout << "Intermediate:";
    for (int i = 1; i <= n; i++) {
        printf("%d ", R[i]);
    }
    cout << endl;
    // 然后对1-n进行插入排序
    for (int i = 2; i <= n; i++) {
        int k = R[i];
        int j = i - 1;
        while (j > 0 && R[j] > k) {
            R[j + 1] = R[j];
            j--;
        }
        R[j + 1] = k;
    }
}
int main() {
    freopen("in.txt", "r", stdin);
    int n, i;
    int a[50];
    scanf("%d %d", &n, &threshold);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);

    sort(a, n);

    printf("Final:");
    for (i = 1; i <= n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
