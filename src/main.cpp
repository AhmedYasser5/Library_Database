#include "Library.h"
#include <iostream>
#include <limits>
using namespace std;
int main() {
  const long MAX = numeric_limits<streamsize>::max();
  cout << "\tWelcome to the digital library program\n";
  Library lib("Library.db");
  while (true) {
    cout << "\tChoose one of the following options:\n";
    cout << "\t\t 1- Add a new book to the library\n";
    cout << "\t\t 2- Search for a book by title\n";
    cout << "\t\t 3- Search for a book by number\n";
    cout << "\t\t 4- Find all books by author\n";
    cout << "\t\t 5- Find all books by publisher\n";
    cout << "\t\t 6- Modify the cost of a book\n";
    cout << "\t\t 7- Modify the quantity of a book\n";
    cout << "\t\t 8- Remove a book from the library\n";
    cout << "\t\t 9- Sort the books by title\n";
    cout << "\t\t10- Find all sold-out books (zero quantity)\n";
    cout << "\t\t11- Find all books that are more expensive than a given "
         << "value\n";
    cout << "\t\t12- Exit the program\n";
    cout << "\t\t**- Print the whole library\n";
    cout << "\tYour choice is: " << flush;
    int option;
    cin >> option;
    cin.ignore(MAX, '\n');
    cout << endl;
    if (option == 1) {
      char again = 'n';
      do {
        lib.addNewBook();
        cout << "Add another book (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 2) {
      char again = 'n';
      do {
        lib.findBook(0);
        cout << "Find another book by title (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 3) {
      char again = 'n';
      do {
        lib.findBook(1);
        cout << "Find another book by number (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 4) {
      char again = 'n';
      do {
        lib.findByAuthor();
        cout << "Find all books by another author (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 5) {
      char again = 'n';
      do {
        lib.findByPublisher();
        cout << "Find all books by another publisher (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 6) {
      char again = 'n';
      do {
        lib.modifyCost();
        cout << "Modify the cost of another book (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 7) {
      char again = 'n';
      do {
        lib.modifyQuantity();
        cout << "Modify the cost of another book (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 8) {
      char again = 'n';
      do {
        lib.removeBook();
        cout << "Remove another book (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 9) {
      lib.sortByTitle();
      cout << endl;
      lib.print();
    } else if (option == 10)
      lib.findSoldOut();
    else if (option == 11) {
      char again = 'n';
      do {
        lib.findByCost();
        cout << "Find books by another cost (y/n)? " << flush;
        cin >> again;
        cin.ignore(MAX, '\n');
        cout << endl;
      } while (again == 'y');
    } else if (option == 12)
      break;
    else
      lib.print();
    cout << endl;
#ifdef __unix__
    system("read -p \"Press return key to continue...\"");
    system("clear");
#else
    system("pause");
    system("cls");
#endif
  }
  return 0;
}
