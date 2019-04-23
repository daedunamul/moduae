/*
	pnode
*/
#pragma once

#include "pmem.h"

// node
struct pnode_Node
{
	void *Value ;
	struct pnode_Node *Left , *Right ;
}

inline void pnode_linkLeft( struct pnode_Node *New , struct pnode_Node *Old ) ;
inline void pnode_linkRight( struct pnode_Node *New , struct pnode_Node *Old ) ;
inline void pnode_unlink( struct pnode_Node *Old ) ;
