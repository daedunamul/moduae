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
	struct edbPropertyValue *TempValue ;
	
	edbcmd_initializeStatus( &Status ) ;
	
	setlocale( LC_ALL , "ko_KR.utf8" ) ;
	
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
				
				printf( "Key Type>\n" ) ;
				scanf( "%d%s" , &TempKey , InputString ) ;
				chdir( edbcmdDirectoryValue ) ;
				edb_defineValue( edb_createNode( Status.WorkingDB , Status.WorkingObject , true , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) , edbcmd_getValueType( InputString ) , &Status.Error ) ;
				chdir( ".." ) ;
				
				edbcmd_printError( &Status.Error ) ;
			break ;
			
			case edbcmdCommandDeleteDB : 
				if( Status.WorkingDB == plibCommonNullPointer )
				{
					printf( "edbcmd>db is not created.\n" ) ;
					continue ;
				}
				
				edb_deleteDB( &Status.WorkingDB , &Status.Error ) ;
				
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
				chdir( edbcmdDirectoryValue ) ;
				edb_deleteNode( Status.WorkingDB , Status.WorkingObject , true , ( plibCommonAnyType* )( &TempKey ) , &Status.Error ) ;
				chdir( ".." ) ;
				
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
				
				TempValue = ( struct edbPropertyValue* )Status.WorkingProperty->Value ;
				switch( TempValue->Type )
				{
					case edbValueTypeByte : 
						printf( "Byte>" ) ;
						scanf( "%u" , ( unsigned int* )TempValue->Data ) ;
					break ;
					case edbValueTypeInteger : 
						printf( "Integer>" ) ;
						scanf( "%d" , ( int32_t* )TempValue->Data ) ;
					break ;
					case edbValueTypeFloat : 
						printf( "Float>" ) ;
						scanf( "%f" , ( float* )TempValue->Data ) ;
					break ;
					case edbValueTypeFile : 
						edbcmd_writeValueFile( ( FILE* )TempValue->Data ) ;
					break ;
					
					case edbValueTypeNull : 
					default : 
						printf( "edbcmd>unknown type.\n" ) ;
				}
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
				
				TempValue = ( struct edbPropertyValue* )Status.WorkingProperty->Value ;
				switch( TempValue->Type )
				{
					case edbValueTypeByte : 
						printf( "edbcmd> Byte : %u\n" , *( unsigned int* )TempValue->Data ) ;
					break ;
					case edbValueTypeInteger : 
						printf( "edbcmd> Integer : %d\n" , *( int32_t* )TempValue->Data ) ;
					break ;
					case edbValueTypeFloat : 
						printf( "edbcmd> Float : %f\n" , *( float* )TempValue->Data ) ;
					break ;
					case edbValueTypeFile : 
						edbcmd_readValueFile( ( FILE* )TempValue->Data ) ;
					break ;
					
					case edbValueTypeNull : 
					default : 
						printf( "edbcmd>unknown type.\n" ) ;
				}
			break ;
			
			case edbcmdCommandLoadDB : 
				
			break ;
			case edbcmdCommandSaveDB : 
				
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
	
	// POSIX
	mkdir( edbcmdDirectoryValue ) ;
	
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
		
	return edbcmdCommandNull ;
}
enum edbValueType edbcmd_getValueType( char *InputString )
{
	if( strcmp( InputString , "byte" ) == 0 )
		return edbValueTypeByte ;
	else if( strcmp( InputString , "integer" ) == 0 )
		return edbValueTypeInteger ; 
	else if( strcmp( InputString , "float" ) == 0 )
		return edbValueTypeFloat ; 
	else if( strcmp( InputString , "file" ) == 0 )
		return edbValueTypeFile ;
	
	return edbValueTypeNull ;
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
		
		case edbErrorValueDefinitionParameter : 
			printf( "some parameters are wrong for defining a value.\n" ) ;
		break ;
		case edbErrorValueDefinitionAllocation : 
			printf( "can't allocate a value for defining a value.\n" ) ;
		break ;
		case edbErrorValueUndefinitionParameter : 
			printf( "some parameters are wrong for undefining a value.\n" ) ;
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

void edbcmd_writeValueFile( FILE *ValueFile )
{
	wchar_t BufferString[ 256 ] ;
	
	printf( "File>\n" ) ;
	wscanf( L"%s" , BufferString ) ;
	rewind( ValueFile ) ;
	fputws( BufferString , ValueFile ) ;
	fflush( ValueFile ) ;
}
void edbcmd_readValueFile( FILE *ValueFile )
{
	wchar_t BufferString[ 256 ] ;
	
	printf( "File>\n" ) ;
	rewind( ValueFile ) ;
	fgetws( BufferString , 256 , ValueFile ) ;
	wprintf( L"%s\n" , BufferString ) ;
}