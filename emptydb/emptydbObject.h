/*
	emptydb::Object
*/
#pragma once
#include "emptydbProperty.h"

bool emptydbObject_createRootObject( struct emptydbRoot *Root , emptydbCommonKeyType Key ) ;
bool emptydbObject_deleteRootObject( struct emptydbRoot *Root ) ;

bool emptydbObject_createObject( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray ) ;
bool emptydbObject_deleteObject( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray ) ;
void emptydbObject_flushObject( struct emptydbRoot *Root , struct plibStdDataBST *ObjectEntryNode ) ;

bool emptydbObject_pointObject( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray ) ;
emptydbCommonCountType emptydbObject_lookupObject( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray , struct plibStdDataBST **ResultObjectArray ) ;