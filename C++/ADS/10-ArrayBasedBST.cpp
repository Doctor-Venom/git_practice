template <typename T>
class ArrayBasedBST
{
	struct Node
	{
		bool exist;
		T data;
	};
private:
	Node *arr;//array that contains nodes of the tree
	int maxSize;//max amount of nodes in this tree
	int count;//number of items in the tree
	int depth;//depth of a tree is the number of edges in the path from the root to the deepest leaf node
	int height;//height of a tree is the number of edges in the path from the deepest leaf to the root
public:
	ArrayBasedBST(int s = 1 << 20)
	{
		maxSize = s > 0 ? s : (1 << 20);
		arr = new Node[maxSize];
		{
			//this block initializes the tree with dummy nodes that has its attribute (exist) set to false to indicate that a node can be inserted in its place
			for (int i = 0; i < maxSize; ++i) { Node dummy; dummy.exist = false; arr[i] = dummy; }
		}
		count = 0;
		depth = 0;
		height = 0;
	}

	int depth_calculator(int cnt = -1, int index = 0)//utility function to calculate the depth of the tree recursively (can also be used to find the depth of a specific node)
	{
		if (index >= maxSize || arr[index].exist == false)//base case
		{ 
			if (cnt < 0)cnt = 0;
			return cnt;
		}
		cnt++;
		return max(depth_calculator(cnt, 2 * index + 1), depth_calculator(cnt, 2 * index + 2));//return the maximum depth between left subtree and right subtree
	}
	void add(T item)
	{
		if (count < maxSize)
		{
			Node temp;
			temp.data = item;
			temp.exist = true;
			if (arr[0].exist == false)//if the tree is empty
			{
				arr[0] = temp;
				++count;
				return;
			}
			else
			{
				int temp_depth = 0;
				int index = 0;
				while (index < maxSize && arr[index].exist != false)//maybe add && (temp_depth <= depth)
				{
					if (temp.data < arr[index].data)//if the value of new item less than the value of the current item go to the left child
					{
						index = (2 * index) + 1;//formula to go to the left child
						if (index >= maxSize) break;
						if (arr[index].exist == false) //if the current position is not used, insert the new node in it
						{
							arr[index] = temp; ++count;
							height = depth = depth_calculator();//after adding a node, the depth of the tree must be recalculated
							return; 
						}
					}
					else//if (temp.data >= arr[index].data) //if the value of new item is greater than or equal to the value of the current item go to the right chile
					{
						index = (2 * index) + 2;//formula to go to the right child
						if (index >= maxSize) break;
						if (arr[index].exist == false)//if the current position is not used, insert the new node in it
						{
							arr[index] = temp; ++count; 
							height = depth = depth_calculator();//after adding a node, the depth of the tree must be recalculated
							return;
						}
					}
					++temp_depth;//each loop we will go 1 level down, when temp depth becomes more than the depth of the tree, stop the loop
				}
			}
			int capacity = calc_current_capacity();
			int wasted = capacity < maxSize ? maxSize - count :  capacity - count;
			cerr << "There is no place in the tree for this item. try to run Red-Black-tree function then try again.\nwasted space can fit " << wasted <<" more items \n";
			return;
		}
		cerr << "The tree is full.\n";
	}

	int calc_current_capacity()//utility function to calculate the number of nodes that can fit into current level of tree (if count == current_capacity then the tree is a full binary tree)
	{		
		int current_capacity = 0;
		for (int i = 0; i <= depth; ++i)
			current_capacity += pow(2,i);
		return current_capacity;
	}
	T* collect_lost_nodes(int index, int &i)//utility function for distribute_lost_nodes() to collect lost nodes after deletion of their root node recursively
	{
		static T *lost = new T[maxSize];//static array that will contain lost nodes
		///[IS IT NECESSARY TO DELETE THE DYNAMICALLY ALLOCATED MEMEORY TO lost[]??? how to do it anyway? i need to be able to return it and process, then when called again have it cleared, but not cleared due to a recursive call]
		if (index >= maxSize || arr[index].exist == false)//base case
			return lost;
		lost[i++] = arr[index].data;//put the value of the node into the lost[] array and increment the iterator by 1 
		arr[index].exist = false;//then set its exist flag to false
		collect_lost_nodes(2 * index + 1, i);//goto elft child
		collect_lost_nodes(2 * index + 2, i);//goto right child
		return lost;
	}
	void distribute_nodes(int index)//utility function that is used when a node with a left child only is deleted
	{
		int i = 0;
		T *lost = collect_lost_nodes(index,i);
		//after collecting all lost nodes, insert them again into the tree
		for (int j = 0; j < i; ++j)
		{
			add(lost[j]);
			--count;//because we didnt add a new node, we just redistributed them, and the add() function will increment count, so we will decrement it to keep it constant
		}
	}
	int search_for_min_val(int index, int &min_index, bool recursion_depth = 0)//utility function to search for the minimum value in a BST recursively 
	{
		static T MIN = arr[index].data;
		if (recursion_depth == 0) MIN = arr[index].data;//important! the MIN variable will keep its last value after executing this function, so we need to renew it each time this function is invoked from another function not by recursion
		if (index >= maxSize || arr[index].exist == false)//base case
			return MIN;
		if (arr[index].data < MIN && arr[index].exist != false) { MIN = arr[index].data; min_index = index; }
		return MIN = min(MIN, min(search_for_min_val(2 * index + 1, min_index, 1), search_for_min_val(2 * index + 2, min_index, 1)));
	}
	void remove(int index = 0)//if the removed Node has left and right children the left becomes the parent of the right, if it has only one children, it becoms the parent
	{
		if (count > 0)
		{
			if (index >= 0 && index < calc_current_capacity() && index < maxSize)//if the index between 0 and the last index in the current level [note that if capacity is 31 (4 levels) then the last index is 30]
			{
				if (arr[index].exist == false) { cerr << "The specified index is empty.\n"; return; }
				else//if an item exists in the specified index then proceed with deletinon
				{
					if (arr[index * 2 + 2].exist == true)//if the node has a sub-tree on the right (no matter if it has a left sub-tree or not)
					{
						//replace the value of the node to be deleted by the minimum value in the right subtree, then set the exist flag of the node of the minimum value in the rght subtree to false
						int min_index = index * 2 + 2;//initialize the index of minimum value to the root of the right subtree
						T MIN = search_for_min_val(index * 2 + 2, min_index);//declare a variable that will be the minimum value in a BST and call the function to find the minimum value
						//this will cause problems(all children of MIN node will be lost)//arr[min_index].exist = false;//set the exist flag of the node in the index of minimum value to false
						remove(min_index); ++count;//recursive call to remove the node in the min_index, count incremented because the recursive call will decrement it, although we didnt actually delete it but moved it
						arr[index].data =  MIN;//replace the value in the node to be deleted by the minimum value in the right subtree
					}
					else if (arr[index * 2 + 1].exist == true)//if the node has a left child only, redistribute it
					{
						arr[index].exist = false;//set the exist flag of the node in the specified index to be false (logically deleted)
						distribute_nodes(index * 2 + 1);//redistribute all nodes in the left subtree
					}
					else//if it does not have any children (it is a leaf node), just set its exist-flag to false
					{
						arr[index].exist = false;
					}
					--count;
					height = depth = depth_calculator();//after deleting a node, the depth of the tree must be recalculated
				}
			}
		}
	}
	void remove_item(T item) { remove(search(item)); }
	void search(T item, int index = 0)
	{
		if (index >= maxSize || arr[index].exist == false)//base case
			return -1e8;
		if (arr[index].data == item) { return index; }//base case
		int L = search(item, 2 * index + 1);//go left
		if (L >= 0 && L < maxSize) return L;//if found on the left, return it
		int R = search(item, 2 * index + 2);//else go search on the right
		if (R >= 0 && R < maxSize) return R;//if found on the right return it
		return -1e8;//if not found neither on the left nor on the right, return negative infinite
	}
	void red_black_tree()
	{
		///under construction...
	}
	void print_preorder_traversal(int index = 0)//VLR
	{
		if (arr[0].exist == false) { cout << "The tree is empty.\n"; return; }
		if (index >= maxSize || arr[index].exist == false) return;//base case
		cout << arr[index].data << " ";//visit
		print_preorder_traversal(index * 2 + 1);//left
		print_preorder_traversal(index * 2 + 2);//right
	}
	void print_inorder_traversal(int index = 0)//LVR
	{
		if (arr[0].exist == false) { cout << "The tree is empty.\n"; return; }
		if (index >= maxSize || arr[index].exist == false) return;//base case
		print_inorder_traversal(index * 2 + 1);//left
		cout << arr[index].data <<  " ";//visit
		print_inorder_traversal(index * 2 + 2);//right
	}
	void print_postorder_traversal(int index = 0)//LRV
	{
		if (arr[0].exist == false) { cout << "The tree is empty.\n"; return; }
		if (index >= maxSize || arr[index].exist == false) return;//base case
		print_postorder_traversal(index * 2 + 1);//left
		print_postorder_traversal(index * 2 + 2);//right
		cout << arr[index].data <<  " ";//visit
	}
	void clear_tree(int index = 0)
	{
		if (index >= maxSize) return;//base case
		arr[index].exist = false;
		clear_tree(index * 2 + 1);
		clear_tree(index * 2 + 2);
	}
	void tree_brief()
	{
		cout << "[+] COUNT: " << count << endl;
		cout << "[+] DEPTH/HEIGHT: " << depth << endl;
		cout << "[+] MAX SIZE: " << maxSize << endl;
		cout << "[+] ROOT: " << arr[0].data << " EXISTANCE: " << arr[0].exist << endl;
	}
};