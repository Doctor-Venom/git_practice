#include "pch.h"
#include "interface.h"


template <typename T>
DATA<T>::DATA(string type)
{
	cout << "class data default constructor. Type:" << type << "   write a description:";
	cin >> info;
}

template <typename T>
void DATA<T>::print()
{
	cout << "info: " << info << endl;
}

template <typename T>
T DATA<T>::get() { return info; }

vehicle::vehicle() :DATA<string>(type)
{
	++numof_vehicles;
	cout << "DEF constructor -  class vehicle. numof vehicles:|" << numof_vehicles << "|" << endl;
	type = "N/A";
}

vehicle::vehicle(string t) :DATA<string>(t)
{
	++numof_vehicles;
	cout << "PARM constructor - class vehicle. numof vehicles:|" << numof_vehicles << "|" << endl;
	type = t;
}

vehicle::vehicle(const vehicle &cpy) :DATA<string>(cpy.type)
{
	++numof_vehicles;
	cout << "CPY constructor - class vehicle. numof vehicles:|" << numof_vehicles << "|" << endl;
	type = cpy.type;
}

void vehicle::set_type(string t)
{
	(*this).type = t;
}

string vehicle::get_type() const
{
	return this->type;
}

vehicle vehicle::print()
{
	cout << "Type: " << endl;
	return *this;
}

int vehicle::get_numof_vehicles()
{
	return numof_vehicles;
}

vehicle::~vehicle()
{
	--numof_vehicles;
	cout << "~Destructor - class vehicle. numof vehicles:|" << numof_vehicles << "|" << endl;
}

engine::engine()
{
	cout << "DEF constructor - class engine" << endl;
	engine_power = 0;
	numof_cylinders = 0;
}

engine::engine(int x, int y)
{
	cout << "PARM constructor - class engine" << endl;
	engine_power = x;
	numof_cylinders = y;
}

engine::engine(const engine &cpy)
{
	cout << "CPY constructor - class engine" << endl;
	engine_power = cpy.engine_power;
	numof_cylinders = cpy.numof_cylinders;
}

engine::~engine()
{
	cout << "~Destructor - class engine" << endl;
}

ostream &operator<<(ostream &print, engine &e)
{
	print << "(Power: " << e.engine_power << "   Number of cylinders: " << e.numof_cylinders << ")";
	return print;
}

istream &operator>>(istream&input, engine&e)
{
	cout << "Engine power= ";
	input >> e.engine_power;
	cout << "Number of cylinders= ";
	input >> e.numof_cylinders;
	return input;
}

car::car() :model_year(0), DATA<int>("car"), vehicle("land transport (car)")
{
	cout << "DEF constructor - class car" << endl;
}

car::car(string Model_name, string car_colour, string Car_number, int Model_year, int engine_power, int number_of_cylinders) : DATA<int>("car"), vehicle("land transport (car)"), model_year(Model_year), motor(engine_power, number_of_cylinders)
{
	cout << "PARM constructor - class car" << endl;
	model_name = Model_name;
	colour = car_colour;
	car_number = Car_number;
}

car::car(const car&cpy) :model_year(cpy.model_year), DATA<int>("car"), vehicle("land transport (car)")
{
	cout << "CPY constructor - class car" << endl;
	model_name = cpy.model_name;
	colour = cpy.colour;
	car_number = cpy.car_number;
	motor = cpy.motor;
}

car::~car()
{
	cout << "~Destructor - class car" << endl;
}

ostream &operator<<(ostream &print, car &c)
{
	print << "Model name: " << c.model_name << "   Model year: " << c.model_year << "   Car Number: " << c.car_number << "   colour:" << c.colour << "   Engine:" << c.motor << endl;
	return print;
}

airplane::airplane() :vehicle("air transport (airplane)")
{
	cout << "DEF constructor - class airplane" << endl;
	model_name = "N/A";
	numof_engines = 0;
	engines = new engine[numof_engines];
}

airplane::airplane(string Model_name, int number_of_engines) :vehicle("air transport (airplane)")
{
	cout << "PARM constructor - class airplane" << endl;
	model_name = Model_name;
	numof_engines = number_of_engines;
	engines = new engine[numof_engines];
	for (int i = 0; i < numof_engines; ++i)
	{
		cout << "Engine[" << i + 1 << "]:\n";
		cin >> engines[i];
	}
}

airplane::airplane(const airplane &cpy) :vehicle("air transport (airplane)")
{
	cout << "CPY constructor - class airplane" << endl;
	model_name = cpy.model_name;
	numof_engines = cpy.numof_engines;
	engines = new engine[numof_engines];
	for (int i = 0; i < numof_engines; ++i)
		engines[i] = cpy.engines[i];
}

airplane::~airplane()
{
	cout << "~Destructor - class airplane" << endl;
	delete[] engines;
}

ostream &operator<<(ostream&print, airplane &a)
{
	print << "Model name: " << a.model_name << "   number of engines: " << a.numof_engines << "\nEngines:\n";
	for (int i = 0; i < a.numof_engines; ++i)
		print << a.engines[i] << endl;
	return print;
}


int vehicle::numof_vehicles = 0;