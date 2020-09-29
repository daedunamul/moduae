/*
	plib::Data::HBST
	Hierarchial Binary Search Tree
*/
#pragma once
#include "plibCommon.h"

enum plibDataHBSTStatus { plibDataHBSTStatusLess , plibDataHBSTStatusGreat , plibDataHBSTStatusEqual } ;

struct plibDataHBSTSub
{
	plibCommonCountType Length , Count ; // array indexes , node counts
	struct plibDataHBST **RootNodeArray ;
} ;
struct plibDataHBST
{
	plibCommonAnyType *Key , *Value ;
	struct plibDataHBST *Left , *Right ;
	
	struct plibDataHBSTSub *Sub ; // for allocated node to use sub
} ;

typedef enum plibDataHBSTStatus ( *plibDataHBSTStatusFxType )( plibCommonAnyType *Key1 , plibCommonAnyType *Key2 ) ;
typedef void ( *plibDataHBSTTraversedNodeFxType )( struct plibDataHBST *TraversedNode ) ;

bool plibDataHBST_push( struct plibDataHBST **EntryNode , struct plibDataHBST *NewNode , plibDataHBSTStatusFxType StatusFx ) ;
struct plibDataHBST* plibDataHBST_pop( struct plibDataHBST **EntryNode , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx ) ;
struct plibDataHBST* plibDataHBST_lookup( struct plibDataHBST *ThisNode , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx ) ;

bool plibDataHBST_pushSub( struct plibDataHBSTSub *Sub , plibCommonCountType Index , struct plibDataHBST *NewNode , plibDataHBSTStatusFxType StatusFx ) ;
struct plibDataHBST* plibDataHBST_popSub( struct plibDataHBSTSub *Sub , plibCommonCountType Index , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx ) ;

void plibDataHBST_traverse( struct plibDataHBST *EntryNode , plibDataHBSTTraversedNodeFxType TraversedNodeFx ) ;