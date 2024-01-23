#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
namespace fs = std::filesystem;
class book {
private:
	string title, genre, authorsName, authorsSurname, anotation;
	int year, numberOfPages;
public:
	void addInfoBookToFile(string autSurname, string autName);
	void addBook();
	void listBooks();
	void listAutorsBooks();
	void delBook();
	void searchInfoBook();
};
class author {
private:
	string surname, name, dateOfBirth, bio;
	int countBooks;
public:
	void addInfoAuthorToFile();
	void addAuthor();
	void listAuthors();
	void searchAuthor();
};
class library :public book, public author {
public:
	void createAccountUser();
	void usersInfo();
};

void author::addInfoAuthorToFile() {
	string author = "Authors/" + surname + "_" + name + ".txt";
	ofstream fout;
	fout.open(author, ios::app);
	if (fout.is_open()) {
		fout << surname << endl;
		fout << name << endl;
		fout << dateOfBirth << endl;
		fout << "Count of books:" << countBooks << endl;
		fout << bio << endl;
		fout.close();
	}
	else {
		cerr << "Could not open file for writing.\n";
	}
}

void author::addAuthor() {
	string path = "Authors/";
	try {
		if (!fs::exists(path)) {
			fs::create_directory(path);
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		cerr << "Error creating a folder 'Authors'" << endl;
	}

	cout << "Enter the author's surname" << endl;
	cin >> surname;
	cout << "Enter the author's name" << endl;
	cin >> name;
	cout << "Enter the author's date if birth" << endl;
	cin >> dateOfBirth;
	cin.ignore();
	cout << "Enter the author's bio" << endl;
	getline(cin, bio);
	cout << "Enter the author's count of books" << endl;
	cin >> countBooks;

	string folderPath = "Authors/";
	ofstream fout;
	folderPath += "listAuthors.txt";
	fout.open(folderPath, ios::app);
	if (fout.is_open()) {
		fout << surname << " " << name << endl;
		fout.close();
	}
	else {
		cerr << "Could not open file for writing.\n";
	}
	addInfoAuthorToFile();
}

void book::addInfoBookToFile(string autSurname, string autName) {
	string path = "books/";

	string folderPath = "books/" + autSurname + autName + "/";
	try {
		if (!fs::exists(folderPath)) {
			if (!fs::create_directory(folderPath)) {
				cerr << "Could not create a folder.\n";
			}
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		cerr << "Error creating a folder" << "books/" + autSurname + autName + "/" << endl;
	}

	string namebook = folderPath + title + ".txt";
	string listbook = folderPath + authorsSurname + "_" + authorsName + ".txt";
	string str = path + "allbooks.txt";
	ofstream fout, flist, llist;
	fout.open(namebook, ios::app);
	if (fout.is_open()) {
		fout << title << endl;
		fout << "Genre: " << genre << endl;
		fout << "Autor`s name: " << authorsName << endl;
		fout << "Autor`s surname: " << authorsSurname << endl;
		fout << "Year of writing the book: " << year << endl;
		fout << "Number of pages: " << numberOfPages << endl;
		fout << "Anotation: " << anotation << endl;
		fout.close();
	}
	else {
		cerr << "Error opening a file to record book information" << endl;
	}
	flist.open(listbook, ios::app);
	if (flist.is_open()) {
		flist << title << endl;
		flist.close();
	}
	else {
		cerr << "Error opening a file to write a book list" << endl;
	}
	llist.open(str, ios::app);
	if (llist.is_open()) {
		llist << title << endl;
		llist.close();
	}
	else {
		cerr << "Error opening a file to write a book list" << endl;
	}
}

void book::addBook() {
	cin.ignore();
	cout << "Enter the title of the book" << endl;
	getline(cin, title);
	cout << "Enter the genre of the book" << endl;
	cin >> genre;
	cout << "Enter the year the book was written" << endl;
	cin >> year;
	cout << "Enter the number of pages in the book" << endl;
	cin >> numberOfPages;
	cout << "Enter an annotation" << endl;
	cin.ignore();
	getline(cin, anotation);
	cout << "Enter the author's surname" << endl;
	cin >> authorsSurname;
	cout << "Enter the author's name" << endl;
	cin >> authorsName;

	string folderPath = "books/";
	try {
		if (!fs::exists(folderPath)) {
			if (fs::create_directory(folderPath)) {
				addInfoBookToFile(authorsSurname, authorsName);
			}
			else {
				cerr << "Could not create a folder.\n";
			}
		}
		else {
			addInfoBookToFile(authorsSurname, authorsName);
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		cerr << "Error creating a folder" << endl;
	}
}

void author::listAuthors() {
	vector <pair<string, string>>listAutors;
	ifstream fin;
	fin.open("Authors/listAuthors.txt");
	if (fin.is_open()) {
		string fullname;
		while (getline(fin, fullname)) {
			istringstream iss(fullname);
			string Surname, Name;
			iss >> Surname;
			iss.ignore();
			getline(iss, Name);
			listAutors.emplace_back(Surname, Name);
		}
		sort(listAutors.begin(), listAutors.end(),
			[](const auto& a, const auto& b) {
				return a.first < b.first;
			});
		fin.close();
	}
	else {
		cerr << "File opening error" << endl;
	}
	cout << "List of authors:" << endl;
	int i = 1;
	for (const auto& author : listAutors) {
		cout << i << ")" << author.first << " " << author.second << endl;
		i++;
	}
}

void book::listAutorsBooks() {
	vector <string>listAutorsBooks;
	ifstream fin;
	string fn, ln;
	cout << "Enter the author's last name and first name" << endl;
	cin >> ln >> fn;
	string lst = "books/" + ln + fn + "/" + ln + "_" + fn + ".txt";
	fin.open(lst);
	if (fin.is_open()) {
		string Title;
		while (getline(fin, Title)) {
			listAutorsBooks.push_back(Title);
		}
		sort(listAutorsBooks.begin(), listAutorsBooks.end());
	}
	else {
		cerr << "Error opening a file to display a list of books by an author" << endl;
	}
	int i = 1;
	for (const auto& book : listAutorsBooks) {
		cout << i << ")" << book << endl;
		i++;
	}
}

void book::listBooks() {
	vector <string>lst, vec;
	string file = "books/allbooks.txt";
	ifstream fout;
	fout.open(file);
	if (fout.is_open()) {
		string line;
		while (getline(fout, line)) {
			lst.push_back(line);
		}
		sort(lst.begin(), lst.end());
		int count = 1;
		for (const string& vecline : lst) {
			cout << count << ")" << vecline << endl;
			count++;
		}
	}
	else {
		cerr << "Error opening a file with all books" << endl;
	}
}

void book::delBook() {
	string nameBook, ln, fn;
	cout << "Enter the name of the book you want to delete" << endl;
	cin.ignore();
	getline(cin, nameBook);
	cout << "Enter the author's last name and first name" << endl;
	cin >> ln >> fn;
	ifstream fin;
	fin.open("books/allbooks.txt");
	if (fin.is_open()) {
		ofstream outputFile;
		outputFile.open("books/temp.txt");
		if (outputFile.is_open()) {
			string line;
			while (getline(fin, line)) {
				if (nameBook != line) {
					outputFile << line << endl;
				}
			}
			fin.close();
			outputFile.close();
		}
		else {
			cerr << "Error opening a temporary file" << endl;
			fin.close();
		}
	}
	else {
		cerr << "File opening error to remove a book from the list of all books" << endl;
	}

	if (remove("books/allbooks.txt") != 0) {
		cerr << "Error deleting the master file" << endl;
	}

	if (rename("books/temp.txt", "books/allbooks.txt") != 0) {
		cerr << "File renaming error" << endl;
	}

	string filename = "books/" + ln + fn + "/" + nameBook + ".txt";
	if (remove(filename.c_str()) != 0) {
		perror("Error deleting file");
	}
	else {
		cout << "File deleted successfully" << endl;
	}

	ifstream fileOpen;
	string pathFile = "books/" + ln + fn + "/" + ln + "_" + fn + ".txt";
	string path = "books/" + ln + fn + "/" + "temp.txt";
	fileOpen.open(pathFile);
	if (fileOpen.is_open()) {
		ofstream outputFile;
		outputFile.open(path);
		if (outputFile.is_open()) {
			string line;
			while (getline(fileOpen, line)) {
				if (nameBook != line) {
					outputFile << line << endl;
				}
			}
			fileOpen.close();
			outputFile.close();
		}
		else {
			cerr << "Error opening a temporary file" << endl;
			fileOpen.close();
		}
	}
	else {
		cerr << "File opening error to remove a book from the list of all books" << endl;
	}

	if (remove(pathFile.c_str()) != 0) {
		cerr << "Error deleting the master file" << endl;
	}

	if (rename(path.c_str(), pathFile.c_str()) != 0) {
		cerr << "File renaming error" << endl;
	}
}

void author::searchAuthor() {
	string lname, fname, fullname;
	cout << "Enter the author's last name and first name" << endl;
	cin >> lname >> fname;
	ifstream fin;
	fullname = "Authors/" + lname + "_" + fname + ".txt";
	fin.open(fullname);
	if (fin.is_open()) {
		string line;
		cout << "Information about the author:" << endl;
		while (getline(fin, line)) {
			cout << line << endl;
		}
		fin.close();
	}
	else {
		cerr << "Error opening the author's file" << endl;
	}
}

void book::searchInfoBook() {
	string nameBook, ln, fn;
	cout << "Enter the title of the book" << endl;
	cin.ignore();
	getline(cin, nameBook);
	cout << "Enter the author's last name and first name" << endl;
	cin >> ln >> fn;
	ifstream fileOpen;
	string nBook = "books/" + ln + fn + "/" + nameBook + ".txt";
	fileOpen.open(nBook);
	if (fileOpen.is_open()) {
		string line;
		while (getline(fileOpen, line)) {
			cout << line << endl;
		}
		fileOpen.close();
	}
	else {
		cerr << "Error opening book information file" << endl;
	}
	cout << endl;
}

void library::createAccountUser() {
	srand(static_cast<unsigned int>(std::time(0)));
	ofstream addUser;
	string uSurname, uName, uDateOfBirth, password;
	cout << "Enter your last name" << endl;
	cin >> uSurname;
	cout << "Enter your name" << endl;
	cin >> uName;
	cout << "Enter your date of birth" << endl;
	cin >> uDateOfBirth;
	int clubNumber = rand() % 9000 + 1000;
	cout << "Your club number is " << clubNumber << endl;
	cout << "Enter your password" << endl;
	cin >> password;

	string path = "Users/";
	try {
		if (!fs::exists(path)) {
			fs::create_directory(path);
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		cerr << "Error creating a folder 'Users'" << endl;
	}

	ofstream pass;
	string clb = path + to_string(clubNumber) + ".txt";
	pass.open(clb);
	if (pass.is_open()) {
		pass << password << endl;
		pass.close();
	}
	else {
		cerr << "Error opening a file to write a password" << endl;
	}
	string filename = "user" + to_string(clubNumber) + ".txt";
	string pathFile = "Users/" + filename;
	addUser.open(pathFile);
	if (addUser.is_open()) {
		addUser << uSurname << " " << uName << endl;
		addUser << uDateOfBirth << endl;
		addUser.close();
	}
	else {
		cerr << "Error opening a file to create user information" << endl;
	}
}

void library::usersInfo() {
	ifstream fin;
	int clubNuber;
	string password;
	cout << "Enter your club number" << endl;
	cin >> clubNuber;
	string path = "Users/" + to_string(clubNuber) + ".txt";
	fin.open(path, ios::in);
	if (fin.is_open()) {
		string line;
		cout << "Enter your password" << endl;
		cin >> password;
		getline(fin, line);
		if (line == password) {
			ifstream fopen;
			string clb = "Users/";
			clb += "user" + to_string(clubNuber) + ".txt";
			fopen.open(clb, ios::in);
			if (fopen.is_open()) {
				string str;
				while (getline(fopen, str)) {
					cout << str << endl;
				}
			}
			else {
				cerr << "Error opening a file with user information" << endl;
			}
		}
		else {
			cerr << "Incorrect password" << endl;
		}
	}
	else {
		cerr << "There is no such club number!" << endl;
	}
}
