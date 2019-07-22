/* 
	binary search tree
*/
#include <stdbool.h>
#include "bst.h"

struct bst_Node* bst_search( struct bst_Node *RootNode , void *Key , enum bst_STATUS ( *judge )( void *Key1 , void *Key2 ) )
{
	struct bst_Node *TempNode = RootNode ;
	enum bst_STATUS Status ;
	
	while( TempNode != NULL )
	{
		Status = judge( Key , TempNode->Key ) ;
		
		if( Status == bst_status_LESS )
			TempNode = TempNode->Left ;
		else if( Status == bst_status_GREAT )
			TempNode = TempNode->Right ;
		else
			break ;
	}
	
	return TempNode ;
}

bool bst_insert( struct bst_Node **RootNode , struct bst_Node *NewNode , enum bst_STATUS ( *judge )( void *Key1 , void *Key2 ) )
{
	struct bst_Node *TempNode = *RootNode ;
	enum bst_STATUS Status ;

	while( TempNode != NULL )
	{
		Status = judge( NewNode->Key , TempNode->Key ) ;
		
		if( Status == bst_status_LESS )
		{
			if( TempNode->Left == NULL )
			{
				TempNode->Left = NewNode ;
				return true ;
			}
			
			TempNode = TempNode->Left ;
		}
		else if( Status == bst_status_GREAT )
		{
			if( TempNode->Right == NULL )
			{
				TempNode->Right = NewNode ;
				return true ;
			}
			
			TempNode = TempNode->Right ;
		}
		else
			return false ;
	}
	
	*RootNode = NewNode ;
	return true ;
}
struct bst_Node* bst_desert( struct bst_Node **RootNode , char *Key , enum bst_STATUS ( *judge )( void *Key1 , void *Key2 ) )
{
	struct bst_Node *ChildNode = *RootNode , *ParentNode = ChildNode , *TempParentNode , *TempChildNode ;
	enum bst_STATUS Status ;
	
	while( ChildNode != NULL )
	{
		Status = judge( Key , ChildNode->Key ) ;
		
		if( Status == bst_status_LESS )
		{
			ParentNode = ChildNode ;
			ChildNode = ChildNode->Left ;
		}
		else if( Status == bst_status_GREAT )
		{
			ParentNode = ChildNode ;
			ChildNode = ChildNode->Right ;
		}
		else
		{
			if( ChildNode->Left == NULL && ChildNode->Right == NULL )
			{
				if( ChildNode == *RootNode )
					*RootNode = NULL ;
				else
				{
					if( Status == bst_status_LESS )
						ParentNode->Left = NULL ;
					else if( Status == bst_status_GREAT )
						ParentNode->Right = NULL ;
				}
			}
			else if( ChildNode->Left != NULL && ChildNode->Right == NULL )
			{
				if( ChildNode == *RootNode )
					*RootNode = ( *RootNode )->Left ;
				else
				{
					if( Status == bst_status_LESS )
						ParentNode->Left = ChildNode->Left ;
					else if( Status == bst_status_GREAT )
						ParentNode->Right = ChildNode->Left ;
				}
			}
			else if( ChildNode->Left == NULL && ChildNode->Right != NULL )
			{
				if( ChildNode == *RootNode )
					*RootNode = ( *RootNode )->Right ;
				else
				{
					if( Status == bst_status_LESS )
						ParentNode->Left = ChildNode->Right ;
					else if( Status == bst_status_GREAT )
						ParentNode->Right = ChildNode->Right ;
				}
			}
			else
			{
				for
				(
					TempChildNode = ChildNode->Right , TempParentNode = TempChildNode ; 
					TempChildNode->Left != NULL ; 
					TempParentNode = TempChildNode , TempChildNode = TempChildNode->Left 
				) ;
			
				if( TempChildNode == TempParentNode )
					TempChildNode->Left = ChildNode->Left ;
				else
				{
					TempParentNode->Left = TempChildNode->Right ;
					TempChildNode->Left = ChildNode->Left ;
					TempChildNode->Right = ChildNode->Right ;
				}
			
				if( ChildNode == *RootNode )
					*RootNode = TempChildNode ;
				else
				{
					if( Status == bst_status_LESS )
						ParentNode->Left = TempChildNode ;
					else if( Status == bst_status_GREAT )
						ParentNode->Right = TempChildNode ;
				}
			}
			
			break ;
		}
	}
	
	return ChildNode ;
}
