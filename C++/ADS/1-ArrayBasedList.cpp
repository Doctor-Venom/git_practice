template<typename T>
class ArrayBasedList
{
private:
	T *list;
	int length;
	long long int max_size;
public:
	ArrayBasedList(long long int s = 1e5)
	{
		s > 0 ? max_size = s : max_size = 1e5;
		list = new T[max_size];
		length = 0;
	}

	bool is_full() { return length == max_size; }

	bool is_empty() { return length == 0; }

	void insert(T item)
	{	
		if (!is_full() && search(item) == -1)
			list[length++] = item;
		else cerr << "[-]ERROR: Unable to insert. Reason: List is full, or item (" << item << ") already exist in the list.\n";
	}
	void insert_end(T item) 
	{
		if (!is_full()) list[length++] = item;
		else cerr << "[-]ERROR: Unable to insert. Reason: List is full.\n";
	}

	void remove_end() 
	{
		if (!is_empty()) length--;
		else cerr << "[-]ERROR: Unable to remove. Reason: List is empty.\n";
	}

	void insert_front(T item)
	{
		if (!is_full()) 
		{
			for (int i = length++; i > 0; i--)
				list[i] = list[i - 1];
			list[0] = item;
		}
		else cerr << "[-]ERROR: Unable to insert. Reason: List is full.\n";
	}

	void remove_front()
	{
		if (!is_empty())
		{
			for (int i = 0; i < length - 1; i++)
				list[i] = list[i + 1];
			length--;
		}
		else
			cerr << "[-]ERROR: Unable to remove. Reason: List is empty.\n";
	}

	void insert_at(int index, T item)
	{
		if (!is_full() && (index >= 0 || index <= length))
		{
			for (int i = length++; i > index; i--)
				list[i] = list[i - 1];
			list[index] = item;
		}
		else cerr << "[-]ERROR: Unable to insert. Reason: List is full.\n";
	}

	void remove_at(int index)
	{
		if (!is_empty() && (index >= 0 && index <= length))
		{
			for (int i = index; i < length - 1; i++)
				list[i] = list[i + 1];
			length--;
		}
		else
			cerr << "[-]ERROR: Unable to remove at index (" << index << "). Reason: List is empty or list index out of range.\n";
	}

	int search(T item)
	{
		for (int i = 0; i < length; i++)
			if (list[i] == item) return i;
		return -1;
	}

	void print()
	{
		if (!is_empty())
		{
			for (int i = 0; i < length; i++)
				cout << list[i] << " ";
			cout << endl;
		}
	}
};