/*
	emptydb::DB
*/
#pragma once
#include "emptydbCommon.h"

struct emptydbDB
{
	size_t ObjectMaxCount , ObjectCount , KeyValueMaxCount , KeyValueCount ;
	struct plibStdDataBST *ObjectRootNode , *ObjectThisNode ;
	struct plibStdMemoryPool *ObjectNodePool , *KeyValueNodePool ;
} ;

struct emptydbDBObjectValueType
{
	struct plibStdDataBST *MemberObjectRootNode , *MemberKeyValueRootNode ;
} ;

struct emptydbDB* emptydbDB_createDB( size_t ObjectMaxCount , size_t KeyValueMaxCount ) ;
bool emptydbDB_deleteDB( struct emptydbDB **DB ) ;
