/*
	plib::Data::Tube
*/
#include "plibDataTube.h"

void plibDataTube_push( bool Direction , struct plibDataTube **EntryNode , struct plibDataTube *NewNode , struct plibErrorType *Error )
{
	// error
	if( EntryNode == plibCommonNullPointer || NewNode == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibDataTube_push ) ;
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
			// Right : EntryNode ... EntryNode.Left-NewNode-EntryNode
			NewNode->Left = ( *EntryNode )->Left ;
			NewNode->Right = *EntryNode ;
			
			( *EntryNode )->Left = NewNode ;
		}
		else
		{
			// Left : EntryNode ... EntryNode-NewNode-EntryNode.Right
			NewNode->Left = *EntryNode ;
			NewNode->Right = ( *EntryNode )->Right ;
		
			( *EntryNode )->Right = NewNode ;
		}
	}
}
struct plibDataTube* plibDataTube_pop( bool Direction , struct plibDataTube **EntryNode , struct plibErrorType *Error )
{
	// error
	if( EntryNode == plibCommonNullPointer || *EntryNode == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibDataTube_pop ) ;
		return plibCommonNullPointer ;
	}
	
	struct plibDataTube* OldNode ;
	
	if( ( *EntryNode )->Left == ( *EntryNode )->Right )
	{
		OldNode = *EntryNode ;
		*EntryNode = plibCommonNullPointer ;
	}
	else
	{
		OldNode = *EntryNode ;
		
		if( Direction )
		{
			// Right : OldNode.Left-OldNode-OldNode.Right ... OldNode.Left-EntryNode
			( *EntryNode )->Right->Left = ( *EntryNode )->Left ;
			*EntryNode = ( *EntryNode )->Right ;
			if( *EntryNode == ( *EntryNode )->Left )
				( *EntryNode )->Right = *EntryNode ;
		}
		else
		{
			// Left : OldNode.Left-OldNode-OldNode.Right ... EntryNode-OldNode.Right
			( *EntryNode )->Left->Right = ( *EntryNode )->Right ;
			*EntryNode = ( *EntryNode )->Left ;
			if( *EntryNode == ( *EntryNode )->Right )
				( *EntryNode )->Left = *EntryNode ;
		}
	}
	
	return OldNode ;
}

void plibDataTube_iterate( bool Direction , struct plibDataTube *EntryNode , plibDataTubeIterationFxType IterationFx , struct plibErrorType *Error )
{
	// error
	if( EntryNode == plibCommonNullPointer || IterationFx == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibDataTube_iterate ) ;
		return plibCommonNullPointer ;
	}
	
	struct plibDataTube *ThisNode = EntryNode ;
	plibCommonCountType Count = 0 ; 
	
	if( Direction )
	{
		do
		{
			IterationFx( Count , ThisNode ) ;
			ThisNode = ThisNode->Right ;
			Count ++ ;
		}
		while( ThisNode != EntryNode ) ;
	}
	else
	{
		do
		{
			IterationFx( Count , ThisNode ) ;
			ThisNode = ThisNode->Left ;
			Count ++ ;
		}
		while( ThisNode != EntryNode ) ;
	}
}