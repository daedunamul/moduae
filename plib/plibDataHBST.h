/*
	plib::Data::HBST
	Hierarchial Binary Search Tree
*/
#pragma once
#include "plibCommon.h"

enum
{
	plibDataHBSTErrorExistance = plibErrorDataHBST + 0x01 , 
	plibDataHBSTErrorNoExistance = plibErrorDataHBST + 0x02 , 
	plibDataHBSTErrorUnknownStatus = plibErrorDataHBST + 0x03 
} ;

enum plibDataHBSTStatus { plibDataHBSTStatusLess , plibDataHBSTStatusGreat , plibDataHBSTStatusEqual } ;

struct plibDataHBSTSub
{
	plibCommonCountType Count ; // array indexes , node counts
	struct plibDataHBST *RootNode ;
} ;
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

typedef enum plibDataHBSTStatus ( *plibDataHBSTStatusFxType )( plibCommonAnyType *Key1 , plibCommonAnyType *Key2 ) ;
typedef void ( *plibDataHBSTTraversalFxType )( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data ) ;

void plibDataHBST_initialize( struct plibDataHBST *Node ) ;

void plibDataHBST_push( struct plibDataHBST **EntryNode , struct plibDataHBST *NewNode , plibDataHBSTStatusFxType StatusFx ) ;
struct plibDataHBST* plibDataHBST_pop( struct plibDataHBST **EntryNode , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx ) ;
struct plibDataHBST* plibDataHBST_lookup( struct plibDataHBST *ThisNode , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx ) ;

void plibDataHBST_pushSub( struct plibDataHBST *Node , plibCommonCountType Index , struct plibDataHBST *NewNode , plibDataHBSTStatusFxType StatusFx ) ;
struct plibDataHBST* plibDataHBST_popSub( struct plibDataHBST *Node , plibCommonCountType Index , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx ) ;

void plibDataHBST_traverse( struct plibDataHBST *EntryNode , plibDataHBSTTraversalFxType TraversalFx , plibCommonAnyType *Data ) ;