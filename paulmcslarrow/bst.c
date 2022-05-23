#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node* left;
  struct Node* right;
} NODE;

/* Simply go all the way to the left most value from NODE r */
NODE* minValueNode( NODE* r)
{
    NODE* current = r;
 
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

/* Use a recursive algorithm to search for the deleteValue and then delete accordingly, based on the case of deletion*/
NODE* delete( int deleteValue, NODE *root )
{

    //Base Case
    if (root == NULL)
        return root;

    //Searching for the deleteValue
    if (deleteValue < root->data)
        root->left = delete(deleteValue, root->left);
        
    else if (deleteValue > root->data)
        root->right = delete(deleteValue, root->right);

    else {
        //Case 1 
        if (root->left == NULL) {
            NODE* temp = root->right;
            free(root);
            return temp;
        }
        
        //Case 2
        else if (root->right == NULL) {
            NODE* temp = root->left;
            free(root);
            return temp;
        }
        
        //Case 3 -- Two Children
        else {
            NODE* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = delete(temp->data, root->right);
        }
    }
    return root;
}

/* Recursively finds the spot where the new value will be stitched in */
void insert( int value, NODE *node )
{
   if (value < node->data)
   {
   	if (node->left == NULL) { 
   	   NODE *new_node = malloc(sizeof(NODE));
   	   new_node->data = value;
   	   node->left = new_node;
   	} else {
   	   insert( value, node->left );
   	}
   } else if (value > node->data) {
   
   	if (node->right == NULL) { 
   	   NODE *new_node = malloc(sizeof(NODE));
   	   new_node->data = value;
   	   node->right = new_node;
   	} else {
   	   insert( value, node->right );
   	}
   }
}

/* 
Pass in a pointer to a NODE type... 
EXP: inorder( root ); 
*/
void inorder( NODE *r )
{
  if (r == NULL){ return; }
  else {
     inorder( r->left );
     printf("%d\n", r->data);
     inorder( r->right );
  }
}



int main(){

  NODE *root = malloc(sizeof(NODE));
  root->data = 55;
  
  insert(22, root);
  insert(66, root);
  insert(9, root);
  insert(15, root);
  insert(60, root);
  insert(100, root);
  
  delete(100, root);
  delete(55, root);
  inorder(root);


  return 0;
}	
