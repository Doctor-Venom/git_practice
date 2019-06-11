template<typename T>
class SortedArrayBasedList
{
private:
	T *list;
	int length;
	long long int max_size;
public:
	SortedArrayBasedList(long long int s = 1e5)
	{
		s > 0 ? max_size = s : max_size = 1e5;
		list = new T[max_size];
		length = 0;
	}

	bool is_full() { return length == max_size; }

	bool is_empty() { return length == 0; }

	void insert(T item)//insert method that search for appropriate position for the item using binary search and thereforce reducing running time.
	{
		if (!is_full())
		{
			//searching for appropriate position
			int i = 0, j = length, index;
			if (length == 0)
				index = 0;
			else if (item == list[i])
				index = 0;
			else if (item == list[j - 1])
				index = length;
			else
			{
				while (i < j)
				{
					int mid = (i + j) / 2;
					if (item == list[mid])
					{
						//maybe just make this throw an error stating that the item already exists in the list?
						//cerr << "[-]ERROR: Unable to insert. Reason: Item already in the list.\n";
						//return;
						index = mid;
						goto out;
					}
					else if (item > list[mid])
						i = mid + 1;
					else if (item < list[mid])
						j = mid;
				}
				index = i;
			}
		out:
			//shifting items to the right
			if (index != length)
				for (int l = length; l > index; l--)
					list[l] = list[l - 1];
			list[index] = item;
			length++;
		}
		else cerr << "[-]ERROR: Unable to insert. Reason: List is full.\n";
	}

	void remove_end()
	{
		if (!is_empty()) length--;
		else cerr << "[-]ERROR: Unable to remove. Reason: List is empty.\n";
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

	int search(T item)//binary search - complexity: O(log(n))
	{
		int i = 0, j = length - 1;
		if (item == list[i])
			return i;
		else if (item == list[j])
			return j;
		else
			while (i <= j)
			{
				int mid = (i + j) / 2;
				if (item == list[mid])
					return mid;
				else if (item > list[mid])
					i = mid + 1;
				else if (item < list[mid])
					j = mid;
			}
		return -1;
	}

	int interpolation_search(T item)
	{
		int lo = 0, hi = length - 1, mid;
		while (lo < hi)
		{
			mid = lo + ((lo + hi) / (list[lo] - list[hi]))*(item - list[lo]);
			if (list[mid] == item) return mid;
			else
			{
				if (list[mid] < item) lo = mid + 1;
				else if (list[mid] > item) hi = mid - 1;
			}
		}
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