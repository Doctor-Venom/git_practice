template<typename T>
class DoublyLinkedList
{
	struct DNode
	{
		T data;
		DNode *next;
		DNode *prev;
	};
private:
	DNode *head, *tail;
	int length;

public:
	DoublyLinkedList()//constructor
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
		DNode *temp = new DNode;
		temp->data = item;
		temp->prev = NULL;
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
		DNode *temp = new DNode;
		temp->data = item;
		temp->next = NULL;
		temp->prev = tail;
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
		DNode *temp = new DNode;
		temp->data = item;
		if (index == 0)
			insert_front(item);
		else if (index == length-1)
			insert_end(item);
		else
		{
			DNode *previous = NULL, *current = NULL;
			current = head;
			for (int i = 0; i < index-1; i++)
			{
				previous = current;
				current = current->next;
			}
			temp->next = current->next;
			current->next = temp;
			temp->prev = current;
			temp->next->prev = temp;
			length++;
		}
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
				DNode *temp = head;
				head = head->next;
				head->prev = NULL;
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
				DNode *temp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
			}
			length--;
		}
		else
			cerr << static_cast<char>(7) << "List is empty.\n";
	}

	void remove_at(int index)
	{
		if (index >= 0 && index < length)
		{
			if (head == tail)//if there is only one item in the list
			{
				delete head;
				head = NULL;
				tail = NULL;
			}
			else
			{
				DNode *current = head;
				for (int i = 0; i < index; ++i)
					current = current->next;
				if (index == 0)
				{
					current->next->prev = NULL;
					head = current->next;
				}
				else if (index == length-1)
				{
					current->prev->next = NULL;
					tail = current->prev;
				}
				else
				{
					current->next->prev = current->prev;
					current->prev->next = current->next;
				}
				delete current;
				length--;
			}
		}
		else
			cerr << static_cast<char>(7) << "List index out of range.\n";
		
	}

	int search(T item)
	{
		int index = 0;
		DNode *current = head;
		while (index != length)
		{
			if (current->data == item) return index;
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
		DNode *current = head;
		if (current != NULL)
		{
			for (int i = 0; i < length; ++i)
			{
				cout << current->data << "=";
				current = current->next;
			}
		}
		cout << "NULL" << endl;
	}

	void merge(DoublyLinkedList l)
	{
		if (head == l.head || tail == l.tail)
		{
			cerr << (char)7 << "Error! cant merge a list with itself.\n";
			return;
		}
		if (!is_empty())
		{
			tail->next = l.head;
			l.head->prev = tail;
			tail = l.tail;
			length += l.length; //+ 1 ?
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
			DNode *previous = NULL, *current = NULL;
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
			DNode *previous = NULL, *current = head;
			while (current!=NULL)
			{
				if (is_prime(current->data))
				{
					if (current == head)//if it is the first item
					{
						if (head == tail)//if it is the only item in the list
						{
							head = NULL;
							tail = NULL;
						}
						else//if there are more nodes in the list that are after the current node
						{
							head = head->next;
							head->prev = NULL;
						}
						delete current;
						current = head;
						length--;
						continue;
					}
					else if (current == tail)//if it is the last item
					{
						if (head == tail)//if it is the only item in the list
						{
							head = NULL;
							tail = NULL;
						}
						else//if there are more nodes in the list that are before the current node
						{
							tail = tail->prev;
							tail->next = NULL;
						}
						delete current;
						length--;
						break;//current reached the last node and iteration must stop
					}
					else//if it is an item in the mid
					{
						DNode *temp = current;
						current = current->next;
						temp->next->prev = temp->prev;
						temp->prev->next = temp->next;
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

	DoublyLinkedList Union(DoublyLinkedList &l)
	{
		DNode *current_1 = head, *current_2 = l.head;
		DoublyLinkedList NEW;
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
	DoublyLinkedList Intersection(DoublyLinkedList &l)
	{
		DNode *current_1 = head, *current_2 = l.head;
		DoublyLinkedList NEW;
		while (current_1 != NULL)
		{
			if (l.search(current_1->data) != -1)
				NEW.insert_end(current_1->data);
			current_1 = current_1->next;
		}
		while (current_2 != NULL)
		{
			if (search(current_2->data) != -1 && NEW.search(current_2->data) == -1)
				NEW.insert_end(current_2->data);
			current_2 = current_2->next;
		}
		return NEW;
	}
	void del_max()
	{
		DNode *previous=NULL, *current = head;
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
					head->prev = NULL;
					delete current;
					current = head;
					length--;
					continue;
				}
				else if (current == tail)
				{
					tail = tail->prev;
					tail->next = NULL;
					delete current;
					length--;
					break;
				}
				else
				{
					current->next->prev = current->prev;
					current->prev->next = current->next;
					previous = current->prev;
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
	
	int count(int item)
	{
		int cnt = 0;
		DNode *current = head;
		while (current != NULL)
		{
			if (current->data == item)
				cnt++;
			current = current->next;
		}
		return cnt;
	}

	void del_redundant()
	{
		if (!is_empty())
		{
			DNode *previous = NULL, *current = head;
			while (current != NULL)
			{
				if (count(current->data)>1)
				{
					if (current == head)//if it is the first item
					{
						if (head == tail)//if it is the only item in the list
						{
							head = NULL;
							tail = NULL;
						}
						else//if there are more nodes in the list that are after the current node
						{
							head = head->next;
							head->prev = NULL;
						}
						delete current;
						current = head;
						length--;
						continue;
					}
					else if (current == tail)//if it is the last item
					{
						if (head == tail)//if it is the only item in the list
						{
							head = NULL;
							tail = NULL;
						}
						else//if there are more nodes in the list that are before the current node
						{
							tail = tail->prev;
							tail->next = NULL;
						}
						delete current;
						length--;
						break;//current reached the last node and iteration must stop
					}
					else//if it is an item in the mid
					{
						DNode *temp = current;
						current = current->next;
						temp->next->prev = temp->prev;
						temp->prev->next = temp->next;
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
	//
};