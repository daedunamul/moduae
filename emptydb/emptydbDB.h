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

struct emptydbDB* emptydbDB_create( plibCommonCountType ObjectMaxCount , plibCommonCountType PropertyMaxCount ) ;
bool emptydbDB_delete( struct emptydbDB **DB ) ;