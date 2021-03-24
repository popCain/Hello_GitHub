/*

	快速排序：平均时间复杂度：nlogn； 最恶时间复杂度：n^2

		1. 选起始位置作为基准值key
		2. 从右往左找比基准值小的数放到起始位置
		3. 从左往右找比基准值大的值，放到右边j的位置
		4. 依次右左右进行至i == j结束一次分割

	类似于二叉树的前序遍历（操作根，递归左，递归右）
*/
#include <stdio.h>
#include <stdlib.h>

#define N 20

// 主要是找出分界元素的索引下标（index其左边都是比他小的数，右边都是比他大的数）
int partition(int a[], int low, int high)
{
	int i, j, key;
	key = a[low]; // 每次选取段的起始位置值作为基准值
	i = low; //分割段的左起点
	j = high; // 分割段的右起点

	// i == j 时一次分割结束
	while(i != j)
	{
		// 从右向左找比基准值小的数（i != j或用i < j是防止尾向前越过首破坏结构）
		while(a[j] >= key && i < j)
			j--;

		// 首尾是否相遇
		if (i < j)
		{
			// 找到小于key的值，赋值给坑a[i];a[j]位置变为坑
			a[i] = a[j];
			i++;

			// 从左往右找比基准值大的值
			while(a[i] <= key && i != j)
				i++;

			if (i < j)
			{

				a[j] = a[i];
				j--;
			}	
		}	
	}
	a[i] = key;
	return i;
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

// 递归进行（前向遍历）根（处理根节点）左右
void quickSort(int a[], int m, int n)
{
	// 跳出递归
	if (a = NULL || m >= n)
	{
		return;
	}
	int key_index;
	// 一次分割完成后返回作为基准值所处的下标
	key_index = partition(a, m, n);
	quickSort(a, m, key_index - 1);
	quickSort(a, key_index + 1, n);
}

int main()
{
	int a[N] = {10, 2, 3, 8, 4, 6, 1, 5, 9, 7, 13, 11, 12, 19, 17, 18, 16, 15, 14, 20};
	printf("排序前：\n");
	traveral(a, N);
	quickSort(a, 0, N-1);

	printf("排序后：\n");
	traveral(a, N);
	return 0;
}