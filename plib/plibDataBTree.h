/*
	plib::Data::BTree
	Balanced Tree
*/
#pragma once
#include "plibData.h"

#define plibDataBTreeDegree 5

struct plibDataBTreeNode
{
	plibDataKeyType Key ;
	plibCommonAnyType *Value ;
} ;
struct plibDataBTreeUnit
{
	struct plibDataBTreeNode Nodes[ plibDataBTreeDegree ] ;
	plibCommonCountType NodeCount ;
	
	struct plibDataBTreeUnit *Top , *Bottoms[ plibDataBTreeDegree + 1 ] ;
	plibCommonCountType BottomCount ;
} ;

void plibDataBTree_swapNode( struct plibDataBTreeNode *Node1 , struct plibDataBTreeNode *Node2 ) ;
void plibDataBTree_sortNode( struct plibDataBTreeNode *NodeArray , plibCommonCountType NodeCount ) ;

void plibDataBTree_initialize( struct plibDataBTreeUnit *Unit , struct plibError *Error ) ;