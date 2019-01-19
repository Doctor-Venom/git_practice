#include <iostream>
using namespace std;

void reverse(char x[], int size)
{
	static int i = 0;
	static int s = size;
	static char *p = new char[size];
	if (size == 0)
	{
		for (int j = 0; j < s; j++)
			x[j] = p[j];
		return;
	}
	else
	{
		p[i] = x[size - 1];
		i++;
		size--;
		return reverse(x, size);
	}

}
int main()
{
	char *ptr = new char[100];
	cin.getline(ptr,100);
	int size = strlen(ptr);
	reverse(ptr, size);
	for (int i = 0; i < size; i++)
	{
		cout << ptr[i];
	}
	cout << endl;
	return 0;
}
