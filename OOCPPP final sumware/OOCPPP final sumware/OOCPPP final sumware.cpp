#include "pch.h"
#include "interface.h"


template<typename T> void print(T &obj)
{
	cout << endl << obj << endl;
}

template<typename T> void ADD_DB(ofstream &DB, T &obj)
{
	DB << "--------------------------------------------------------------------------------------\n" << obj << "\n--------------------------------------------------------------------------------------\n";
}
int main()
{
	int choice;
	ofstream DB("DB.txt");
	while (1)
	{
		choice = NULL;
		cout << "[1]Car or [2]Airplane?";
		cin >> choice;
		if (choice == 1)
		{
			string x, y, z;
			int a, b, c;
			cout << "add a car to the data base.\n(Model Name, Colour, Car Number, Model Year, Engine power, Number of cylinders)\n";
			cin >> x >> y >> z >> a >> b >> c;
			car cr(x, y, z, a, b, c);
			print(cr);
			ADD_DB(DB, cr);
			cout << "DONE.\n";
		}
		else if (choice == 2)
		{
			string x;
			int a;
			cout << "Add an airplane to the data base.\n(Model Name, Number of engines)\n";
			cin >> x >> a;
			airplane air(x, a);
			print(air);
			ADD_DB(DB, air);
			cout << "DONE.\n";
		}
	}
	return 0;
}