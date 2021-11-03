/*В строке, состоящей из групп нулей и единиц,
найти и вывести на экран группы с четным количеством символов*/

#include <iostream>
#include <string>
using namespace std;


bool isStringCorrect(string);
void countEvenGroups(string);

int main()
{
	string str; 

	cout << "String: ";

	do {
		getline(cin, str);
	} while (isStringCorrect(str));

	cout << endl << "Groups with even amount of elemets: ";
	countEvenGroups(str);

	cout << endl;
	system("pause");
	return 0;
}

bool isStringCorrect(string str)
{
	for (int index = 0; index <= str.size(); index++)
	{
		if (str[index] != '0' && str[index] != '1' && str[index] != ' ' && str[index] != '\0')
		{
			cout << "You have entered the string that is not only from 0 and 1!\tEnter the string again:\n";
			return true;
		}
	}
	return false;
}
void countEvenGroups(string str)
{
	for (int index = 0, index_after_space = 0, amount = 0; index <= str.size(); index++)
	{
		if (str[index] == ' ' || str[index] == '\0')
		{
			if (amount % 2 == 0 && amount )
			{
				for (index_after_space; index_after_space < index; index_after_space++)
				{
					cout << str[index_after_space];

				}
				cout << ' ';
			}
			index_after_space = index + 1;
			amount = 0;
		}
		else
		{
			amount++;
		}
	}
}
