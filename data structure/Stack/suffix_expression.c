/*
	输入的中缀表达式为: 9+(3-1)*3+10/2
	(逆波兰)后缀表达式： 9 3 1 -3 *+10 2 /+

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
#include <ctype.h>
#include <assert.h>

typedef char elemType;

typedef struct Node
{
	elemType data;
	struct Node* next;
}Node;
typedef struct Node* linkedStack;

// 初始化
linkedStack initLinkedStack(linkedStack LS)
{
	
	LS->next = NULL;
	LS->data = 'H';
	return LS;
}

// 头插法(入栈) push
linkedStack push(linkedStack LS, elemType e)
{
	//创建节点Node
	Node* tempNode = (Node*)malloc(sizeof(Node));
	tempNode->data = e;
	tempNode->next = LS->next;
	LS->next = tempNode;
	//printf("入栈成功：%c\n", e);
	return LS;
}

// pop的参数e有问题

// 类似从头遍历，但每次出栈一个元素（出栈） pop
elemType pop(linkedStack LS)
{
	if (LS->next == NULL)
	{
		printf("空栈！！\n");
		return NULL;
	}
	Node* tempNode = LS->next;
	elemType e = tempNode->data;
	//printf("出栈元素为：%c\n", e);
	LS->next = tempNode->next;
	free(tempNode);
	return e;
}

elemType* infix2suffix(linkedStack LS, elemType* str)
{
	elemType* suffix_expression = (elemType*)malloc(sizeof(elemType)*40);
	//char suffix_expression[30];
	int i = 0;
	int j = 0;
	elemType e;
	// '\0'为字符串结束标志（所以C中，字符串所占内存字节：需要字节数+1（‘\0’））
	while(str[i] != '\0')
	{
		// 如果是数字直接输出--多位数的情况（直到下一位是运算符时输出空格作为多位数的间隔）
		while(isdigit(str[i]))
		{
			printf("%c", str[i]);
			
			//  后缀表达式字符串
			suffix_expression[j++] = str[i];
			i++;
			// 当下一个字符不是数字时，输出空格
			if(!isdigit(str[i]))
			{
				printf(" ");
				// 空格分隔多位数与其他字符
				suffix_expression[j++] = ' ';

			}
		}
		// 加减法优先级最低，如果空栈直接进栈
		// 否则将栈中存储的运算符全部出栈，
		if (str[i]=='+' || str[i]=='-')
		{
			//printf("%c\n", str[i]);
			// 栈不空时
			if (LS->next)
			{

				// 将栈内符号全部出栈（直至遇到左括号‘（’）
				do{

					e = pop(LS);
					if (e == '(')
					{
						LS = push(LS, e);
					}
					else{
						printf("%c", e);
						suffix_expression[j++] = e;
						suffix_expression[j++] = ' ';
						//j++;
					}
				}while(LS->next && e != '(');
				// 将‘+’或'-'号入栈
				LS = push(LS, str[i]);
			}else{
				// 将‘+’或‘-’号入栈
				LS = push(LS, str[i]);
			}
		// 乘，除，左括号优先级高；直接入栈
		}else if (str[i]=='*' || str[i]=='/' || str[i]=='(')
		{
			LS = push(LS, str[i]);

		// 当遇到右括号时，将栈中运算符弹出，直至匹配到左括号（左括号弹出不打印，右括号也不入栈）
		}else if (str[i] == ')')
		{
			e = pop(LS);
			while(e != '(')
			{
				printf("%c", e);
				suffix_expression[j++] = e;
				suffix_expression[j++] = ' ';
				//j++;
				e = pop(LS);
			}

		}else if (str[i] == '\0')
		{
			break;

		}else{
			printf("输入格式错误！！\n");
			return NULL;
		}
		
		i++;
	}// while结束

	// 最后将栈中剩余的运算符弹栈，打印
	while(LS->next)
	{
		e = pop(LS);
		printf("%c", e);
		suffix_expression[j++] = e;
		suffix_expression[j++] = ' ';
		//j++;
	}
	suffix_expression[j] = '\0';
	printf("\n");
	return suffix_expression;
}

int main()
{
	//初始化栈
	linkedStack LS;
	LS = (Node*)malloc(sizeof(Node));
	LS = initLinkedStack(LS);

	elemType str[30];
	//str = (elemType*)malloc(sizeof(elemType));
	gets(str);
	printf("输入的表达式为: %s\n", str);

	elemType* suffix_expression = infix2suffix(LS, str);
	
	printf("转化为后缀表达式后: %s\n", suffix_expression);
	return 0;
}