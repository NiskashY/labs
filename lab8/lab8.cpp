#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace std;
const char MENU[] = "\nCreate New File - 1\nAdd information - 2\nView information - 3\nSort information - 4\nEXIT - another symbol \n\nchoose mode you want to use: ";

struct Person {
	char name[15];
	char lastName[15];
	char patronymic[15];
	int year;
	int groupNumber;
	struct Marks {
		int math;
		int physics;
		int informatics;
		int chemistry;
	} marks;
	double average_score;
} student;
void createEmptyFile(FILE*, char*);
void viewFile(FILE*, char*);
void sortInformation(FILE*, char*);
void addInformation(FILE* StudFile, char fileName[50]);
void My_strcat(char*, char*);
int My_strlen(char*);
void MyGets(char*);
void chooseDataType(char*);
bool isFileNameCorrect(char*);
void inputInformation();


int main() {
	char fileName[50] = "";
	FILE* StudFile = nullptr;
	char choice;

	while (true) {
		printf(MENU);
		choice = _getch();
		printf("%c\n", choice);
		switch (choice) {
		case '1': {
			createEmptyFile(StudFile, fileName);
			break;
		}
		case '2': {
			addInformation(StudFile, fileName);
			break;
		}
		case '3': {
			break;
		}
		case '4': {
			break;
		}
		default: {
			printf("\n\t\t\t\t\tGood Bye!\n");
			return 0; 
		}
		}


	}

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
void My_strcat(char* s1, char* s2) {
	while (*s1) {
		s1++;
	}
	int length = My_strlen(s2);
	while (*s2 && length) {
		*s1 = *s2;
		s1++; s2++; length--;
	}
	*s1 = '\0';
}
void chooseDataType(char* fileName) {
	printf("Choose type of your file: \n1 - .dat\nelse - .txt");
	char file_type1[] = ".dat";
	char file_type2[] = ".txt";
	char choice = _getch();
	printf(" %c\n", choice);
	choice == '1' ? My_strcat(fileName, file_type1) : My_strcat(fileName, file_type2);
}
bool isFileNameCorrect(char* str)
{
	int len = My_strlen(str);
	for (int index = 0; index <= len; index++)
	{
		if (str[index] == '<' || str[index] == '>' || str[index] == ':' || str[index] == '/' || str[index] == '\'' || str[index] == '|' || str[index] == '*' || str[index] == '?' || str[len-1] == ' ' || str[len - 1] == '.')
		{
			cout << "You have entered wrong name for file. It shouldnt contains <>?*|\'/ or end with 'space' or end with the dot. \n";

			return true;
		}
	}
	return false;
}
void inputInformation() {
	printf("\n Last name - ");
	scanf_s("%s", student.name, 15);
	printf("\n Name - ");
	scanf_s("%s", student.lastName, 15);
	printf("\n Patronymic - ");
	scanf_s("%c", student.patronymic, 15);
	printf("\n Year of birth - ");
	scanf_s("%d", &student.year);
	printf("\n Group number - ");
	scanf_s("%d", &student.groupNumber);
	printf("\n Marks:\n math - ");
	scanf_s("%d", &student.marks.math);
	printf("\n Physics - ");
	scanf_s("%d", &student.marks.physics);
	printf("\n Informatics - ");
	scanf_s("%d", &student.marks.informatics);
	printf("\n Chemistry - ");
	scanf_s("%d", &student.marks.chemistry);
}
void createEmptyFile(FILE* StudFile, char fileName[50]) {
		printf("Type a name for your file: ");
		do {
			fflush(stdin);
			scanf_s("%s", fileName, 50);
		} while (isFileNameCorrect(fileName));
		
		chooseDataType(fileName);

		fopen_s(&StudFile, fileName, "wb");
		if (fopen_s == NULL) {
			printf("Create file Failed!!!\n");
			return;
		}
		printf("Succesfull create of file %s!\n", fileName);
		fclose(StudFile);
		//system("pause");

}
void addInformation(FILE* StudFile, char fileName[50]) {

	fopen_s(&StudFile, fileName, "ab");
	//system("pause");
	inputInformation();
	int size = sizeof(Person);
	fwrite(&student, size, 1, StudFile);
	fclose(StudFile);
}
void viewFile(FILE* StudFile, char fileName[50]) {

}
void sortInformation(FILE* StudFile, char fileName[50]) {

}
