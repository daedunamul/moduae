/*
	emptydb::Object
*/
#pragma once
#include "emptydbProperty.h"

#define emptydbObjectSubIndex 0

bool emptydbObject_createRoot( struct emptydbDB *DB , emptydbCommonKeyType Key ) ;
bool emptydbObject_deleteRoot( struct emptydbDB *DB ) ;

struct plibDataHBST* emptydbObject_create( struct emptydbDB *DB , plibCommonAnyType *Key ) ;
void emptydbObject_createStream( struct emptydbDB *DB , struct emptydbStream *Stream ) ;

bool emptydbObject_delete( struct emptydbDB *DB , plibCommonAnyType *Key ) ;
void emptydbObject_deleteStream( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
void emptydbObject_flushFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data ) ;

bool emptydbObject_pointStream( struct emptydbDB *DB , struct emptydbStream *Stream ) ;

struct plibDataHBST* emptydbObject_lookup( struct emptydbDB *DB , plibCommonAnyType *Key ) ;
void emptydbObject_lookupStream( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream ) ;