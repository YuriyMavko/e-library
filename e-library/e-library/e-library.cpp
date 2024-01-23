#include <iostream>
#include "e-library.h"
using namespace std;
int main()
{
    cout << "To use the  e-library, follow the steps below" << endl;
    bool value = false;
    library object;
    int number;
    cout << "To log in as a user, enter 1, as an employee - 2" << endl;
    cin >> number;
    while (!value) {
        if (number == 1) {
            bool variable = false;
            int num;
            cout << "Enter 1 if you already have an account, 2 to create one" << endl;
            cin >> num;
            if (num == 1) {
                int clb;
                string password;
                cout << "Enter your club number" << endl;
                cin >> clb;
                cout << "Enter your password" << endl;
                cin >> password;
                ifstream fin;
                string path = "Users/" + to_string(clb) + ".txt";
                fin.open(path);
                if (fin.is_open()) {
                    string line;
                    getline(fin, line);
                    if (password == line) {
                        variable = true;
                    }
                    else {
                        cerr << "Wrong club number or password" << endl;
                    }
                }
                else {
                    cerr << "Error opening an access file" << endl;
                }
            }
            else if (num == 2) {
                object.createAccountUser();
                variable = true;
            }
            else {
                cerr << "Input error" << endl;
            }
            if (variable) {
                int val;
                cout << "Enter 1 if you want to display the list of authors" << endl;
                cout << "Enter 2 if you want to display the author's books" << endl;
                cout << "Enter 3 if you want to display a list of books" << endl;
                cout << "Enter 4 if you want to find the author" << endl;
                cout << "Enter 5 if you want to find information about the book" << endl;
                cout << "Enter 6 if you want to find information about the user" << endl;
                cin >> val;
                switch (val) {
                case 1: {
                    object.listAuthors();
                }break;

                case 2: {
                    object.listAutorsBooks();
                }break;

                case 3: {
                    object.listBooks();
                }break;

                case 4: {
                    object.searchAuthor();
                }break;

                case 5: {
                    object.searchInfoBook();
                }break;

                case 6: {
                    object.usersInfo();
                }break;

                default: {
                    cerr << "Input error" << endl;
                }
                }
            }
        }
        else if (number == 2) {
            string password;
            cout << "Enter the employee's password" << endl;
            cin >> password;
            if (password == "emplo8751") {
                int digit;
                cout << "Enter 1 if you want to add an author" << endl;
                cout << "Enter 2 if you want to add a book" << endl;
                cout << "Enter 3 if you want to display a list of authors" << endl;
                cout << "Enter 4 if you want to display the author's books" << endl;
                cout << "Enter 5 if you want to display a list of books" << endl;
                cout << "Enter 6 if you want to delete the book" << endl;
                cout << "Enter 7 if you want to find information about the author" << endl;
                cout << "Enter 8 if you want to find information about the book" << endl;
                cout << "Enter 9 if you want to find information about the user" << endl;
                cin >> digit;
                switch (digit) {
                case 1: {
                    object.addAuthor();
                }break;

                case 2: {
                    object.addBook();
                }break;

                case 3: {
                    object.listAuthors();
                }break;

                case 4: {
                    object.listAutorsBooks();
                }break;

                case 5: {
                    object.listBooks();
                }break;

                case 6: {
                    object.delBook();
                }break;

                case 7: {
                    object.searchAuthor();
                }break;

                case 8: {
                    object.searchInfoBook();
                }break;

                case 9: {
                    object.usersInfo();
                }break;
                default:
                    cout << "Input error" << endl;
                }
            }
            else {
                cout << "Input error" << endl;
            }
        }
        else {
            cerr << "Employee password is incorrect" << endl;
        }
        int num;
        cout << "If you want to continue, press 1, otherwise press any other digit" << endl;
        cin >> num;
        if (num != 1)value = true;
    }
    cout << "The end" << endl;
}