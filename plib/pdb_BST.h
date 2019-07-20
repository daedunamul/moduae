/*
	pdb
	BST
*/
#pragma once
#include "core/pmem.h"

enum
{
	pdb_bst_key_LENGTH = 32
} ;

struct pdb_bst_Node
{
	char *Key ;
	void *Value ;
	struct pdb_bst_Node *Left , *Right ;
} ;

struct pdb_bst_Node* pdb_bst_search( struct pdb_bst_Node *RootNode , char *Key ) ;

bool pdb_bst_insert( struct pdb_bst_Node **RootNode , struct pdb_bst_Node *NewNode ) ;
struct pdb_bst_Node* pdb_bst_desert( struct pdb_bst_Node **RootNode , char *Key ) ;
