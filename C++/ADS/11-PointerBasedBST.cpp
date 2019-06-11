template <typename T>
class PointerBasedBST
{
	struct Node
	{
		T data;
		Node *parent;
		Node *left;
		Node *right;
	};
private:
	Node *root;//pointer to the root node
	int count;//number of items in the tree
	int depth;//depth of a tree is the number of edges in the path from the root to the deepest leaf node
	int height;//height of a tree is the number of edges in the path from the deepest leaf to the root
public:
	PointerBasedBST()
	{
		root = NULL;
		count = 0;
	}

	void add(T item)
	{
		Node *temp = new Node;
		temp->data = item;
		temp->left = NULL;
		temp->right = NULL;
		if (root == NULL)//if the tree is empty
		{
			temp->parent = NULL;
			root = temp;
			++count;
			return;
		}
		else
		{
			Node *current = root;
			while (1)
				if (temp->data < current->data)//if the value of new item less than the value of the current item go to the left child
				{
					if (current->left == NULL) { temp->parent = current; current->left = temp; break; }
					else current = current->left;

				}
				else//if (temp->data >= current->data) //if the value of new item is greater than or equal to the value of the current item go to the right child
				{
					if (current->right == NULL) { temp->parent = current; current->right = temp; break; }
					else current = current->right;
				}
			++count;
		}
	}

	Node* search_for_min_val(Node *subroot, Node *min)//utility function to search for the minimum value in a BST recursively 
	{
		if (subroot->data <= min->data)
			min = subroot;
		if (subroot == NULL || (subroot->left == NULL && subroot->right == NULL))//base case
			return min;
		Node *L_min, *R_min;
		if (subroot->left != NULL) L_min = search_for_min_val(subroot->left, min); else { L_min = new Node; L_min->data = 1e9; }
		if (subroot->right != NULL) R_min = search_for_min_val(subroot->right, min); else { R_min = new Node; R_min->data = 1e9; }
		if (L_min->data <= R_min->data) return L_min;
		else return R_min;
	}
	void remove(Node *todel)//function to remove a node from the tree, there are 3 cases: (1)mama has no children, (2)mama has left child only, (3)mama has 2 children
	{
		if (count > 0 && todel != NULL)//if the tree is not empty
		{
			if (todel->right != NULL)//if the node has a sub-tree on the right (no matter if it has a left sub-tree or not)
			{
				//replace the value of the node to be deleted by the minimum value in the right subtree, then remove the node with miniumum value recursively
				Node *MIN = search_for_min_val(todel->right, todel->right);//declare a variable Node that will store the minimum value in a BST and call the function to find the minimum value
				//this will cause problems(all children of MIN node will be lost) so we need to call the function recursively to ensure proper deletion of the MIN node
				todel->data = MIN->data;//replace the value in the node to be deleted by the minimum value in the right subtree
				remove(MIN); ++count;//recursive call to remove the node in the min_index, count incremented because the recursive call will decrement it, although we didnt actually delete it but moved it
			}
			else if (todel->left != NULL)//if the node has a left child only
			{
				if (todel == root)
				{
					Node *temp = root;
					root = root->left;
					delete temp;
					root->parent = NULL;
				}
				else
				{
					Node *mama = todel->parent;
					if (mama->left == todel) { mama->left = todel->left; delete todel; }
					else if (mama->right == todel) { mama->right = todel->left; delete todel; }
				}

			}
			else//if it does not have any children (it is a leaf node), just delete it
			{
				if (todel == root)
					delete root;
				else
				{
					Node *mama = todel->parent;
					if (mama->left == todel) { delete todel; mama->left = NULL; }
					else if (mama->right == todel) { delete todel; mama->right = NULL; }
				}

			}
			--count;
			if (count == 0) root = NULL;
		}
	}
	void remove_item(T item) { remove(search(item, root)); }
	Node* search(T item, Node *current)
	{
		if (current == NULL)//base case
			return NULL;
		if (current->data == item) { return current; }//base case
		return search(item, current->left);//go left
		return search(item, current->right);//go right
	}
	void red_black_tree()
	{
		///under construction...
	}
	void print_preorder_traversal(Node *current)//VLR
	{
		if (root == NULL) { cout << "The tree is empty.\n"; return; }
		if (current == NULL) return;//base case
		cout << current->data << " ";//visit
		print_preorder_traversal(current->left);//left
		print_preorder_traversal(current->right);//right
	}
	void print_inorder_traversal(Node *current)//LVR
	{
		if (root == NULL) { cout << "The tree is empty.\n"; return; }
		if (current == NULL) return;//base case
		print_inorder_traversal(current->left);//left
		cout << current->data << " ";//visit
		print_inorder_traversal(current->right);//right
	}
	void print_postorder_traversal(Node *current)//LRV
	{
		if (root == NULL) { cout << "The tree is empty.\n"; return; }
		if (current == NULL) return;//base case
		print_postorder_traversal(current->left);//left
		print_postorder_traversal(current->right);//right
		cout << current->data << " ";//visit
	}
	void clear_tree(Node *current)
	{
		if (current == NULL) return;//base case
		clear_tree(current->left);
		clear_tree(current->right);
		delete current;
	}
	Node* get_root()
	{
		return root;
	}
};

int main()
{
	PointerBasedBST<int> t;
	int arr[] = { 15,6,65,9,4,15,32,98,75,-15 };
	int arr2[] = { 9,20,3,5,8,4,9,12,6,54 };

	for (int i = 0; i < 10; i++)
		t.add(arr[i]);

	t.print_inorder_traversal(t.get_root()); cout << endl;
	cout << endl;

	for (int i = 0; i < 10; i++)
		t.remove(t.get_root());
	t.print_inorder_traversal(t.get_root()); cout << endl;
	cout << endl;
	//t.clear_tree();

	for (int i = 0; i < 10; i++)
		t.add(arr2[i]);
	t.print_inorder_traversal(t.get_root()); cout << endl;	 cout << endl;
	for (int i = 0; i < 10; i++)
		t.remove(t.get_root());

	t.print_inorder_traversal(t.get_root()); cout << endl;
}