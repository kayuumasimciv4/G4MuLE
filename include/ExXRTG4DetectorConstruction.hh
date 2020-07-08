// ExXRTG4DetectorConstruction.hh
//
// Giuseppe Vacanti (cosine Science & Computing BV)
// October 14, 2009
//
// This file is part of the XRTG4 Geant4 extension.

//     The XRTG4 Geant4 extension is free software: you can
//     redistribute it and/or modify it under the terms of the GNU
//     General Public License as published by the Free Software
//     Foundation, either version 2 of the License, or (at your
//     option) any later version.

//     XRTG4 Geant4 extension is distributed in the hope that it will
//     be useful, but WITHOUT ANY WARRANTY; without even the implied
//     warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//     PURPOSE.  See the GNU General Public License for more details.

//     You should have received a copy of the GNU General Public
//     License along with XRTG4 Geant4 extension.  If not, see
//     <http://www.gnu.org/licenses/>.
//

#ifndef EXXRTG4DETECTORCONSTRUCTION_HH
#define EXXRTG4DETECTORCONSTRUCTION_HH 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4XraySpecularReflectingSurface;
class G4VPhysicalVolume;

class ExXRTG4DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  ExXRTG4DetectorConstruction(G4XraySpecularReflectingSurface *);
  virtual ~ExXRTG4DetectorConstruction();
  virtual G4VPhysicalVolume *Construct();
  G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

private:
  G4XraySpecularReflectingSurface *xray_surface_property;
  G4LogicalVolume *Si_Pore;
  G4LogicalVolume *Spoke_L;
  G4LogicalVolume *fScoringVolume;
};

#endif // EXXRTG4DETECTORCONSTRUCTION_HH
