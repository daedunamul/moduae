/*
	emptydb::Common
*/
#pragma once
#include "../plib/plibDataHBST.h"
#include "../plib/plibMemoryPool.h"

typedef uint32_t emptydbCommonKeyType ;
typedef uint32_t emptydbCommonCountType ;

struct emptydbCommonObjectValueType
{
	struct plibStdDataBST *MemberObjectGenesisNode , *MemberPropertyGenesisNode ;
} ;

struct emptydbCommonPropertyValueType
{
	emptydbCommonCountType DataSize , DataLength ;
	uint8_t DataType ;
	uint8_t *Data ;
} ;

enum plibStdDataBSTStatus emptydbCommon_compareKey( uint8_t *Key1 , uint8_t *Key2 ) ;

#define emptydbCommon_referNode( EntryAddress ) ( ( struct plibStdDataBST* )EntryAddress )
#define emptydbCommon_referKey( EntryAddress ) ( EntryAddress + sizeof( struct plibStdDataBST ) )
#define emptydbCommon_referValue( EntryAddress ) ( EntryAddress + sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) )