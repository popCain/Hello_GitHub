public class MergeSort{

	public static void merge(int[] a, int left, int mid, int right){
		int i = left;
		int j = mid + 1;
		int[] tmp = new int[right-left+1];
		for (int k=0; k<right-left+1; k++) {
			// 左路归并结束
			if (i == mid + 1) {
				tmp[k] = a[j];
				j++;
			}else if(j == right+1){
				tmp[k] = a[i];
				i++;
			}else if(a[i] < a[j]){
				tmp[k] = a[i];
				i++;
			}else{
				tmp[k] = a[j];
				j++;
			}
		}

		for (int i2=0; i2<right-left+1; i2++) {
			a[left+i2] = tmp[i2];
		}
	}

	public static void mergeSort(int[] array, int left, int right){
		if (array == null || left>=right) {
			return;
		}

		int mid = (right + left)/2;
		mergeSort(array, left, mid);
		mergeSort(array, mid+1, right);
		merge(array, left, mid, right);
	}

	public static void main(String[] args){
		int[] array = {2, 3, 10, 15, 13, 18, 3, 2, 1, 16, 20, 11, 17, 14, 8, 9, 19};
		mergeSort(array, 0, array.length-1);
		for (int i1=0; i1<array.length-1; i1++) {
			System.out.print(array[i1]+" ");
		}
		System.out.println();
	}
}