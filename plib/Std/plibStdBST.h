/*
	plib
	Std
	Binary Search Tree
*/
#pragma once
#include "plibStdType.h"

enum plibStdBST_STATUS { plibStdBST_status_LESS , plibStdBST_status_GREAT , plibStdBST_status_EQUAL } ;

struct plibStdBST_Node
{
	void *Key ;
	void *Value ;
	struct plibStdBST_Node *Left , *Right ;
} ;

struct plibStdBST_Node* plibStdBST_search( struct plibStdBST_Node *RootNode , void *Key , enum plibStdBST_STATUS ( *judge )( void *Key1 , void *Key2 ) ) ;

bool plibStdBST_insert( struct plibStdBST_Node **RootNode , struct plibStdBST_Node *NewNode , enum plibStdBST_STATUS ( *judge )( void *Key1 , void *Key2 ) ) ;
struct plibStdBST_Node* plibStdBST_desert( struct plibStdBST_Node **RootNode , char *Key , enum plibStdBST_STATUS ( *judge )( void *Key1 , void *Key2 ) ) ;
