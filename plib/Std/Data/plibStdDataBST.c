/*
	plib::Std::Data::BST
*/
#include "plibStdDataBST.h"

bool
plibStdDataBST_push
(
	struct plibStdDataBST **ThisNode , 
	struct plibStdDataBST *NewNode , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
)
{
	enum plibStdDataBST_Status Status ;

	if( ThisNode == NullPointer )
		*ThisNode = NewNode ;
	else
	{
		do
		{
			Status = Operator( NewNode->Key , ( *ThisNode )->Key ) ;
		
			if( Status == plibStdDataBST_Status_Less )
			{
				if( ( *ThisNode )->Left == NullPointer )
				{
					( *ThisNode )->Left = NewNode ;
					break ;
				}
				else
					( *ThisNode ) = ( *ThisNode )->Left ;
			}
			else if( Status == plibStdDataBST_Status_Great )
			{
				if( ( *ThisNode )->Right == NullPointer )
				{
					( *ThisNode )->Right = NewNode ;
					break ;
				}
				else
					( *ThisNode ) = ( *ThisNode )->Right ;
			}
			else
				return false ;
		}
			else
		while( *ThisNode != NullPointer ) ;
	}
	
	return true ;
}
struct plibStdDataBST*
plibStdDataBST_pop
(
	struct plibStdDataBST **RootNode , 
	void *Key , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
)
{
	struct plibStdDataBST *ThisNode = *RootNode , *CandidateNode , **CandidateParentPointer = NullPointer , **ParentPointer = NullPointer ;
	enum plibStdDataBST_Status Status ;
	
	while( ThisNode != NullPointer )
	{
		Status = Operator( Key , ThisNode->Key ) ;
		
		if( Status == plibStdDataBST_Status_Less )
		{
			ParentPointer = &( ThisNode->Left ) ;
			ThisNode = ThisNode->Left ;
		}
		else if( Status == plibStdDataBST_Status_Great )
		{
			ParentPointer = &( ThisNode->Right ) ;
			ThisNode = ThisNode->Right ;
		}
		else
		{
			if( ThisNode->Left != NullPointer && ThisNode->Right != NullPointer )
			{
				for
				( 
					CandidateNode = ThisNode->Right ; 
					CandidateNode->Left != NullPointer ; 
					CandidateParentPointer = &( CandidateNode->Left ) , CandidateNode = CandidateNode->Left 
				) ;
				
				CandidateNode->Left = ThisNode->Left ;
				if( CandidateParentPointer != NullPointer )
					*CandidateParentPointer = CandidateNode->Right ;
				CandidateNode->Right = ThisNode->Right ;
				
				*ParentPointer = CandidateNode ;
			}
			else
			{
				if( ParentPointer == NullPointer )
					*RootNode = ThisNode->Left != NullPointer ? ThisNode->Left : ThisNode->Right ;
				else
					*ParentPointer = ThisNode->Left != NullPointer ? ThisNode->Left : ThisNode->Right ;
			}
		}
	}
	
	return ThisNode ;
}
struct plibStdDataBST*
plibStdDataBST_lookup
(
	struct plibStdDataBST *ThisNode , 
	void *Key , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
)
{
	enum plibStdDataBST_Status Status ;
	
	while( ThisNode != NullPointer )
	{
		Status = Operator( Key , ThisNode->Key ) ;
		
		if( Status == plibStdDataBST_Status_Less )
			ThisNode = ThisNode->Left ;
		else if( Status == plibStdDataBST_Status_Great )
			ThisNode = ThisNode->Right ;
		else
			break ;
	}
	
	return ThisNode ;
}
