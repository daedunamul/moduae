/* 
	binary search tree
*/
#pragma once
#include "type.h"

enum bst_STATUS { bst_status_LESS , bst_status_GREAT , bst_status_EQUAL } ;

struct bst_Node
{
	void *Key ;
	void *Value ;
	struct bst_Node *Left , *Right ;
} ;

struct bst_Node* bst_search( struct bst_Node *RootNode , void *Key , enum bst_STATUS ( *judge )( void *Key1 , void *Key2 ) ) ;

bool bst_insert( struct bst_Node **RootNode , struct bst_Node *NewNode , enum bst_STATUS ( *judge )( void *Key1 , void *Key2 ) ) ;
struct bst_Node* pdb_bst_desert( struct bst_Node **RootNode , char *Key , enum bst_STATUS ( *judge )( void *Key1 , void *Key2 ) ) ;
