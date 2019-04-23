/*
	pnode
*/
#include "pnode.h"

// node
void pnode_linkLeft( struct pnode_Node *New , struct pnode_Node *Old )
{
	// no prevention for accessing null memories
	// Old <- New -> Old.Right
	New->Left = Old ;
	New->Right = Old->Right ;
	
	// New.Left -> New <- New.Right
	New->Left->Right = New ;
	New->Right->Left = New ;
}
void pnode_linkRight( struct pnode_Node *New , struct pnode_Node *Old )
{
	// no prevention for accessing null memories
	// Old.Left <- New -> Old
	New->Left = Old->Left ;
	New->Right = Old ;
	
	// New.Left -> New <- New.Right
	New->Left->Right = New ;
	New->Right->Left = New ;
}
void pnode_unlink( struct pnode_Node *Old )
{
	// no prevention for accessing null memories
	Old->Left->Right = Old->Right ;
	Old->Right->Left = Old->Left ;
}
