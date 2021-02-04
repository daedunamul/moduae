/*
	plib::Data::HBST
	Hierarchial Binary Search Tree
*/
#pragma once
#include "plibData.h"

enum plibDataHBSTStatus { plibDataHBSTStatusLess , plibDataHBSTStatusGreat , plibDataHBSTStatusEqual } ;

struct plibDataHBST
{
	plibCommonAnyType *Key , *Value ;
	struct plibDataHBST *Top , *Left , *Right ;
	
	// Super
	plibCommonCountType SuperIndex ;
	struct plibDataHBST *Super ;
	
	// Sub
	plibCommonCountType SubLength ;
	struct plibDataHBSTSub *Sub ; // for allocated node to use sub
} ;
struct plibDataHBSTSub
{
	plibCommonCountType Count ; // array indexes , node counts
	struct plibDataHBST *RootNode ;
} ;

typedef enum plibDataHBSTStatus ( *plibDataHBSTStatusFxType )( plibCommonAnyType *Key1 , plibCommonAnyType *Key2 ) ;
typedef void ( *plibDataHBSTTraversalFxType )( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error ) ;

void plibDataHBST_initialize( struct plibDataHBST *Node , struct plibErrorType *Error ) ;

void plibDataHBST_push( struct plibDataHBST **EntryNode , struct plibDataHBST *NewNode , plibDataHBSTStatusFxType StatusFx , struct plibErrorType *Error ) ;
struct plibDataHBST* plibDataHBST_pop( struct plibDataHBST **EntryNode , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx , struct plibErrorType *Error ) ;
struct plibDataHBST* plibDataHBST_lookup( struct plibDataHBST *ThisNode , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx , struct plibErrorType *Error ) ;

void plibDataHBST_pushSub( struct plibDataHBST *Node , plibCommonCountType Index , struct plibDataHBST *NewNode , plibDataHBSTStatusFxType StatusFx , struct plibErrorType *Error ) ;
struct plibDataHBST* plibDataHBST_popSub( struct plibDataHBST *Node , plibCommonCountType Index , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx , struct plibErrorType *Error ) ;

void plibDataHBST_traverse( struct plibDataHBST *EntryNode , plibDataHBSTTraversalFxType TraversalFx , plibCommonAnyType *Data , struct plibErrorType *Error ) ;