#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
#include "linkedStack.h"

int main()
{
	//elemType e;
	linkedStack LS;
	LS = initLinkedStack(LS);
	LS = push(LS, 'a');
	LS = push(LS, 'b');
	LS = push(LS, 'c');
	LS = push(LS, 'd');
	LS = push(LS, 'e');

	/*
	for (int i = 0; i < 6; ++i)
	{
		e = pop(LS);
	}
	*/
	return 0;
}