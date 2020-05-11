/*
	plib::Std::Data::Chain
*/
#include "plibStdDataChain.h"

void plibStdDataChain_push( bool Direction , struct plibStdDataChain **EntryNode , struct plibStdDataChain *NewNode )
{
	if( *EntryNode == NullPointer )
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
	
	if( *EntryNode == NullPointer )
		return NullPointer ;
	else if( ( *EntryNode )->Left == ( *EntryNode )->Right )
	{
		OldNode = *EntryNode ;
		*EntryNode = NullPointer ;
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
struct plibStdDataChain* plibStdDataChain_lookup( bool Direction , unsigned int Index , struct plibStdDataChain *EntryNode )
{
	unsigned int Count ;
	
	if( EntryNode == NullPointer )
		return NullPointer ;
	else
	{
		if( Direction )
			for( Count = 0 ; Count < Index ; Count ++ , EntryNode = EntryNode->Right ) ;
		else
			for( Count = 0 ; Count < Index ; Count ++ , EntryNode = EntryNode->Left ) ;
	}
	
	return EntryNode ;
}
