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
#include "G4SystemOfUnits.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"

#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "ExXRTG4DetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4VPVParameterisation.hh"
#include "G4PoreParametrization.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4XraySpecularReflectingSurface.hh"
#include "G4PoreN.hh"
#include "G4GeometryConstants.hh"
//#include "G4SpokeParametrization.hh"

ExXRTG4DetectorConstruction::ExXRTG4DetectorConstruction(G4XraySpecularReflectingSurface *property)
    : G4VUserDetectorConstruction(), xray_surface_property(property) {}

ExXRTG4DetectorConstruction::~ExXRTG4DetectorConstruction()
{
  // delete copperVisAttributes;
}

G4VPhysicalVolume *ExXRTG4DetectorConstruction::Construct()
{

  G4double plusalpha = G4GeometryConstants::Getboxdiff_length();
  G4double focal_length = G4GeometryConstants::Getfocal_length();
  G4double wafer_thickness = G4GeometryConstants::Getwafer_thickness();
  G4double curvature_radius = G4GeometryConstants::Getcurvature_radius();
  G4double spoke_width = G4GeometryConstants::Getspoke_width();
  G4double spoke_thickness = G4GeometryConstants::Getspoke_thickness();
  G4double pore_size = G4GeometryConstants::Getpore_size();
  G4double hole_size = G4GeometryConstants::Gethole_size();
  G4double plate_angle = G4GeometryConstants::Getplate_angle();
  G4double effarea_size = G4GeometryConstants::Geteffarea_size();

  G4Material *vacuum = new G4Material("Vacuum", 1.0, 1.01 * g / mole, 1.0E-25 * g / cm3,
                                      kStateGas, 2.73 * kelvin, 3.0E-18 * pascal);
  G4Material *si = new G4Material("si", 14, 28.0855 * g / mole, 2.329 * g / cm3);
  G4Material *pt = new G4Material("pt", 78, 195.08 * g / mole, 21.45 * g / cm3);
  //G4Material *al = new G4Material("al", 13., 26.98 * g / mole, 2.70 * g / cm3);
  //G4Material *ir = new G4Material("ir", 77., 192.22 * g / mole, 22.42 * g / cm3);

  G4Box *solidWorld =
      new G4Box("World",                    //its name
                1.5 * m, 1.5 * m, 1.5 * m); //its size

  G4LogicalVolume *logicWorld =
      new G4LogicalVolume(solidWorld,  //its solid
                          vacuum,      //its material
                          "WorldLog"); //its name

  G4VPhysicalVolume *physWorld =
      new G4PVPlacement(0,               //no rotation
                        G4ThreeVector(), //at (0,0,0)
                        logicWorld,      //its logical volume
                        "PhysWorld",     //its name
                        0,               //its mother  volume
                        false,           //no boolean operation
                        0,               //copy number
                        0);              //overlaps checking

  //---------------------------------------

  //spoke placement
  G4VSolid *Spoke_World_S = new G4Box("Spoke_W_S", effarea_size / 2, effarea_size / 2, spoke_thickness / 2);

  G4LogicalVolume *Spoke_World_L = new G4LogicalVolume(Spoke_World_S, vacuum, "Spoke_World_L");

  G4VSolid *Spoke_S = new G4Box("Spoke_S", effarea_size * sqrt(2) / 2, spoke_width / 2, spoke_thickness / 2);
  Spoke_L = new G4LogicalVolume(Spoke_S, si, "Spoke_L");
  new G4LogicalSkinSurface("SpokeSurface", Spoke_L, xray_surface_property);

  for (auto spokeid = 0; spokeid < 24; spokeid++)
  {
    G4RotationMatrix myRot = G4RotationMatrix();
    myRot.rotateZ(15 * spokeid * deg);
    G4ThreeVector position = G4ThreeVector(0, 0, 0);
    G4Transform3D trans = G4Transform3D(myRot, position);
    new G4PVPlacement(trans, Spoke_L, "spoke", Spoke_World_L, false, spokeid, 0);
  }
  //---------------------------------------

  G4VSolid *LEOpticsWorldSolid = new G4Box("LEOpticsWorldSolid", effarea_size / 2, effarea_size / 2, (wafer_thickness + plusalpha) / 2);
  G4LogicalVolume *LEOpticsWorldLog0 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog0");
  G4LogicalVolume *LEOpticsWorldLog1 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog1");
  G4LogicalVolume *LEOpticsWorldLog2 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog2");
  G4LogicalVolume *LEOpticsWorldLog3 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog3");
  G4LogicalVolume *LEOpticsWorldLog4 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog4");
  G4LogicalVolume *LEOpticsWorldLog5 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog5");
  G4LogicalVolume *LEOpticsWorldLog6 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog6");
  G4LogicalVolume *LEOpticsWorldLog7 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog7");
  G4LogicalVolume *LEOpticsWorldLog8 = new G4LogicalVolume(LEOpticsWorldSolid, vacuum, "LEOpticsWorldLog8");

  G4double pore_size_inside = (curvature_radius - wafer_thickness) / (curvature_radius)*pore_size;
  G4VSolid *Si_Pillar = new G4Trd("Long_Pore_Trd", pore_size_inside / 2, pore_size / 2, pore_size_inside / 2, pore_size / 2, wafer_thickness / 2);
  G4VSolid *Hole_Pillar = new G4Trd("Hole_Pillar", 0, hole_size / 2, 0, hole_size / 2, curvature_radius / 2);

  G4VSolid *Pore = new G4SubtractionSolid("Pore", Si_Pillar, Hole_Pillar, 0, G4ThreeVector(0, 0, (wafer_thickness - curvature_radius) / 2));
  Si_Pore = new G4LogicalVolume(Pore, pt, "Si_Pore_Log");
  new G4LogicalSkinSurface("TargetPtSurface", Si_Pore, xray_surface_property);

  G4PoreParametrization *poreParam0 = new G4PoreParametrization(0 * deg);
  G4PoreParametrization *poreParam1 = new G4PoreParametrization(10 * deg);
  G4PoreParametrization *poreParam2 = new G4PoreParametrization(20 * deg);
  G4PoreParametrization *poreParam3 = new G4PoreParametrization(30 * deg);
  G4PoreParametrization *poreParam4 = new G4PoreParametrization(40 * deg);
  G4PoreParametrization *poreParam5 = new G4PoreParametrization(50 * deg);
  G4PoreParametrization *poreParam6 = new G4PoreParametrization(60 * deg);
  G4PoreParametrization *poreParam7 = new G4PoreParametrization(70 * deg);
  G4PoreParametrization *poreParam8 = new G4PoreParametrization(80 * deg);

  for (auto plateid = 0; plateid < 9; plateid++)
  {
    G4double spoke_Z_default = focal_length + wafer_thickness / 2 + plusalpha / 2 + spoke_thickness / 2;
    //G4double spoke_curvature_radius = (curvature_radius + (wafer_thickness + plusalpha + spoke_thickness) / 2);
    G4RotationMatrix myRot_plate = G4RotationMatrix();
    G4ThreeVector position_plate;
    G4ThreeVector position_spoke;
    G4LogicalVolume *WorldLog;
    G4PoreParametrization *param;
    switch (plateid)
    {
    default:
    case 0:
      position_plate = G4ThreeVector(0, 0, focal_length);
      position_spoke = G4ThreeVector(0, 0, spoke_Z_default);
      WorldLog = LEOpticsWorldLog0;
      param = poreParam0;
      break;

    case 1:
      myRot_plate.rotateY(2 * plate_angle);
      WorldLog = LEOpticsWorldLog1;
      param = poreParam1;

      position_plate =
          G4ThreeVector(focal_length * sin(2 * plate_angle),
                        0,
                        focal_length * cos(2 * plate_angle));

      position_spoke =
          G4ThreeVector(spoke_Z_default * sin(2 * plate_angle),
                        0,
                        spoke_Z_default * cos(2 * plate_angle));

      break;

    case 2:
      myRot_plate.rotate(26.08 * deg, G4ThreeVector(-1 / sqrt(2), 1 / sqrt(2), 0));
      WorldLog = LEOpticsWorldLog2;
      param = poreParam2;

      position_plate =
          G4ThreeVector(focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));

      position_spoke =
          G4ThreeVector(spoke_Z_default * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        spoke_Z_default * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        spoke_Z_default * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));
      break;

    case 3:
      myRot_plate.rotateX(-2 * plate_angle);
      WorldLog = LEOpticsWorldLog3;
      param = poreParam3;
      position_plate =
          G4ThreeVector(0,
                        focal_length * sin(2 * plate_angle),
                        focal_length * cos(2 * plate_angle));

      position_spoke =
          G4ThreeVector(0,
                        spoke_Z_default * sin(2 * plate_angle),
                        spoke_Z_default * cos(2 * plate_angle));
      break;

    case 4:
      myRot_plate.rotate(-26.08 * deg, G4ThreeVector(1 / sqrt(2), 1 / sqrt(2), 0));
      WorldLog = LEOpticsWorldLog4;
      param = poreParam4;
      position_plate =
          G4ThreeVector(-focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));

      position_spoke =
          G4ThreeVector(-spoke_Z_default * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        spoke_Z_default * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        spoke_Z_default * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));

      break;

    case 5:
      myRot_plate.rotateY(-2 * plate_angle);
      WorldLog = LEOpticsWorldLog5;
      param = poreParam5;
      position_plate =
          G4ThreeVector(-focal_length * sin(2 * plate_angle),
                        0,
                        focal_length * cos(2 * plate_angle));
      position_spoke =
          G4ThreeVector(-spoke_Z_default * sin(2 * plate_angle),
                        0,
                        spoke_Z_default * cos(2 * plate_angle));
      break;

    case 6:
      WorldLog = LEOpticsWorldLog6;
      param = poreParam6;
      myRot_plate.rotate(-26.08 * deg, G4ThreeVector(-1 / sqrt(2), 1 / sqrt(2), 0));

      position_plate =
          G4ThreeVector(-focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        -focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));

      position_spoke =
          G4ThreeVector(-spoke_Z_default * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        -spoke_Z_default * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        spoke_Z_default * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));
      break;

    case 7:
      WorldLog = LEOpticsWorldLog7;
      param = poreParam7;
      myRot_plate.rotateX(2 * plate_angle);

      position_plate =
          G4ThreeVector(0,
                        -focal_length * sin(2 * plate_angle),
                        focal_length * cos(2 * plate_angle));

      position_spoke =
          G4ThreeVector(0,
                        -spoke_Z_default * sin(2 * plate_angle),
                        spoke_Z_default * cos(2 * plate_angle));
      break;

    case 8:
      WorldLog = LEOpticsWorldLog8;
      param = poreParam8;
      myRot_plate.rotate(26.08 * deg, G4ThreeVector(1 / sqrt(2), 1 / sqrt(2), 0));

      position_plate =
          G4ThreeVector(focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        -focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));

      position_spoke =
          G4ThreeVector(spoke_Z_default * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        -spoke_Z_default * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                        spoke_Z_default * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));
      break;
    }

    G4Transform3D trans_plate = G4Transform3D(myRot_plate, position_plate);
    G4Transform3D trans_spoke = G4Transform3D(myRot_plate, position_spoke);
    new G4PVPlacement(trans_plate,     //no rotation
                      WorldLog,        //its logical volume
                      "LEOpticsWorld", //its name
                      logicWorld,      //its mother  volume
                      false,           //no boolean operation
                      1,               //copy number
                      0);              //overlaps checking  }

    int cellN = param->GetcellN();
    new G4PVParameterised("Si_Wafer", Si_Pore, WorldLog, kXAxis, cellN, param);

    new G4PVPlacement(
        trans_spoke,
        Spoke_World_L,
        "SpokeWorld",
        logicWorld,
        false,
        2,
        0);
  }

  G4VSolid *TargetBoxWorldSolid = new G4Box("TargetBoxWorldSolid", 20 * cm, 20 * cm, 2 * cm);
  G4LogicalVolume *TargetBoxWorldLog = new G4LogicalVolume(TargetBoxWorldSolid, vacuum, "TargetBoxWorldLog");
  G4VPhysicalVolume *TargetBoxWorld =
      new G4PVPlacement(0,                               //no rotation
                        G4ThreeVector(0., 0., -2. * cm), //at (0,0,0)
                        TargetBoxWorldLog,               //its logical volume
                        "TargetBoxWorldLog",             //its name
                        logicWorld,                      //its mother  volume
                        false,                           //no boolean operation
                        0,                               //copy number
                        0);                              //overlaps checking

  //targetbox placement
  G4Box *targetbox = new G4Box("targetbox", 20. * cm, 20. * cm, 2. * cm); //its size
  G4LogicalVolume *targetbox_Log = new G4LogicalVolume(targetbox, si, "targetbox_Log");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 0 * cm), targetbox_Log, "target", TargetBoxWorldLog, false, 0, 0);

  //auto visAttributes = new G4VisAttributes(G4Colour(0.7, 0.4, 0.1));
  //visAttributes->SetVisibility(false);
  auto brown = G4Colour(0.7, 0.4, 0.1);
  G4VisAttributes *copperVisAttributes = new G4VisAttributes(brown);
  //Spoke_L->SetVisAttributes(copperVisAttributes);
  Spoke_L->SetVisAttributes(G4VisAttributes::Invisible);
  //Spoke_World_L->SetVisAttributes(G4VisAttributes::Invisible);
  Spoke_World_L->SetVisAttributes(copperVisAttributes);

  //LEOpticsWorldLog->SetVisAttributes(G4VisAttributes::Invisible);
  Si_Pore->SetVisAttributes(G4VisAttributes::Invisible);
  //Si_Pore->SetVisAttributes(copperVisAttributes);
  TargetBoxWorldLog->SetVisAttributes(G4VisAttributes::Invisible);

  //targetbox_Log->SetVisAttributes(copperVisAttributes);

  return physWorld;
}