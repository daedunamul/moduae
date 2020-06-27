/*
	plib::Std::Data::BST
*/
#include "plibStdDataBST.h"

bool
plibStdDataBST_push
(
	struct plibStdDataBST **EntryNode , 
	struct plibStdDataBST *NewNode , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
)
{
	struct plibStdDataBST *ThisNode = *EntryNode ;
	enum plibStdDataBST_Status Status ;

	if( ThisNode == plibStdData_Pointer_Null )
		*EntryNode = NewNode ;
	else
	{
		do
		{
			Status = Operator( NewNode->Key , ThisNode->Key ) ;
		
			if( Status == plibStdDataBST_Status_Less )
			{
				if( ThisNode->Left == plibStdData_Pointer_Null )
				{
					ThisNode->Left = NewNode ;
					break ;
				}
				else
					ThisNode = ThisNode->Left ;
			}
			else if( Status == plibStdDataBST_Status_Great )
			{
				if( ThisNode->Right == plibStdData_Pointer_Null )
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
		while( ThisNode != plibStdData_Pointer_Null ) ;
	}
	
	return true ;
}
struct plibStdDataBST*
plibStdDataBST_pop
(
	struct plibStdDataBST **EntryNode , 
	void *Key , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
)
{
	struct plibStdDataBST *ThisNode = *EntryNode , *CandidateNode , *CandidateParent = plibStdData_Pointer_Null , **ParentPointer = plibStdData_Pointer_Null ;
	enum plibStdDataBST_Status Status ;
	
	while( ThisNode != plibStdData_Pointer_Null )
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
			if( ThisNode->Left != plibStdData_Pointer_Null && ThisNode->Right != plibStdData_Pointer_Null )
			{
				for
				( 
					CandidateNode = ThisNode->Right ; 
					CandidateNode->Left != plibStdData_Pointer_Null ; 
					CandidateParent = CandidateNode , CandidateNode = CandidateNode->Left 
				) ;
				
				if( CandidateParent != plibStdData_Pointer_Null )
					CandidateParent->Left = CandidateNode->Right ;
					
				CandidateNode->Left = ThisNode->Left ;
				if( ThisNode->Right != CandidateNode )
					CandidateNode->Right = ThisNode->Right ;
				
				if( ParentPointer == plibStdData_Pointer_Null )
					*EntryNode = CandidateNode ;
				else
					*ParentPointer = CandidateNode ;
			}
			else
			{
				if( ParentPointer == plibStdData_Pointer_Null )
					*EntryNode = ThisNode->Left != plibStdData_Pointer_Null ? ThisNode->Left : ThisNode->Right ;
				else
					*ParentPointer = ThisNode->Left != plibStdData_Pointer_Null ? ThisNode->Left : ThisNode->Right ;
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
	void *Key , 
	enum plibStdDataBST_Status ( *Operator )( void *Key1 , void *Key2 ) 
)
{
	enum plibStdDataBST_Status Status ;
	
	while( ThisNode != plibStdData_Pointer_Null )
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
