/*
	plib::Std::Data::BST
*/
#include "plibStdDataBST.h"

bool
plibStdDataBST_push
(
	struct plibStdDataBST **EntryNode , 
	struct plibStdDataBST *NewNode , 
	enum plibStdDataBSTStatus ( *Operator )( uint8_t *Key1 , uint8_t *Key2 ) 
)
{
	struct plibStdDataBST *ThisNode = *EntryNode ;
	enum plibStdDataBSTStatus Status ;

	if( ThisNode == plibStdTypeNullPointer )
		*EntryNode = NewNode ;
	else
	{
		do
		{
			Status = Operator( NewNode->Key , ThisNode->Key ) ;
		
			if( Status == plibStdDataBSTStatusLess )
			{
				if( ThisNode->Left == plibStdTypeNullPointer )
				{
					ThisNode->Left = NewNode ;
					break ;
				}
				else
					ThisNode = ThisNode->Left ;
			}
			else if( Status == plibStdDataBSTStatusGreat )
			{
				if( ThisNode->Right == plibStdTypeNullPointer )
				{
					ThisNode->Right = NewNode ;
					break ;
				}
				else
					ThisNode = ThisNode->Right ;
			}
			else
				return false ;
		}
		while( ThisNode != plibStdTypeNullPointer ) ;
	}
	
	return true ;
}
struct plibStdDataBST*
plibStdDataBST_pop
(
	struct plibStdDataBST **EntryNode , 
	uint8_t *Key , 
	enum plibStdDataBSTStatus ( *Operator )( uint8_t *Key1 , uint8_t *Key2 ) 
)
{
	struct plibStdDataBST *ThisNode = *EntryNode , *CandidateNode , *CandidateParent = plibStdTypeNullPointer , **ParentPointer = plibStdTypeNullPointer ;
	enum plibStdDataBSTStatus Status ;
	
	while( ThisNode != plibStdTypeNullPointer )
	{
		Status = Operator( Key , ThisNode->Key ) ;
		
		if( Status == plibStdDataBSTStatusLess )
		{
			ParentPointer = &( ThisNode->Left ) ;
			ThisNode = ThisNode->Left ;
		}
		else if( Status == plibStdDataBSTStatusGreat )
		{
			ParentPointer = &( ThisNode->Right ) ;
			ThisNode = ThisNode->Right ;
		}
		else
		{
			if( ThisNode->Left != plibStdTypeNullPointer && ThisNode->Right != plibStdTypeNullPointer )
			{
				for
				( 
					CandidateNode = ThisNode->Right ; 
					CandidateNode->Left != plibStdTypeNullPointer ; 
					CandidateParent = CandidateNode , CandidateNode = CandidateNode->Left 
				) ;
				
				if( CandidateParent != plibStdTypeNullPointer )
					CandidateParent->Left = CandidateNode->Right ;
					
				CandidateNode->Left = ThisNode->Left ;
				if( ThisNode->Right != CandidateNode )
					CandidateNode->Right = ThisNode->Right ;
				
				if( ParentPointer == plibStdTypeNullPointer )
					*EntryNode = CandidateNode ;
				else
					*ParentPointer = CandidateNode ;
			}
			else
			{
				if( ParentPointer == plibStdTypeNullPointer )
					*EntryNode = ThisNode->Left != plibStdTypeNullPointer ? ThisNode->Left : ThisNode->Right ;
				else
					*ParentPointer = ThisNode->Left != plibStdTypeNullPointer ? ThisNode->Left : ThisNode->Right ;
			}
			
			break ;
		}
	}
	
	return ThisNode ;
}
struct plibStdDataBST*
plibStdDataBST_lookup
(
	struct plibStdDataBST *ThisNode , 
	uint8_t *Key , 
	enum plibStdDataBSTStatus ( *Operator )( uint8_t *Key1 , uint8_t *Key2 ) 
)
{
	enum plibStdDataBSTStatus Status ;
	
	while( ThisNode != plibStdTypeNullPointer )
	{
		Status = Operator( Key , ThisNode->Key ) ;
		
		if( Status == plibStdDataBSTStatusLess )
			ThisNode = ThisNode->Left ;
		else if( Status == plibStdDataBSTStatusGreat )
			ThisNode = ThisNode->Right ;
		else
			break ;
	}
	
	return ThisNode ;
}
