
#ifndef G4PoreN_hh
#define G4PoreN_hh 1

#include "globals.hh"

constexpr G4int kNofEmColumns = 3183; //9cm*(cos(45deg)+sin(45deg))/40um
constexpr G4int kNofEmRows = 3183;    //9cm*(cos(45deg)+sin(45deg))/40um
//constexpr G4int kNofEmColumns = 31; //for test
//constexpr G4int kNofEmRows = 31;    //for test

constexpr G4int kNofEmCells = kNofEmColumns * kNofEmRows;
constexpr G4int kNofspokeCells = 3000;

// G4int G4GeometryConstants:: kNofEmColumns = 2251; //9cm/40um
// G4int G4GeometryConstants:: kNofEmRows = 2251;    //9cm/40um

#endif