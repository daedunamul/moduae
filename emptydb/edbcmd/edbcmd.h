/*
	edbcmd
*/
#pragma once
#include "../edb.h"
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>

#define edbcmdStringMaxLength 32
#define edbcmdDirectoryValue "edbValue"

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
	
	edbcmdCommandLoadDB , //
	edbcmdCommandSaveDB //
} ;

struct edbcmdStatus
{
	struct edbError Error ;
	struct edbDB *WorkingDB ;
	struct plibDataHBST *WorkingObject , *WorkingProperty ;
} ;

void edbcmd_run(  ) ;

bool edbcmd_initializeStatus( struct edbcmdStatus *Status ) ;

enum edbcmdCommand edbcmd_getCommand( char *InputString ) ;
enum edbValueType edbcmd_getValueType( char *InputString ) ;

void edbcmd_printError( struct edbError *Error ) ;
void edbcmd_printNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error ) ;

void edbcmd_writeValueFile( FILE *ValueFile ) ;
void edbcmd_readValueFile( FILE *ValueFile ) ;