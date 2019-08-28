/**
* @file tree.cpp
* @brief This CPP program finds the AVL tree and REDBLACK tree
* @author Deepanshu Matia
* @date 18-8-2019
**/


#include<iostream>
using namespace std;

enum Color {RED, BLACK};

struct Node
{
       int data;
       Node *parent;
       bool color;
       Node *left;
       Node *right;
       int height;     
};

Node *Root=NULL;
Node *q=NULL;
Node* rooot=NULL;


int r=0;
int z=0;
   
void insertfix(Node *);
void leftrotate(Node *);
void rightrotate(Node *);
void disp();
void display( Node *);
void Print(Node* r,int x);
int Height_calculator(Node* q);
void Inorder(Node* s);
void Inorder0(void);

int max(int a, int b);  

int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    
    return N->height;  
} 

int max(int a, int b)  
{return (a > b)? a : b;}  

//! function to create new node
Node* newNode(int data)  
{  
    Node* Nod = new Node(); 
    Nod->data = data;  
    
    Nod->left = NULL;  
    Nod->right = NULL;  
   
    Nod->height = 1;  
    
    return(Nod);  
} 

//! function to rotate tree to right
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
    
    x->right = y;  
    y->left = T2;  
    
    y->height = max(height(y->left),height(y->right)) + 1;  
    x->height = max(height(x->left),height(x->right)) + 1;  
    
    return x;  
}  
    
//! function to rotate tree to left
Node *leftRotate(Node *x)  
{   
	Node *y = x->right;  
    Node *T2 = y->left;  
    
    y->left = x;  
    x->right = T2;  
    
    x->height = max(height(x->left),height(x->right)) + 1;  
    y->height = max(height(y->left),height(y->right)) + 1;  
    
    return y;  
}  
  
//! function to find balance of tree
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  
 
//! function to insert in tree
Node* insert3(Node* Node, int data)  
{  
    if (Node == NULL)  
        return(newNode(data));  
    if (data < Node->data)  
        Node->left = insert3(Node->left, data);  
    else if (data > Node->data)  
        Node->right = insert3(Node->right, data);  
    else  
        return Node;  
  
    Node->height = 1 + max(height(Node->left),height(Node->right));  
  
    int balance = getBalance(Node);  
      
    if (balance > 1 && data < Node->left->data)  
        return rightRotate(Node);  
    if (balance < -1 && data > Node->right->data)  
        return leftRotate(Node);  
    
    if (balance > 1 && data > Node->left->data)  
    {  
        Node->left = leftRotate(Node->left);  
        return rightRotate(Node);  
    }   
    
    if (balance < -1 && data < Node->right->data)  
    {  
        Node->right = rightRotate(Node->right);  
        return leftRotate(Node);  
    }  
  
    return Node;  
} 

Node* root=NULL;

struct Node* insert(Node* n,int k)
{
	Node* temp=new Node;
	if(n==NULL)
	{
		temp->data=k;
		temp->right=NULL;
		temp->left=NULL;
		return temp;
    }
	
	if(k<n->data)
	{n->left=insert(n->left,k);}
	else if(k>n->data)
	{n->right=insert(n->right,k);}
	
	return n;
}

//! function to insert in BST
Node* BSTInsert(Node* Root, Node *pt) 
{ 
	/* If the tree is empty, return a new node */
	if (Root == NULL) 
	return pt; 

	/* Otherwise, recur down the tree */
	if (pt->data < Root->data) 
	{ 
		Root->left = BSTInsert(Root->left, pt); 
		Root->left->parent = Root; 
	} 
	else if (pt->data > Root->data) 
	{ 
		Root->right = BSTInsert(Root->right, pt); 
		Root->right->parent = Root; 
	} 

	/* return the (unchanged) node pointer */
	return Root; 
} 

//! function to rotate to left
void rotateLeft(Node *&Root, Node *&pt) 
{ 
	Node *pt_right = pt->right; 

	pt->right = pt_right->left; 

	if (pt->right != NULL) 
		pt->right->parent = pt; 

	pt_right->parent = pt->parent; 

	if (pt->parent == NULL) 
		Root = pt_right; 

	else if (pt == pt->parent->left) 
		pt->parent->left = pt_right; 

	else
		pt->parent->right = pt_right; 

	pt_right->left = pt; 
	pt->parent = pt_right; 
} 

//! function to rotate to left
void rotateRight(Node *&Root, Node *&pt) 
{ 
	Node *pt_left = pt->left; 

	pt->left = pt_left->right; 

	if (pt->left != NULL) 
		pt->left->parent = pt; 

	pt_left->parent = pt->parent; 

	if (pt->parent == NULL) 
		Root = pt_left; 

	else if (pt == pt->parent->left) 
		pt->parent->left = pt_left; 

	else
		pt->parent->right = pt_left; 

	pt_left->right = pt; 
	pt->parent = pt_left; 
} 

//! function to fix violations caused by BST insertion 
void fixViolation(Node *&Root, Node *&pt) 
{ 
	Node *parent_pt = NULL; 
	Node *grand_parent_pt = NULL; 

	while ((pt != Root) && (pt->color != BLACK) && 
		(pt->parent->color == RED)) 
	{ 

		parent_pt = pt->parent; 
		grand_parent_pt = pt->parent->parent; 

		/* Case : A 
			Parent of pt is left child of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left) 
		{ 

			Node *uncle_pt = grand_parent_pt->right; 

			/* Case : 1 
			The uncle of pt is also red 
			Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color == RED) 
			{ 
				grand_parent_pt->color = RED; 
				parent_pt->color = BLACK; 
				uncle_pt->color = BLACK; 
				pt = grand_parent_pt; 
			} 

			else
			{ 
				/* Case : 2 
				pt is right child of its parent 
				Left-rotation required */
				if (pt == parent_pt->right) 
				{ 
					rotateLeft(Root, parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				/* Case : 3 
				pt is left child of its parent 
				Right-rotation required */
				rotateRight(Root, grand_parent_pt); 
				swap(parent_pt->color, grand_parent_pt->color); 
				pt = parent_pt; 
			} 
		} 

		/* Case : B 
		Parent of pt is right child of Grand-parent of pt */
		else
		{ 
			Node *uncle_pt = grand_parent_pt->left; 

			/* Case : 1 
				The uncle of pt is also red 
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color == RED)) 
			{ 
				grand_parent_pt->color = RED; 
				parent_pt->color = BLACK; 
				uncle_pt->color = BLACK; 
				pt = grand_parent_pt; 
			} 
			else
			{ 
				/* Case : 2 
				pt is left child of its parent 
				Right-rotation required */
				if (pt == parent_pt->left) 
				{ 
					rotateRight(Root, parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				/* Case : 3 
				pt is right child of its parent 
				Left-rotation required */
				rotateLeft(Root, grand_parent_pt); 
				swap(parent_pt->color, grand_parent_pt->color); 
				pt = parent_pt; 
			} 
		} 
	} 

	Root->color = BLACK; 
} 

//! Function to insert a new node with given data 
void insert1(const int &Data) 
{ 
	Node *pt = new Node; 
	pt->data=Data;
	pt->color=RED;
	pt->left=NULL;
	pt->right=NULL;
	pt->parent=NULL;
	// Do a normal BST insert 
	Root = BSTInsert(Root, pt); 

	// fix Red Black Tree violations 
	fixViolation(Root, pt); 
} 

///////////////////////////////////////////////////////////////////////////////////////

//! function to calculate tree height
int Height_calculator(Node* q)
{
	int height=0;
	int a=0,b=0;
	if(q->right==NULL&&q->left==NULL)
	{return 0;}
	
	if(q->right)
	{a=1+Height_calculator(q->right);}
	
	if(q->left)
	{b=1+Height_calculator(q->left);}
	
	if(a>b)
	{height=height+a;}
	else
	{height=height+b;}
	
	return height;
}

//! function to display tree using Print()
void disp()
{Print(Root,0);}

//! core function to print tree
void Print(Node* r,int x)
{
	
	int a=x;
	int a1=x;
	int y1=0;

		if(r)
		{
			while(a1!=0)
			{
				cout<<"    ";
				a1--;
			}
			
			if(r->left&&r->right)
			{y1=Height_calculator(r->left)-Height_calculator(r->right);}
			
			else if(r->left==NULL&&r->right!=NULL)
			{y1=Height_calculator(r);}
			
			else if(r->right==NULL&&r->left!=NULL)
			{y1=Height_calculator(r);}
			
			if(y1<0)
			{y1=0-y1;}
			
			if(y1!=0)
			cout<<r->data<<"["<<y1<<"]";
			else
			cout<<r->data;
			
			if(r->color==1)
          		cout<<"["<<"Black"<<"]"<<endl;
            else
              	cout<<"["<<"Red"<<"]"<<endl;
			
		}
		if(r->left&&r->right){
			a++;
			Print(r->left,a);
			Print(r->right,a);
		}
		else{
		if(r->left){
			a++;
			Print(r->left,a);
		}
		if(r->right){
		a++;				
			Print(r->right,a);
		}}
}

void print3(Node* r,int x)
{
	
	int a=x;
	int a1=x;
	int y1=0;
	if(r)
	{
		
		while(a1!=0)
		{
			cout<<"    ";
			a1--;
		}
		
		if(r->left&&r->right)
		{y1=Height_calculator(r->left)-Height_calculator(r->right);}
		
		else if(r->left==NULL&&r->right!=NULL)
		{y1=Height_calculator(r);}
		
		else if(r->right==NULL&&r->left!=NULL)
		{y1=Height_calculator(r);}
		
		if(y1<0)
		{y1=0-y1;}
		
		if(r->right||r->left)
		cout<<r->data<<"["<<y1<<"]"<<endl;
		else
		cout<<r->data<<endl;
	
    }
	
		if(r->left&&r->right)
		{
			a++;
			print3(r->left,a);
			print3(r->right,a);
	    }
		else
		{
		if(r->left)
		{
			a++;
			print3(r->left,a);
		}
		
		if(r->right)
		{
		    a++;				
			print3(r->right,a);
		}
    }
}
void print(Node* r,int x)
{
	int a=x;
	int a1=x;
	if(r)
		{
			while(a1!=0)
			{
				cout<<"    ";
				a1--;
			}
			
			if(Height_calculator(r)!=0)
			cout<<r->data<<"["<<Height_calculator(r)<<"]"<<endl;
			else
			cout<<r->data<<endl;
			
		}
		
		if(r->left&&r->right)
		{
			a++;
			print(r->left,a);
			print(r->right,a);
		}
		else
		{
		
			if(r->left)
			{
				a++;
				print(r->left,a);
			}
			
			if(r->right)
			{
				a++;				
				print(r->right,a);
			}
	    }
}
		

//! Recursive function to create AVL in order
void inorder_AVL_creation(Node* l)
{
	if(l)
	{
		inorder_AVL_creation(l->left);
		
		if(rooot==NULL)
			{rooot=insert3(rooot,l->data);}
		else
			{rooot=insert3(rooot,l->data);}
		
		inorder_AVL_creation(l->right);
	}	
}

//! Function to order tree
void Inorder(Node* s)
{
	if(s)
	{
		Inorder(s->left);
		cout<<s->data<<" ";
		Inorder(s->right);
	}	
}

//! function to print array
void printArray(int ints[], int len) 
{ 
	int i; 
	for (i = 0; i < len; i++) 
	{ for(int j=i;j<len;j++){
		cout << ints[j]; 
		if(j!=len-1){
			cout<<"->";
		}
	}
	cout<<endl;
	} 
	cout<<endl; 
} 

void printPathsRecur(Node* Node, int path[], int pathLen) 
{ 
	if (Node == NULL) 
		return; 
	path[pathLen] = Node->data; 
	pathLen++; 
	
	if (Node->left == NULL && Node->right == NULL) 
	{ 
		printArray(path, pathLen); 
	} 
	else
	{ 
		printPathsRecur(Node->left, path, pathLen); 
		printPathsRecur(Node->right, path, pathLen); 
	} 
} 

//! function to print path
void printPaths(Node* Node) 
{ 
	int path[1000]; 
	printPathsRecur(Node, path, 0); 
} 

int main(void)
{

	int imp=0;
	int imp1=0;
	int a;

	while(1)
	{
        cout<<"press 1 To insert a Node in the BST and in the red-black tree "<<endl;
		cout<<"press 2 To create AVL tree from the inorder traversal of BST "<<endl;
		cout<<"press 3 To print the inorder traversal of the BST/AVL/red-black tree "<<endl;
		cout<<"press 4 To display all the paths in the BST/AVL tree/red-black tree "<<endl;
		cout<<"press 5 To print the BST/AVL tree/red-black Tree in the terminal using level-wise indentation "<<endl;
		cout<<"press 6 to Exit "<<endl;
		
		cin>>a;
		
		switch(a)
		{
			case 1:
			{
				imp=0;
				imp1=1;
				int c;
				cout<<"enter the number to be inserted"<<endl;
				cin>>c;
				insert1(c);                             
				if(root==NULL)
				{
					root=insert(root,c);
				}
				else
				{
					insert(root,c);
				}
				cout<<"\nNode Inserted.\n";
				break;
			}

			case 2:
			{
				imp=1;
				if(imp1==1)
				{
					inorder_AVL_creation(root);
			 		cout<<"AVL tree created"<<endl;
			 	}
				else
			 		cout<<"Tree is empty.Please insert first"<<endl;
				
				break;
			}
			
			case 3:
			{
					if(imp1==1)
					{
					  cout<<"inorder traversal of BST"<<endl;
					  Inorder(root);
					  cout<<endl;
					  cout<<"Inorder traversal of Red-Black tree"<<endl;
					  Inorder(Root);
					  cout<<endl;
					  
					  if(imp==1)
					  {
						  cout<<"Inorder traversal of AVL tree "<<endl;
						  Inorder(rooot);
						  cout<<endl;
					  }
					  else
					 	{cout<<"First press 2 for creating the AVL tree"<<endl;}
			        }
					else
					 cout<<"Tree is empty.Please insert first"<<endl;
					 break;
			}

			case 4:
			{
				if(imp1==1)
				{
					cout<<"The paths of BST"<<endl;
					printPaths(root);
					cout<<"The paths of Red Black Tree"<<endl;
					printPaths(Root);
					cout<<"The paths of AVL tree"<<endl;
					printPaths(rooot);
				}
				
				else
					cout<<"Tree is empty.Please insert first"<<endl;
				
				break;
			}
			
			case 5:
			{
				if(imp1==1)
				{
					cout<<"BST"<<endl;
					print(root,0);
					cout<<"Red-Black tree"<<endl;
					disp();
					if(imp==1)
						print3(rooot,0);
					else
					 	cout<<"First press 2 for creating the AVL tree"<<endl;
			    }
			 
			 	else
			 		cout<<"Tree is empty.Please insert first"<<endl;
				
				break;
			}
			
			case 6:
			{
				exit(1);
				break;
			}
			
			default:
				cout<<"press only from 1 to 6"<<endl;
			    break;
		}
	}
return 0;
}