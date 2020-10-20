/*
	emptydb::Common
*/
#pragma once
#include "../plib/plibDataHBST.h"
#include "../plib/plibMemoryPool.h"

typedef uint32_t emptydbCommonKeyType ;

enum plibDataHBSTStatus emptydbCommon_compareKey( plibCommonAnyType *Key1 , plibCommonAnyType *Key2 ) ;