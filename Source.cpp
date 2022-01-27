#include<iostream>
using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T>* leftchild;
	Node<T>* rightchild;
	Node()
	{
		data = T();
		leftchild = NULL;
		rightchild = NULL;
	}
	Node(T d)
	{
		data = d;
		leftchild = NULL;
		rightchild = NULL;
	}

};

template <typename T>
class IntBinaryTree
{
private:
	Node<T>* root; // Pointer to the root of BST

	//void destroySubTree(Node<T>*)//Recursively delete all tree nodes
	void deleteNode(int num, Node<T>*& nodePtr)
	{
		if (nodePtr == NULL) // node does not exist in the tree
			cout << num << "not found.\n";

		else if (num < nodePtr->data)

			deleteNode(num, nodePtr->leftchild); // find in leftchild subtree

		else if (num > nodePtr->data)
			deleteNode(num, nodePtr->rightchild); // find in rightchild subtree

		else // num == nodePtr->data i.e. node is found
			makeDeletion(nodePtr); // actually deletes node from BST
	}
	void makeDeletion(Node<T>*& nodePtr)
	{
		Node<T>* tempNodePtr; // Temperary pointer

		if (nodePtr->rightchild == NULL) { // case for leaf and one (leftchild) child
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->leftchild; // Reattach the leftchild child
			delete tempNodePtr;
		}

		else if (nodePtr->leftchild == NULL) { // case for one (rightchild) child
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->rightchild; // Reattach the rightchild child
			delete tempNodePtr;
		}

		else { // case for two children.
			tempNodePtr = nodePtr->rightchild; // Move one node to the rightchild
			while (tempNodePtr->leftchild) { // Go to the extreme leftchild node
				tempNodePtr = tempNodePtr->leftchild;

			}

			tempNodePtr->leftchild = nodePtr->leftchild; // Reattach the leftchild subtree
			tempNodePtr = nodePtr;
			nodePtr = nodePtr->rightchild; // Reattach the rightchild subtree
			delete tempNodePtr;

		}
	}
	void displayInOrder(Node<T>* p)
	{
		if (p != NULL)
		{
			displayInOrder(p->leftchild);
			cout << p->data << " ";
			displayInOrder(p->rightchild);
		}
	}
	void displayPreOrder(Node<T>* p)
	{
		if (p != NULL)
		{
			cout << p->data << " ";
			displayPreOrder(p->leftchild);
			displayPreOrder(p->rightchild);
		}
	}
	void displayPostOrder(Node<T>* p)
	{
		if (p != NULL)
		{
			displayPostOrder(p->leftchild);
			displayPostOrder(p->rightchild);
			cout << p->data << " ";
		}
	}
	int checkheight(Node<T>* r)
	{
		if (r == NULL)//if the tree doesn't exits returns -1
		{
			return -1;
		}

		int leftchild = checkheight(r->leftchild);//checking for the height of left subtree recursively
		int rightchild = checkheight(r->rightchild);//checking for the height of right subtree recursively


		//returns the height of the tree
		if (leftchild > rightchild)
		{
			return leftchild + 1;
		}
		else
		{
			return rightchild + 1;
		}
	}
	void createtree(int arr[], int low, int high)
	{
		/*
		* Function to create a tree with minimal height
		*/
		if (low > high)//base case
		{
			return;
		}

		int middle = (low + high) / 2;

		insertNode(arr[middle]);//root of the tree

		createtree(arr, low, middle - 1);
		createtree(arr, middle + 1, high);
	}

public:
	IntBinaryTree()
	{
		root = NULL;
	}
	~IntBinaryTree()
	{
		//destroySubTree(root);
	}
	void insertNode(int num)
	{
		Node<T>* newNode, * nodePtr; // Pointer to create new node & traverse tree

		newNode = new Node<T>; // Create a new node
		newNode->data = num;
		newNode->leftchild = newNode->rightchild = NULL;

		if (!root) root = newNode; // If tree is empty.

		else { // Tree is not empty
			nodePtr = root;

			while (nodePtr != NULL) {

				if (num < nodePtr->data) { // Left subtree

					if (nodePtr->leftchild) { nodePtr = nodePtr->leftchild; }
					else { nodePtr->leftchild = newNode; break; }
				}

				else if (num > nodePtr->data) { // Right subtree

					if (nodePtr->rightchild) nodePtr = nodePtr->rightchild;
					else { nodePtr->rightchild = newNode; break; }
				}
				else { cout << "Duplicate data found in tree.\n"; break; }
			}

		}
	}
	bool find(int num)
	{
		// The function starts from the root

		Node<T>* nodePtr = root;

		while (nodePtr) {

			if (nodePtr->data == num)

				return true; // data is found

			else if (num < nodePtr->data)

				nodePtr = nodePtr->leftchild;

			else

				nodePtr = nodePtr->rightchild;
		}

		return false; // data not found
	}
	void remove(int num)
	{
		deleteNode(num, root);
	}
	void showNodesInOrder()
	{
		displayInOrder(root);
	}
	void showNodesPreOrder()
	{
		displayPreOrder(root);
	}
	void showNodesPostOrder()
	{
		displayPostOrder(root);
	}
	int createminimalheighttree(int arr[],int size)
	{
		int low = 0;
		int high = size - 1;
		createtree(arr, low, high);
		int h = checkheight(root);
		return h;
	}
};


int main()
{
	int arr[7] = { 1,2,3,4,5,6,7};
	IntBinaryTree<int> T;
	int h=T.createminimalheighttree(arr,7);
	if (h == -1)
	{
		cout << "Tree doesn't exit!" << endl;
	}
	else
	{
		cout << "Height of the tree is: " << h << endl;
	}
	T.showNodesInOrder();
	return 0;
}

