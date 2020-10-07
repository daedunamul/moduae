/*
	emptydb::Object
*/
#pragma once
#include "emptydbProperty.h"

bool emptydbObject_createRoot( struct emptydbDB *DB , emptydbCommonKeyType Key ) ;
bool emptydbObject_deleteRoot( struct emptydbDB *DB ) ;

bool emptydbObject_create( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
bool emptydbObject_delete( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
void emptydbObject_flush( struct emptydbDB *DB , struct plibDataHBST *ObjectEntryNode ) ;

bool emptydbObject_point( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
void emptydbObject_lookup( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream ) ;