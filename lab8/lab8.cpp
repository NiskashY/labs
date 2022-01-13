/*Распечатать анкетные данные студентов, фамилии которых начинаются с буквы А, и сдавших математику на 8, или 9, или 10.*/
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <windows.h> 

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
	void showInformation() {
		printf("%s %d %d %d %d %d %d %lf", fio, year, groupNumber, marks.math, marks.physics, marks.informatics, marks.chemistry, average_score);
	}
};

/*--------------------------Prototypes for funtions-----------------------------*/
void sleep();
void My_strcat(char*, char*);
int My_strlen(char*);
void MyGets(char*);
void chooseTypeOfCorrection(Person&);
void chooseDataType(char*);
bool isFileNameCorrect(char*);
bool isStudentClever(Person&);
bool isMarkCorrect(const int&);
void inputInformation(Person&);
int checkNum();
void inputGroupNumber(Person&);
void inputYear(Person&);
void inputMarks(Person&);
void core(FILE*, char*, const int&);
bool showMenuEmpty(FILE*, char*, const int&, const char);
bool showMenuNotEmpty(FILE*, char*, const int&, const char);
void deletePersonInFile(FILE* StudFile, char* fileName, const int& SIZE);
void corectionOfPersonInformation(FILE* StudFile, char* fileName, const int& SIZE);
int GetAmountOfStudents(FILE* StudFile, char* fileName, const int& SIZE);
void chooseTypeOfSort(FILE*, char*, const int&);
void sortByFio(FILE*, char*, const int&, bool (*sortType) (char*, char*));
bool ascending(char*, char*);
bool descending(char*, char*);
void createEmptyFile(FILE*, char*);
void addInformation(FILE*, char*, const int&);
void viewFile(FILE*, char*, const int&);
void correctionOfFile(FILE*, char*, const int&);
void cleverStudents(FILE*, char*, const int& SIZE);
void chooseFileFromCurrentFolder(FILE*, char*);
void writeIntoFile(FILE*, char*, const int&);

/*--------------------------------Main Function-----------------------------------*/
int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* StudFile = nullptr;
	const int SIZE = sizeof(Person);
	char fileName[50] = "";
	core(StudFile, fileName, SIZE);
	return 0;
}

/*--------------------------------MyFunctions-----------------------------------*/

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
	char* start = str;
	do {
		input = _getch();
		printf("%c", input);
		if (input == '\r') {
			printf("\n");
			break;
		}
		*str = input;
		if (input == '\b' && str != start) {
			str--;
			printf(" \b");
		}
		if (input != '\b') {
			str++;
		}
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
int My_strcmp(char* fio1, char* fio2) {
	while (*fio1 || *fio2) {
		if (*fio1 > *fio2) {
			return 1;
		}
		if (*fio1 < *fio2) {
			return -1;
		}
		fio1++;
		fio2++;
	}

	return 0;
}
bool ascending(char* fio1, char* fio2) {
	return My_strcmp(fio1, fio2) > 0;
}
bool descending(char* fio1, char* fio2) {
	return My_strcmp(fio1, fio2) < 0;
}

/*--------------------Functions for working with file data----------------------*/

void chooseTypeOfCorrection(Person& student) {
	printf("FIO - 1, Year - 2, Group number - 3, Marks - 4, else - back to menu\nChoose what you want to correct: ");
	char choice = _getch();
	printf("%c\n", choice);
	switch (choice) {
	case '1': {
		printf("\nType FIO: ");
		MyGets(student.fio);
		break;
	}
	case '2': {
		printf("\nType Year: ");
		inputYear(student);
		break;
	}
	case '3': {
		printf("\nType Group number: ");
		inputGroupNumber(student);
		break;
	}
	case '4': {
		printf("\nType Marks:\n");
		inputMarks(student);
		break;
	}
	default: {
		return;
	}
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
bool isStudentClever(Person& student) {
	return (student.fio[0] == -64 || student.fio[0] == 65 || student.fio[0] == -32) && (student.marks.math >= 8);
}
void inputInformation(Person& student) {
	printf("\nLastName, Name and Patronymic - ");
	fflush(stdin);
	MyGets(student.fio);
	printf("Year of birth - ");
	inputYear(student);
	printf("Group number - ");
	inputGroupNumber(student);
	printf("Marks:\n");
	inputMarks(student);
	student.average_score = ((double)student.marks.math + (double)student.marks.physics + (double)student.marks.informatics + (double)student.marks.chemistry) / 4.;
	printf("\n");
}
void inputYear(Person& student) {
	int current_year = (int)(time(0) / 3.154e7 + 1970);
	while (true) {
		student.year = checkNum();
		if (student.year <= 1900 || student.year >= current_year) {
			printf("People with this age do not exist:/\n");
			continue;
		}
		return;
	}
}
void inputGroupNumber(Person& student) {
	while (true) {
		student.groupNumber = checkNum();
		if (student.groupNumber <= 0 || student.groupNumber >= 1000000) {
			printf("No group with this number! (Should be [0,1000 000\n");
			continue;
		}
		return;
	}
}
void inputMarks(Person& student) {
	printf("Math - ");
	do {
		student.marks.math = checkNum();
	} while (isMarkCorrect(student.marks.math));
	printf("Physics - ");
	do {
		student.marks.physics = checkNum();
	} while (isMarkCorrect(student.marks.physics));
	printf("Informatics - ");
	do {
		student.marks.informatics = checkNum();
	} while (isMarkCorrect(student.marks.informatics));
	printf("Chemistry - ");
	do {
		student.marks.chemistry = checkNum();
	} while (isMarkCorrect(student.marks.chemistry));
	student.average_score = ((double)student.marks.math + (double)student.marks.physics + (double)student.marks.informatics + (double)student.marks.chemistry) / 4.;
}
bool isMarkCorrect(const int& mark) {
	bool tmp = (mark > 10 || mark < 0);
	if (tmp) {
		printf("Mark shoud be [0,10]\n");
	}
	return tmp;
}
bool showMenuEmpty(FILE* StudFile, char* fileName, const int& SIZE, const char choice) {
	switch (choice) {
		case '1': {
			createEmptyFile(StudFile, fileName);
			break;
		}
		case '2': {
			chooseFileFromCurrentFolder(StudFile, fileName);
			break;
		}
		default: {
			printf("\n\t\t\t\t\tGood Bye!\n");
			return 0;
		}
	}
	return 1;
}
bool showMenuNotEmpty(FILE* StudFile, char* fileName, const int& SIZE, const char choice) {
	switch (choice) {
		case '1': {
			createEmptyFile(StudFile, fileName);
			break;
		}
		case '2': {
			addInformation(StudFile, fileName, SIZE);
			break;
		}
		case '3': {
			viewFile(StudFile, fileName, SIZE);
			system("pause");
			break;
		}
		case '4': {
			correctionOfFile(StudFile, fileName, SIZE);
			break;
		}
		case '5': {
			cleverStudents(StudFile, fileName, SIZE);
			break;
		}
		case '6': {
			chooseTypeOfSort(StudFile, fileName, SIZE);
			break;
		}
		case '7': {
			chooseFileFromCurrentFolder(StudFile, fileName);
			break;
		}
		default: {
			printf("\n\t\t\t\t\tGood Bye!\n");
			return 0;
		}
	}
	return 1;
}
int GetAmountOfStudents(FILE* StudFile, char* fileName, const int& SIZE) {
	fopen_s(&StudFile, fileName, "r+b");
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return 0;
	}
	int amount = _filelength(_fileno(StudFile)) / SIZE;

	fclose(StudFile);
	return amount;
}
void chooseTypeOfSort(FILE* StudFile, char* fileName, const int& SIZE) {
	printf("1 - ascending, 2 - descending, else - exit");
	char choice = _getch();
	printf("%c\n", choice);
	if (choice == '1') {
		sortByFio(StudFile, fileName, SIZE, ascending);
	}
	else if (choice == '2') {
		sortByFio(StudFile, fileName, SIZE, descending);
	}
}

/*--------------------Functions for working with files--------------------------*/

void core(FILE* StudFile, char* fileName, const int& SIZE) {
	char choice;
	const char MENU_NONE[] = "Current file - %s\n\nCreate New File(and delete inforamtion if the name is same) - 1\nChoose file from folder - 2\nEXIT - another symbol\n\nChoose mode you want to use: ";
	const char MENU[] = "Current file - %s\n\nCreate New File and delete Current File - 1\nAdd information - 2\nView information - 3\nCorrection of information - 4\nClever students - 5\nSort by Fio - 6\nChoose file from folder - 7\nEXIT - another symbol\n\nChoose mode you want to use: ";
	while (true) {
		system("cls");
		
		printf((fileName[0] == '\0' ? MENU_NONE : MENU), (fileName[0] == '\0' ? "none" : fileName)); // если имя файла пустое, то сначала печатаю меню, затем имя файла в этом меню
		choice = _getch();
		printf("%c\n", choice);
		if (fileName[0] == '\0') {
			if (showMenuEmpty(StudFile, fileName, SIZE, choice) == 0) { //в самой функции есть условие, при котором выпадает 0
				return;
			}
		}
		else {
			if (showMenuNotEmpty(StudFile, fileName, SIZE, choice) == 0) {//в самой функции есть условие, при котором выпадает 0
				return;
			}
		}
		writeIntoFile(StudFile, fileName, SIZE);
	}
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
void addInformation(FILE* StudFile, char* fileName, const int& SIZE) {
	fopen_s(&StudFile, fileName, "ab");
	Person student;
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return;
	}
	inputInformation(student);
	fwrite(&student, SIZE, 1, StudFile);
	fclose(StudFile);
	printf("Succesfull added information in file %s!\n", fileName);
	sleep();
}
void viewFile(FILE* StudFile, char* fileName, const int& SIZE) {
	Person student;
	fopen_s(&StudFile, fileName, "rb");
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return;
	}
	int amount = _filelength(_fileno(StudFile)) / SIZE;
	for (int i = 0; i < amount; i++) {
		fread(&student, SIZE, 1, StudFile);
		printf("\n%d. ", i + 1);
		student.showInformation();
	}
	printf("\n");
	fclose(StudFile);
	printf("\n");
}
void cleverStudents(FILE* StudFile, char* fileName, const int& SIZE) {
	fopen_s(&StudFile, fileName, "rb");
	Person student;
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return;
	}
	int amount = _filelength(_fileno(StudFile)) / SIZE;
	for (int i = 0; i < amount; i++) {
		fread(&student, SIZE, 1, StudFile);
		if (isStudentClever(student)) {
			student.showInformation();
			printf("\n");
		}
	}
	fclose(StudFile);
	printf("\n");
	system("pause");
}
void correctionOfFile(FILE* StudFile, char* fileName, const int& SIZE) {
	viewFile(StudFile, fileName, SIZE);
	printf("Edit information of student - 1, delete student - 2, else - leave this stage\nChoose which one you want to: ");

	char choice = _getch();
	printf("%c\n", choice);

	switch (choice) {
		case '1': {
			corectionOfPersonInformation(StudFile, fileName, SIZE);
			break;
		}
		case '2': {
			deletePersonInFile(StudFile, fileName, SIZE);
			break;
		}
		default: {
			return;
		}
	}

	printf("Done!\n");
	sleep();
}
void corectionOfPersonInformation(FILE* StudFile, char* fileName, const int& SIZE) {
	int amount_of_students = GetAmountOfStudents(StudFile, fileName, SIZE), number_of_student;
	Person student;

	printf("Choose number of student: ");
	scanf_s("%d", &number_of_student);
	fopen_s(&StudFile, fileName, "r+b");
	if (StudFile == NULL) {
		printf("Create file Failed!!!\n");
		sleep();
		return;
	}

	fseek(StudFile, (number_of_student - 1) * SIZE, SEEK_SET);
	fread(&student, SIZE, 1, StudFile);

	chooseTypeOfCorrection(student);

	fseek(StudFile, (number_of_student - 1) * SIZE, SEEK_SET);
	fwrite(&student, SIZE, 1, StudFile);

	fclose(StudFile);
}
void deletePersonInFile(FILE* StudFile, char* fileName, const int& SIZE) {
	int amount_of_students = GetAmountOfStudents(StudFile, fileName, SIZE), number_of_student;
	Person student;

	printf("Choose number of student: ");
	scanf_s("%d", &number_of_student);

	fopen_s(&StudFile, fileName, "r+b");
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return;
	}

	Person* arr = new Person[amount_of_students];
	for (int i = 0; i < amount_of_students; i++) {
		fread(&arr[i], SIZE, 1, StudFile);
	}

	if (number_of_student <= amount_of_students && number_of_student > 0) {
		for (int i = number_of_student - 1; i < amount_of_students - 1; i++) {
			arr[i] = arr[i + 1];
		}
		amount_of_students--;
	}
	else {
		printf("No such student with this number! \n");
	}



	fclose(StudFile);
	fopen_s(&StudFile, fileName, "wb");
	if (StudFile == NULL) {
		printf("Create file Failed!!!\n");
		sleep();
		return;
	}

	for (int i = 0; i < amount_of_students; i++) {
		fwrite(&arr[i], SIZE, 1, StudFile);
	}

	delete[] arr;
	fclose(StudFile);
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
		fopen_s(&StudFile, fileNameCopy, "rb");
		if (StudFile == NULL) {
			printf("\nNo such file with this name in this directory!");
			continue;
		}
		printf("\nOK!\n");
		for (int i = 0; i < My_strlen(fileNameCopy); i++) {
			fileName[i] = fileNameCopy[i];
		}
		break;
	} while (true);
	fclose(StudFile);
	system("pause");
}
void writeIntoFile(FILE* StudFile, char* fileName, const int& SIZE) {

	fopen_s(&StudFile, fileName, "r+b");
	if (StudFile == NULL) {
		printf("\Ge information into output.txt failed!!!\n");
		return;
	}
	int amount_of_students = _filelength(_fileno(StudFile)) / SIZE;
	int amount_of_clever_students = 0;
	Person* array_of_students = new Person[amount_of_students];
	Person* array_of_clever_students = new Person[amount_of_students];
	fread(array_of_students, SIZE, amount_of_students, StudFile);

	fclose(StudFile);

	FILE* FileForOutput;
	fopen_s(&FileForOutput, "output.txt", "w");
	if (FileForOutput == NULL) {
		printf("Create file Failed!!!\n");
		sleep();
		return;
	}
	fprintf(FileForOutput, "------All students-----\n");
	for (int i = 0, j = 0; i < amount_of_students; i++) {
		fprintf(FileForOutput, "%d. %s, %d, %d, %d, %d, %d, %d, %lf\n", i + 1, array_of_students[i].fio, array_of_students[i].year, array_of_students[i].groupNumber, array_of_students[i].marks.math, array_of_students[i].marks.physics, array_of_students[i].marks.informatics, array_of_students[i].marks.chemistry, array_of_students[i].average_score);
		if ((array_of_students[i].fio[0] == -64 || array_of_students[i].fio[0] == 65 || array_of_students[i].fio[0] == -32) && (array_of_students[i].marks.math >= 8)) {
			array_of_clever_students[j++] = array_of_students[i];
			amount_of_clever_students++;
		}
	}
	fprintf(FileForOutput, "------Clever students-----\n");
	for (int i = 0; i < amount_of_clever_students; i++) {
		fprintf(FileForOutput, "%d. %s, %d, %d, %d, %d, %d, %d, %lf\n", i + 1, array_of_clever_students[i].fio, array_of_clever_students[i].year, array_of_clever_students[i].groupNumber, array_of_clever_students[i].marks.math, array_of_clever_students[i].marks.physics, array_of_clever_students[i].marks.informatics, array_of_clever_students[i].marks.chemistry, array_of_clever_students[i].average_score);
	}

	fclose(FileForOutput);
	delete[] array_of_students;
	delete[] array_of_clever_students;
}
void sortByFio (FILE* StudFile, char* fileName, const int& SIZE, bool (*sortType) (char*, char*) ) {
	int amount_of_students = GetAmountOfStudents(StudFile, fileName, SIZE);
	Person student;
	Person* arr = new Person[amount_of_students];

	fopen_s(&StudFile, fileName, "r+b");
	if (StudFile == NULL) {
		printf("Open file Failed!!!\n");
		sleep();
		return;
	}

	for (int i = 0; i < amount_of_students; i++) {
		fread(&arr[i], SIZE, 1, StudFile);
	}
	fclose(StudFile);

	for (int i = 0; i < amount_of_students; i++) {
		for (int j = 0; j < amount_of_students - 1; j++) {
			if (sortType(arr[j].fio, arr[j + 1].fio)) {
				Person tmp_student = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp_student;
			}
		}
	}


	fopen_s(&StudFile, fileName, "w+b");
	if (StudFile == NULL) {
		printf("Create file Failed!!!\n");
		sleep();
		return;
	}

	for (int i = 0; i < amount_of_students; i++) {
		fwrite(&arr[i], SIZE, 1, StudFile);
	}

	fclose(StudFile);

	printf("Done!\n");
	delete[] arr;
	system("pause");

}
