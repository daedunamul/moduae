/*
	emptydb::Root
*/
#pragma once
#include "emptydbCommon.h"

struct emptydbRoot
{
	emptydbCommonCountType ObjectMaxCount , ObjectCount , KeyValueMaxCount , KeyValueCount ;
	struct plibStdMemoryPool *ObjectNodePool , *KeyValueNodePool ;
	struct plibStdDataBST *ObjectRootNode , *ObjectThisNode , *KeyValueThisNode ;
} ;

struct emptydbRoot* emptydbRoot_create( emptydbCommonCountType ObjectMaxCount , emptydbCommonCountType KeyValueMaxCount ) ;
bool emptydbRoot_delete( struct emptydbRoot **Root ) ;
