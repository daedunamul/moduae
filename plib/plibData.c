/*
	plib::Data
*/
#include "plibData.h"

// node
void plibData_linkNode( plibCommonCountType Count , ... )
{
	va_list ArgumentPointer ;
	struct plibDataNode *PreNode , *ThisNode ;
	plibCommonCountType Index ;
	
	va_start( ArgumentPointer , Count ) ;
	for( Index = 0 , PreNode = plibCommonNullPointer ; Index < Count ; Index ++ )
	{
		ThisNode = va_arg( ArgumentPointer , struct plibDataNode* ) ;
		ThisNode->Left = PreNode ;
		
		if( PreNode != plibCommonNullPointer )
			PreNode->Right = ThisNode ;
		PreNode = ThisNode ;
	}
	va_end( ArgumentPointer ) ;
}
void plibData_swapNode( struct plibDataNode *Node1 , struct plibDataNode *Node2 )
{
	struct plibDataNode *TempLeftNode = Node1->Left , *TempRightNode = Node1->Right ;
	
	Node1->Left = Node2->Left ;
	Node1->Right = Node2->Right ;
	Node2->Left = TempLeftNode ;
	Node2->Right = TempRightNode ;
}

// key
void plibData_initializeKey( plibDataKeyType Key )
{
	plibCommonCountType Count ;
	
	for( Count = 0 ; Count < plibDataKeyLength ; Count ++ )
		Key[ Count ] = 0 ;
}
enum plibDataKeyComparison plibData_compareKey( plibDataKeyType Key1 , plibDataKeyType Key2 )
{
	plibCommonCountType Count , Length = plibData_getKeyLength( Key1[ 0 ] ) ;
	
	for( Count = 0 ; Count < Length ; Count ++ )
	{
		// Key[ 0 ] == length of a key
		if( Key1[ Count ] > Key2[ Count ] )
			return plibDataKeyComparisonGreat ; 
		else if( Key1[ Count ] < Key2[ Count ] )
			return plibDataKeyComparisonLess ;
	}
	
	return plibDataKeyComparisonEqual ;
}
void plibData_getKeyFromString( plibDataKeyType Key , char *String )
{
	plibCommonCountType Count = 0 ;
	plibCommonCountType Index ;
	
	plibData_initializeKey( Key ) ;
	while( Count < plibDataKeyStringLength && String[ Count ] != '\0' )
	{
		Index = 1 + Count / 8 ;
		Key[ Index ] = ( Key[ Index ] << ( 8 * Count % 8 ) ) + String[ Count ] ;
		Count ++ ;
	}
	Key[ 0 ] = Count ;
}