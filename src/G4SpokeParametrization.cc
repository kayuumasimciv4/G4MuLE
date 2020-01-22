

#include "G4SpokeParametrization.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeometryConstants.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4SpokeParametrization::G4SpokeParametrization()
    : G4VPVParameterisation()
{
  G4double pore_angle = G4GeometryConstants::Getpore_angle();
  G4double curvature_radius = G4GeometryConstants::Getcurvature_radius();
  G4double wafer_thickness = G4GeometryConstants::Getwafer_thickness();

  for (auto copyNo = 0; copyNo < kNofspokeCells; copyNo++)
  {

    double C = (-copyNo + (kNofEmRows - 1) / 2);
    fYCell[copyNo] = (curvature_radius - wafer_thickness / 2) * sin(C * pore_angle);
    fZCell[copyNo] = (curvature_radius - wafer_thickness / 2) * (1 - cos(C * pore_angle));
    rXCell[copyNo] = C * pore_angle;

    ;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4SpokeParametrization::~G4SpokeParametrization()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4SpokeParametrization::ComputeTransformation(
    const G4int copyNo, G4VPhysicalVolume *physVol) const
{

  G4RotationMatrix *myRot = new G4RotationMatrix();
  myRot->rotateY(rXCell[copyNo]);
  physVol->SetRotation(myRot);

  physVol->SetTranslation(G4ThreeVector(fXCell[copyNo], 0, -fZCell[copyNo]));
  delete myRot;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......