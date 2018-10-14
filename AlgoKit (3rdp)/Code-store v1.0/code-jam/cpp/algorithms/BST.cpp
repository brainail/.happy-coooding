#include<iostream>

using namespace std;

struct BST {
   int val;
   struct BST *left , *right;
};

BST* create(int val) 
{
     BST *node = new BST;
     node->val = val;
     node->left = NULL;
     node->right = NULL;
     return node;
}

void insert(BST **root, int val)
{
        
   while(*root != NULL) {
      if((*root)->val < val)
           root = &((* root)->left);
      else
           root = &((* root)->right);
   }     
   *root = create(val);

}

void list(BST *root)
{
   if(root != NULL) {
      list(root->right);
      cout << root->val << " ";
      list(root->left);
   }
}

int find(BST **root, int val)
{
    int tval;
    while(*root != NULL) {
       tval = (* root)->val;
       if(tval < val)
          root = &((* root)->left);
       else if(tval > val)
          root = &((* root)->right);
       else
          return 1;
    }
    return 0;
}

int main() 
{
   BST *tree = new BST;
   tree = NULL;
   insert(&tree, 1);
   insert(&tree, 4);
   insert(&tree, 10);insert(&tree, 20);
   list(tree);
   
   cout << "Searching " << endl;
   printf("%d ", find(&tree, 10));
   printf("%d ", find(&tree, 20));
   printf("%d ", find(&tree, 7));
   return 0;
}
