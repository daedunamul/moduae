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

enum plibStdDataBSTStatus emptydbCommon_compareKey( uint8_t *Key1 , uint8_t *Key2 ) ;
