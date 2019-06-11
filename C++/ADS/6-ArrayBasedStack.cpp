template <typename T>
class ArrayBasedStack
{
private:
	T *Stack;
	int Top, maxSize;

public:
	ArrayBasedStack(int s = 100)
	{
		maxSize = s > 0 ? s : 100;
		Top = 0;
		Stack = new T[maxSize];
	}
	ArrayBasedStack(ArrayBasedStack& that)//[very important] copy constructor to be able to make a copy of the current stack to make an operation like printing etc...
	{
		if (this != &that)
		{
			maxSize = that.maxSize;
			Top = 0;
			Stack = new T[maxSize];
			ArrayBasedStack temp(that.maxSize);
			while (!that.is_empty())
				temp.push(that.pop());
			while (!temp.is_empty())
			{
				(*this).push(temp.top());
				that.push(temp.pop());
			}
		}
	}
	bool is_empty() { if (Top == 0) return true; return false; }
	bool is_full() { if (Top == maxSize) return true; return false; }
	void push(T item)
	{
		if (!is_full()) Stack[Top++] = item;
		else cerr << (char)7 << "The stack is full.\n";
	}
	T pop()
	{
		if (!is_empty()) return Stack[--Top];
		else cerr << (char)7 << "The stack is empty.\n";
	}
	T top() { return Stack[Top-1]; }
	void print()
	{
		if (!is_empty())
		{
			ArrayBasedStack temp(*this); cout << "[TOP]["; //ArrayBasedStack temp = *this;
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
	void clear_stack() { Top = 0; }
	bool search(T item) 
	{
		ArrayBasedStack temp(*this);
		while (!temp.is_empty())
			if (temp.pop() == item) return true;
		return false;
	}
	T most_repeated_element() 
	{
		ArrayBasedStack temp(*this);
		T *arr = new T[temp.maxSize];
		int i = 0;
		while (!temp.is_empty())
			arr[i++] = temp.pop();
		int MRC = 0, MRE = 0;
		for (int i = 0; i < Top; i++)
		{
			int repeats = 1;
			for (int j = 0; j < Top; j++)
				if (arr[i] == arr[j])
					++repeats;
			if (repeats > MRC)
			{
				MRC = repeats;
				MRE = arr[i];
			}
		}
		return MRE;
	}
	void del_MRE()
	{
		ArrayBasedStack temp(*this);
		temp.reverse();
		T MRE = most_repeated_element();
		clear_stack();
		while (!temp.is_empty())
		{
			if (temp.top() != MRE)
				push(temp.pop());
			else
				temp.pop();
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
		ArrayBasedStack temp(*this);
		temp.reverse();
		clear_stack();
		while (!temp.is_empty())
		{
			if (!is_prime(temp.top()))
				push(temp.pop());
			else
				temp.pop();
		}
	}
	void del_max()
	{
		ArrayBasedStack temp(*this);
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
		ArrayBasedStack temp(*this);
		clear_stack();
		while (!temp.is_empty())
			push(temp.pop());
	}
	void del_redundant()
	{
		ArrayBasedStack temp(*this);
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