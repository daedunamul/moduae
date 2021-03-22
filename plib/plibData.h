/*
	plib::Data
*/
#pragma once
#include "plibError.h"
#include <stdarg.h>

// node
struct plibDataNode
{
	struct plibDataNode *Left , *Right ;
	plibCommonAnyType *Value ;
} ;

void plibData_linkNode( plibCommonCountType Count , ... ) ;
void plibData_swapNode( struct plibDataNode *Node1 , struct plibDataNode *Node2 ) ;

// key
#define plibDataKeyLength 9
#define plibDataKeyStringLength 64

enum plibDataKeyComparison
{
	plibDataKeyComparisonEqual = 0 , 
	plibDataKeyComparisonLess = 1 , 
	plibDataKeyComparisonGreat = 2 
} ;
typedef uint64_t plibDataKeyType[ plibDataKeyLength ] ;
typedef uint64_t plibDataKeyUnitType ;

#define plibData_getKeyLength( Count ) ( Count == 0 ? 1 : 2 + ( ( Count - 1 ) >> 3 ) )

void plibData_initializeKey( plibDataKeyType Key ) ;
enum plibDataKeyComparison plibData_compareKey( plibDataKeyType Key1 , plibDataKeyType Key2 ) ;
void plibData_getKeyFromString( plibDataKeyType Key , char *String ) ;