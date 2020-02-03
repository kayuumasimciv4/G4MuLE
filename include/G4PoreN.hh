
#ifndef G4PoreN_hh
#define G4PoreN_hh 1

#include "globals.hh"

//constexpr G4int kNofEmColumns = 2885; //9cm*(cos(20deg)+sin(20deg))/40um
//constexpr G4int kNofEmRows = 2885;    //9cm*(cos(20deg)+sin(20deg))/40um
constexpr G4int kNofEmColumns = 11; //for test
constexpr G4int kNofEmRows = 11;    //for test

constexpr G4int kNofEmCells = kNofEmColumns * kNofEmRows;
constexpr G4int kNofspokeCells = 3000;

// G4int G4GeometryConstants:: kNofEmColumns = 2251; //9cm/40um
// G4int G4GeometryConstants:: kNofEmRows = 2251;    //9cm/40um

#endif