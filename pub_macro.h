#ifndef _PUB_MACRO_H
#define _PUB_MACRO_H

typedef unsigned char UINT8;
typedef char INT8;
typedef unsigned short UINT16;
typedef short INT16;
typedef unsigned int UINT32;
typedef int INT32;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef void VOID;

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

/*define common return value*/
#define RESULT_TRUE		TRUE
#define RESULT_FALSE	FALSE

/*common function macro*/
#define PUB_PRINT		printf
#define PUB_PTR_IS_NULL(p)  ((p) == NULL ? RESULT_TRUE : RESULT_FALSE )

#ifndef PUB_MEM_FREE
/*until pub_memory.c come out...*/
#define PUB_MEM_FREE	free
#endif

#ifndef PUB_MEM_MALLOC
#define PUB_MEM_MALLOC	malloc
#endif
/*init list pointer*/
#define PUB_LIST_INIT(list) INIT_LIST_HEAD(list)
/*insert a node after the list head*/
#define PUB_LIST_ADD(srcList, dstList)	list_add((srcList), (dstList))
/*define a list param & init*/
#define PUB_LIST_ROOT_DEF(listRoot)	LIST_HEAD(listRoot)
/*get list node one by one*/
#define PUB_LIST_TRAVERSAL(iterator, listRoot, listNode)	list_for_each_entry(iterator, listRoot, listNode) 
/*traversal for delete list node*/
#define PUB_LIST_TRAVERSAL_SAFE(iterator, next, listRoot, listNode)	list_for_each_entry_safe(iterator, next, listRoot, listNode)
/*del a list node */
#define PUB_LIST_DEL(node)	list_del(node)
/*list is empty or not*/
#define PUB_LIST_IS_EMPTY(list)	list_empty(list)
/*clear all list node & free memory*/
#define PUB_LIST_CLEAR(iterator, next, head, listNode)	\
do														\
{														\
	PUB_LIST_TRAVERSAL_SAFE(iterator, next, head, listNode) {	\
		if (PUB_LIST_IS_EMPTY(head))					\
			break;										\
		PUB_LIST_DEL(&iterator->listNode);				\
		PUB_MEM_FREE(iterator);							\
	}													\
}while(0)



#endif

