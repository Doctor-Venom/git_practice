template <typename T>
class CircularLinkedList
{
	struct CNode
	{
		T data;
		CNode *next;
	};
private:
	CNode *head;
	int length;
public:
	CircularLinkedList() { head = NULL; length = 0; }
	bool is_empty() { if (head == NULL) return true; return false; }
	void insert(T item)
	{
		CNode *temp = new CNode;
		temp->data = item;
		temp->next = NULL;

		if (is_empty())//the item will be added at the first position and point at itself
		{
			head = temp;
			temp->next = temp;
		}
		else if (length == 1)//if(head->next == head)//the item will be added at the second position and point at the first item 
		{
			temp->next = head;
			head->next = temp;
		}
		else//the item will be added at the second position and point at the third item (which was the second before adding new item)
		{
			temp->next = head->next;
			head->next = temp;
		}
		++length;
	}
	void insert_at(T item, int index)//index is the position (0->first, 1->second and so on)
	{
		if (index >= 0 && index <= length)
		{
			if (index == 1)//if it is to be at the second position, we already have a function for that
				insert(item);
			else//if it is not in the second position
			{
				CNode *temp = new CNode;
				temp->data = item;
				temp->next = NULL;
				if (index == 0)//if it is to be inserted in the first position, we point the head and the last item at it and make it point at the previously first Node
				{
					CNode *current = head;
					while (current->next != head)//locate the last item first, to make it point at the temp node
						current = current->next;
					current->next = temp;//last item points at new node
					temp->next = head;//new node points at first node
					head = temp;//head points at the new node
				}
				else if (index == length)
				{
					CNode *current = head;
					while (current->next != head)//loop until the last node
						current = current->next;
					temp->next = head;//last node points at the first node
					current->next = temp;//prevoiusly last item points at the new item
				}
				else
				{
					CNode *current = head;
					for (int i = 0; i < index - 1; ++i)//loop until the item before the index, to put the new node in the index position
						current = current->next;
					temp->next = current->next;//new item points at the next position
					current->next = temp;//previous item points at new item
				}
				++length;//this should  be exactly in this scope
			}
		}
		else
			cerr << (char)7 << "Index is out of range.\n";
	}
	void remove()
	{
		if (!is_empty())//deletion occurs at the second item
		{
			CNode *current = head->next;//temporary pointer that points at the second element
			head->next = current->next;//head points at the third element
			delete current;//delete the second element
			--length;
		}
		else
			cerr << (char)7 << "The list is empty.\n";
	}
	void remove_at(int index)
	{
		if (!is_empty())
		{
			if (index >= 0 && index <= length)
			{
				if (index == 1)//if the position to delete is the second item, we already have a function for that
					remove();
				else//if it is not in the second item
				{
					if (index == 0)//if the first item is to be deleted
					{
						CNode *current = head;
						while (current->next != head)//locate the last item first, to make it point at the second node
							current = current->next;
						current->next = head->next;//last item points at second item
						delete head;//delete the first node
						head = current->next;//make the head points at the second node(which became the first node after deletion)

					}
					else if (index == length)
					{
						CNode *current = head;
						while (current->next->next != head)//loop until the node before the last node
							current = current->next;
						delete current->next;//delete the last node
						current->next = head;//make the node before the last node point at the first node
					}
					else
					{
						CNode *current = head;
						for (int i = 0; i < index - 1; ++i)//loop until the item before the index, to delete the node after it
							current = current->next;
						CNode *temp = current->next;//create a temporary pointer that points at the node that will be deleted
						current->next = temp->next;//make the node before the temp point at the node after temp
						delete temp;//delete temp
					}
					--length;//this should  be exactly in this scope
				}
			}
			else
				cerr << (char)7 << "Index is out of range.\n";
		}
		else
			cerr << (char)7 << "The list is empty.\n";

	}
	int search(T item)
	{
		CNode *current = head;
		for (int i = 0; i < length; ++i)
		{
			if (current->data = item)
				return i;
			current = current->next;
		}
		return -1;
	}
	void delete_item(T item) { delete_at(search(item)); }
	void print()
	{
		if (is_empty())
			cerr << (char)7 << "The list is empty, nothing to print.\n";
		else
		{
			CNode *current = head;
			for (int i = 0; i < length; ++i)
			{
				cout << current->data << "~";
				current = current->next;
			}
			cout << "....." << endl;
		}
	}
	void merge(CircularLinkedList l)
	{
		CNode *current1 = head, *current2 = l.head;
		while (current1->next != head)//loop until reaching the last node in list1
			current1 = current1->next;
		while (current2->next != l.head)//loop until reahcing the last node in list2
			current2 = current2->next;
		current1->next = l.head;//make the last item of list1 point at the first item of list2
		current2->next = head;//make the last item of list2 point at the first item of list1
		length += l.length;//sum up length of list1 and list2
	}
	void destroy()
	{
		CNode *previous, *current = head;
		while (length--)
		{
			previous = current;
			current = current->next;
			delete previous;
		}
		head = NULL;
	}
};