#include<iostream>

using namespace std;

struct Node{
	Node *left;
	Node *right;
	int data;
};

class Tree{
	int count;
	public:
		Node *root, *temp;
		Tree(){
			root=temp=NULL;
			count=0;
		}
		void create();
		void dispreorder(Node *rootn);
		void dispostorder(Node *rootn);
		void dispinorder(Node *rootn);
		void displevelorder(Node *rootn);		
		void countnodes();
		int deletebst();
		int height(Node* node);
		int printlevel(Node *root, int level);
};

void Tree::countnodes(){
	cout << "Number of nodes = " << count << endl;
}

void Tree::create(){
	int n;
	char ch;
	cout << "Please enter element: ";
	cin >> n;
	Node *newnode = new Node();
	newnode->data=n;
	if(!root){
		newnode->left=newnode->right=NULL;
		root = newnode;
		cout << "Root element stored\n";
		count++;
	}else{
		temp=root;
		while(1){
			if(temp->data!=n){
				if(n < temp->data){
					if(temp->left) 
						temp=temp->left; 
					else{
						temp->left=newnode;
						count++;
						break;
					}
				}else{
					if(temp->right)
						temp=temp->right;
					else{
						temp->right=newnode;
						count++;
						break;
					} 
				}
			} else{
				cout << "Element already exists please try again\n";
				break;
			}
		}
	}
}

void Tree::dispreorder(Node *rootn){
	cout << rootn->data << " ";
	if(rootn->left)
		dispreorder(rootn->left);
	if(rootn->right)
		dispreorder(rootn->right);
}

void Tree::dispinorder(Node *rootn){
	if(rootn->left)
		dispinorder(rootn->left);
	cout << rootn->data << " ";
	if(rootn->right)
		dispinorder(rootn->right);
}

void Tree::dispostorder(Node *rootn){
	if(rootn->left)
		dispostorder(rootn->left);
	if(rootn->right)
		dispostorder(rootn->right);
	cout << rootn->data << " ";
}

void Tree::displevelorder(Node *rootn){
	int i =0, h=height(rootn);
	for(i=1;i<=h;i++){
		printlevel(root, i);
		cout << endl;
	}	
}

int Tree::printlevel(Node *root, int level){
	for(int i=height(root)-level;i>0;i--)
		cout << " ";
	if (root == NULL){
        cout << "N ";
        return 0;
	}
    if (level == 1)  
        cout << root->data << " ";  
    else if (level > 1)  
    {  
        printlevel(root->left, level-1);  
        printlevel(root->right, level-1);  
    }  
}

int Tree::height(Node* node)  
{  
    if (node == NULL)  
        return 0;  
    else
    {  
        /* compute the height of each subtree */
        int lheight = height(node->left);  
        int rheight = height(node->right);  
  
        /* use the larger one */
        if (lheight > rheight)  
            return(lheight + 1);  
        else return(rheight + 1);  
    }  
}  

int Tree::deletebst(){
	int n;
	Node *troot, *t1, *t2;
	cout << "Enter element you want to delete: ";
	cin >> n;
	temp=root;

	// Finding the element to delete and it's parent
	while(1){
		cout << "n = " << n << "\ntemp->data =  " << temp->data << "\ntemp==NULL" << temp << endl;
		troot=temp;
		if(n<temp->data)
			temp=temp->left;
		else
			temp=temp->right;
		if(temp){
			if(n==temp->data)
				break;
		}else{
			cout << "Element doesn't exist\n";
			return 0;
		}
	}

	//case 1: Deleting leaf node
	if(!temp->left && !temp->right){
		if(temp==troot->left)
			troot->left=NULL;
		else
			troot->right=NULL;
			
	//case 2: Deleting node with 1 child
	}else if(!temp->right){
		if(temp==troot->left)
			troot->left=temp->left;
		else
			troot->right=temp->left;		
	}else if(!temp->left){
		if(temp==troot->left)
			troot->left=temp->right;
		else
			troot->right=temp->right;
	
	//case 3: Deleting node with 2 childs
	}else{
		if(temp==troot->left){
			cout<<"Deleting element to the left of " << troot->data << "data = " << temp->data << endl;
			t2=temp;
			t1=temp->left;
			while(t1->right){
				t2=t1;
				t1=t1->right;
			}
			t1->right=temp->right;
			t2->right=NULL;
			troot->left=t1;
		}else if(temp==troot->right){
			cout<<"Deleting element to the right of " << troot->data << endl;
				t2=temp;
			t1=temp->right;
			while(t1->left){
				t2=t1;
				t1=t1->left;
			}
			t1->left=temp->left;
			t2->left=NULL;
			troot->right=t1;
		}
	}
	delete temp;				
}

int main(){
	int i=0;
	Tree l;
	while(i!=8){
		cout<<"\n1. To Create(or)insert at end\n2. For Length\n3. To Display inorder\n4. To Display Preorder\n5. To Display Postorder\n6. To Delete\n7. To Display Level Order\n8. To Exit\n";
		cin >> i;
		switch(i){
			case 1:
				l.create();
				break;
			case 2:
				l.countnodes();
				break;
			case 3:
				cout << "Inorder: ";
				l.dispinorder(l.root);
				break;
			case 4:
				cout << "Preorder: ";
				l.dispreorder(l.root);
				break;
			case 5:
				cout << "Postorder: ";
				l.dispostorder(l.root);
				break;
			case 6:
				l.deletebst();
				break;
			case 7:
				l.displevelorder(l.root);
				break;
			case 8: break;
			default: i=0;	
		}
	}
	
	//test case
	//1 12 1 5 1 15 1 3 1 7 1 13 1 17 1 1 1 9 1 14 1 20 1 8 1 11 1 18
	// 12 5 15 3 7 13 17 1 9 14 20 8 11 18
}
