/*
	plib::Std::Data::BST
*/
#pragma once
#include "plibStdType.h"

enum plibStdDataBSTStatus { plibStdDataBSTStatusLess , plibStdDataBSTStatusGreat , plibStdDataBSTStatusEqual } ;

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
	enum plibStdDataBSTStatus ( *Operator )( void *Key1 , void *Key2 ) 
) ;
struct plibStdDataBST*
plibStdDataBST_pop
(
	struct plibStdDataBST **EntryNode , 
	void *Key , 
	enum plibStdDataBSTStatus ( *Operator )( void *Key1 , void *Key2 ) 
) ;
struct plibStdDataBST*
plibStdDataBST_lookup
(
	struct plibStdDataBST *ThisNode , 
	void *Key , 
	enum plibStdDataBSTStatus ( *Operator )( void *Key1 , void *Key2 ) 
) ;
