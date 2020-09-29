/*
	plib::Data::HBST
	Hierarchial Binary Search Tree
*/
#include "plibDataHBST.h"

bool plibDataHBST_push( struct plibDataHBST **EntryNode , struct plibDataHBST *NewNode , plibDataHBSTStatusFxType StatusFx )
{
	struct plibDataHBST *ThisNode = *EntryNode ;
	enum plibDataHBSTStatus Status ;

	if( ThisNode == plibCommonNullPointer )
		*EntryNode = NewNode ;
	else
	{
		do
		{
			Status = StatusFx( NewNode->Key , ThisNode->Key ) ;
			
			if( Status == plibDataHBSTStatusLess )
			{
				if( ThisNode->Left == plibCommonNullPointer )
				{
					ThisNode->Left = NewNode ;
					break ;
				}
				
				ThisNode = ThisNode->Left ;
			}
			else if( Status == plibDataHBSTStatusGreat )
			{
				if( ThisNode->Right == plibCommonNullPointer )
				{
					ThisNode->Right = NewNode ;
					break ;
				}
				
				ThisNode = ThisNode->Right ;
			}
			else
				return false ;
		}
		while( ThisNode != plibCommonNullPointer ) ;
	}
	
	return true ;
}
struct plibDataHBST* plibDataHBST_pop( struct plibDataHBST **EntryNode , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx )
{
	struct plibDataHBST *ThisNode = *EntryNode , *CandidateNode , *CandidateParent = plibCommonNullPointer , **ParentPointer = plibCommonNullPointer ;
	enum plibDataHBSTStatus Status ;
	
	while( ThisNode != plibCommonNullPointer )
	{
		Status = StatusFx( Key , ThisNode->Key ) ;
		
		if( Status == plibDataHBSTStatusLess )
		{
			ParentPointer = &( ThisNode->Left ) ;
			ThisNode = ThisNode->Left ;
		}
		else if( Status == plibDataHBSTStatusGreat )
		{
			ParentPointer = &( ThisNode->Right ) ;
			ThisNode = ThisNode->Right ;
		}
		else
		{
			if( ThisNode->Left != plibCommonNullPointer && ThisNode->Right != plibCommonNullPointer )
			{
				for
				( 
					CandidateNode = ThisNode->Right ; 
					CandidateNode->Left != plibCommonNullPointer ; 
					CandidateParent = CandidateNode , CandidateNode = CandidateNode->Left 
				) ;
				
				if( CandidateParent != plibCommonNullPointer )
					CandidateParent->Left = CandidateNode->Right ;
					
				CandidateNode->Left = ThisNode->Left ;
				if( ThisNode->Right != CandidateNode )
					CandidateNode->Right = ThisNode->Right ;
				
				if( ParentPointer == plibCommonNullPointer )
					*EntryNode = CandidateNode ;
				else
					*ParentPointer = CandidateNode ;
			}
			else
			{
				if( ParentPointer == plibCommonNullPointer )
					*EntryNode = ThisNode->Left != plibCommonNullPointer ? ThisNode->Left : ThisNode->Right ;
				else
					*ParentPointer = ThisNode->Left != plibCommonNullPointer ? ThisNode->Left : ThisNode->Right ;
			}
			
			break ;
		}
	}
	
	return ThisNode ;
}
struct plibDataHBST* plibDataHBST_lookup( struct plibDataHBST *ThisNode , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx )
{
	enum plibDataHBSTStatus Status ;
	
	while( ThisNode != plibCommonNullPointer )
	{
		Status = StatusFx( Key , ThisNode->Key ) ;
		
		if( Status == plibDataHBSTStatusLess )
			ThisNode = ThisNode->Left ;
		else if( Status == plibDataHBSTStatusGreat )
			ThisNode = ThisNode->Right ;
		else
			break ;
	}
	
	return ThisNode ;
}

bool plibDataHBST_pushSub( struct plibDataHBSTSub *Sub , plibCommonCountType Index , struct plibDataHBST *NewNode , plibDataHBSTStatusFxType StatusFx )
{
	if( Sub == plibCommonNullPointer || Index >= Sub->Length )
		return false ;

	if( plibDataHBST_push( &Sub->RootNodeArray[ Index ] , NewNode , StatusFx ) == false )
		return false ;
	
	Sub->Count ++ ;
	return true ;
}
struct plibDataHBST* plibDataHBST_popSub( struct plibDataHBSTSub *Sub , plibCommonCountType Index , plibCommonAnyType *Key , plibDataHBSTStatusFxType StatusFx )
{
	if( Sub == plibCommonNullPointer || Index >= Sub->Length )
		return plibCommonNullPointer ;
	
	struct plibDataHBST *Node = plibDataHBST_pop( &Sub->RootNodeArray[ Index ] , Key , StatusFx ) ;
	
	if( Node != plibCommonNullPointer )
		Sub->Count -- ;
	return Node ;
}

void plibDataHBST_traverse( struct plibDataHBST *EntryNode , plibDataHBSTTraversedNodeFxType TraversedNodeFx )
{
	if( EntryNode == plibCommonNullPointer )
		return ;
	
	plibCommonCountType Index ;
	
	if( EntryNode->Sub != plibCommonNullPointer )
		for( Index = 0 ; Index < EntryNode->Sub->Length ; Index ++ )
			plibDataHBST_traverse( EntryNode->Sub->RootNodeArray[ Index ] , TraversedNodeFx ) ;
	plibDataHBST_traverse( EntryNode->Left , TraversedNodeFx ) ;
	plibDataHBST_traverse( EntryNode->Right , TraversedNodeFx ) ;
	
	if( TraversedNodeFx != plibCommonNullPointer )
		TraversedNodeFx( EntryNode ) ;
}