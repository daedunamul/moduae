/*
	plib::Data::BTree
	Balanced Tree
*/
#pragma once
#include "plibData.h"

typedef uint32_t plibDataBTreeKeyType ;

struct plibDataBTreeNode
{
	plibCommonAnyType *Top , *Bottom ;
	struct plibDataBTreeNode *Left , *Right ;
	
	plibDataBTreeKeyType Key ;
	plibCommonAnyType *Value ;
} ;
struct plibDataBTreeTable
{
	struct plibDataBTreeTable *Top ;
	struct plibDataBTreeNode *Head , *Tail ;
	plibCommonCountType MaxCount , Count ;
} ;

plibDataBTree_initializeTable( struct plibDataBTreeTable *Table , plibCommonCountType MaxCount , struct plibError *Error ) ;