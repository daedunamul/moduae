/*
	emptydb::File
*/
#include "emptydbFile.h"

bool emptydbFile_write( struct emptydbDB *DB , char *FileName )
{
	if( DB == plibCommonNullPointer )
		return false ;
	
	struct emptydbFileHeader Header ;
	
	FILE *File = fopen( FileName , "wb" ) ;
	if( File == plibCommonNullPointer )
		return false ;
	
	// db header
	Header.ObjectMaxCount = DB->ObjectMaxCount ;
	Header.PropertyMaxCount = DB->PropertyMaxCount ;
	Header.ObjectRootNodeKey = *( emptydbCommonKeyType* )DB->ObjectRootNode->Key ;
	fwrite( &Header , sizeof( struct emptydbFileHeader ) , 1 , File ) ;
	
	// node
	plibDataHBST_traverse( DB->ObjectRootNode , emptydbFile_writeNode , ( plibCommonAnyType* )File ) ;
	
	fclose( File ) ;
	return true ;
}
void emptydbFile_writeNode( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data )
{
	struct emptydbFileNode Node ;
	struct emptydbFileValue Value ;
	
	struct emptydbDBPropertyValueType *PropertyValue ;
	
	FILE *File = ( FILE* )Data ;
	
	// node
	Node.SuperIndex = Index ;
	if( TraversedNode->Super == plibCommonNullPointer )
		Node.SuperKey = 0 ;
	else
		Node.SuperKey = *( emptydbCommonKeyType* )TraversedNode->Super->Key ;
	Node.Key = *( emptydbCommonKeyType* )TraversedNode->Key ;
	Node.SubFlag = TraversedNode->SubLength == 0 ? false : true ;
	fwrite( &Node , sizeof( struct emptydbFileNode ) , 1 , File ) ;
	
	// value
	if( Index == emptydbPropertySubIndex )
	{
		PropertyValue = ( struct emptydbDBPropertyValueType* )TraversedNode->Value ;
		Value.Type = PropertyValue->Type ;
		Value.Size = PropertyValue->Size ;
		Value.Length = PropertyValue->Length ;
		//// data
		fwrite( &Value , sizeof( struct emptydbFileValue ) , 1 , File ) ;
	}
}

struct emptydbDB* emptydbFile_read( char *FileName )
{
	struct emptydbDB *DB ;
	struct plibDataHBST *TempNode ;
	struct emptydbDBPropertyValueType *PropertyValue ;
	struct emptydbStream *InputStream = emptydbStream_create( 1 , sizeof( emptydbCommonKeyType ) ) ;
	
	struct emptydbFileHeader Header ;
	struct emptydbFileNode Node ;
	struct emptydbFileValue Value ;
	
	FILE *File = fopen( FileName , "rb" ) ;
	if( File == plibCommonNullPointer )
		return plibCommonNullPointer ;
		
	// creating a db through reading db header
	fread( &Header , sizeof( struct emptydbFileHeader ) , 1 , File ) ;
	DB = emptydbDB_create( Header.ObjectMaxCount , Header.PropertyMaxCount ) ;
	
	// creating root object
	fread( &Node , sizeof( struct emptydbFileNode ) , 1 , File ) ;
	emptydbObject_createRoot( DB , Node.Key ) ;
	DB->ObjectThisNode = DB->ObjectRootNode ;
	
	// creating
	while( true )
	{
		// reading node
		fread( &Node , sizeof( struct emptydbFileNode ) , 1 , File ) ;
		if( feof( File ) )
			break ;
		
		emptydbStream_setKey( InputStream , Node.Key ) ;
		switch( Node.SuperIndex )
		{
			case emptydbObjectSubIndex : 
				// setting this node
				while( Node.SuperKey != *( emptydbCommonKeyType* )DB->ObjectThisNode->Key )
					DB->ObjectThisNode = DB->ObjectThisNode->Super ;
				
				// creating object
				TempNode = emptydbObject_create( DB , InputStream ) ;
				if( Node.SubFlag )
					DB->ObjectThisNode = TempNode ;
			break ;
			case emptydbPropertySubIndex : 
				// setting this node
				while( Node.SuperKey != *( emptydbCommonKeyType* )DB->ObjectThisNode->Key )
					DB->ObjectThisNode = DB->ObjectThisNode->Super ;
				
				// creating property
				TempNode = emptydbProperty_create( DB , InputStream ) ;
				PropertyValue = ( struct emptydbDBPropertyValueType* )TempNode->Value ;
				
				// reading value
				fread( &Value , sizeof( struct emptydbFileValue ) , 1 , File ) ;
				PropertyValue->Type = Value.Type ;
				PropertyValue->Size = Value.Size ;
				PropertyValue->Length = Value.Length ;
			break ;
		}
		emptydbStream_reset( InputStream ) ;
	}
	DB->ObjectThisNode = plibCommonNullPointer ;
	
	emptydbStream_delete( &InputStream ) ;
	fclose( File ) ;
	return DB ;
}