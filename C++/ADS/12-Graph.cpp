#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;

struct edge
{
	int neighbourID;//ID of the neighbour vertex
	int weight;//the weight,value or cost of the edge

	edge(int neighbour_ID = NULL, int Weight = 1)//constructor
	{
		neighbourID = neighbour_ID;
		weight = Weight;
	}
};

class list
{
	struct node
	{
		edge data;
		node *next;
	};
public:
	list()
	{
		head = NULL;
		tail = NULL;
	}

	/**/list &createnode(edge val)//code for creation of new node
	{
		node *temp = new node;//dynamically allocates memory to an object of type node which will be new node in the current object of type list
		temp->data = val;//put the value in the newly reated node
		temp->next = NULL;//newly added node is the last node, so it points to NULL

		if (head == NULL)//if the list was empty
		{
			head = temp;//head points to the first node in the list which is the newly created node
			tail = temp;//tail points to the last node in the list which is the newly created node
			temp = NULL;//deletes the pointer temp (not mandatory statement)
		}
		else//if the list was not empty
		{
			tail->next = temp;//tail is the previous node, and we make the previous node point to the current node which is being created
			tail = temp;//tail points to the last node in the list which is the newly created node
			temp = NULL;//deletes the pointer temp (not mandatory statement)
		}
		return *this;
	}

	/**/void display()//this method is specific for edge structure only
	{
		node *temp = new node;//temporary object of type temp, we will use it to iterate
		temp = head;//set the address at wich temp points to the address of the first node in the list


		while (temp != NULL)
		{
			cout << ">>>Neighbour_ID:(" << temp->data.neighbourID << ") Weight:(" << temp->data.weight << ")   ";//print the data in the node that is pointed to by temp
			temp = temp->next;//set temp to the next node in the list
		}
		cout << "\n";
	}

	/**/void insert_start(edge val)
	{
		node *temp = new node;//dynamically allocates memory to an object of type node which will be new node in the current object of type list
		temp->data = val;//put the value in the newly reated node
		temp->next = head;//make it point to the address stored in head which is the first node, which became the second node
		head = temp;//change the address pointed to by head to make it point to the first node
	}
	/**/void insert_mid(edge val, int pos)///Q: when we create previous and current pointers and allocate them memory then change the object to which they point, will that result in a memory leak? we have to declare a pointer without dynamically allocaton memory
	{
		node *previous = NULL;
		node *current = NULL;
		node *temp = new node;//dynamically allocates memory to an object of type node which will be new node in the current object of type list
		current = head;//change the object to which current points to be the first object in the list, to start iterating from it

		for (int i = 0; i < pos; ++i)//iterats through the list
		{
			previous = current;//change the object to which previous points to be the current object
			current = current->next;//change the object to which previous points to be the next object
		}

		temp->data = val;//put the value in the newly reated node
		previous->next = temp;//make previous node point to the inserted node
		temp->next = current;//make the current node point to the next node
	}
	/**/void insert_end(edge val)
	{
		createnode(val);
	}

	/**/void delete_start()
	{
		node *temp = NULL;//temporary pointer
		temp = head;//make temp pointer point to the first node
		head = head->next;//make head point to the second node
		delete temp;//deallocate the firs node
	}
	/**/void delete_mid(int pos)
	{
		node *current = NULL;
		node *previous = NULL;
		current = head;//make the pointer current point to the first node to start iteration from it

		for (int i = 0; i < pos; ++i)//iterates until the user defined position
		{
			previous = current;//move the address of the current node to be the previous node
			current = current->next;//move the address of the next node to be the current node
		}
		previous->next = current->next;//make the previous node point to the next node
		delete current;//deallocate the current node
	}
	/**/void delete_end()
	{
		node *current = NULL;
		node *previous = NULL;
		current = head;//make the pointer current point to the first node to start iteration from it

		while (current->next != NULL)//iterates until the last node which points to NULL
		{
			previous = current;//move the address of the current node to be the previous node
			current = current->next;//move the address of the next node to be the current node
		}
		tail = previous;//make tail point to the node before the last node
		previous->next = NULL;//make the node before the last node point to NULL as it will become the last node after deletion
		delete current;//deallocate the last node, destroy it, delete it from existance, make it like a dust which disapears like it never existed!!!
	}

private:
	node *head, *tail;//head points to the first node, tail points to the last node
};

struct vertex
{
	int x, y;//coordinates of the vertex
	list adjacency_list;//list of adjacent vertecies

	vertex(int X = 0, int Y = 0) { x = X; y = Y; }//constructor

	vertex add_adjecency(int neighbour_id, int weight = 1)//method for adding adjancies
	{
		adjacency_list.createnode(edge(neighbour_id, weight));
		return *this;
	}
};

class graph
{
public:
	int numof_vertecies;//number of vertecies in the graph
	vertex *vertices;//pointer for dynamic allocation of an array of vertecies

	graph(int num)//constructor
	{
		numof_vertecies = num;
		vertices = new vertex[numof_vertecies];
	}

	void display()//method to print each vertex in the graph and all its adjancies
	{
		for (int i = 0; i < numof_vertecies - 1; i++)
		{
			cout << "vertex [" << i << "]:" << endl;
			vertices[i].adjacency_list.display();
			cout << "______________________________________________________________________________________________________________________________________________________________\n";
		}
	}

};

int main()
{
	graph g1(7);
	g1.vertices[0].add_adjecency(1).add_adjecency(3);
	g1.vertices[1].add_adjecency(0).add_adjecency(2);
	g1.vertices[2].add_adjecency(1).add_adjecency(5);
	g1.vertices[3].add_adjecency(0).add_adjecency(4);
	g1.vertices[4].add_adjecency(3).add_adjecency(5);
	g1.vertices[5].add_adjecency(2).add_adjecency(4).add_adjecency(6);
	g1.vertices[6].add_adjecency(5);
	/*
	(0)----(1)-----(2)
	|				|
	|				|
	(3)----(4)-----(5)-----(6)
	*/
	g1.display();
	return 0;
}