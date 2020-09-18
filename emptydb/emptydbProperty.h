/*
	emptydb::Property
*/
#pragma once
#include "emptydbRoot.h"

bool emptydbProperty_create( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray , emptydbCommonCountType DataSize , emptydbCommonCountType DataLength ) ;
bool emptydbProperty_delete( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray ) ;
void emptydbProperty_flush( struct em32ptydbRoot *Root , struct plibStdDataBST *KeyValueEntryNode ) ;

emptydbCommonCountType emptydbKeyValue_lookupKeyValue( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray , struct plibStdDataBST **ResultKeyValueArray ) ;