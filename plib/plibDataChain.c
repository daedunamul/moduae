/*
	plib::Data::Chain
*/
#include "plibDataChain.h"

void plibDataChain_push( bool Direction , struct plibDataChain **EntryNode , struct plibDataChain *NewNode , struct plibErrorType *Error )
{
	// error
	if( EntryNode == plibCommonNullPointer || NewNode == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibDataChain_push ) ;
		return ;
	}
	
	if( *EntryNode == plibCommonNullPointer )
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
struct plibDataChain* plibDataChain_pop( bool Direction , struct plibDataChain **EntryNode , struct plibErrorType *Error )
{
	// error
	if( EntryNode == plibCommonNullPointer || *EntryNode == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibDataChain_pop ) ;
		return plibCommonNullPointer ;
	}
	
	struct plibDataChain* OldNode ;
	
	if( ( *EntryNode )->Left == ( *EntryNode )->Right )
	{
		OldNode = *EntryNode ;
		*EntryNode = plibCommonNullPointer ;
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
struct plibDataChain* plibDataChain_lookup( bool Direction , plibCommonCountType Index , struct plibDataChain *ThisNode , struct plibErrorType *Error )
{
	// error
	if( ThisNode == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibDataChain_lookup ) ;
		return plibCommonNullPointer ;
	}
	
	plibCommonCountType Count ;
	
	if( ThisNode == plibCommonNullPointer )
		return plibCommonNullPointer ;
	else
	{
		if( Direction )
			for( Count = 0 ; Count < Index ; Count ++ , ThisNode = ThisNode->Right ) ;
		else
			for( Count = 0 ; Count < Index ; Count ++ , ThisNode = ThisNode->Left ) ;
	}
	
	return ThisNode ;
}