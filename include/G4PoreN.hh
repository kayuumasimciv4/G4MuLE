
#ifndef G4PoreN_hh
#define G4PoreN_hh 1

#include "globals.hh"

constexpr G4int kNofEmColumns = 2885; //9cm*(cos(20deg)+sin(20deg))/40um
constexpr G4int kNofEmRows = 2885;    //9cm*(cos(20deg)+sin(20deg))/40um
constexpr G4int kNofEmCells = kNofEmColumns * kNofEmRows;
constexpr G4int kNofspokeCells = 3000;

#endif