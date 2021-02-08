/*
	edbcmd
*/
#pragma once
#include "../edb.h"
#include <string.h>
#include <unistd.h>

#define edbcmdStringMaxLength 32
#define edbcmdWorkingDirectory "edbcmd"

enum edbcmdCommand
{
	edbcmdCommandNull = 0 , 
	edbcmdCommandQuit , 
	
	edbcmdCommandShowStatus , 
	edbcmdCommandShowNode , 
	
	edbcmdCommandCreateDB , 
	edbcmdCommandCreateObject , 
	edbcmdCommandCreateProperty , 
	
	edbcmdCommandDeleteDB , 
	edbcmdCommandDeleteObject , 
	edbcmdCommandDeleteProperty , 
	
	edbcmdCommandPointRoot , 
	edbcmdCommandPointSuper , 
	edbcmdCommandPointObject , 
	edbcmdCommandPointProperty , 
	
	edbcmdCommandwriteValue , 
	edbcmdCommandreadValue , 
	
	edbcmdCommandLoadDB , 
	edbcmdCommandSaveDB 
} ;

struct edbcmdStatus
{
	struct edbError Error ;
	struct edbDB *WorkingDB ;
	struct plibDataHBST *WorkingObject , *WorkingProperty ;
} ;

struct edbcmdFileDB
{
	plibCommonCountType ObjectMaxCount , PropertyMaxCount ;
	edbKeyType ObjectRootKey ;
} ;
struct edbcmdFileNode
{
	plibCommonCountType SuperIndex ;
	edbKeyType SuperKey , Key ;
	bool SubFlag ;
} ;

void edbcmd_run(  ) ;

bool edbcmd_initializeStatus( struct edbcmdStatus *Status ) ;

enum edbcmdCommand edbcmd_getCommand( char *InputString ) ;

void edbcmd_printError( struct edbError *Error ) ;
void edbcmd_printNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error ) ;

void edbcmd_writeValueFile( struct edbPropertyValue *Value ) ;
void edbcmd_readValueFile( struct edbPropertyValue *Value ) ;
void edbcmd_flushValueFileFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error ) ;

struct edbDB* edbcmd_readDB( char *DBNameString ) ;
void edbcmd_writeDB( struct edbDB *DB , char *DBNameString ) ;
void edbcmd_writeNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error ) ;