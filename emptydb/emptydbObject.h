/*
	emptydb::Object
*/
#pragma once
#include "emptydbProperty.h"

#define emptydbObjectSubIndex 0

bool emptydbObject_createRoot( struct emptydbDB *DB , emptydbCommonKeyType Key ) ;
bool emptydbObject_deleteRoot( struct emptydbDB *DB ) ;

struct plibDataHBST* emptydbObject_create( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
bool emptydbObject_delete( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
void emptydbObject_flushFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data ) ;

bool emptydbObject_point( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
void emptydbObject_lookup( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream ) ;