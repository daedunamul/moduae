/*
	pnode
	Chain
*/
#pragma once

#include "pnode.h"

struct pnode_Chain
{
	struct pnode_Node *Entry ;
} ;

inline void pnode_chain_push( struct pnode_Chain *Chain , bool Flag , struct pnode_Node *NewNode ) ;
inline struct pnode_Node* pnode_chain_pop( struct pnode_Chain *Chain , bool Flag ) ;
inline struct pnode_Node* pnode_chain_lookup
( 
	struct pnode_Chain *Chain , bool Flag , void *Data , 
	bool ( *judge )( void* , void* )
) ;
