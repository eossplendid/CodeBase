#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pub_include.h"
#include "hash.h"


#define MAX_STRING_LEN		32

typedef struct hash	T_HASH;
typedef struct {
	UINT8 ucString[MAX_STRING_LEN];
	UINT32 uiAttri;
	UINT32 uiValue;
}T_STRING_NODE;


UINT32 StringNodeHashKey(VOID *ptData)
{
	UINT32 uiReturn = 0;
	T_STRING_NODE *ptNode = NULL;

	if(PUB_PTR_IS_NULL(ptData)) {
		//DEBUG("ptData is null");
		goto EXIT_LABEL;
	}
	
	ptNode = (T_STRING_NODE *)ptData;
	uiReturn = string_hash_make((const INT8 *)ptNode->ucString);

EXIT_LABEL:
	return uiReturn;
}

INT32 StringNodeHashCmp(const VOID *ptData1, const VOID *ptData2)
{
	INT32 iReturn = 0;
	T_STRING_NODE *ptNode1, *ptNode2;

	if (PUB_PTR_IS_NULL(ptData1) || PUB_PTR_IS_NULL(ptData2)) {
		goto EXIT_LABEL;
	}
	ptNode1 = (T_STRING_NODE *)ptData1;
	ptNode2 = (T_STRING_NODE *)ptData2;
	iReturn = (strcmp(ptNode1->ucString, ptNode2->ucString) == 0);

EXIT_LABEL:
	return iReturn;
}

VOID *StringNodeHashAlloc(VOID *ptData)
{
	return ptData;
}

VOID *StringNodeHashFree(VOID *ptNode)
{
	if (PUB_PTR_IS_NULL(ptNode)) {
		return NULL;
	}
	PUB_MEM_FREE((T_STRING_NODE *)ptNode);
	return;
}

INT32 HashFuncTest()
{
	T_HASH *ptHash = NULL;
	T_STRING_NODE *ptNode = NULL;
	T_STRING_NODE *ptNode2 = NULL;
	T_STRING_NODE *ptTest = NULL;

	ptHash = hash_create(StringNodeHashKey, StringNodeHashCmp);
	if (PUB_PTR_IS_NULL(ptHash)) {
		goto EXIT_LABEL;
	}
	ptNode = (T_STRING_NODE *)PUB_MEM_MALLOC(sizeof(T_STRING_NODE));
	if (PUB_PTR_IS_NULL(ptNode)) {
		goto EXIT_LABEL;
	}
	strcpy(ptNode->ucString, "string no 1");
	ptNode->uiAttri = 0x1;
	ptNode->uiValue = 0x1;

	hash_get(ptHash, ptNode, StringNodeHashAlloc);
	ptTest = hash_get(ptHash, ptNode, StringNodeHashAlloc);
	if (PUB_PTR_IS_NULL(ptTest)) {
		printf("error:%d\n", __LINE__);
		goto EXIT_LABEL;
	}

	printf("str:%s\n,attri:%d\nval:%d\n",ptTest->ucString,
			ptTest->uiAttri, ptTest->uiValue);

	ptNode2 = (T_STRING_NODE *)PUB_MEM_MALLOC(sizeof(T_STRING_NODE));
	if (PUB_PTR_IS_NULL(ptNode2)) {
		goto EXIT_LABEL;
	}
	strcpy(ptNode2->ucString, "string no 2");
	ptNode2->uiAttri = 0x2;
	ptNode2->uiValue = 0x2;

	hash_get(ptHash, ptNode2, StringNodeHashAlloc);

	//hash map free
	hash_clean(ptHash, NULL);
	hash_free(ptHash);
	free(ptNode);
	free(ptNode2);
EXIT_LABEL:
	return 0;
}

int main()
{
	HashFuncTest();
	return 0;
}


