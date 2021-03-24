/*
	归并排序：分治思想

		- 先分割（回归），再归并（两路归并）

			1. 回归（参考后向遍历）


*/

#include <stdio.h>
#include <stdlib.h>

// （已排序）两路归并：左路-（left, mid）; 右路-(mid+1, right)
void merge(int a[], int left, int mid, int right)
{
	int i, j;
	i = left;
	j = mid + 1;

	int N = right-left+1; // 两路归并后新数组长度
	int tmp[N]; //存放归并的新数组
	int k = 0;

	for (k = 0; k < N; ++k)
	{
		// 左路归并结束（将右路所剩依次存进新数组）
		if (i == mid + 1)
		{
			tmp[k] = a[j];
			j++;
		// 右路归并结束（将左路剩余元素依次放入新数组）
		}else if (j == right + 1)
		{
			tmp[k] = a[i];
			i++;
		}else if (a[i] < a[j])
		{
			tmp[k] = a[i];
			i++;
		}else{
			tmp[k] = a[j];
			j++;
		}
	}
	// 将归并后新数组（已排序），赋值给原数组位置
	for (i = 0; i < N; ++i)
	{
		a[left+i] = tmp[i];
	}
}

// 递归（参考后序遍历）：分割至单个元素（叶），左右根（处理根节点：两路归并）的顺序
void mergeSort(int a[], int left, int right)
{
	// 遍历结束条件
	if (a == NULL || left >= right)
	{
		return;
	}

	int mid = (left + right)/2;
	mergeSort(a, left, mid);
	mergeSort(a, mid+1, right);
	merge(a, left, mid, right);
	
/*
	// 分割
	int mid = (left + right)/2;

	// 左、右路均含一个元素为止（跳出递归）
	if (left < mid)
	{
		mergeSort(a, left, mid);
	}
	if (mid + 1 < right)
	{
		mergeSort(a, mid + 1, right);
	}

	// 统治(两路归并) -- 左路：(left, mid)； 右路：（mid+1, right）
	merge(a, left, mid, right);
*/

}

// 遍历
void traveral(int a[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	int a[20] = {10, 2, 3, 8, 4, 6, 1, 5, 9, 7, 13, 11, 12, 19, 17, 18, 16, 15, 14, 20};
	printf("排序前：\n");
	traveral(a, 20);

	mergeSort(a, 0, 19);
	printf("排序后：\n");
	traveral(a, 20);
	return 0;
}