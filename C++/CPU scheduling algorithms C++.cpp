#include<iostream>
#include<string>
using namespace std;

class process
{

	friend void FCFS(process ps[], int size);
	friend void SJF(process ps[], int size);
	friend void priority(process ps[], int size);
	friend ostream&operator<<(ostream&print, process &p);
private:
	int pid, AT, CPUB, priority;
	static int numof_P;
public:
	process(int a = 0, int b = 0, int c = 0, int d = 0)
	{
		numof_P++;
		pid = a;
		AT = b;
		CPUB = c;
		priority = d;
	}
	void setall(int i)
	{
		cout << "Process[" << i + 1 << "]: ";
		cin >> pid >> AT >> CPUB >> priority;
	}
	~process()
	{
		numof_P--;
	}
};

ostream&operator<<(ostream&print, process &p)
{
	cout << "P" << p.pid << endl;
	return print;
}


void FCFS(process ps[], int size)
{

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (ps[i].AT > ps[j].AT)
			{
				process temp = ps[i];
				ps[i] = ps[j];
				ps[j] = temp;
			}
		}
	}

	int *TAT, *WT, *RT;
	int tat = 0, wt = 0, rt = 0, time = 0;
	TAT = new int[size];
	WT = new int[size];
	RT = new int[size];
	for (int i = 0; i < size; i++)
	{
		time += ps[i].CPUB;
		TAT[i] = time - ps[i].AT;
		WT[i] = TAT[i] - ps[i].CPUB;
		RT[i] = WT[i];
	}
	time = 0;
	cout << "\nGantt Chart(FCFS):\n_______________________________________________________________________________________________________________________________________________________...." << endl;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
			cout << " |\tP" << ps[i].pid << "\t|";
		else
			cout << "|\tP" << ps[i].pid << "\t|";
	}
	cout << "\n_______________________________________________________________________________________________________________________________________________________...." << endl;
	for (int i = 0; i < size + 1; i++)
	{
		cout << "-" << time << "-\t\t";
		time += ps[i].CPUB;
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		tat += TAT[i];
		wt += WT[i];
		rt += RT[i];
	}
	tat /= size;
	wt /= size;
	rt /= size;
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Process[" << ps[i].pid << "]:\tAT= " << ps[i].AT << "\t\tCPUB= " << ps[i].CPUB << "\t\tPriority= " << ps[i].priority << "\t\t\tTAT= " << TAT[i] << "\t\tWT= " << WT[i] << "\t\tRT= " << RT[i] << endl;
	}
	cout << "Average turnaround time = " << tat << endl;
	cout << "Average waiting time = " << wt << endl;
	cout << "Average response time = " << rt << endl;
}

void SJF(process ps[], int size)
{
	//ps[] has been modified from FCFS and the first arrived process is placed first, so we dont need to repeat the sorting procedure again (we only need the process that has arrived first)
	int time = 0;
	time += ps[0].CPUB;
	process *tmp = new process[size];
	process *ordered = new process[size];
	ordered[0] = ps[0];
	tmp[0] = ps[0];
	int tmp_index = 1;
	int last_index = 1;
	int ordr_index = 1;

	for (int i = 0; i < size; i++)
	{
		process *tmp = new process[size];
		tmp[0] = ps[0];
		tmp_index = 1;
		for (int j = 1; j < size; j++)
		{
			if (ps[j].AT <= time)
			{
				tmp[tmp_index] = ps[j];
				tmp_index++;
			}
		}
		for (int l = last_index; l < tmp_index; l++)
		{
			for (int t = l + 1; t < tmp_index; t++)
			{
				if (tmp[l].CPUB > tmp[t].CPUB)
				{
					process temp = tmp[l];
					tmp[l] = tmp[t];
					tmp[t] = temp;
				}
			}
		}
		ordered[ordr_index] = tmp[last_index];
		time += ordered[ordr_index].CPUB;
		ordr_index++;
		last_index++;
		for (int h = 0; h < tmp_index; h++)
			ps[h] = tmp[h];
	}

	int *TAT, *WT, *RT;
	int tat = 0, wt = 0, rt = 0;
	time = 0;
	TAT = new int[size];
	WT = new int[size];
	RT = new int[size];
	for (int i = 0; i < size; i++)
	{
		time += ps[i].CPUB;
		TAT[i] = time - ps[i].AT;
		WT[i] = TAT[i] - ps[i].CPUB;
		RT[i] = WT[i];
	}
	time = 0;
	cout << "\nGantt Chart(SJF):\n_______________________________________________________________________________________________________________________________________________________...." << endl;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
			cout << " |\tP" << ordered[i].pid << "\t|";
		else
			cout << "|\tP" << ordered[i].pid << "\t|";
	}
	cout << "\n_______________________________________________________________________________________________________________________________________________________...." << endl;
	for (int i = 0; i < size + 1; i++)
	{
		cout << "-" << time << "-\t\t";
		time += ordered[i].CPUB;
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		tat += TAT[i];
		wt += WT[i];
		rt += RT[i];
	}
	tat /= size;
	wt /= size;
	rt /= size;
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Process[" << ordered[i].pid << "]:\tAT= " << ordered[i].AT << "\t\tCPUB= " << ordered[i].CPUB << "\t\tPriority= " << ordered[i].priority << "\t\t\tTAT= " << TAT[i] << "\t\tWT= " << WT[i] << "\t\tRT= " << RT[i] << endl;
	}
	cout << "Average turnaround time = " << tat << endl;
	cout << "Average waiting time = " << wt << endl;
	cout << "Average response time = " << rt << endl;

}

void priority(process ps[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (ps[i].AT > ps[j].AT)
			{
				process temp = ps[i];
				ps[i] = ps[j];
				ps[j] = temp;
			}
		}
	}
	int time = ps[0].CPUB;

	process *final = new process[size];
	int final_index = 1;
	final[0] = ps[0];

	process *temp = new process[size];
	int temp_index = 1;
	temp[0] = ps[0];

	while (final_index != size)
	{
		temp_index = 1;

		for (int i = 1; i < size; ++i)
		{
			if (ps[i].AT <= time)
			{
				temp[temp_index] = ps[i];
				++temp_index;
			}
		}

		for (int i = 1; i < temp_index; ++i)
		{
			for (int j = i + 1; j < temp_index; ++j)
			{
				if (temp[i].priority > temp[j].priority)
				{
					process tmp = temp[i];
					temp[i] = temp[j];
					temp[j] = tmp;
				}
			}
		}

		final[final_index] = temp[final_index];
		time += final[final_index].CPUB;
		++final_index;
	}
	int *TAT, *WT, *RT;
	int tat = 0, wt = 0, rt = 0;
	time = 0;
	TAT = new int[size];
	WT = new int[size];
	RT = new int[size];
	for (int i = 0; i < size; i++)
	{
		time += ps[i].CPUB;
		TAT[i] = time - ps[i].AT;
		WT[i] = TAT[i] - ps[i].CPUB;
		RT[i] = WT[i];
	}
	time = 0;
	cout << "\nGantt Chart(priority):\n_______________________________________________________________________________________________________________________________________________________...." << endl;
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
			cout << " |\tP" << final[i].pid << "\t|";
		else
			cout << "|\tP" << final[i].pid << "\t|";
	}
	cout << "\n_______________________________________________________________________________________________________________________________________________________...." << endl;
	for (int i = 0; i < size + 1; i++)
	{
		cout << "-" << time << "-\t\t";
		time += final[i].CPUB;
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		tat += TAT[i];
		wt += WT[i];
		rt += RT[i];
	}
	tat /= size;
	wt /= size;
	rt /= size;
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Process[" << final[i].pid << "]:\tAT= " << final[i].AT << "\t\tCPUB= " << final[i].CPUB << "\t\tPriority= " << final[i].priority << "\t\t\tTAT= " << TAT[i] << "\t\tWT= " << WT[i] << "\t\tRT= " << RT[i] << endl;
	}
	cout << "Average turnaround time = " << tat << endl;
	cout << "Average waiting time = " << wt << endl;
	cout << "Average response time = " << rt << endl;
}

int process::numof_P = 0;

int main()
{
	process *ptr;
	int size;
	cout << "Enter number of processes: ";
	cin >> size;
	ptr = new process[size];
	cout << "Enter PID, AT, CPUB and priority of the process respectively." << endl;
	for (int i = 0; i < size; i++)
		ptr[i].setall(i);
	FCFS(ptr, size);
	SJF(ptr, size);
	priority(ptr, size);
	return 0;
}
