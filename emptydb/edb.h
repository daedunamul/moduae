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
	edbErrorNodeLookingupNothing , 
	
	edbErrorValueDefinitionParameter , 
	edbErrorValueDefinitionAllocation , 
	edbErrorValueUndefinitionParameter 
} ;
enum edbValueType
{
	edbValueTypeNull = 0 , 
	edbValueTypeByte , // unsigned 1 byte
	edbValueTypeInteger , // signed 4 byte
	edbValueTypeFloat , // signed 4 byte
	edbValueTypeFile // byte file stream
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
	enum edbValueType Type ;
	char Name[ edbValueNameLength ] ;
	plibCommonAnyType *Data ;
} ;

void edb_initializeError( struct edbError *Error ) ;
void edb_reportError( struct edbError *Error , enum edbErrorType ErrorConstant ) ;

struct edbDB* edb_createDB( plibCommonCountType ObjectMaxCount , plibCommonCountType PropertyMaxCount , struct edbError *Error ) ;
void edb_deleteDB( struct edbDB **DB , struct edbError *Error ) ; // need to free values

struct plibDataHBST* edb_createNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error ) ;
void edb_deleteNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error ) ;
void edb_flushNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error ) ;
struct plibDataHBST* edb_lookupNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error ) ;

void edb_defineValue( struct plibDataHBST *Property , enum edbValueType Type , struct edbError *Error ) ;
void edb_undefineValue( struct plibDataHBST *Property , struct edbError *Error ) ;
void edb_flushValueFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error ) ;