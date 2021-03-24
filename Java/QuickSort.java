public class QuickSort{

	// 找凸点
	public static int partition(int[] a, int left, int right){
		int i, j, key;
		key = a[left];
		i = left;
		j = right;

		while(i != j){

			// 从右向左找小于key的
			while(a[j] >= key && i < j){
				j--;
			}
			// 放到左边
			if(i < j){
				a[i] = a[j];
				i++;

				// 从左向右找大于key的值
				while(a[i] <= key && i < j)
				{
					i++;
				}

				// 放到右边
				if(i < j){
					a[j] = a[i];
					j--;
				}
			}
		}
		a[i] = key;
		return i;
	}

	public static void quickSort(int[] array, int left, int right){
		// 跳出递归
		if (array == null || left >= right) {
			return;
		}

		int key_index = partition(array, left, right);
		quickSort(array, left, key_index - 1);
		quickSort(array, key_index + 1, right);
	}

	public static void main(String[] arg){

		int[] array = {11, 2, 4, 1, 5, 7, 15, 19, 9, 10, 14, 20, 30, 3};
		quickSort(array, 0, array.length - 1);

		for (int i = 0; i < array.length - 1; i++) {
			System.out.print(array[i] + " ");
		}
		System.out.println();

	}
}