#include "Library.h"

Library::Books::Books(const Book &bb, Books *prv) : b(bb), next(NULL) {
  if (prv != NULL)
    prv->next = this;
}
Library::Books::~Books() {
  if (next != NULL)
    delete next;
}

ostream &operator<<(ostream &s, const Library::Books &other) {
  s << other.b;
  Library::Books *ptr = other.next;
  while (ptr != NULL) {
    s << endl << ptr->b;
    ptr = ptr->next;
  }
  return s;
}

bool Library::compareByTitle(const Book &first, const Book &second) {
  return strcmp(first.title, second.title) == 0;
}
bool Library::compareByNumber(const Book &first, const Book &second) {
  return first.number == second.number;
}
bool Library::compareByAuthor(const Book &first, const Book &second) {
  return strcmp(first.author, second.author) == 0;
}
bool Library::compareByPublisher(const Book &first, const Book &second) {
  return strcmp(first.publisher, second.publisher) == 0;
}
bool Library::compareByQuantity(const Book &first, const Book &second) {
  return first.available_quantity == second.available_quantity;
}
bool Library::compareByCost(const Book &first, const Book &second) {
  return first.cost > second.cost;
}

uint Library::search(Books *&collection, const Book &other, func cmp,
                     bool onlyOne) {
  uint n = rfs.GetNumberOfRecords(), cnt = 0;
  Book cur;
  Books *last = collection;
  for (uint i = 0; i < n; ++i) {
    if (!rfs.get(&cur, i))
      break;
    if (cur.isActive() && cmp(cur, other)) {
      last = new Books(cur, last);
      if (collection == NULL)
        collection = last;
      ++cnt;
      if (onlyOne)
        break;
    }
  }
  return cnt;
}

Library::Library(const char filename[])
    : MAX(std::numeric_limits<std::streamsize>::max()),
      rfs(sizeof(Book), filename) {}
Library::~Library() {}

bool Library::addNewBook() {
  Book newBook;
  cout << "\tEnter its title: " << flush;
  cin.getline(newBook.title, Book::MAX);
  cout << "\tEnter its number: " << flush;
  cin >> newBook.number;
  cin.ignore(MAX, '\n');
  cout << "\tEnter its author: " << flush;
  cin.getline(newBook.author, Book::MAX);
  cout << "\tEnter its publisher: " << flush;
  cin.getline(newBook.publisher, Book::MAX);
  cout << "\tEnter the available quantity: " << flush;
  cin >> newBook.available_quantity;
  cin.ignore(MAX, '\n');
  cout << "\tEnter the number of pages: " << flush;
  cin >> newBook.number_of_pages;
  cin.ignore(MAX, '\n');
  cout << "\tEnter its cost: " << flush;
  cin >> newBook.cost;
  cin.ignore(MAX, '\n');
  if (rfs.put(&newBook)) {
    cout << "\tThe book has been added successfully" << endl;
    return true;
  }
  return false;
}

bool Library::findBook() {
  cout << "\tFind book by title (t) or number (n)? " << flush;
  char op;
  cin >> op;
  cin.ignore(MAX, '\n');
  Books *lst = NULL;
  Book other;
  if (op == 't') {
    cout << "\tEnter its title: " << flush;
    cin.getline(other.title, Book::MAX);
    search(lst, other, compareByTitle, true);
  } else {
    cout << "\tEnter its number: " << flush;
    cin >> other.number;
    cin.ignore(MAX, '\n');
    search(lst, other, compareByNumber, true);
  }
  if (lst == NULL) {
    cout << "\tThe book was not found in the library" << endl;
    return false;
  }
  cout << *lst << endl;
  delete lst;
  return true;
}

bool Library::findByAuthor() {
  cout << "\tEnter the author: " << flush;
  Book other;
  cin.getline(other.author, Book::MAX);
  Books *lst = NULL;
  uint num = search(lst, other, compareByAuthor);
  cout << '\t' << num << " book";
  if (num == 1)
    cout << " was";
  else
    cout << "s were";
  cout << " found";
  if (num != 0) {
    cout << ":\n";
    cout << *lst;
    delete lst;
  }
  cout << endl;
  return num;
}

bool Library::findByPublisher() {
  cout << "\tEnter the publisher: " << flush;
  Book other;
  cin.getline(other.publisher, Book::MAX);
  Books *lst = NULL;
  uint num = search(lst, other, compareByPublisher);
  cout << '\t' << num << " book";
  if (num == 1)
    cout << " was";
  else
    cout << "s were";
  cout << " found";
  if (num != 0) {
    cout << ":\n";
    cout << *lst;
    delete lst;
  }
  cout << endl;
  return num;
}

bool Library::modifyCost() {
  cout << "\tEnter the book's number: " << flush;
  Book other;
  cin >> other.number;
  cin.ignore(MAX, '\n');
  Books *lst = NULL;
  if (!search(lst, other, compareByNumber, true)) {
    cout << "\tThe book was not found in the library" << endl;
    return false;
  }
  cout << "\tEnter its new cost: " << flush;
  cin >> lst->b.cost;
  cin.ignore(MAX, '\n');
  if (!rfs.update(&lst->b)) {
    cout << "\tThe book couldn't be modified" << endl;
    return false;
  }
  cout << "\tThe book was modified successfully" << endl;
  delete lst;
  return true;
}

bool Library::modifyQuantity() {
  cout << "\tEnter the book's number: " << flush;
  Book other;
  cin >> other.number;
  cin.ignore(MAX, '\n');
  Books *lst = NULL;
  if (!search(lst, other, compareByNumber, true)) {
    cout << "\tThe book was not found in the library" << endl;
    return false;
  }
  cout << "\tEnter its new quantity: " << flush;
  cin >> lst->b.available_quantity;
  cin.ignore(MAX, '\n');
  if (!rfs.update(&lst->b)) {
    cout << "\tThe book couldn't be modified" << endl;
    return false;
  }
  cout << "\tThe book was modified successfully" << endl;
  delete lst;
  return true;
}

bool Library::removeBook() {
  cout << "\tEnter the book's number: " << flush;
  Book other;
  cin >> other.number;
  cin.ignore(MAX, '\n');
  Books *lst = NULL;
  if (!search(lst, other, compareByNumber, true)) {
    cout << "\tThe book was not found in the library" << endl;
    return false;
  }
  if (!rfs.del(&lst->b)) {
    cout << "\tThe book couldn't be removed" << endl;
    return false;
  }
  cout << "\tThe book was removed successfully" << endl;
  delete lst;
  return true;
}

bool Library::sortByTitle() {
  Book cur, other;
  uint n = rfs.GetNumberOfRecords();
  bool ok = true;
  for (uint i = 0; i + 1 < n; ++i) {
    if (!rfs.get(&cur, i)) {
      ok = false;
      break;
    }
    for (uint j = i + 1; j < n; ++j) {
      if (!rfs.get(&other, j)) {
        ok = false;
        break;
      }
      if (!other.isActive())
        continue;
      if (!cur.isActive() || strcmp(cur.title, other.title) > 0) {
        if (!rfs.put(&cur, j)) {
          ok = false;
          break;
        }
        cur = other;
      }
    }
    ok &= rfs.put(&cur, i);
    if (!ok)
      break;
  }
  if (ok && rfs.clean()) {
    cout << "\tThe library has been sorted successfully" << endl;
    return true;
  }
  return false;
}

bool Library::findSoldOut() {
  Books *lst = NULL;
  uint num = search(lst, Book(), compareByQuantity);
  cout << '\t' << num << " book";
  if (num == 1)
    cout << " was";
  else
    cout << "s were";
  cout << " found";
  if (num != 0) {
    cout << ":\n";
    cout << *lst;
    delete lst;
  }
  cout << endl;
  return num;
}

bool Library::findByCost() {
  cout << "\tEnter the maximum allowable cost: " << flush;
  Book other;
  cin >> other.cost;
  cin.ignore(MAX, '\n');
  Books *lst = NULL;
  uint num = search(lst, other, compareByCost);
  cout << '\t' << num << " book";
  if (num == 1)
    cout << " was";
  else
    cout << "s were";
  cout << " found";
  if (num != 0) {
    cout << ":\n";
    cout << *lst;
    delete lst;
  }
  cout << endl;
  return num;
}

bool Library::print() {
  uint n = rfs.GetNumberOfRecords();
  Book cur;
  bool ok = false;
  for (uint i = 0; i < n; ++i) {
    if (!rfs.get(&cur, i))
      cout << "\tError occured" << endl;
    if (cur.isActive()) {
      cout << cur << endl;
      ok = true;
    }
  }
  if (!ok)
    cout << "\tThe library is empty" << endl;
  return rfs.good();
}
