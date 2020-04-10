/*
	plib::Std::Data::Chain
*/
#include "plibStdDataChain.h"

void plibStdDataChain_push( bool Direction , struct plibStdDataChain **TopNode , struct plibStdDataChain *NewNode )
{
	if( *TopNode == NullPointer )
	{
		NewNode->Left = NewNode ;
		NewNode->Right = NewNode ;
		*TopNode = NewNode ;
	}
	else
	{
		if( Direction )
		{
			// Right
			NewNode->Left = *TopNode ;
			NewNode->Right = ( *TopNode )->Right ;
		
			( *TopNode )->Right->Left = NewNode ;
			( *TopNode )->Right = NewNode ;
		}
		else
		{
			// Left
			NewNode->Left = ( *TopNode )->Left ;
			NewNode->Right = *TopNode ;
		
			( *TopNode )->Left->Right = NewNode ;
			( *TopNode )->Left = NewNode ;
		}
	}
}
struct plibStdDataChain* plibStdDataChain_pop( bool Direction , struct plibStdDataChain **TopNode )
{
	struct plibStdDataChain* OldNode ;
	
	if( *TopNode == NullPointer )
		return NullPointer ;
	else if( ( *TopNode )->Left == ( *TopNode )->Right )
	{
		OldNode = *TopNode ;
		*TopNode = NullPointer ;
	}
	else
	{
		if( Direction )
			// Right
			OldNode = ( *TopNode )->Right ;
		else
			// Left
			OldNode = ( *TopNode )->Left ;
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
