#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream> 
#include <fstream>
#include <string>

	using namespace std;

template <typename T> class DATA
{
public:
	DATA(string type = "N/A");
	void print();
protected:
	T get();
private:
	T info;
};

class vehicle : public DATA<string>
{
public:
	vehicle();
	vehicle(string t);
	vehicle(const vehicle &cpy);
	void set_type(string t);
	string get_type() const;
	vehicle print();
	static int get_numof_vehicles();
	~vehicle();
private:
	string type;
	static int numof_vehicles;
};

const class engine
{
	friend ostream&operator<<(ostream&print, engine &e);
	friend istream&operator>>(istream&input, engine&e);
	friend class car;
public:
	engine();
	engine(int x, int y);
	engine(const engine &cpy);
	~engine();
private:
	int engine_power;
	int numof_cylinders;
};


class car :public vehicle, DATA<int>
{
	friend ostream&operator<<(ostream &print, car &c);
public:
	car();
	car(string Model_name, string car_colour, string Car_number, int Model_year, int engine_power, int number_of_cylinders);
	car(const car&cpy);
	~car();
private:
	string model_name;
	string colour;
	string car_number;
	const int model_year;
	engine motor;
};

class airplane :public vehicle
{
	friend ostream&operator<<(ostream&print, airplane &a);
public:
	airplane();
	airplane(string Model_name, int number_of_engines);
	airplane(const airplane &cpy);
	~airplane();
private:
	string model_name;
	int numof_engines;
	engine *engines;
};

#endif
/*
[DONE]classes, data members and member function, and objects
[DONE]access specifiers
[DONE]constructors (default, parametrized, copy) / destructors and scopes of objects (automatic and static objects, local and global)
[DONE]member wise assignment and copy constructor
[DONE]member initializer list
[DONE]friend functions and friend classes
[DONE]the this pointer and cascaded function call
[DONE]const objects and member functions
[DONE]composition
[DONE]dynamic memory management in classes (dangling pointer)
[DONE]static class members (static data members and member functions
[DONE]operator overloading (overloaded oprators, member or non member operator overloading, compiler call translation)
[DONE]inheritance (inheritance types, the effect of access specifiers)
[DONE]templates (class templates, function templates)
[DONE]separating interface from implementation
*/