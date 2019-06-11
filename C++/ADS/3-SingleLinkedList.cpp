template<typename T>
class LinkedList
{
	struct Node
	{
		T data;
		Node *next;
	};
private:
	Node *head, *tail;
	int length;
public:
	LinkedList()
	{
		length = 0;
		head = NULL;
		tail = NULL;
	}

	bool is_empty()
	{
		if (head == NULL && tail == NULL && length == 0)
			return true;
		else
			return false;
	}

	void insert_front(T item)
	{
		Node *temp = new Node;
		temp->data = item;
		if (is_empty())
		{
			head = temp;
			tail = temp;
			temp->next = NULL;
		}
		else
		{
			temp->next = head;
			head = temp;
		}
		length++;
	}

	void insert_end(T item)
	{
		Node *temp = new Node;
		temp->data = item;
		temp->next = NULL;
		if (is_empty())
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		length++;
	}

	void insert_at(T item, int index)
	{
		if (index < 0 || index > length)
		{
			cerr << static_cast<char>(7) << "List index out of range.\n";
			return;
		}
		Node *temp = new Node;
		temp->data = item;
		if (index == 0)
			insert_front(item);
		else if (index == length)
			insert_end(item);
		else
		{
			Node *previous = NULL, *current = NULL;
			current = head;
			for (int i = 0; i < index; i++)
			{
				previous = current;
				current = current->next;
			}
			temp->next = current->next;
			current->next = temp;
		}
		length++;
	}

	void remove_front()
	{
		if (!is_empty())
		{
			if (head == tail)//if there is only one item in the list
			{
				delete head;
				head = NULL;
				tail = NULL;
			}
			else
			{
				Node *temp = NULL;
				temp = head;
				head = head->next;
				delete temp;
			}
			length--;
		}
		else
			cerr << static_cast<char>(7) << "List is empty.\n";
	}

	void remove_end()
	{
		if (!is_empty())
		{
			if (head == tail)//if there is only one item in the list
			{
				delete tail;
				head = NULL;
				tail = NULL;
			}
			else
			{
				Node *previous = NULL, *current = NULL;
				current = head;
				for (int i = 0; i < length; ++i)
				{
					previous = current;
					current = current->next;
				}
				previous->next = NULL;
				tail = previous;
				delete current;
			}
			length--;
		}
		else
			cerr << static_cast<char>(7) << "List is empty.\n";
	}

	void remove_at(int index)
	{
		if (index < 0 || index > length)
		{
			cerr << static_cast<char>(7) << "List index out of range.\n";
			return;
		}
		if (head == tail)//if there is only one item in the list
		{
			delete tail;
			head = NULL;
			tail = NULL;
		}
		else
		{
			Node *previous = NULL, *current = NULL;
			current = head;
			for (int i = 0; i < index; ++i)
			{
				previous = current;
				current = current->next;
			}
			previous->next = NULL;
			tail = previous;
			delete current;
		}
		length--;
	}

	int search(T item)
	{
		int index = 0;
		Node *previous = NULL, *current = NULL;
		current = head;
		while (index != length)
		{
			if (current->data == item) return index;
			previous = current;
			current = current->next;
			index++;
		}
		return -1;
	}

	void delete_item(T item)
	{
		remove_at(search(item));
	}

	void print()
	{
		Node *previous = NULL, *current = NULL;
		current = head;
		for (int i = 0; i < length; ++i)
		{
			cout << current->data << "-";
			previous = current;
			current = current->next;
		}
		cout << "NULL" << endl;
	}

	void merge(LinkedList l)
	{
		if (head == l.head)
		{
			cerr << (char)7 << "Error! cant merge a list with itself.\n";
			return;
		}
		if (!is_empty())
		{
			tail->next = l.head;
			tail = l.tail;
			length += l.length + 1;
		}
		else
		{
			head = l.head;
			tail = l.tail;
			length = l.length;
		}
	}

	void destroy()//if a merged list is destroyed, the second list should not be accessed after destroying because its items will be deleted and will cause an error when trying to fetch the next pointer of an element.
	{
		if (!is_empty())
		{
			Node *previous = NULL, *current = NULL;
			current = head;
			while (current != NULL)
			{
				previous = current;
				current = current->next;
				delete previous;
			}
			head = NULL;
			tail = NULL;
			length = 0;
		}
		else
			cerr << "List is empty.\n";
	}

	//
	bool is_prime(int item)
	{
		for (int i = 2; i <= item / 2; i++)
			if (item%i == 0)
				return false;
		return true;
	}
	void delete_primes()
	{
		if (!is_empty())
		{
			Node *previous = NULL, *current = head;
			while (current != NULL)
			{
				if (is_prime(current->data))
				{
					if (current == head)
					{
						head = head->next;
						delete current;
						current = head;
						length--;
						continue;
					}
					else
					{
						Node *temp = current;
						previous->next = current->next;
						previous = current;
						current = current->next;
						delete temp;
						length--;
						continue;
					}
				}
				previous = current;
				current = current->next;
			}
		}
	}
	LinkedList Union(LinkedList &l)
	{
		Node *current_1 = head, *current_2 = l.head;
		LinkedList NEW;
		while (current_1 != NULL)
		{
			if (NEW.search(current_1->data) == -1)
				NEW.insert_end(current_1->data);
			current_1 = current_1->next;
		}
		while (current_2 != NULL)
		{
			if (NEW.search(current_2->data) == -1)
				NEW.insert_end(current_2->data);
			current_2 = current_2->next;
		}
		return NEW;
	}
	LinkedList Intersection(LinkedList &l)
	{
		Node *current_1 = head, *current_2 = l.head;
		LinkedList NEW;
		while (current_1 != NULL)
		{
			if (l.search(current_1->data) == -1)
				NEW.insert_end(current_1->data);
			current_1 = current_1->next;
		}
		while (current_2 != NULL)
		{
			if (search(current_2->data) == -1)
				NEW.insert_end(current_2->data);
			current_2 = current_2->next;
		}
		return NEW;
	}
	void del_max()
	{
		Node *previous = NULL, *current = head;
		int max = (T)0;
		while (current != NULL)
		{
			current->data > max ? max = current->data : 1;
			current = current->next;
		}
		current = head;
		while (current != NULL)
		{
			if (current->data == max)
			{
				if (current == head)
				{
					head = head->next;
					delete current;
					length--;
					current = head;
					continue;
				}
				else
				{
					previous->next = current->next;
					delete current;
					current = previous->next;
					length--;
					continue;
				}
			}
			previous = current;
			current = current->next;
		}
	}
};