template <typename T>
class ListBasedQueue
{
	struct Node
	{
		T data;
		Node *next;
	};
private:
	Node *front, *rear;
	int length;
public:
	ListBasedQueue(int s = 10)
	{
		length = 0;
		front = NULL;
		rear = NULL;
	}
	bool is_empty() { return front == NULL; }
	void enqueue(T item)//insert at the end of the list
	{
		Node *temp = new Node;
		temp->data = item;
		temp->next = NULL;
		if (is_empty())
		{
			front = rear = temp;
		}
		else
		{
			rear->next = temp;
			rear = temp;
		}
		++length;
	}
	T dequeue()//remove from the begining of the list
	{
		if (!is_empty())
		{
			Node *temp = front;
			T data = front->data;
			front = front->next;
			delete temp;
			--length;
			return data;
		}
		else
			cerr << (char)7 << "The queue is empty.\n";
	}
	T Front() { if (!is_empty()) return front->data; else cerr << (char)7 << "The queue is empty.\n"; }
	T Rear() { if (!is_empty()) return rear->data; else cerr << (char)7 << "The queue is empty.\n"; }
	void print()
	{
		if (!is_empty())
		{
			Node *current = front;
			while (current != NULL)
			{
				cout << current->data << ":";
				current = current->next;
			}
			cout << ":\n";
		}
		else
			cerr << (char)7 << "The queue is empty.\n";
	}
};