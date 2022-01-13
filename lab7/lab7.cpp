/*В строке, состоящей из групп нулей и единиц,
найти и вывести на экран группы с четным количеством символов*/

#include <iostream>
#include <cstdio>
#include <conio.h>

using namespace std;

bool isStringCorrect(char*);
void countEvenGroups(char*);
int My_strlen(char*);
void MyGets(char*);

int main()
{
	char str[1000] = "";
	cout << "String: ";
	do {
		MyGets(str);
	} while (isStringCorrect(str));
	cout << endl << "Groups with even amount of elements: ";
	countEvenGroups(str);

	cout << endl;
	system("pause");
	return 0;
}

void MyGets(char* str) {//сюда мы копируем только адрес str[1000], и все
						//т.е. указатель, который у str[1000] остается на месте
						//а с помощью копии адреса и нового локального 
						//указателя заполняем наше str[1000]
	char input;
	do {
		input = _getch();
		cout << input;
		if (input == '\r') {
			cout << '\n';
			break;
		}
		*str = input;
		str++;
	} while (true);
	*str = '\0';//делаем для того, чтобы работал вывод: 
				//если ввели больше в пред раз, а в этот раз меньше, ставим на позицию, 
				//где был нажат enter \0и тем самым обозначаем границу вывода

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
		if (str[index] != '0' && str[index] != '1' && str[index] != '\0')
		{
			cout << "You have entered the string that is not only from 0 and 1!\tEnter the string again:\n";
			return true;
		}
	}
	return false;
}
void countEvenGroups(char* str)
{
	int len = My_strlen(str);
	char* pstr = str;
	int amount_of_groups = 0;
	for (int index = 0, index_after_space = 0, amount = 0; index <= len; index++)
	{
		if (index != 0 && str[index] != str[index - 1])
		{
			if (amount % 2 == 0 && amount)
			{
				cout << str[index - 1];
				str[index - 1] = '\0';
				cout << pstr << ' ';
				amount_of_groups++;
			}
			pstr = &str[index];
			index_after_space = index;
			amount = 0;
		}
		amount++;
	}
	if (amount_of_groups == 0) {
		cout << "none";
	}
	//ниже есть ещё варианты выполненения поиска групп. 
}
/*void countEvenGroups(char* str)
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
/*
void countEvenGroups(char* str)
{
	//00010001111000 -> 1111
	int len = My_strlen(str), amount_of_groups = 0;
	char token[1000];
	char* p_str = str, *p_token;

	while (*p_str) {
		p_token = token;
		int amount = 0;
		while (true) {
			*p_token = *p_str;
			p_token++;
			p_str++;
			amount++;

			if (*p_str != *(p_str - 1)) {
				break;
			}
		}

		*p_token = '\0';
		if (amount % 2 == 0 && amount) {
			amount_of_groups++;
			cout << token << ' ';
		}
	}

	if (amount_of_groups == 0) {
		cout << "none";
	}
}*/
