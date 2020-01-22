#ifndef G4GeometryConstants_hh
#define G4GeometryConstants_hh 1
#include "globals.hh"
#include "math.h"
#include "G4SystemOfUnits.hh"
class G4GeometryConstants
{
public:
  G4GeometryConstants();
  virtual ~G4GeometryConstants();
  static void SetkNofEmColumns(G4int val) { kNofEmColumns = val; };
  static G4int GetkNofEmColumns() { return kNofEmColumns; };

  static void SetkNofEmRows(G4int val) { kNofEmRows = val; };
  static G4int GetkNofEmRows() { return kNofEmRows; };

  static G4int GetkNofEmCells() { return kNofEmCells * kNofEmRows; };

  static void Setfocal_length(G4double val) { focal_length = val; };
  static G4double Getfocal_length() { return focal_length; };

  static void Setwafer_thickness(G4double val) { wafer_thickness = val; };
  static G4double Getwafer_thickness() { return wafer_thickness; };

  static void Setcurvature_radius(G4double val) { curvature_radius = val; };
  static G4double Getcurvature_radius() { return curvature_radius; };

  static void Setspoke_width(G4double val) { spoke_width = val; };
  static G4double Getspoke_width() { return spoke_width; };

  static void Setspoke_thickness(G4double val) { spoke_thickness = val; };
  static G4double Getspoke_thickness() { return spoke_thickness; };

  static void Setpore_size(G4double val) { pore_size = val; };
  static G4double Getpore_size() { return pore_size; };

  static void Sethole_size(G4double val) { hole_size = val; };
  static G4double Gethole_size() { return hole_size; };

  static void Seteffarea_size(G4double val) { effarea_size = val; };
  static G4double Geteffarea_size() { return effarea_size; };

  static void Setrandomize_fraction(G4double val) { randomize_fraction = val; };
  static G4double Getrandomize_fraction() { return randomize_fraction; };

  static void Setplate_size(G4double val) { plate_size = val; };
  static G4double Getplate_size() { return plate_size; };

  static G4double Getpore_angle() { return 2 * asin(pore_size / 2 / curvature_radius) * rad; };
  static G4double Getplate_angle() { return plate_size / curvature_radius * rad; };
  static G4double Getboxdiff_length()
  {
    return (curvature_radius - wafer_thickness / 2) * (1 - cos(sqrt(pow((kNofEmRows - 1) / 2, 2) + pow((kNofEmRows - 1) / 2, 2)) * Getpore_angle()));
  }

private:
  static G4int kNofEmColumns;
  static G4int kNofEmRows;
  static G4int kNofEmCells;
  static G4int kNofspokeCells;
  static G4double focal_length;
  static G4double wafer_thickness;
  static G4double curvature_radius;
  static G4double spoke_width;
  static G4double spoke_thickness;
  static G4double pore_size;
  static G4double hole_size;
  static G4double effarea_size;
  static G4double randomize_fraction;
  static G4double plate_size;
};
#endif