/*
	edb
	emptydb
*/
#pragma once
#include "edbKey.h"
#include <time.h>
#include <stdio.h>

#define edbValueNameLength 20

enum
{
	edbNodeObject = 0 , 
	edbNodeProperty 
} ;

enum edbErrorType
{
	edbErrorNull = 0 , 
	
	edbErrorDBCreationParameter , 
	edbErrorDBCreationAllocation , 
	edbErrorDBCreationAllocationObjectNodePool , 
	edbErrorDBCreationAllocationPropertyNodePool , 
	edbErrorDBDeletionParameter , 
	
	edbErrorNodeCreationParameter , 
	edbErrorNodeCreationAllocation , 
	edbErrorNodeCreationPushing , 
	edbErrorNodeDeletionParameter , 
	edbErrorNodeDeletionDeallocation , 
	edbErrorNodeLookingupNothing 
} ;

struct edbError
{
	enum edbErrorType Error ;
	struct plibErrorType InternalError ;
} ;
struct edbDB
{
	plibCommonCountType ObjectMaxCount , ObjectCount , PropertyMaxCount , PropertyCount ;
	struct plibMemoryPool *ObjectNodePool , *PropertyNodePool ;
	struct plibDataHBST *ObjectRootNode ;
} ;
struct edbPropertyValue
{
	uint8_t Type ;
	char Name[ edbValueNameLength ] ;
	plibCommonAnyType *Data ;
} ;

void edb_initializeError( struct edbError *Error ) ;
void edb_reportError( struct edbError *Error , enum edbErrorType ErrorConstant ) ;

struct edbDB* edb_createDB( plibCommonCountType ObjectMaxCount , plibCommonCountType PropertyMaxCount , struct edbError *Error ) ;
void edb_deleteDB( struct edbDB **DB , struct edbError *Error ) ;

struct plibDataHBST* edb_createNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error ) ;
void edb_deleteNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error ) ;
void edb_flushNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error ) ;
struct plibDataHBST* edb_lookupNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error ) ;