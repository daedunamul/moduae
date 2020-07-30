/*
	pdb
*/
#pragma once
#include "../plib/plibStdFormatName64.h"
#include "../plib/plibStdDataBST.h"
#include "../plib/plibStdMemoryPool.h"
#include "pdbHash.h"
#include <stdlib.h>

typedef uint32_t pdbKeyType ;

enum pdbType { pdbTypeObject , pdbTypeKeyValue , pdbTypeValueBoolean , pdbTypeValueInterger , pdbTypeValueFloat , pdbTypeValueString } ;

struct pdbObjectValue
{
	struct plibStdDataBST *MemberObjectRootNode , *MemberKeyValueRootNode ;
} ;

struct pdbDB
{
	size_t QueryKeyMaxCount , QueryKeyCount , QueryResultCount ;
	pdbKeyType *QueryKeyStack ;
	struct plibStdDataBST **QueryResultStack ;
	
	size_t ObjectMaxCount , ObjectCount , KeyValueMaxCount , KeyValueCount ;
	struct plibStdDataBST *ObjectRootNode , *ObjectThisNode ;
	struct plibStdMemoryPool *ObjectNodePool , *KeyValueNodePool ;
} ;

// Query # all processes based on batch job with two stack
struct pdbDB* pdbQuery_createDB( size_t QueryKeyMaxCount , size_t ObjectMaxCount , size_t KeyValueMaxCount ) ;
bool pdbQuery_deleteDB( struct pdbDB **DB ) ;

bool pdbQuery_pushStack( struct pdbDB *DB , pdbKeyType Key ) ;
void pdbQuery_flushStack( struct pdbDB *DB ) ;

bool pdbQuery_pointObject( struct pdbDB *DB ) ;
void pdbQuery_lookupObject( struct pdbDB *DB ) ;
void pdbQuery_createObject( struct pdbDB *DB ) ;
void pdbQuery_deleteObject( struct pdbDB *DB ) ;

void pdbQuery_lookupKeyValue( struct pdbDB *DB ) ;
void pdbQuery_createKeyValue( struct pdbDB *DB , uint8_t Type ) ;
void pdbQuery_deleteKeyValue( struct pdbDB *DB ) ;

enum plibStdDataBSTStatus pdbQuery_compareKey( uint8_t *Key1 , uint8_t *Key2 ) ;
