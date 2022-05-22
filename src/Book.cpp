#include "Book.h"
Book::Book() : Record(), available_quantity(0), number_of_pages(0) {
  strcpy(title, "");
  strcpy(author, "");
  strcpy(publisher, "");
}
Book::Book(const Book &other) : Book() { *this = other; }
Book::~Book() {}
Book &Book::operator=(const Book &other) {
  this->Record::operator=(&other);
  number = other.number;
  available_quantity = other.available_quantity;
  number_of_pages = other.number_of_pages;
  cost = other.cost;
  strcpy(title, other.title);
  strcpy(author, other.author);
  strcpy(publisher, other.publisher);
  return *this;
}
ostream &operator<<(ostream &s, const Book &b) {
  s << "\t  ***\tNumber: " << b.number;
  s << "\n\t\tBook Title: " << b.title;
  s << "\n\t\tAuthor: " << b.author;
  s << "\n\t\tPublisher: " << b.publisher;
  s << "\n\t\tAvailable Quantity: " << b.available_quantity;
  s << "\n\t\tNumber of Pages: " << b.number_of_pages;
  s << "\n\t\tCost: " << b.cost;
  return s;
}
