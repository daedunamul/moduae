/*
	edbcmd
*/
#include "edbcmd.h"

void edbcmd_run(  )
{
	struct edbcmdStatus Status ;
	enum edbcmdCommand Command = edbcmdCommandNull ;
	char InputString[ edbcmdStringMaxLength ] ;
	int Temp1 , Temp2 ;
	edbKeyType TempKey ;
	struct plibDataHBST *TempNode ;
	
	edbcmd_initializeStatus( &Status ) ;
	
	// POSIX
	mkdir( edbcmdWorkingDirectory ) ;
	chdir( edbcmdWorkingDirectory ) ;
	
	while( Command != edbcmdCommandQuit )
	{
		printf( "Command>" ) ;
		scanf( "%s" , InputString ) ;
		Command = edbcmd_getCommand( InputString ) ;
		
		switch( Command )
		{
			case edbcmdCommandQuit : 
				edb_deleteDB( &Status.WorkingDB , &Status.Error ) ;
				continue ;
			
			case edbcmdCommandShowStatus : 
				printf
				( 
					"edbcmd>WorkingDB : %p\nWorkingObject : %p\nWorkingProperty : %p\n" , 
					Status.WorkingDB , Status.WorkingObject , Status.WorkingProperty
				) ;
				if( Status.WorkingDB != plibCommonNullPointer )
				{
					printf
					( 
						"ObjectMaxCount : %d\nObjectCount : %d\nPropertyMaxCount : %d\nPropertyCount : %d\n" , 
						Status.WorkingDB->ObjectMaxCount , Status.WorkingDB->ObjectCount , Status.WorkingDB->PropertyMaxCount , Status.WorkingDB->PropertyCount 
					) ;
				}
			break ;
			case edbcmdCommandShowNode : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				
				printf( "edbcmd>\n" ) ;
				plibDataHBST_traverse( Status.WorkingDB->ObjectRootNode , edbcmd_printNodeFx , plibCommonNullPointer , &Status.Error.InternalError ) ;
			break ;
			
			case edbcmdCommandCreateDB : 
				if( Status.WorkingDB != plibCommonNullPointer )
				{
					printf( "edbcmd>db is created.\n" ) ;
					continue ;
				}
				
				printf( "ObjectMaxCount PropertyMaxCount>\n" ) ;
				scanf( "%d%d" , &Temp1 , &Temp2 ) ;
				Status.WorkingDB = edb_createDB( ( plibCommonCountType )Temp1 , ( plibCommonCountType )Temp2 , &Status.Error ) ;
				if( Status.Error.Error == edbErrorNull )
					Status.WorkingObject = Status.WorkingDB->ObjectRootNode ;
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			case edbcmdCommandCreateObject : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingObject == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no woriking object.\n" ) ;
					continue ;
				}
				
				printf( "Key>" ) ;
				scanf( "%d" , &TempKey ) ;
				edb_createNode( Status.WorkingDB , Status.WorkingObject , false , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) ;
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			case edbcmdCommandCreateProperty : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingObject == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no working object.\n" ) ;
					continue ;
				}
				
				printf( "Key>\n" ) ;
				scanf( "%d" , &TempKey ) ;
				edb_createNode( Status.WorkingDB , Status.WorkingObject , true , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) ;
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			
			case edbcmdCommandDeleteDB : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>db is not created.\n" ) ;
					continue ;
				}
				
				edb_deleteDB( &Status.WorkingDB , &Status.Error ) ;
				edbcmd_initializeStatus( &Status ) ;
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			case edbcmdCommandDeleteObject : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingObject == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no working object.\n" ) ;
					continue ;
				}
				
				printf( "Key>" ) ;
				scanf( "%d" , &TempKey ) ;
				plibDataHBST_traverse( Status.WorkingObject , edbcmd_flushValueFileFx , plibCommonNullPointer , &Status.Error.InternalError ) ;
				edb_deleteNode( Status.WorkingDB , Status.WorkingObject , false , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) ;
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			case edbcmdCommandDeleteProperty : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingObject == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no working object.\n" ) ;
					continue ;
				}
				
				printf( "Key>" ) ;
				scanf( "%d" , &TempKey ) ;
				edbcmd_flushValueFileFx( edb_lookupNode( Status.WorkingDB , Status.WorkingObject , edbNodeProperty , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) , edbNodeProperty , plibCommonNullPointer , plibCommonNullPointer ) ;
				edb_deleteNode( Status.WorkingDB , Status.WorkingObject , true , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) ;
				Status.WorkingProperty = plibCommonNullPointer ;
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			
			case edbcmdCommandPointRoot : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				
				Status.WorkingObject = Status.WorkingDB->ObjectRootNode ;
				Status.WorkingProperty = plibCommonNullPointer ;
			break ;
			case edbcmdCommandPointSuper : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingObject == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no working object.\n" ) ;
					continue ;
				}
				
				if( Status.WorkingObject->Super == plibCommonNullPointer )
					printf( "edbcmd>there is no working object.\n" ) ;
				else
				{
					Status.WorkingObject = Status.WorkingObject->Super ;
					Status.WorkingProperty = plibCommonNullPointer ;
				}
			break ;
			case edbcmdCommandPointObject : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingObject == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no working object.\n" ) ;
					continue ;
				}
				
				printf( "Key>" ) ;
				scanf( "%d" , &TempKey ) ;
				TempNode = edb_lookupNode( Status.WorkingDB , Status.WorkingObject , false , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) ;
				
				if( TempNode == plibCommonNullPointer )
				{
					printf( "edbcmd>no object is founded.\n" ) ;
				}
				else
				{
					Status.WorkingObject = TempNode ;
					Status.WorkingProperty = plibCommonNullPointer ;
					
					printf( "edbcmd>an object you want is founded.\n" ) ;
					printf( "Key : %lu , SuperIndex : %u , SubCount : %u\n" , *( ( unsigned long* )Status.WorkingObject->Key ) , ( unsigned int )Status.WorkingObject->SuperIndex , ( unsigned int )Status.WorkingObject->Sub->Count ) ;
				}
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			case edbcmdCommandPointProperty : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingObject == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no working object.\n" ) ;
					continue ;
				}
				
				printf( "Key>" ) ;
				scanf( "%d" , &TempKey ) ;
				TempNode = edb_lookupNode( Status.WorkingDB , Status.WorkingObject , true , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) ;
				
				if( TempNode == plibCommonNullPointer )
				{
					printf( "edbcmd>no property is founded.\n" ) ;
				}
				else
				{
					Status.WorkingProperty = TempNode ;
					
					printf( "edbcmd>a property you want is founded.\n" ) ;
					printf( "Key : %lu , SuperIndex : %u\n" , *( ( unsigned long* )Status.WorkingProperty->Key ) , ( unsigned int )Status.WorkingProperty->SuperIndex ) ;
				}
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			
			case edbcmdCommandwriteValue : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingProperty == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no working property.\n" ) ;
					continue ;
				}
				
				edbcmd_writeValueFile( ( struct edbPropertyValue* )Status.WorkingProperty->Value ) ;
			break ;
			case edbcmdCommandreadValue : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no db.\n" ) ;
					continue ;
				}
				else if( Status.WorkingProperty == plibCommonNullPointer )
				{
					printf( "edbcmd>there is no working property.\n" ) ;
					continue ;
				}
				
				edbcmd_readValueFile( ( struct edbPropertyValue* )Status.WorkingProperty->Value ) ;
			break ;
			
			case edbcmdCommandLoadDB : 
				if( Status.WorkingDB != plibCommonNullPointer )
				{
					printf( "edbcmd>db is existed.\n" ) ;
					continue ;
				}
				
				printf( "DB Name>\n" ) ;
				scanf( "%s" , InputString ) ;
				Status.WorkingDB = edbcmd_readDB( InputString ) ;
				if( Status.WorkingDB != plibCommonNullPointer )
					Status.WorkingObject = Status.WorkingDB->ObjectRootNode ;
			break ;
			case edbcmdCommandSaveDB : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>db is not existed.\n" ) ;
					continue ;
				}
				
				printf( "DB Name>\n" ) ;
				scanf( "%s" , InputString ) ;
				edbcmd_writeDB( Status.WorkingDB , InputString ) ;
			break ;
			
			default : 
				printf( "edbcmd>unknown command.\n" ) ;
		}
	}
}

bool edbcmd_initializeStatus( struct edbcmdStatus *Status )
{
	if( Status == plibCommonNullPointer )
		return false ;
	
	edb_initializeError( &Status->Error ) ;
	Status->WorkingDB = plibCommonNullPointer ;
	Status->WorkingObject = plibCommonNullPointer ;
	Status->WorkingProperty = plibCommonNullPointer ;
	
	return true ;
}

enum edbcmdCommand edbcmd_getCommand( char *InputString )
{
	if( strcmp( InputString , "quit" ) == 0 )
		return edbcmdCommandQuit ;
		
	else if( strcmp( InputString , "showstatus" ) == 0 )
		return edbcmdCommandShowStatus ;
	else if( strcmp( InputString , "shownode" ) == 0 )
		return edbcmdCommandShowNode ;
	
	else if( strcmp( InputString , "createdb" ) == 0 )
		return edbcmdCommandCreateDB ;
	else if( strcmp( InputString , "createobject" ) == 0 )
		return edbcmdCommandCreateObject ;
	else if( strcmp( InputString , "createproperty" ) == 0 )
		return edbcmdCommandCreateProperty ;
	
	else if( strcmp( InputString , "deletedb" ) == 0 )
		return edbcmdCommandDeleteDB ;
	else if( strcmp( InputString , "deleteobject" ) == 0 )
		return edbcmdCommandDeleteObject ;
	else if( strcmp( InputString , "deleteproperty" ) == 0 )
		return edbcmdCommandDeleteProperty ;
		
	else if( strcmp( InputString , "pointroot" ) == 0 )
		return edbcmdCommandPointRoot ;
	else if( strcmp( InputString , "pointsuper" ) == 0 )
		return edbcmdCommandPointSuper ;
	else if( strcmp( InputString , "pointobject" ) == 0 )
		return edbcmdCommandPointObject ;
	else if( strcmp( InputString , "pointproperty" ) == 0 )
		return edbcmdCommandPointProperty ;
		
	else if( strcmp( InputString , "writevalue" ) == 0 )
		return edbcmdCommandwriteValue ;
	else if( strcmp( InputString , "readvalue" ) == 0 )
		return edbcmdCommandreadValue ;
		
	else if( strcmp( InputString , "load" ) == 0 )
		return edbcmdCommandLoadDB ;
	else if( strcmp( InputString , "save" ) == 0 )
		return edbcmdCommandSaveDB ;
		
	return edbcmdCommandNull ;
}

void edbcmd_printError( struct edbError *Error )
{
	if( Error->Error == edbErrorNull )
		return ;
	
	printf( "edbcmd>an error occured.\n" ) ;
	switch( Error->Error )
	{
		case edbErrorDBCreationParameter : 
			printf( "some parameters are wrong for creating a db.\n" ) ;
		break ;
		case edbErrorDBCreationAllocation :
			printf( "can't allocate a db.\n" ) ;
		break ; 
		case edbErrorDBCreationAllocationObjectNodePool : 
			printf( "can't allocate an object node pool for creating a db.\n" ) ;
		break ;
		case edbErrorDBCreationAllocationPropertyNodePool : 
			printf( "can't allocate a property node pool for creating a db.\n" ) ;
		break ;
		case edbErrorDBDeletionParameter : 
			printf( "some parameters are wrong for deleting a db.\n" ) ;
		break ;
		
		case edbErrorNodeCreationParameter : 
			printf( "some parameters are wrong for creating a node.\n" ) ;
		break ;
		case edbErrorNodeCreationAllocation : 
			printf( "can't allocate a node.\n" ) ;
		break ;
		case edbErrorNodeCreationPushing : 
			printf( "can't push a node for creating a node.\n" ) ;
		break ;
		case edbErrorNodeDeletionParameter : 
			printf( "some parameters are wrong for deleting a node.\n" ) ;
		break ;
		case edbErrorNodeDeletionDeallocation : 
			printf( "can't deallocate a node.\n" ) ;
		break ;
		case edbErrorNodeLookingupNothing : 
			printf( "can't found the node.\n" ) ;
		break ;
	
		default : 
			printf( "unknown error.\n" ) ;
	}
	
	edb_initializeError( Error ) ;
}
void edbcmd_printNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error )
{
	if( Index == edbNodeObject )
	{
		printf( "Object : \n{\n" ) ;
		printf( "\tKey : %lu\n" , *( ( unsigned long* )TraversedNode->Key ) ) ;
		if( TraversedNode->Super != plibCommonNullPointer )
		{
			printf( "\tSuperKey : %lu\n" , *( ( unsigned long* )TraversedNode->Super->Key ) ) ;
			printf( "\tSuperIndex : %u\n" , ( unsigned int )TraversedNode->SuperIndex ) ;
		}
		printf( "\tSubObjectCount : %u\n" , ( unsigned int )( ( ( struct plibDataHBSTSub *)TraversedNode->Sub )[ edbNodeObject ].Count ) ) ;
		printf( "\tSubPropertyCount : %u\n" , ( unsigned int )( ( ( struct plibDataHBSTSub *)TraversedNode->Sub )[ edbNodeProperty ].Count ) ) ;
	}
	else if( Index == edbNodeProperty )
	{
		printf( "Property : \n{\n" ) ;
		printf( "\tKey : %lu\n" , *( ( unsigned long* )TraversedNode->Key ) ) ;
		if( TraversedNode->Super != plibCommonNullPointer )
		{
			printf( "\tSuperKey : %lu\n" , *( ( unsigned long* )TraversedNode->Super->Key ) ) ;
			printf( "\tSuperIndex : %u\n" , ( unsigned int )TraversedNode->SuperIndex ) ;
		}
	}
	printf( "}\n" ) ;
}

void edbcmd_writeValueFile( struct edbPropertyValue *Value )
{
	char BufferString[ 256 ] ;
	FILE *ValueFile = fopen( Value->Name , "w" ) ;
	if( ValueFile == plibCommonNullPointer )
	{
		printf( "edbcmd>there are some problems to open a file.\n" ) ;
		return ;
	}
	
	printf( "Content>\n" ) ;
	scanf( "%s" , BufferString ) ;
	fputs( BufferString , ValueFile ) ;
	fclose( ValueFile ) ;
}
void edbcmd_readValueFile( struct edbPropertyValue *Value )
{
	char BufferString[ 256 ] ;
	FILE *ValueFile = fopen( Value->Name , "r" ) ;
	if( ValueFile == plibCommonNullPointer )
	{
		printf( "edbcmd>there is no value file.\n" ) ;
		return ;
	}
	
	printf( "Content>\n" ) ;
	fgets( BufferString , 256 , ValueFile ) ;
	printf( "%s\n" , BufferString ) ;
	fclose( ValueFile ) ;
}
void edbcmd_flushValueFileFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error )
{
	if( Index == edbNodeObject )
		return ;
	
	struct edbPropertyValue *Value = ( struct edbPropertyValue* )TraversedNode->Value ;
	remove( Value->Name ) ;
}

struct edbDB* edbcmd_readDB( char *DBNameString )
{
	if( DBNameString == plibCommonNullPointer )
	{
		printf( "edbcmd>db name is null.\n" ) ;
		return plibCommonNullPointer ;
	}
	
	struct edbcmdFileDB FileDB ;
	struct edbcmdFileNode FileNode ;
	
	struct edbDB *DB ;
	struct plibDataHBST *WorkingObject , *TempNode ;
	struct edbPropertyValue *TempValue ;
	
	FILE *File = fopen( DBNameString , "rb" ) ;
	if( File == plibCommonNullPointer )
	{
		printf( "edbcmd>there are some problems to read a db from a file.\n" ) ;
		return plibCommonNullPointer ;
	}
	
	// db
	fread( &FileDB , sizeof( struct edbcmdFileDB ) , 1 , File ) ;
	DB = edb_createDB( FileDB.ObjectMaxCount , FileDB.PropertyMaxCount , plibCommonNullPointer ) ;
	if( DB == plibCommonNullPointer )
		goto ErrorCreation ;
	WorkingObject = DB->ObjectRootNode ;
	
	// node
	Creation : 
		fread( &FileNode , sizeof( struct edbcmdFileNode ) , 1 , File ) ;
		if( feof( File ) )
			goto Termination ;
			
		// moving up if the super key is different
		while( FileNode.SuperKey != *( edbKeyType* )WorkingObject->Key )
			WorkingObject = WorkingObject->Super ;
		
		switch( FileNode.SuperIndex )
		{
			case edbNodeObject : 
				TempNode = edb_createNode( DB , WorkingObject , false , ( plibCommonAnyType* )( &FileNode.Key ) , plibCommonNullPointer ) ;
				if( TempNode == plibCommonNullPointer )
					goto ErrorCreation ;
				
				if( FileNode.SubFlag )
					WorkingObject = TempNode ;
			break ;
			case edbNodeProperty :
				TempNode = edb_createNode( DB , WorkingObject , true , ( plibCommonAnyType* )( &FileNode.Key ) , plibCommonNullPointer ) ;
				if( TempNode == plibCommonNullPointer )
					goto ErrorCreation ;
				TempValue = ( struct edbPropertyValue* )TempNode->Value ;
				
				// value
				fread( &TempValue->Type , sizeof( uint8_t ) , 1 , File ) ;
				fread( TempValue->Name , sizeof( char ) , edbValueNameLength , File ) ;
			break ;
		}
		goto Creation ;
	
	// ErrorCreation
	ErrorCreation : 
		if( DB != plibCommonNullPointer )
		{
			edb_deleteDB( &DB , plibCommonNullPointer ) ;
			DB = plibCommonNullPointer ;
		}
		printf( "edbcmd>there are some problems to read a db.\n" ) ;
		fclose( File ) ;
	
	// Termination
	Termination : 
		return DB ;
}
void edbcmd_writeDB( struct edbDB *DB , char *DBNameString )
{
	if( DB == plibCommonNullPointer )
	{
		printf( "edbcmd>db is null.\n" ) ;
		return ;
	}
	
	struct edbcmdFileDB FileDB ;
	
	FILE *File = fopen( DBNameString , "wb" ) ;
	if( File == plibCommonNullPointer )
	{
		printf( "edbcmd>there are some problems to write a db to a file.\n" ) ;
		return ;
	}
	
	// db
	FileDB.ObjectMaxCount = DB->ObjectMaxCount ;
	FileDB.PropertyMaxCount = DB->PropertyMaxCount ;
	FileDB.ObjectRootKey = *( edbKeyType* )DB->ObjectRootNode->Key ;
	fwrite( &FileDB , sizeof( struct edbcmdFileDB ) , 1 , File ) ;
	
	// node
	if( DB->ObjectRootNode->Sub != plibCommonNullPointer )
		plibDataHBST_traverse( DB->ObjectRootNode->Sub[ edbNodeObject ].RootNode , edbcmd_writeNodeFx , ( plibCommonAnyType* )File , plibCommonNullPointer ) ;
	
	fclose( File ) ;
	return ;
}
void edbcmd_writeNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error )
{
	FILE *File = ( FILE* )Data ;
	struct edbcmdFileNode FileNode ;
	struct edbPropertyValue *Value ;
	
	// node
	FileNode.SuperIndex = Index ;
	if( TraversedNode->Super == plibCommonNullPointer )
		FileNode.SuperKey = ( edbKeyType )0 ;
	else
		FileNode.SuperKey = *( edbKeyType* )TraversedNode->Super->Key ;
	FileNode.Key = *( edbKeyType* )TraversedNode->Key ;
	FileNode.SubFlag = TraversedNode->SubLength == 0 ? false : true ;
	fwrite( &FileNode , sizeof( struct edbcmdFileNode ) , 1 , File ) ;
	
	// value
	if( Index == edbNodeProperty )
	{
		Value = ( struct edbPropertyValue* )TraversedNode->Value ;
		fwrite( &Value->Type , sizeof( uint8_t ) , 1 , File ) ;
		fwrite( &Value->Name , sizeof( char ) , edbValueNameLength , File ) ;
	}
}