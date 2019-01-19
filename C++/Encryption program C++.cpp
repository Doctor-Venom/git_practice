#include "stdafx.h"
#include <iostream> 
#include <iomanip>
#include <string>
#include <math.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;


void encrypt(char CH[], int num, int key);
void decrypt(char crypt[], int key);

int main()
{
	char arr[1024]; //declares a C-string that will be filled by the user
	cout << "Enter the message(50 characters max):";
	cin.getline(arr, 1024);
	cout << endl;
	int num = 0;

	for (int i = 0; arr[i] != '\0'; i++)//counts how many characters in the entered text
		num++;

	int key; // declares a variable that represents the key for encryption and decryption of the message entered by the user
invalidkey:
	cout << "Enter the key (0 - 6):";
	cin >> key;
	cout << endl;
	if (key > 6 || key < 0)
	{
		cout << "Invalid key value.";
		goto invalidkey;
	}

	char choice; //takes input from the user to navigate to encryption or decrytopn function
again:
	cout << "Enter 1 to Encrypt the message or Enter 2 to Decrypt the message: ";
	cin >> choice;
	cout << endl;

	switch (choice)
	{
	case '1':
		encrypt(arr, num, key);
		break;
	case '2':
		decrypt(arr, key);
		break;
	default:
		cout << "ERROR!" << endl;
		goto again;
	}

	return 0;
}

void encrypt(char CH[], int num, int key)
{

	char crypted[1024];
	char input;
	srand(time(0));

	for (int i = 0; i < 1024; i++) //fill the array crypted[] with random ASCII characters except a-z A-Z and white spaces and ambigious ASCII characters
	{
		input = 32 + (rand() % 223);
		if (input == 127 || input == 129 || input == 141 || input == 143 || input == 144 || input == 157 || input == 160 || input == 173 || input == 255)
			crypted[i] = '#';
		else
			crypted[i] = static_cast<char>(input);

		if (crypted[i] >= 'A' && crypted[i] <= 'Z')
			crypted[i] = '>';
		else if (crypted[i] >= 'a' && crypted[i] <= 'z')
			crypted[i] = '<';
		else if (crypted[i] == ' ')
			crypted[i] = '*';

	}

	int x = 0;
	int y = 0;
	srand(time(0));
	for (int i = 8, j = 0; i < 1024; i++, j++) // puts the contents of array CH[] in random places in array crypt[]
	{
		y = x + (rand() % i);
		if (y == x)
		{
			i--;
			j--;
			continue;
		}
		else
			x = y;
		if (x >= 1024)
			break;
		if (j == num)
			break;
		crypted[x] = CH[j];
	}
	for (int i = 0; i < 1024; i++) //changes the current characters using the key to next characters in ASCII table
	{
		int x;
		x = crypted[i];
		x += key;
		crypted[i] = x;
	}
	char encrypted[1024]; //declares a C-string that will contain the encrypted message in reverse order
	for (int i = 0; i < 1024; i++)
	{
		encrypted[i] = crypted[1023 - i];
		cout << encrypted[i]; //prints the encrypted message
	}
	cout << endl << endl;
}

void decrypt(char crypt[], int key)
{
	for (int i = 0; i < 1024; i++) //changes the current characters to the second previous character in ASCII table
	{
		int x;
		x = crypt[i];
		x -= key;
		crypt[i] = x;
	}

	char decrypted[1024]; //declare a C-string that will store extracted letters
	int counter = 0;
	for (int i = 0; i <= 1024; i++)
	{
		if ((crypt[i] >= 'a' && crypt[i] <= 'z') || (crypt[i] >= 'A' && crypt[i] <= 'Z') || crypt[i] == ' ') //if the character is a letter it will put it in the array decrypted[]
		{
			decrypted[counter] = crypt[i];
			counter++;
		}
	}

	for (int i = 0; i <= counter; i++) //prints all letters in the array decrypted[]
		cout << decrypted[counter - i];
	cout << endl << endl;
}
