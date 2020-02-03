#include "G4GeometryConstants.hh"

G4GeometryConstants::G4GeometryConstants() {}
G4GeometryConstants::~G4GeometryConstants() {}

G4double G4GeometryConstants::focal_length = 300 * mm;
G4double G4GeometryConstants::wafer_thickness = 300 * um;
G4double G4GeometryConstants::curvature_radius = focal_length * 2;
G4double G4GeometryConstants::spoke_width = 300 * um;
G4double G4GeometryConstants::pore_size = 40 * um;
G4double G4GeometryConstants::hole_size = 20 * um;
G4double G4GeometryConstants::spoke_thickness = 1 * um;
G4double G4GeometryConstants::effarea_size = 9 * cm;
//G4double G4GeometryConstants::randomize_fraction = 0;
G4double G4GeometryConstants::randomize_fraction = 12.8;

G4double G4GeometryConstants::plate_size = 10 * cm;