public class HeapSort{
	public static void adjustHeap(int[] a, int start, int end){
		// 父节点
		int i = start;
		// 左子
		int j = 2*i + 1;
		// 父值
		int father = a[i];

		while(j <= end){
			if (j<=end-1 && a[j]>a[j+1]) {
				j = j+1;
			}
			// 以下子树均为堆，所以无需再往下比,跳出循环
			if (father <= a[j]) {
				break;
			}
			a[i] = a[j];
			i = j;
			j = 2*i + 1;
		}
		a[i] = father;
	}

	public static void createHeap(int[] a){
		int length = a.length;
		for (int i = length/2 - 1; i>=0; i--) {
			adjustHeap(a, i, length-1);
		}
	}

	public static void heapSort(int[] array){

		createHeap(array);

		System.out.println("创建的堆为：");
		for (int k=0; k<array.length-1; k++) {
			System.out.print(array[k]+" ");
		}
		System.out.println();


		int end_index = array.length - 1;

		while(end_index > 0){
			int topValue = array[0];
			array[0] = array[end_index];
			array[end_index] = topValue;

			adjustHeap(array, 0, end_index-1);
			end_index--;
		}
	}

	public static void main(String[] args){
		int[] array = {1, 10, 2, 4, 5, 7, 20, 14, 17, 4, 9, 8, 17, 18, 19, 11, 12};
		heapSort(array);

		for (int i = 0; i < array.length; i++) {
			System.out.print(array[i]+" ");
		}
		System.out.println();

	}
}