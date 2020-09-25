/*
	emptydb::Property
*/
#pragma once
#include "emptydbRoot.h"

bool emptydbProperty_create( struct emptydbRoot *Root , uint8_t *Stream ) ;
bool emptydbProperty_delete( struct emptydbRoot *Root , uint8_t *Stream ) ;
void emptydbProperty_flush( struct emptydbRoot *Root , struct plibStdDataBST *PropertyEntryNode ) ;

emptydbCommonCountType emptydbProperty_lookup( struct emptydbRoot *Root , uint8_t *InputStream , uint8_t *OutputStream ) ;