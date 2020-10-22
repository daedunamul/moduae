/*
	emptydb::Property
*/
#pragma once
#include "emptydbDB.h"

#define emptydbPropertySubIndex 0

bool emptydbProperty_create( struct emptydbDB *DB , struct emptydbStream *Stream ) ;
bool emptydbProperty_delete( struct emptydbDB *DB , struct emptydbStream *Stream ) ;

void emptydbProperty_lookup( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream ) ;