/*
	pdb
	BST
*/
#pragma once
#include "core/pmem.h"

enum
{
	pdb_bst_status_NULL = 0 , 
	pdb_bst_status_NONEOFLEFT , 
	pdb_bst_status_NONEOFRIGHT , 
	
	pdb_bst_status_NONEOFPARENT , 
	pdb_bst_status_LEFTOFPARENT , 
	pdb_bst_status_RIGHTOFPARENT , 
	pdb_bst_status_BOTHOFPARENT 
} ;

struct pdb_bst_Node
{
	uint64_t Key ;
	
	struct pdb_bst_Node *Left , *Right ;
} ;
struct pdb_bst_Parameter
{
	struct pdb_bst_Node *ParentNode , *Node ;
	uint8_t Status ;
} ;

struct pdb_bst_Parameter pdb_bst_search( struct pdb_bst_Node *TopNode , uint64_t Key ) ;
struct pdb_bst_Parameter pdb_bst_getCandidate( struct pdb_bst_Node *Node ) ;
bool pdb_bst_insert( struct pdb_bst_Node **TopNode , struct pdb_bst_Node *NewNode ) ;
