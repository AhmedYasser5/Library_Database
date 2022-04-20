#ifndef LIBRARY_HEADER
#define LIBRARY_HEADER
#include "Book.h"
#include "RFS.h"
#include <cstring>
#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::flush;
class Library {
private:
  typedef unsigned int uint;
  typedef bool (*func)(const Book &, const Book &);
  const unsigned long MAX;
  RFS rfs;

public:
  class Books {
  private:
    Book b;
    Books *next;
    Books() = delete;
    Books(const Book &bb, Books *prv = NULL);
    ~Books();
    friend class Library;

  public:
    friend ostream &operator<<(ostream &s, const Books &other);
  };

private:
  static bool compareByTitle(const Book &first, const Book &second);
  static bool compareByNumber(const Book &first, const Book &second);
  static bool compareByAuthor(const Book &first, const Book &second);
  static bool compareByPublisher(const Book &first, const Book &second);
  static bool compareByQuantity(const Book &first, const Book &second);
  static bool compareByCost(const Book &first, const Book &second);
  uint search(Books *&collection, const Book &other, func cmp,
              bool onlyOne = false);

public:
  Library(const char filename[] = "Library.db");
  ~Library();

  bool addNewBook();
  bool findBook();
  bool findByAuthor();
  bool findByPublisher();
  bool modifyCost();
  bool modifyQuantity();
  bool removeBook();
  bool sortByTitle();
  bool findSoldOut();
  bool findByCost();
  bool print();
};
#endif
