/*В строке, состоящей из групп нулей и единиц,
найти и вывести на экран группы с четным количеством символов*/

#include <iostream>

using namespace std;

bool isStringCorrect(char*);
void countEvenGroups(char*);
int My_strlen(char*);

int main()
{
	char str[100] = "";
	cout << "String: ";

	do {
		gets_s(str);
	} while (isStringCorrect(str));

	cout << endl << "Groups with even amount of elements: ";
	countEvenGroups(str);

	cout << endl;
	system("pause");
	return 0;
}

int My_strlen(char* str) {
	int length = 0;
	for (length; str[length]; ++length);
	return length;
}
bool isStringCorrect(char* str)
{
	int len = My_strlen(str);
	for (int index = 0; index <= len; index++)
	{
		if (str[index] != '0' && str[index] != '1' && str[index] && str[index] != '\0')
		{
			cout << "You have entered the string that is not only from 0 and 1!\tEnter the string again:\n";
			return true;
		}
	}
	return false;
}/*
void countEvenGroups(char* str)
{
	int len = My_strlen(str);
	for (int index = 0, index_after_space = 0, amount = 0; index <= len; index++)
	{
		if (index != 0 && str[index] != str[index - 1])
		{
			if (amount % 2 == 0 && amount)
			{
				for (index_after_space; index_after_space < index; index_after_space++)
				{
					cout << str[index_after_space];
				}
				cout << ' ';
			}
			index_after_space = index;
			amount = 0;
		}
		amount++;
	}
}*/
void countEvenGroups(char* str)
{
	int len = My_strlen(str);
	char* pstr = str;
	for (int index = 0, index_after_space = 0, amount = 0; index <= len; index++)
	{
		if (index != 0 && str[index] != str[index - 1])
		{
			if (amount % 2 == 0 && amount)
			{
				cout << str[index - 1];
				str[index - 1] = '\0';
				cout << pstr << ' ';
			}
			pstr = &str[index];
			index_after_space = index;
			amount = 0;
		}
		amount++;
	}
}
