/*
	emptydb::Property
*/
#pragma once
#include "emptydbDB.h"
#include "emptydbStream.h"

bool emptydbProperty_create( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
bool emptydbProperty_delete( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
void emptydbProperty_flush( struct emptydbDB *DB , struct plibDataHBST *PropertyEntryNode ) ;

void emptydbProperty_lookup( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream ) ;