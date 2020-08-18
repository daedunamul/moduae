/*
	emptydb::Object
*/
#pragma once
#include "emptydbKeyValue.h"

bool emptydbObject_createRootObject( struct emptydbRoot *Root , emptydbCommonKeyType Key ) ;
bool emptydbObject_deleteRootObject( struct emptydbRoot *Root ) ;

bool emptydbObject_createObject( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray ) ;
bool emptydbObject_deleteObject( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray ) ;
void emptydbObject_flushObject( struct emptydbRoot *Root , struct plibStdDataBST *ObjectEntryNode ) ;

bool emptydbObject_pointObject( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray ) ;
size_t emptydbObject_lookupObject( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray , struct plibStdDataBST **ResultObjectArray ) ;
