/*
	plib::Data::Tube
*/
#include "plibDataTube.h"

void plibDataTube_initialize( struct plibDataTube *Tube , struct plibError *Error )
{
	// error
	if( Tube == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorParameter , plibDataTube_initialize ) ;
		return ;
	}
	
	Tube->EntryNode = plibCommonNullPointer ;
	Tube->Count = 0 ;
}

void plibDataTube_push( bool Direction , struct plibDataTube *Tube , struct plibDataNode *NewNode , struct plibError *Error )
{
	// error
	if( Tube == plibCommonNullPointer || NewNode == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorParameter , plibDataTube_push ) ;
		return ;
	}
	
	if( Tube->EntryNode == plibCommonNullPointer )
		plibData_linkNode( 2 , NewNode , NewNode ) ;
	else
	{
		if( Direction )
		{
			// Right : EntryNode ... EntryNode.Left-NewNode-EntryNode
			plibData_linkNode( 3 , Tube->EntryNode->Left , NewNode , Tube->EntryNode ) ;
		}
		else
		{
			// Left : EntryNode ... EntryNode-NewNode-EntryNode.Right
			plibData_linkNode( 3 , Tube->EntryNode , NewNode , Tube->EntryNode->Right ) ;
		}
	}
	Tube->EntryNode = NewNode ;
	Tube->Count ++ ;
}
struct plibDataNode* plibDataTube_pop( bool Direction , struct plibDataTube *Tube , struct plibError *Error )
{
	// error
	if( Tube == plibCommonNullPointer || Tube->EntryNode == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorParameter , plibDataTube_pop ) ;
		return plibCommonNullPointer ;
	}
	
	struct plibDataNode* OldNode = Tube->EntryNode ;
	
	if( Tube->Count == 1 )
		Tube->EntryNode = plibCommonNullPointer ;
	else
	{
		// OldNode.Left-OldNode.Right ... OldNode
		plibData_linkNode( 2 , OldNode->Left , OldNode->Right ) ;
		if( Direction )
		{
			// Right : OldNode.Left-EntryNode
			Tube->EntryNode = OldNode->Right ;
		}
		else
		{
			// Left : EntryNode-OldNode.Right
			Tube->EntryNode = OldNode->Left ;
		}
	}
	Tube->Count -- ;
	
	return OldNode ;
}

void plibDataTube_iterate( bool Direction , struct plibDataTube *Tube , plibDataTubeIterationFxType IterationFx , struct plibError *Error )
{
	// error
	if( Tube == plibCommonNullPointer || Tube->EntryNode == plibCommonNullPointer || IterationFx == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorParameter , plibDataTube_iterate ) ;
		return ;
	}
	
	struct plibDataNode *ThisNode = Tube->EntryNode ;
	plibCommonCountType Count = 0 ; 
	
	if( Direction )
	{
		do
		{
			IterationFx( Count , ThisNode ) ;
			ThisNode = ThisNode->Right ;
			Count ++ ;
		}
		while( ThisNode != Tube->EntryNode ) ;
	}
	else
	{
		do
		{
			IterationFx( Count , ThisNode ) ;
			ThisNode = ThisNode->Left ;
			Count ++ ;
		}
		while( ThisNode != Tube->EntryNode ) ;
	}
}
struct plibDataNode* plibDataTube_index( struct plibDataTube *Tube , plibCommonCountType Index , struct plibError *Error )
{
	// error
	if( Tube == plibCommonNullPointer || Tube->EntryNode == plibCommonNullPointer || Index >= Tube->Count )
	{
		plibError_report( Error , plibErrorParameter , plibDataTube_index ) ;
		return plibCommonNullPointer ;
	}
	
	struct plibDataNode *TempNode ;
	
	for( TempNode = Tube->EntryNode ; Index > 0 ; Index -- )
		TempNode = TempNode->Right ;
	
	return TempNode ;
}