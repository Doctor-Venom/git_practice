///BETTER VERSION WITH LOWER COMPLEXITY (its just awesome!)
template <typename T>
class ArrayBasedQueue
{
private:
	T *Queue;
	int front, rear, length;
	const int maxSize;
public:
	ArrayBasedQueue(int s = 10) :maxSize(s > 0 ? s : 10)
	{
		length = 0;
		front = 0;
		rear = maxSize - 1;
		Queue = new T[maxSize];
	}
	bool is_full() { return length == maxSize; }
	bool is_empty() { return length == 0; }
	void enqueue(T item)
	{
		if (!is_full())
		{
			Queue[++rear %= maxSize] = item;
			++length;
		}
		else
			cerr << (char)7 << "The queue is full.\n";
	}
	T dequeue()
	{
		if (!is_empty())
		{
			T data = Queue[front];
			++front %= maxSize;
			--length;
			return data;
		}
		else
			cerr << (char)7 << "The queue is empty.\n";
	}
	T Front() { if (!is_empty()) return Queue[front]; else cerr << (char)7 << "The queue is empty.\n"; }
	T Rear() { if (!is_empty()) return Queue[rear]; else cerr << (char)7 << "The queue is empty.\n"; }
	void print()
	{
		if (!is_empty())
		{
			int index = front;
			for (int i = 0; i < length; ++i)
			{
				cout << Queue[index] << ":";
				++index %= maxSize;
			}
			cout << ":\n";
		}
		else
			cerr << (char)7 << "The queue is empty.\n";
	}
};
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
///ANOTHER VERSION WITH HIGHER COMPLEXITY
template <typename T>
class ArrayBasedQueue
{
private:
	T *Queue;
	int length, maxSize;
public:
	ArrayBasedQueue(int s = 10)
	{
		length = 0;
		maxSize = s > 0 ? s : 10;
		Queue = new T[maxSize];
	}
	bool is_full() { return length == maxSize; }
	bool is_empty() { return length == 0; }
	void enqueue(T item)//adds an item at the end of the queue
	{
		if (!is_full())
			Queue[length++] = item;
		else
			cerr << (char)7 << "The queue is full.\n";
	}
	T dequeue()//removes an item from the begining of the queue and shift all items to the left by 1
	{
		if (!is_empty())
		{
			T data = Queue[0];
			for (int i = 0; i < length - 1; ++i)
				Queue[i] = Queue[i + 1];
			--length;
			return data;
		}
		else
			cerr << (char)7 << "The queue is empty.\n";
	}
	T Front() { if (!is_empty()) return Queue[0]; else cerr << (char)7 << "The queue is empty.\n"; }
	T Rear() { if (!is_empty()) return Queue[length-1]; else cerr << (char)7 << "The queue is empty.\n"; }
	void print()
	{
		if (!is_empty())
		{
			for (int i = 0; i < length; i++)
				cout << Queue[i] << ":";
			cout << ":\n";
		}
		else
			cerr << (char)7 << "The queue is empty.\n";
	}
};