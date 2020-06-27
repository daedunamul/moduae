/*
	plib::Std::Data::Chain
*/
#include "plibStdDataChain.h"

void plibStdDataChain_push( bool Direction , struct plibStdDataChain **EntryNode , struct plibStdDataChain *NewNode )
{
	if( *EntryNode == plibStdData_Pointer_Null )
	{
		NewNode->Left = NewNode ;
		NewNode->Right = NewNode ;
		*EntryNode = NewNode ;
	}
	else
	{
		if( Direction )
		{
			// Right
			NewNode->Left = *EntryNode ;
			NewNode->Right = ( *EntryNode )->Right ;
		
			( *EntryNode )->Right->Left = NewNode ;
			( *EntryNode )->Right = NewNode ;
		}
		else
		{
			// Left
			NewNode->Left = ( *EntryNode )->Left ;
			NewNode->Right = *EntryNode ;
		
			( *EntryNode )->Left->Right = NewNode ;
			( *EntryNode )->Left = NewNode ;
		}
	}
}
struct plibStdDataChain* plibStdDataChain_pop( bool Direction , struct plibStdDataChain **EntryNode )
{
	struct plibStdDataChain* OldNode ;
	
	if( *EntryNode == plibStdData_Pointer_Null )
		return plibStdData_Pointer_Null ;
	else if( ( *EntryNode )->Left == ( *EntryNode )->Right )
	{
		OldNode = *EntryNode ;
		*EntryNode = plibStdData_Pointer_Null ;
	}
	else
	{
		if( Direction )
			// Right
			OldNode = ( *EntryNode )->Right ;
		else
			// Left
			OldNode = ( *EntryNode )->Left ;
		OldNode->Left->Right = OldNode->Right ;
		OldNode->Right->Left = OldNode->Left ;
	}
	
	return OldNode ;
}
struct plibStdDataChain* plibStdDataChain_lookup( bool Direction , unsigned int Index , struct plibStdDataChain *ThisNode )
{
	unsigned int Count ;
	
	if( ThisNode == plibStdData_Pointer_Null )
		return plibStdData_Pointer_Null ;
	else
	{
		if( Direction )
			for( Count = 0 ; Count < Index ; Count ++ , ThisNode = ThisNode->Right ) ;
		else
			for( Count = 0 ; Count < Index ; Count ++ , ThisNode = ThisNode->Left ) ;
	}
	
	return ThisNode ;
}
