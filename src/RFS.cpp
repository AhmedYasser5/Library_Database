// RFS.cpp: implementation of the RFS class.
//
//////////////////////////////////////////////////////////////////////
#include "RFS.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
RFS::~RFS() { F.close(); }
//////////////////////////////////////////////////////////////////
RFS::RFS(int sor, const char filename[])
    : numberOfRecords(0), sizeOfRecord(sor) {
  this->filename = new char[strlen(filename)];
  strcpy(this->filename, filename);
  F.open(filename, ios::app | ios::out | ios::binary);
  F.close();
  F.open(filename, ios::ate | ios::out | ios::in | ios::binary);
  if (F.good()) {
    cout << '\t' << filename << " is open" << endl;
    numberOfRecords = F.tellg() / sizeOfRecord;
    clean();
  } else {
    cout << "\tCould not open " << filename << endl;
  }
}
/////////////////////////////////////////////
bool RFS::get(Record *r, uint i) {
  if (!F.good()) {
    cout << "\tError reading from file" << endl;
    return false;
  }
  if (i < numberOfRecords) {
    F.seekg(recordLocation(i), ios::beg);
    F.read((char *)r, sizeOfRecord);
    return true;
  }
  cout << "\tInvalid get location" << endl;
  return false;
}
/////////////////////////////////////////////
bool RFS::put(Record *r, uint i) {
  if (!F.good()) {
    cout << "\tError writing to file" << endl;
    return false;
  }
  if (i == uint(-1)) { // append
    r->RecordNumber = numberOfRecords;
    numberOfRecords++;
  } else if (i < numberOfRecords)
    r->RecordNumber = i;
  else {
    cout << "\tInvalid put location" << endl;
    return false;
  }
  F.seekg(recordLocation(r->RecordNumber), ios::beg);
  F.write((char *)r, sizeOfRecord);
  return true;
}
/////////////////////////////////////////////
bool RFS::del(Record *r) {
  r->active = false;
  bool ret = update(r);
  return ret && clean();
}
/////////////////////////////////////////////
bool RFS::update(Record *r) { return put(r, r->RecordNumber); }
/////////////////////////////////////////////
bool RFS::good() const { return F.good(); }
/////////////////////////////////////////////
uint RFS::recordLocation(uint i) const { return i * sizeOfRecord; }
/////////////////////////////////////////////
uint RFS::GetNumberOfRecords() const { return numberOfRecords; }
/////////////////////////////////////////////
bool RFS::clean() {
  if (!F.good())
    return false;
  Record *r = (Record *)malloc(sizeOfRecord);
  uint tmp = numberOfRecords;
  while (numberOfRecords) {
    F.seekg(recordLocation(numberOfRecords - 1), ios::beg);
    F.read((char *)r, sizeOfRecord);
    if (!r->isActive())
      numberOfRecords--;
    else
      break;
  }
  free(r);
  if (truncate64(filename, 1LL * sizeOfRecord * numberOfRecords)) {
    numberOfRecords = tmp;
    cout << "Error truncating the file" << endl;
    return false;
  }
  return true;
}
