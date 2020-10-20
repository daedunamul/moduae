/*
	emptydb::DB
*/
#pragma once
#include "emptydbStream.h"

struct emptydbDB
{
	plibCommonCountType ObjectMaxCount , ObjectCount , PropertyMaxCount , PropertyCount ;
	struct plibMemoryPool *ObjectNodePool , *PropertyNodePool ;
	struct plibDataHBST *ObjectRootNode , *ObjectThisNode , *PropertyThisNode ;
} ;

struct emptydbDBPropertyValueType
{
	plibCommonCountType Type , Size , Length ;
	plibCommonAnyType *Data ;
} ;

struct emptydbDB* emptydbDB_create( plibCommonCountType ObjectMaxCount , plibCommonCountType PropertyMaxCount ) ;
bool emptydbDB_delete( struct emptydbDB **DB ) ;

#define emptydbDB_referNodeFromMemory( MemoryAddress ) ( struct plibDataHBST* )( MemoryAddress )
#define emptydbDB_referKeyFromMemory( MemoryAddress ) ( MemoryAddress + sizeof( struct plibDataHBST ) )
#define emptydbDB_referSubFromMemory( MemoryAddress ) ( struct plibDataHBSTSub* )( MemoryAddress + sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) )
#define emptydbDB_referPropertyValueFromMemory( MemoryAddress ) ( MemoryAddress + sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) )