template <typename T>
class ListBasedStack
{
	struct Node
	{
		T data;
		Node *next;
	};
private:
	Node *Top;
	int length;

public:
	ListBasedStack()
	{
		Top = NULL;
		length = 0;
	}
	ListBasedStack(ListBasedStack& that)//copy constructor to be able to make a copy of the current stack to make an operation like printing etc...
	{
		if (this != &that)
		{
			ListBasedStack temp;
			while (!that.is_empty())
				temp.push(that.pop());
			while (!temp.is_empty())
			{
				(*this).push(temp.top());
				that.push(temp.pop());
			}
		}
	}
	ListBasedStack& operator=(ListBasedStack& that)
	{
		if (this != &that)
		{
			ListBasedStack temp;
			while (!that.is_empty())
				temp.push(that.pop());
			while (!temp.is_empty())
			{
				(*this).push(temp.top());
				that.push(temp.pop());
			}
		}
		return *this;
	}
	bool is_empty() { if (Top == NULL) return true; return false; }
	void push(T item)
	{
		Node *temp = new Node;
		temp->data = item;
		temp->next = Top;
		Top = temp;
		++length;
	}
	T pop()
	{
		if (!is_empty())
		{
			Node *temp = Top;
			T data = Top->data;
			Top = Top->next;
			delete temp;
			if (!--length) Top = NULL;
			return data;
		}
		else cerr << (char)7 << "The stack is empty.\n";
	}
	T top() { return Top->data; }
	void print()
	{
		if (!is_empty())
		{
			ListBasedStack temp(*this); cout << "[TOP][";
			while (!temp.is_empty())
			{
				cout << temp.pop() << "][";
			}
			cout << "_]\n";
		}
		else
			cerr << (char)7 << "The stack is empty.\n";
	}
	//
	void clear_stack()
	{
		Node *temp;
		while (!is_empty())
		{
			temp = Top;
			Top = Top->next;
			delete temp;
			if (!--length) Top = NULL;
		}
	}
	bool search(T item) 
	{
		ListBasedStack temp(*this);
		while (!temp.is_empty())
			if (temp.pop() == item)
				return true;
		return false;
	}
	T most_repeated_element() 
	{
		ListBasedStack temp(*this);
		T *arr = new T[temp.length];
		int i = 0, MRC = 0;
		T MRE;
		while (!temp.is_empty())
			arr[i++] = temp.pop();
		for (i = 0; i < length; ++i)
		{
			int repeats = 1;
			for (int j = 0; j < length; ++j)
				if (arr[i] == arr[j]) ++repeats;
			if (repeats > MRC) { MRC = repeats;	MRE = arr[i]; }
		}
		return MRE;
	}
	void del_MRE()
	{
		ListBasedStack temp(*this);
		temp.reverse();
		T MRE = most_repeated_element();
		clear_stack();
		while (!temp.is_empty())
		{
			if (temp.top() != MRE) push(temp.pop());
			else temp.pop();
		}
	}
	bool is_prime(int val)
	{
		for (int i = 2; i <= val / 2; i++)
			if (!(val % i)) return false;
		return true;
	}
	void del_primes()
	{
		ListBasedStack temp(*this);
		temp.reverse();
		clear_stack();
		while (!temp.is_empty())
		{
			if (!is_prime(temp.top())) push(temp.pop());
			else temp.pop();
		}
	}
	void del_max()
	{
		ListBasedStack temp(*this);
		temp.reverse();
		T MAX = top();
		while (!is_empty()) if (top() > MAX) MAX = pop(); else pop();//find max value and clear the actual stack
		while (!temp.is_empty())//insert all items that is in temp stack that are not the max value to the actual stack
		{
			if (temp.top() != MAX) push(temp.pop());
			else temp.pop();
		}
	}
	void reverse()
	{
		ListBasedStack temp(*this);
		clear_stack();
		while (!temp.is_empty()) push(temp.pop());
	}
	void del_redundant()
	{
		ListBasedStack temp(*this);
		temp.reverse();
		clear_stack();
		while (!temp.is_empty())
		{
			if (this->search(temp.top()))//if the item is found in the stack pop it out without inserting
				temp.pop();
			else//if the item is not found in the stack then insert it
				this->push(temp.pop());
		}
	}
	//
};