
#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"
/*Left Rotation*/
void leftRotate(node **root, node *x)
{
extern node *nilT;
/*y stored pointer of right child of x*/
node *y = x->right;
/*store y's left subtree's pointer as x's right child*/
x->right = y->left;
/*update parent pointer of x's right*/
if(y->left != nilT)
y->left->parent = x;
/*update y's parent pointer*/
y->parent = x->parent;
/*if x's parent is nilT make y as root of tree*/
if(x->parent == nilT)
(*root) = y;
/*store y at the place of x*/
else if(x == x->parent->left)
x->parent->left = y;
else
x->parent->right = y;
/*make x as left child of y*/
y->left = x;
/*update parent pointer of x*/
x->parent = y;
}
/*Right Rotation (Similar to LeftRotate)*/
void rightRotate(node **root, node *x)
{
extern node *nilT;
node *y = x->left;
x->left = y->right;
if(y->right != nilT)
y->right->parent = x;
y->parent = x->parent;
if(x->parent == nilT)
(*root) = y;
else if(x == x->parent->right)
x->parent->right = y;
else x->parent->left = y;
y->right = x;
x->parent = y;
}
/*Utility function to fixup the Red-Black tree after standard BST insertion*/
void insertFixUp(node **root, node *z)
{
extern node *nilT;
/*iterate until z is not the root and z's parent color is red*/
while(z->parent->color == RED)
{
node *y;
/*Find uncle and store uncle in y*/
if(z->parent == z->parent->parent->left)
{
y = z->parent->parent->right;
/*Case 1*/
if(y->color == RED)
{
z->parent->color = BLACK;
y->color = BLACK;
z->parent->parent->color = RED;
z = z->parent->parent;
}
/*Case 2*/
else if(z == z->parent->right)
{
z = z->parent;
leftRotate(root, z);
z->parent->color = BLACK;
z->parent->parent->color = RED;
rightRotate(root, z->parent->parent);
}
/*Case 3*/
else
{
z->parent->color = BLACK;
z->parent->parent->color = RED;
rightRotate(root, z->parent->parent);
}
}
else
{
y = z->parent->parent->left;
/*Case 1*/
if(y->color == RED)
{
z->parent->color = BLACK;
y->color = BLACK;
z->parent->parent->color = RED;
z = z->parent->parent;
}
/*Case 2*/
else if(z == z->parent->left)
{
z = z->parent;
rightRotate(root, z);
z->parent->color = BLACK;
z->parent->parent->color = RED;
leftRotate(root, z->parent->parent);
}
/*Case 3*/
else
{
z->parent->color = BLACK;
z->parent->parent->color = RED;
leftRotate(root, z->parent->parent);
}
}
}
/*keep root always black*/
(*root)->color = BLACK;
}
/*Utility function to insert newly node in RedBlack tree*/
void insertByID(node **root, int accountID, int ID, int balance, char *name)
{
extern node *nilT;
node *y = nilT;
node *x = (*root);
/*Allocate memory for new node*/
node *z = (node *) calloc(ONE_NODE, sizeof(node));
if(!z)
{
printf("Memory allocation failed");
exit(0);
}
z->accountID = accountID;
z->name = name;
z->ID = ID;
z->balance = balance;
z->key = getKey(accountID, balance);
z->left = nilT;
z->right = nilT;
z->parent = nilT;
/*Follow standard BST insert steps to first insert the node*/
while(x != nilT)
{
y = x;
if(z->accountID < x->accountID)
x = x->left;
else
x = x->right;
}
z->parent = y;
if(y == nilT)
(*root) = z;
else if(z->accountID < y->accountID)
y->left = z;
else
y->right = z;
z->color = RED;
/*Call insertFixUp to fix reb-black tree*/
insertFixUp(root, z);
}
/*The same like insert by account just for the RB-Tree by balance*/
void insertByBalance(node **root, int accountID, int ID, int balance, char *name)
{
extern node *nilT, *richest;
node *y = nilT;
node *x = (*root);
/*Allocate memory for new node*/
node *z = (node *) calloc(ONE_NODE, sizeof(node));
if(!z)
{
printf("Memory allocation failed");
exit(0);
}
z->key = getKey(accountID, balance);
z->accountID = accountID;
z->name = name;
z->ID = ID;
z->balance = balance;
z->left = nilT;
z->right = nilT;
z->parent = nilT;
/*Keep on the richest actually is*/
if(richest == nilT || z->balance > richest->balance)
richest = z;
/*Follow standard BST insert steps to first insert the node*/
while(x != nilT)
{
y = x;
if(z->key < x->key)
x = x->left;
else
x = x->right;
}
z->parent = y;
if(y == nilT)
(*root) = z;
else if(z->key < y->key)
y->left = z;
else
y->right = z;
z->color = RED;
/*Call insertFixUp to fix reb-black tree*/
insertFixUp(root, z);
}
/*Search in BST for the RB-Tree by account*/
struct node *searchByID(node *x, int accountID)
{
extern node *nilT;
while(x != nilT && x->accountID != accountID)
{
if(accountID < x->accountID)
x = x->left;
else
x = x->right;
}
return x;
}
/*Search in BST for the RB-Tree by balance*/
struct node *searchByBalance(node *x, long long int key)
{
extern node *nilT;
while(x != nilT && x->key != key)
{
if(key < x->key)
x = x->left;
else
x = x->right;
}
return x;
}
/*Fine the successor like BST*/
struct node *successor(node *x)
{
extern node *nilT;
node *y;
if(x->right != nilT)
{
x = x->right;
while(x->left != nilT)
x = x->left;
return x;
}
y = x->parent;
while(y != nilT && x == y->right)
{
x = y;
y = y->parent;
}
return y;
}
/*Delete node from the account RB-Tree*/
void deleteByID(node **root, int accountID)
{
extern node *nilT;
node *z = searchByID(*root, accountID);
node *x, *y;
if(z->left == nilT || z->right == nilT)
y = z;
else
y = successor(z);
if(y->left != nilT)
x = y->left;
else
x = y->right;
x->parent = y->parent;
if(y->parent == nilT)
*root = x;
else if(y == y->parent->left)
y->parent->left = x;
else
y->parent->right = x;
if(y != z)
{
z->accountID = y->accountID;
z->name = y->name;
z->ID = y->ID;
z->balance = y->balance;
z->key = y->key;
}
if(y->color == BLACK)
deleteFixup(root, x);
}
/*Delete node from the balance RB-Tree*/
void deleteByBalance(node **root, long long int key)
{
extern node *nilT;
node *z = searchByBalance(*root, key);
node *x, *y;
if(z->left == nilT || z->right == nilT)
y = z;
else
y = successor(z);
if(y->left != nilT)
x = y->left;
else
x = y->right;
x->parent = y->parent;
if(y->parent == nilT)
*root = x;
else if(y == y->parent->left)
y->parent->left = x;
else
y->parent->right = x;
if(y != z)
{
z->accountID = y->accountID;
z->name = y->name;
z->ID = y->ID;
z->balance = y->balance;
z->key = y->key;
free(y);
}
if(y->color == BLACK)
deleteFixup(root, x);
}
/*Fixeup the RB-Tree after delete*/
void deleteFixup(node **root, node *x)
{
extern node *nilT;
node *w;
while(x != *root && x->color == BLACK)
{
if(x == x->parent->left)
{
w = x->parent->right;
/*Case 1*/
if(w->color == RED)
{
w->color = BLACK;
x->parent->color = RED;
leftRotate(root, x->parent);
w = x->parent->right;
}
/*Case 2*/
if(w->left->color == BLACK && w->right->color == BLACK)
{
w->color = RED;
x = x->parent;
}
/*Case 3*/
else if(w->right->color == BLACK)
{
w->left->color = BLACK;
w->color = RED;
rightRotate(root, w);
w = x->parent->right;
w->color = x->parent->color;
x->parent->color = BLACK;
w->right->color = BLACK;
leftRotate(root, x->parent);
x = *root;
}
/*Case 4*/
else
{
w->color = x->parent->color;
x->parent->color = BLACK;
w->right->color = BLACK;
leftRotate(root, x->parent);
x = *root;
}
}
else
{
w = x->parent->left;
/*Case 1*/
if(w->color == RED)
{
w->color = BLACK;
x->parent->color = RED;
rightRotate(root, x->parent);
w = x->parent->left;
}
/*Case 2*/
if(w->left->color == BLACK && w->right->color == BLACK)
{
w->color = RED;
x = x->parent;
}
/*Case 3*/
else if(w->left->color == BLACK)
{
w->right->color = BLACK;
w->color = RED;
leftRotate(root, w);
w = x->parent->left;
w->color = x->parent->color;
x->parent->color = BLACK;
w->left->color = BLACK;
rightRotate(root, x->parent);
x = *root;
}
/*Case 4*/
else
{
w->color = x->parent->color;
x->parent->color = BLACK;
w->left->color = BLACK;
rightRotate(root, x->parent);
x = *root;
}
}
}
x->color = BLACK;
}

/*Free the memory that allocated to the tree*/
void freeRBTree(node *root)
{
extern node *nilT;
if(root == nilT)
return;
freeRBTree(root->left);
freeRBTree(root->right);
free(root);
}
/*The balance tree should get a valid value without copies so the function create a valid
* value for the the value contain the balance in the left 9 characters and in 7 from the right the account number */
long long int getKey(int accountID, int balance)
{
long long int key = balance;
int i;
for(i = 0; i < ACCOUNT_CHARACTERS; ++i)
{
key = key * 10;
}
key += accountID;
return key;
}

   
   

