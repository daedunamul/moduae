/*
	emptydb::Property
*/
#pragma once
#include "emptydbDB.h"

#define emptydbPropertySubIndex 1

struct plibDataHBST* emptydbProperty_create( struct emptydbDB *DB , plibCommonAnyType *Key ) ;
void emptydbProperty_createStream( struct emptydbDB *DB , struct emptydbStream *Stream ) ;

bool emptydbProperty_delete( struct emptydbDB *DB , plibCommonAnyType *Key ) ;
void emptydbProperty_deleteStream( struct emptydbDB *DB , struct emptydbStream *Stream ) ;

struct plibDataHBST* emptydbProperty_lookup( struct emptydbDB *DB , plibCommonAnyType *Key ) ;
void emptydbProperty_lookupStream( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream ) ;