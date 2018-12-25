
#define RED 'r'
#define BLACK 'b'
#define ONE_NODE 1
#define MAX_ACCOUNT_NUMBER 9999999
#define MIN_ACCOUNT_NUMBER 1000000
#define ACCOUNT_CHARACTERS 7
/*A Red-Black tree node structure*/
typedef struct node
{
long long int key;
int accountID;
int ID;
int balance;
char *name;
char color;
/*links for left, right children and parent*/
struct node *left, *right, *parent;
} node;
/*Functions prototype*/
/*RB-Tress functions*/
void leftRotate(node **root, node *x);
void insertFixUp(node **root, node *z);
void insertByID(node **root, int accountID, int ID, int balance, char *name);
void insertByBalance(node **root, int accountID, int ID, int balance, char *name);
void inorderByID(node *root);
struct node *searchByID(node *x, int accountID);
struct node *searchByBalance(node *x, long long int key);
struct node *successor(node *x);
/*Bank program functions*/
void showDebtors(node *x);
node *theRichest(node **balanceTreeRoot);
void showClientBalance(node **accountIDTreeRoot, int accountID);
void deleteClient(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID);
void addNewClient(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID, int ID, int balance, char *name);
void updateBalance(node **accountIDTreeRoot, node **balanceTreeRoot, int accountID, int balanceChange);
/*Other functions*/
void initNilT();
int lineCounter(FILE *file);
long long int getKey(int accountID, int balance);
void freeRBTree(node *root);
void deleteByID(node **root, int accountID);
void deleteByBalance(node **root, long long int key);
void deleteFixup(node **root, node *x);

