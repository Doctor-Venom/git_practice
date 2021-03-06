#include "stdafx.h"
#include <iostream> 
#include <iomanip>
#include <string>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

class finalMark
{
	friend class student;
	friend class CLASS;
private:
	int mark;
	static int bonus;
	int sum() const { return (mark + bonus); }
public:
	finalMark() :mark(0) {  }
	finalMark(int a) :mark(a) { }
	finalMark(const finalMark &cpy) :mark(cpy.mark) {  }
	~finalMark(){ }
	void setall(int a, int b) { mark = a; bonus = b; }
	int getx() const { return mark; }
	int gety() const { return bonus; }
	void print() const { cout << mark << " + " << bonus << " = " << sum() << endl; }
};

class student
{
	friend class CLASS;
private:
	string name; 
	int id;
	finalMark m;
public:
	student() :name(" "), id(0), m(finalMark()) {  }
	student(string x, int y, finalMark z):name(x),id(y),m(z) { }
	student(const student &cpy) :name(cpy.name), id(cpy.id), m(cpy.m) { }
	~student() {  }
	void setall(string x, int y, finalMark &mark) { name = x; id = y; m = mark; }
	string getname()  { return name; }
	int getid() { return id; }
	finalMark getmark() { return m; }
	void print() { cout << name << "\t" << id << "\t\tFinal mark: " << m.sum() << endl; }
};
class CLASS
{
private:
	const int numofStu;
	int avgofStu;
	static int maxMark;
	static int bonus;
	student *students = new student[numofStu];
public:
	CLASS() :numofStu(0), avgofStu(0){}
	CLASS(int x, student z[]):numofStu(x), avgofStu(0)
	{
		for (int i = 0; i < numofStu; i++)
			students[i] = z[i];
		avg();
	}
	CLASS(const CLASS &cpy) :numofStu(cpy.numofStu), avgofStu(cpy.avgofStu)
	{
		for (int i = 0; i < cpy.numofStu; i++)
			students[i] = cpy.students[i];
		avg();
	}
	void avg() {
		int sum = 0;
		for (int i = 0; i < numofStu; i++)
			sum = sum + students[i].m.mark;
		avgofStu = (sum / numofStu);
	}
	void seekmax()
	{
		int max = 0;
		for (int i = 0; i < numofStu; i++)
			if (max < students[i].m.mark)
				max = students[i].m.mark;
		maxMark = max;

	}
	void setbonus()
	{
		if (avgofStu <= 10 && avgofStu != 0)
			bonus = (20 - maxMark);
		else
			bonus = 0;
		finalMark::bonus = bonus;
	}
	void print()
	{
		cout << "Number of students in this class: " << numofStu << endl;
		cout << "The average of student marks in tis class: " << avgofStu << endl;
		cout << "Highest mark in this class: " << maxMark << endl;
		cout << "Bonus marks for this class: " << bonus << endl << endl;
		cout << "###Student Data: ###" << endl;
		for (int i = 0; i < numofStu; i++)
			students[i].print();

	}
};
int CLASS::maxMark = 0;
int CLASS::bonus = 0;
int finalMark::bonus = 0;

int main()
{
	int num;
	cout << "Enter number of students: ";
	cin >> num;
	student *A = new student[num];

	string name;
	int ID;
	int mark;
	cout << "\nEnter the information of each student (Name, ID, mark):\n";

	for (int i = 0; i < num; i++)
	{
		cout << "Student [ " << i + 1 << " ]:" << endl << "Name: ";
		cin >> name;
		cout << "ID: ";
		cin >> ID;
		again:
		cout << "Mark: ";
		cin >> mark;
		if (mark < 0 || mark > 20)
		{
			cout << "Error! The range of the variable mark is 0-20!" << endl;
			goto again;
		}
		cout << endl;
		finalMark temp(mark);
		A[i].setall(name, ID, temp);
	}
	CLASS AA(num, A);
	AA.seekmax();
	AA.setbonus();
	AA.print();
	
	return 0;
}
