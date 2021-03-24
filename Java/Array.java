/***************************************************************************
*	    		数据结构(データ構造こうぞう)：逻辑结构 + 物理结构（存储结构）
*
* 1.逻辑结构（論理構造　ロジック）：
*	- 线性结构：线性表・線形構造（“一对一”)（List, queue, stack..）
*	- 非线性结构：集合・セット（"互斥"），树・木構造（"一对多"），图・グラフ構造（“多对多”）..
*
* 2.物理结构（存储结构・保存方式）：顺序存储（連続するメモリ），链式存储（リンク・連結）
*
* 3.基本操作：遍历（めぐり）+访问（增删查改）
*
* 4.遍历方式：for/while迭代；递归
* ------------------------------- 一. 线性表 ----------------------------------
* （1）- 顺序表（配列）：主要注意插入，删除操作：需要移位 ¥¥¥¥¥¥-- 最主要是“移位操作”
******************************************************************************/

public class Array{

	// 数组存储
	private int[] intArray;
	// 最大存储
	private int maxLength;
	// 现实际长度
	private int length;
	// 初始化
	public Array(int maxLength){

		this.maxLength = maxLength;
		this.intArray = new int[this.maxLength];
		length = 0;
	}

	// 插入
	public void addLast(int value){
		if (length == maxLength) {
			System.out.println("数组越界！！");
			return;
		}
		intArray[length] = value;
		System.out.println("插入数据成功!");
		length++;
	}

	// 遍历
	public void display(){
		for (int i = 0; i < length ; i++) {
			System.out.print(this.intArray[i] + " ");
		}
		System.out.println("");
	}

	// 冒泡排序（bubble sort）
	public void bubbleSort(){

		for (int i = 0; i < length-1 ; i++) {
			System.out.println("第"+(i+1)+"趟排序结果：");
			for (int j = 0; j<length-i-1 ; j++) {
				if (this.intArray[j] > this.intArray[j+1]) {
					int temp = this.intArray[j];
					this.intArray[j] = this.intArray[j+1];
					this.intArray[j+1] = temp;
				}
			}
			display();
		}
	}

	// 选择排序（selectSort）
	public void selectSort(){
		for (int i = 0; i < length-1; i++) {
			int min = i;
			for (int j = i+1; j < length; j++) {
				if (this.intArray[j]<this.intArray[min]) {
					min = j;
				}
			}
			if (i != min) {
				int temp = this.intArray[i];
				this.intArray[i] = this.intArray[min];
				this.intArray[min] = temp;
			}
			display();
		}
	}

	// 插入排序（insertSort）
	public void insertSort(){
		for (int i = 1; i < length; i++) {
			int j = i;
			int temp = intArray[i];

			while(j > 0 && intArray[j-1]>temp){
				intArray[j] = intArray[j-1];
				j--;
			}
			intArray[j] = temp;
		}
		display();
	}


	// 入口
	public static void main(String[] args){

		Array array = new Array(10);
		array.addLast(6);
		array.addLast(10);
		array.addLast(1);
		array.addLast(7);
		array.addLast(14);
		array.addLast(7);
		array.addLast(11);
		array.addLast(8);
		array.addLast(3);
		array.addLast(4);

		array.display();
		//array.bubbleSort();
		array.selectSort();
		//array.insertSort();

	}
}