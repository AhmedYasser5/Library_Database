#ifndef BOOK_HEADER
#define BOOK_HEADER
#include "Record.h"
#include <cstring>
#include <ostream>
using std::ostream;
class Library;
class Book : public Record {
private:
  enum { MAX = 100 };
  uint number, available_quantity, number_of_pages, cost;
  char title[MAX], author[MAX], publisher[MAX];
  friend class Library;

public:
  Book();
  Book(const Book &other);
  virtual ~Book();
  Book &operator=(const Book &other);
  friend ostream &operator<<(ostream &s, const Book &b);
};
#endif
