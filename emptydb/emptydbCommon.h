/*
	emptydb::Common
*/
#pragma once
#include "../plib/plibDataHBST.h"
#include "../plib/plibMemoryPool.h"

typedef uint32_t emptydbCommonKeyType ;

struct emptydbCommonPropertyValueType
{
	plibCommonCountType Type , Size , Length ;
	plibCommonAnyType *Data ;
} ;

#define emptydbCommon_referNode( MemoryAddress ) ( struct plibDataHBST* )( MemoryAddress )
#define emptydbCommon_referKey( MemoryAddress ) ( MemoryAddress + sizeof( struct plibDataHBST ) )
#define emptydbCommon_referSub( MemoryAddress ) ( struct plibDataHBSTSub* )( MemoryAddress + sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) )
#define emptydbCommon_referSubRootArray( MemoryAddress ) ( struct plibDataHBST** )( MemoryAddress + sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) + sizeof( struct plibDataHBSTSub ) )
#define emptydbCommon_referPropertyValue( MemoryAddress ) ( MemoryAddress + sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) )
#define emptydbCommon_referSubProperty( SubAddress ) ( SubAddress->RootNodeArray )
#define emptydbCommon_referSubObject( SubAddress ) ( SubAddress->RootNodeArray + 1 )

enum plibDataHBSTStatus emptydbCommon_compareKey( plibCommonAnyType *Key1 , plibCommonAnyType *Key2 ) ;