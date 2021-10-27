#include <iostream>
#include <string>
using namespace std;
int main()
{
	string str;
	int count = 0;
	bool flag = false;
	cout << "String: ";
	do {
		getline(cin, str);
		for (int i = 0; i < str.size(); i++) 
		{
			if (str[i] != '0' && str[i] != '1' && str[i] != ' ')
			{
				cout << "You have entered the string that is not only from 0 and 1!\tEnter the string again:\n";
				flag = true;
				break;
			}
			else flag = false ;
		}
	} while (flag);
	cout << endl << "Groups with even amount of elemets: ";
	for (int i = 0, j = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			if (count % 2 == 0)
			{
				for (j; j < i; j++)
				{
					cout << str[j] ;
				}
				cout << ' ';
				
			}
			j = i + 1;
			count = 0;
		}
		else
		{
			count++;
		}
	}
	cout << endl;
	return 0;
}