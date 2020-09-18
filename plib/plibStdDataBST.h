/*
	plib::Std::Data::BST
*/
#pragma once
#include "plibStdType.h"

enum plibStdDataBSTStatus { plibStdDataBSTStatusLess , plibStdDataBSTStatusGreat , plibStdDataBSTStatusEqual } ;

struct plibStdDataBST
{
	uint8_t *Key ;
	uint8_t *Value ;
	struct plibStdDataBST *Left , *Right ;
} ;

bool
plibStdDataBST_push
(
	struct plibStdDataBST **EntryNode , 
	struct plibStdDataBST *NewNode , 
	enum plibStdDataBSTStatus ( *Operator )( uint8_t *Key1 , uint8_t *Key2 ) 
) ;
struct plibStdDataBST*
plibStdDataBST_pop
(
	struct plibStdDataBST **EntryNode , 
	uint8_t *Key , 
	enum plibStdDataBSTStatus ( *Operator )( uint8_t *Key1 , uint8_t *Key2 ) 
) ;
struct plibStdDataBST*
plibStdDataBST_lookup
(
	struct plibStdDataBST *ThisNode , 
	uint8_t *Key , 
	enum plibStdDataBSTStatus ( *Operator )( uint8_t *Key1 , uint8_t *Key2 ) 
) ;