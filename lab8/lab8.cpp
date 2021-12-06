#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include "windows.h"

using namespace std;

const int SIZE_OF_FIO = 50;

struct Person {
	char fio[SIZE_OF_FIO] ;
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
void viewFile(FILE*, char*, const int&);
void addInformation(FILE*, char*, const int&);
void cleverStudents(FILE*, char*, const int& size);
void chooseFileFromCurrentFolder(FILE*, char*);
void sleep();
void My_strcat(char*, char*);
int My_strlen(char*);
void MyGets(char*);
void chooseDataType(char*);
bool isFileNameCorrect(char*);
void inputInformation();
void showInformation();
int checkNum();


int main() {
	FILE* StudFile = nullptr;
	int size = sizeof(Person);
	const char MENU[] = "Current file - %s\nCreate New File - 1\nAdd information - 2\nView information - 3\nClever students - 4\nChoose file from folder - 5\nEXIT - another symbol\n\nchoose mode you want to use: ";
	char fileName[50] = "";
	char choice;
	while (true) {
		system("cls");
		printf(MENU, (fileName[0] == '\0' ? "none" : fileName));
		choice = _getch();
		printf("%c\n", choice);
		switch (choice) {
		case '1': {
			createEmptyFile(StudFile, fileName);
			break;
		}
		case '2': {
			addInformation(StudFile, fileName, size);
			break;
		}
		case '3': {
			viewFile(StudFile, fileName, size);
			break;
		}
		case '4': {
			cleverStudents(StudFile, fileName, size);
			break;
		}
		case '5': {
			chooseFileFromCurrentFolder(StudFile, fileName);
			break;
		}
		default: {
			printf("\n\t\t\t\t\tGood Bye!\n");
			return 0;
		}
		}
	}
}

int checkNum() {
	int var;
	while (!(scanf_s("%d", &var)) || cin.get() != '\n') {
		cout << "Error! Something go wrong ReEnter: ";
		cin.clear();
		while (cin.get() != '\n');
	}
	return var;
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
void sleep() {
	printf("This stage will close in 2 seconds: ");
	for (int i = 1; i <= 2; i++) {
		printf("...%d", i);
		Sleep(1000);
	}
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
	int current_year = time(0) / 3.154e7 + 1970;
	printf("\nLastName, Name and Patronymic - ");
	fflush(stdin);
	MyGets(student.fio);
	printf("Year of birth - ");
	do {
		student.year = checkNum();
	} while (student.year <= 1940 || student.year >= current_year);
	printf("Group number - ");
	student.groupNumber = checkNum();
	printf("Marks:\nMath - ");
	student.marks.math = checkNum();
	printf("Physics - ");
	student.marks.physics = checkNum();
	printf("Informatics - ");
	student.marks.informatics = checkNum();
	printf("Chemistry - ");
	student.marks.chemistry = checkNum();
	student.average_score = ((double)student.marks.math + (double)student.marks.physics + (double)student.marks.informatics + (double)student.marks.informatics) / 4.;
	printf("\n");
}
void showInformation() {
	printf("\n%s %d %d %d %d %d %d %lf\n", student.fio, student.year, student.groupNumber, student.marks.math, student.marks.physics, student.marks.informatics, student.marks.chemistry, student.average_score);
}

void createEmptyFile(FILE* StudFile, char* fileName) {
		printf("Type a name for your file: ");
		do {
			fflush(stdin);
			scanf_s("%s", fileName, 50);
		} while (isFileNameCorrect(fileName));
		
		chooseDataType(fileName);

		fopen_s(&StudFile, fileName, "wb");
		if (StudFile == NULL) {
			printf("Create file Failed!!!\n");
			sleep();
			return;
		}
		fclose(StudFile);
		printf("Succesfull create of file %s!\n", fileName);
		sleep();
}
void addInformation(FILE* StudFile, char* fileName, const int& size) {
	fopen_s(&StudFile, fileName, "ab");
	
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return;
	}
	inputInformation();
	fwrite(&student, size, 1, StudFile);
	fclose(StudFile);
	printf("Succesfull added information in file %s!\n", fileName);
	sleep();
}
void viewFile(FILE* StudFile, char* fileName, const int& size) {
	fopen_s(&StudFile, fileName, "rb");
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return;
	}
	int amount = _filelength(_fileno(StudFile)) / size;
	for (int i = 0; i < amount; i++) {
		fread(&student, size, 1, StudFile);
		showInformation();
	}
	fclose(StudFile);
	system("pause");
}
void cleverStudents(FILE* StudFile, char* fileName, const int& size) {
	fopen_s(&StudFile, fileName, "rb");
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return;
	}
	int amount = _filelength(_fileno(StudFile)) / size;
	for (int i = 0; i < amount; i++) {
		fread(&student, size, 1, StudFile);
		if ((student.fio[0] == -128 || student.fio[0] == 65) && (student.marks.math == 8 || student.marks.math == 9)) {
			showInformation();
		}
	}
	fclose(StudFile);
	system("pause");
}   
void chooseFileFromCurrentFolder(FILE* StudFile, char* fileName) {
	system("dir *.txt *.dat");
	char fileNameCopy[50];
	do {
		printf("\nIf you want to leave this mode type: 'q'\nChoose File from list before: ");
		scanf_s("%s", fileNameCopy, 50);
		if (fileNameCopy[0] == 'q' && fileNameCopy[1] == '\0'  ) {
			return;
		}
		fopen_s(&StudFile, fileName, "rb");
		if (StudFile == NULL) {
			printf("\No such file with this name in this directory!");
			continue;
		}
		for (int i = 0; i < My_strlen(fileNameCopy); i++) {
			fileName[i] = fileNameCopy[i];
		}
		break;
	} while (true);
	fclose(StudFile);
	system("pause");
}