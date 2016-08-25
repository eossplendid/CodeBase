#include <stdio.h>
#include <stdlib.h>
#include "pub_list.h"
#include "pub_macro.h"

typedef struct {
	UINT32 uiAge;
	UINT32 uiSex;
	UINT32 uiScore;
	T_DOUBLE_LINK_LIST tListNode;
}T_TEST_STU;

VOID test1()
{
	T_TEST_STU *ptStu = NULL;
	T_TEST_STU *ptStu2 = NULL;
	LIST_HEAD(tListRoot);
	T_TEST_STU *iterator;

	ptStu = (T_TEST_STU *)malloc(sizeof(T_TEST_STU));
	if (PUB_PTR_IS_NULL(ptStu)) {
		PUB_PRINT("ptStu malloc failed\n");
		goto EXIT_LABEL;
	}
	ptStu->uiAge = 1;
	ptStu->uiSex = 1;
	ptStu->uiScore = 100;


	INIT_LIST_HEAD(&ptStu->tListNode);
	list_add(&ptStu->tListNode,&tListRoot);

	ptStu2 = (T_TEST_STU *)malloc(sizeof(T_TEST_STU));
	if (PUB_PTR_IS_NULL(ptStu)) {
		PUB_PRINT("ptStu malloc failed\n");
		goto EXIT_LABEL;
	}
	ptStu2->uiAge = 2;
	ptStu2->uiSex = 2;
	ptStu2->uiScore = 150;
	INIT_LIST_HEAD(&ptStu2->tListNode);
	list_add(&ptStu2->tListNode,&tListRoot);

	list_for_each_entry(iterator, &tListRoot,tListNode) {
		printf("age:%d, sex%d, score:%d\n",
				iterator->uiAge,
				iterator->uiSex,
				iterator->uiScore);
		list_del(&iterator->tListNode);
	}	

	PUB_PRINT("list is empty:%x\n",list_empty(&tListRoot));
	
		
EXIT_LABEL:
	return ;
}

int main()
{
	test1();
	return 0;
}
