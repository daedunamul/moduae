/*
	emptydb::Root
*/
#pragma once
#include "emptydbCommon.h"

struct emptydbRoot
{
	size_t ObjectMaxCount , ObjectCount , KeyValueMaxCount , KeyValueCount ;
	struct plibStdDataBST *ObjectRootNode , *ObjectThisNode ;
	struct plibStdMemoryPool *ObjectNodePool , *KeyValueNodePool ;
} ;

struct emptydbRoot* emptydbRoot_create( size_t ObjectMaxCount , size_t KeyValueMaxCount ) ;
bool emptydbRoot_delete( struct emptydbRoot **Root ) ;
