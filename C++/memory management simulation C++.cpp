#include <iostream>
using namespace std;

class memory
{
public:
	static int frame_size;
	int memory_size;
	int numof_frames;
	memory(int x = 0)
	{
		memory_size = x;
		numof_frames = memory_size / frame_size;
	}
};

class process
{
	friend void MMU(process p, memory m);
private:
	int PID;
	int program_size;
	int numof_pages;
	int *page_table;
	int *base, limit;
	int offset_limit;
public:
	static int page_size;
	void set_data(int x, int y)
	{
		program_size = x;
		PID = y;
		numof_pages = program_size / page_size;
		page_table = new int[numof_pages];
		cout << "Define the page table for process " << PID  << endl;
		for (int i = 0; i < numof_pages; ++i)
		{
			cout << "page[" << i << "] in frame:";
			cin >> page_table[i];
		}
		base = page_table;
		limit = numof_pages;
		offset_limit = page_size;
	}
};

void MMU(process p, memory m)
{
	cout << "________________________________________________________________________________________________________________________________________" << endl;
	cout << "#[Memory info]#\n" << "Memory size: " << m.memory_size << "\nFrame size: " << m.frame_size << "\nNumber of frames: " << m.numof_frames << endl << endl;
	cout << "#[Process info]#\n" << "PID: " << p.PID << "\nProcess size: " << p.program_size << "\nPage size: " << p.page_size << "\nNumber of pages: " << p.numof_pages << endl << endl;
	cout << "Limit: " << p.limit << "     Offset's limit: " << p.offset_limit << endl;
	cout << "#[Memeory Map]#\n";
	for (int i = 0; i < p.numof_pages; ++i)
	{
		cout << "Page[" << i << "]->Frame[" << p.page_table[i] << "]" << "   Base address: " << &p.page_table[i] << "   addresses in range:  " << p.page_table[i] * m.frame_size << " - " << p.page_table[i] * m.frame_size + 7 << endl;
	}
	cout << "________________________________________________________________________________________________________________________________________" << endl;
}

int process::page_size = 8;
int memory::frame_size = 8;

int main()
{
	int mem_size;
	cout << "Enter the size of the memory:";
	cin >> mem_size;
	cout << "Enter the size of the frame:";
	cin >> memory::frame_size;
	process::page_size = memory::frame_size;
	memory mem1(mem_size);

	int numof_processes;
	cout << "Enter number of processes: ";
	cin >> numof_processes;
	process *ps = new process[numof_processes];
	for (int i = 0; i < numof_processes; ++i)
	{
		int s;
		int pid = i + 1;
		cout << "Enter thes size of process " << i+1 << ":";
		cin >> s;
		ps[i].set_data(s, pid);
	}
	for (int i = 0; i < numof_processes; ++i)
	{
		cout << endl;
		MMU(ps[i], mem1);
		cout << endl;
	}

	return 0;
}
