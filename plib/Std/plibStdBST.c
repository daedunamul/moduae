/*
	plib
	Std
	Binary Search Tree
*/
#include "plibStdBST.h"

struct plibStdBST_Node* plibStdBST_search( struct plibStdBST_Node *RootNode , void *Key , enum plibStdBST_STATUS ( *judge )( void *Key1 , void *Key2 ) )
{
	struct plibStdBST_Node *TempNode = RootNode ;
	enum plibStdBST_STATUS Status ;
	
	while( TempNode != NULL )
	{
		Status = judge( Key , TempNode->Key ) ;
		
		if( Status == plibStdBST_status_LESS )
			TempNode = TempNode->Left ;
		else if( Status == plibStdBST_status_GREAT )
			TempNode = TempNode->Right ;
		else
			break ;
	}
	
	return TempNode ;
}

bool plibStdBST_insert( struct plibStdBST_Node **RootNode , struct plibStdBST_Node *NewNode , enum plibStdBST_STATUS ( *judge )( void *Key1 , void *Key2 ) )
{
	struct plibStdBST_Node *TempNode = *RootNode ;
	enum plibStdBST_STATUS Status ;

	while( TempNode != NULL )
	{
		Status = judge( NewNode->Key , TempNode->Key ) ;
		
		if( Status == plibStdBST_status_LESS )
		{
			if( TempNode->Left == NULL )
			{
				TempNode->Left = NewNode ;
				return true ;
			}
			
			TempNode = TempNode->Left ;
		}
		else if( Status == plibStdBST_status_GREAT )
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
struct plibStdBST_Node* plibStdBST_desert( struct plibStdBST_Node **RootNode , char *Key , enum plibStdBST_STATUS ( *judge )( void *Key1 , void *Key2 ) )
{
	struct plibStdBST_Node *ChildNode = *RootNode , *ParentNode = ChildNode , *TempParentNode , *TempChildNode ;
	enum plibStdBST_STATUS Status ;
	
	while( ChildNode != NULL )
	{
		Status = judge( Key , ChildNode->Key ) ;
		
		if( Status == plibStdBST_status_LESS )
		{
			ParentNode = ChildNode ;
			ChildNode = ChildNode->Left ;
		}
		else if( Status == plibStdBST_status_GREAT )
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
					if( Status == plibStdBST_status_LESS )
						ParentNode->Left = NULL ;
					else if( Status == plibStdBST_status_GREAT )
						ParentNode->Right = NULL ;
				}
			}
			else if( ChildNode->Left != NULL && ChildNode->Right == NULL )
			{
				if( ChildNode == *RootNode )
					*RootNode = ( *RootNode )->Left ;
				else
				{
					if( Status == plibStdBST_status_LESS )
						ParentNode->Left = ChildNode->Left ;
					else if( Status == plibStdBST_status_GREAT )
						ParentNode->Right = ChildNode->Left ;
				}
			}
			else if( ChildNode->Left == NULL && ChildNode->Right != NULL )
			{
				if( ChildNode == *RootNode )
					*RootNode = ( *RootNode )->Right ;
				else
				{
					if( Status == plibStdBST_status_LESS )
						ParentNode->Left = ChildNode->Right ;
					else if( Status == plibStdBST_status_GREAT )
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
					if( Status == plibStdBST_status_LESS )
						ParentNode->Left = TempChildNode ;
					else if( Status == plibStdBST_status_GREAT )
						ParentNode->Right = TempChildNode ;
				}
			}
			
			break ;
		}
	}
	
	return ChildNode ;
}
