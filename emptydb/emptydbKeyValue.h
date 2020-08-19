/*
	emptydb::KeyValue
*/
#pragma once
#include "emptydbRoot.h"

bool emptydbKeyValue_createKeyValue( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray , size_t DataSize , size_t DataLength ) ;
bool emptydbKeyValue_deleteKeyValue( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray ) ;
void emptydbKeyValue_flushKeyValue( struct emptydbRoot *Root , struct plibStdDataBST *ObjectRootNode ) ;

size_t emptydbKeyValue_lookupKeyValue( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray , struct plibStdDataBST **ResultKeyValueArray ) ;
