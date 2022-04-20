// RFS.h: interface for the RFS class.
//
//////////////////////////////////////////////////////////////////////
#ifndef RFSInclude
#define RFSInclude
#include "Record.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;
using std::ios;
class RFS {
protected:
  typedef unsigned int uint;
  uint numberOfRecords;
  uint sizeOfRecord;
  std::fstream F;
  char *filename;
  uint recordLocation(uint i) const;

public:
  RFS(int sor, const char filename[]);
  bool get(Record *r, uint i);
  bool put(Record *r, uint i = -1); // single input = append
  bool update(Record *r);
  bool del(Record *r);
  bool good() const;
  uint GetNumberOfRecords() const;
  bool clean();
  virtual ~RFS();
};
#endif
