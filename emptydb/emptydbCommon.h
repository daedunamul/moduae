/*
	emptydb::Common
*/
#pragma once
#include "../plib/plibStdDataBST.h"
#include "../plib/plibStdMemoryPool.h"

typedef uint32_t emptydbCommonKeyType ;

struct emptydbCommonObjectValueType
{
	struct plibStdDataBST *MemberObjectRootNode , *MemberKeyValueRootNode ;
} ;

struct emptydbCommonKeyValueType
{
	size_t DataSize , DataLength ;
	uint8_t *Data ;
} ;

enum plibStdDataBSTStatus emptydbCommon_compareKey( uint8_t *Key1 , uint8_t *Key2 ) ;
