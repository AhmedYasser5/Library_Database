// Record.cpp: implementation of the Record class.
//
//////////////////////////////////////////////////////////////////////
#include "Record.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Record::Record() : active(true) {}
Record::Record(const Record &other) : Record() { *this = other; }
Record::~Record() {}
bool Record::isActive() const { return active; }
Record &Record::operator=(const Record &other) { return *(*this = &other); }
Record *Record::operator=(const Record *other) {
  active = other->active;
  RecordNumber = other->RecordNumber;
  return this;
}
