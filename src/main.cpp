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
    cout << "\t\t 2- Search for a book by the title or number\n";
    cout << "\t\t 3- Find all books written by an author\n";
    cout << "\t\t 4- Find all books published by a publisher\n";
    cout << "\t\t 5- Change the cost of a book\n";
    cout << "\t\t 6- Change the quantity of a book\n";
    cout << "\t\t 7- Remove a book from the library\n";
    cout << "\t\t 8- Sort the books by their titles\n";
    cout << "\t\t 9- Find all sold-out books (zero quantity)\n";
    cout << "\t\t10- Find all books that are more expensive than a given "
         << "value\n";
    cout << "\t\t11- Print the whole library\n";
    cout << "\t\t**- Exit the program\n";
    cout << "\tYour choice: " << flush;
    int option;
    cin >> option;
    cin.ignore(MAX, '\n');
    if (option == 1)
      lib.addNewBook();
    else if (option == 2)
      lib.findBook();
    else if (option == 3)
      lib.findByAuthor();
    else if (option == 4)
      lib.findByPublisher();
    else if (option == 5)
      lib.modifyCost();
    else if (option == 6)
      lib.modifyQuantity();
    else if (option == 7)
      lib.removeBook();
    else if (option == 8)
      lib.sortByTitle();
    else if (option == 9)
      lib.findSoldOut();
    else if (option == 10)
      lib.findByCost();
    else if (option == 11)
      lib.print();
    else
      break;
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
