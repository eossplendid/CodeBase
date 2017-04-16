#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pub_list.h"
#include "pub_macro.h"

/*test struct 1*/
typedef struct {
	UINT32 uiAge;
	UINT32 uiSex;
	UINT32 uiScore;
	T_DOUBLE_LINK_LIST tListNode;
}T_TEST_STU;

/*test struct 2*/
typedef struct {
	UINT32 uiCmdCode;
	UINT16 usOper;
	UINT16 usStatus;
	T_DOUBLE_LINK_LIST tListNode;
}T_CMD_NODE;

/*FUNC set the value of T_TEST_STU*/
#define FUNC_SET_STU(stu, age, sex, score)	\
do	\
{\
	(stu)->uiAge = (age);	\
	(stu)->uiSex = (sex);	\
	(stu)->uiScore = (score);	\
}while(0)

/*FUNC set the value of T_CMD_NODE*/
#define FUNC_SET_CMD(cmd, code, oper, status)	\
do	\
{\
	(cmd)->uiCmdCode = (code);	\
	(cmd)->usOper = (oper);	\
	(cmd)->usStatus = (status);	\
}while(0)

extern int errno;

#if 0
/*use origin list interface*/
VOID test1()
{
	T_TEST_STU *ptStu = NULL;
	T_TEST_STU *ptStu2 = NULL;
	LIST_HEAD(tListRoot);
	T_TEST_STU *iterator;

	ptStu = (T_TEST_STU *)PUB_MEM_MALLOC(sizeof(T_TEST_STU));
	if (PUB_PTR_IS_NULL(ptStu)) {
		PUB_PRINT("ptStu PUB_MEM_MALLOC failed\n");
		goto EXIT_LABEL;
	}
	FUNC_SET_STU(ptStu, 1, 1, 100);

	INIT_LIST_HEAD(&ptStu->tListNode);
	list_add(&ptStu->tListNode,&tListRoot);

	ptStu2 = (T_TEST_STU *)PUB_MEM_MALLOC(sizeof(T_TEST_STU));
	if (PUB_PTR_IS_NULL(ptStu)) {
		PUB_PRINT("ptStu PUB_MEM_MALLOC failed\n");
		goto EXIT_LABEL;
	}
	FUNC_SET_STU(ptStu2, 2, 2, 150);
	INIT_LIST_HEAD(&ptStu2->tListNode);
	list_add(&ptStu2->tListNode,&tListRoot);

	list_for_each_entry(iterator, &tListRoot,tListNode) {
		if (list_empty(&tListRoot)) {
			break;
		}
		printf("age:%d, sex%d, score:%d\n",
				iterator->uiAge,
				iterator->uiSex,
				iterator->uiScore);
		list_del(&iterator->tListNode);
		PUB_MEM_FREE(iterator);
	}	

	PUB_PRINT("list is empty:%x\n",list_empty(&tListRoot));
	
		
EXIT_LABEL:
	return ;
}
#endif

/*use self defined macro*/
VOID test2()
{
	/*define a list root*/
	PUB_LIST_ROOT_DEF(tCmdRoot);	
	/*define list node & iterator for traversal*/
	T_CMD_NODE *ptNode = NULL;
	T_CMD_NODE *ptNode2;
	T_CMD_NODE *ptIterator, *next = NULL;

	/*create node*/
	ptNode = (T_CMD_NODE *)PUB_MEM_MALLOC(sizeof(T_CMD_NODE));
	if (PUB_PTR_IS_NULL(ptNode)) {
		PUB_PRINT("ptNode PUB_MEM_MALLOC failed:%s\n", strerror(errno));
		goto EXIT_LABEL;
	}

	FUNC_SET_CMD(ptNode, 0x1A2B3C4D, 0x1, 0x1);

	/*init list in the node & add to list root*/
	PUB_LIST_INIT(&ptNode->tListNode);
	PUB_LIST_ADD(&ptNode->tListNode, &tCmdRoot);

	ptNode2 = (T_CMD_NODE *)PUB_MEM_MALLOC(sizeof(T_CMD_NODE));
	if (PUB_PTR_IS_NULL(ptNode2)) {
		PUB_PRINT("ptNode2 PUB_MEM_MALLOC failed\n");
		goto EXIT_LABEL;
	}

	FUNC_SET_CMD(ptNode2, 0xDCBA4321, 0x2, 0x2);
	
	PUB_LIST_INIT(&ptNode2->tListNode);
	PUB_LIST_ADD(&ptNode2->tListNode, &tCmdRoot);

	/*
	 * list traversal, check every node, 
	 * if you need to delete some node, use PUB_LIST_TRAVERSAL_SAFE()
	 * */
	PUB_LIST_TRAVERSAL(ptIterator, &tCmdRoot, tListNode) {
		PUB_PRINT("cmd:%x, opr:%x, status:%x\n",
					ptIterator->uiCmdCode,
					ptIterator->usOper,
					ptIterator->usStatus);
	}

	/*
	 * clear all node & PUB_MEM_FREE the memory, leave root empty
	 * if tCmdRoot is not cleared here, you can check this issue out by using valgrind 
	 * */
	PUB_PRINT("list status:%d\n",PUB_LIST_IS_EMPTY(&tCmdRoot));
	PUB_LIST_CLEAR(ptIterator, next, &tCmdRoot, tListNode);
	PUB_PRINT("list status:%d\n",PUB_LIST_IS_EMPTY(&tCmdRoot));
	
EXIT_LABEL:
	return;
}

int main()
{
//	test1();
	test2();
	return 0;
}
