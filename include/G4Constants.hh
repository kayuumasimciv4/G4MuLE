
#ifndef G4Constants_h
#define G4Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"
//constexpr G4int kNofEmColumns = 3183; //9cm*sqrt(2)/40um
//constexpr G4int kNofEmRows = 3183;    //9cm*sqrt(2)/40um

constexpr G4int kNofEmColumns = 2885; //9cm*(cos(20deg)+sin(20deg))/40um
constexpr G4int kNofEmRows = 2885;    //9cm*(cos(20deg)+sin(20deg))/40um

//constexpr G4int kNofEmColumns = 2251; //9cm/40um
//constexpr G4int kNofEmRows = 2251;    //9cm/40um

//constexpr G4int kNofEmColumns = 10; //for test
//constexpr G4int kNofEmRows = 10;    //for test

constexpr G4int kNofEmCells = kNofEmColumns * kNofEmRows;
constexpr G4int kNofspokeCells = 3000;
constexpr G4double focal_length = 300 * mm;
constexpr G4double wafer_thickness = 300 * um;
constexpr G4double curvature_radius = focal_length * 2;
constexpr G4double spoke_width = 300 * um;
constexpr G4double pore_size = 40 * um;
constexpr G4double hole_size = 20 * um;
constexpr G4double spoke_thickness = 1 * um;
constexpr G4double effarea_size = 9 * cm;
//constexpr G4double randamize_fraction=9.25;
constexpr G4double randomize_fraction = 12.8;
//constexpr G4double randomize_fraction = 0; // for test

#endif