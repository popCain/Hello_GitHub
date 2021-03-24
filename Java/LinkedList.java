public class LinkedList{

	// 头节点
	private Node head;

	class Node{
		// 存值(数据域)
		private int data;
		//存下一节点位置（指针域）
		private Node next;

		public Node(){
			data = -1;
			next = null;
		}

		public Node(int value){
			data = value;
			next = null;
		}
	}

	public LinkedList(){
		head = new Node();
	}



	// 头插法
	public void insertFromHead(int value){
		Node cur_Node = new Node(value);
		cur_Node.next = head.next;
		head.next = cur_Node;
	}

	// 尾插法
	public void insertFromLast(int value){
		Node cur_Node = new Node(value);
		Node tmp = head;
		while(tmp.next != null){
			tmp = tmp.next;
		}
		tmp.next = cur_Node;
	}

	public void traveral(){
		Node tmp = head;
		System.out.println("遍历开始：");
		while(tmp.next != null){
			System.out.print(tmp.data+" ");
			tmp = tmp.next;
		}
		System.out.println("");

	}

	public static void main(String[] args){
		LinkedList linkedList = new LinkedList();
		linkedList.insertFromHead(1);
		linkedList.insertFromLast(2);
		linkedList.insertFromHead(3);
		linkedList.insertFromLast(4);
		linkedList.insertFromHead(5);
		linkedList.insertFromLast(6);

		linkedList.traveral();

	}
}