// Record.h: interface for the Record class.
//
//////////////////////////////////////////////////////////////////////
#ifndef RecoreInclude
#define RecoreInclude
class RFS;
class Record {
protected:
  typedef unsigned int uint;
  uint RecordNumber;
  bool active; // lazy delete
  friend class RFS;

public:
  Record();
  Record(const Record &other);
  virtual ~Record();
  bool isActive() const;
  Record &operator=(const Record &other);
  Record *operator=(const Record *other);
};
#endif
