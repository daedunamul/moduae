/*
	emptydb::Root
*/
#pragma once
#include "emptydbCommon.h"

struct emptydbRoot
{
	emptydbCommonCountType ObjectMaxCount , ObjectCount , PropertyMaxCount , PropertyCount ;
	struct plibStdMemoryPool *ObjectNodePool , *PropertyNodePool ;
	struct plibStdDataBST *ObjectGenesisNode , *ObjectThisNode , *PropertyThisNode ;
} ;

struct emptydbRoot* emptydbRoot_create( emptydbCommonCountType ObjectMaxCount , emptydbCommonCountType PropertyMaxCount ) ;
bool emptydbRoot_delete( struct emptydbRoot **Root ) ;