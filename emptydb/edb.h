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

enum edbError
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

struct edbStatus
{
	enum edbError Error ;
	struct plibError InternalError ;
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

void edb_initializeStatus( struct edbStatus *Status ) ;
void edb_reportStatus( struct edbStatus *Status , enum edbError ErrorConstant ) ;

struct edbDB* edb_createDB( plibCommonCountType ObjectMaxCount , plibCommonCountType PropertyMaxCount , struct edbStatus *Status ) ;
void edb_deleteDB( struct edbDB **DB , struct edbStatus *Status ) ;

struct plibDataHBST* edb_createNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbStatus *Status ) ;
void edb_deleteNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbStatus *Status ) ;
void edb_flushNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibError *Status ) ;
struct plibDataHBST* edb_lookupNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbStatus *Status ) ;