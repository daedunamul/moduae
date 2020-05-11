/*
	plib::Std::Data::BST
*/
#pragma once
#include "plibStdData.h"

enum plibStdDataBST_Status { plibStdDataBST_Status_Less , plibStdDataBST_Status_Great , plibStdDataBST_Status_Equal } ;

struct plibStdDataBST
{
	void *Key ;
	void *Value ;
	struct plibStdDataBST *Left , *Right ;
} ;

bool
plibStdDataBST_push
(
	struct plibStdDataBST **EntryNode , 
	struct plibStdDataBST *NewNode , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
) ;
struct plibStdDataBST*
plibStdDataBST_pop
(
	struct plibStdDataBST **EntryNode , 
	void *Key , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
) ;
struct plibStdDataBST*
plibStdDataBST_lookup
(
	struct plibStdDataBST *ThisNode , 
	void *Key , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
) ;
