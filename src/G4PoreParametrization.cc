

#include "G4PoreParametrization.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4Constants.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4PoreParametrization::G4PoreParametrization()
    : G4VPVParameterisation()
{
  G4double pore_angle = 2 * asin(pore_size / 2 / curvature_radius) * rad;

  G4long seed = 1;
  G4double mu = 0;
  G4double sigma = pore_angle * randomize_fraction;
  CLHEP::HepRandom::setTheSeed(seed);

  for (auto copyNo = 0; copyNo < kNofEmCells; copyNo++)
  {

    auto column = copyNo / kNofEmRows;
    auto row = copyNo % kNofEmRows;
    double C = (-column + (kNofEmRows - 1) / 2);
    double R = (row - (kNofEmRows - 1) / 2);
    fYCell[copyNo] = (curvature_radius - wafer_thickness / 2) * sin(C * pore_angle);
    fXCell[copyNo] = (curvature_radius - wafer_thickness / 2) * sin(R * pore_angle);
    fZCell[copyNo] = (curvature_radius - wafer_thickness / 2) * (1 - cos(sqrt(pow(C, 2) + pow(R, 2)) * pore_angle));
    rXCell[copyNo] = C * pore_angle;
    rYCell[copyNo] = -R * pore_angle;
    rErrXCell[copyNo] = G4RandGauss::shoot(mu, sigma);
    rErrYCell[copyNo] = G4RandGauss::shoot(mu, sigma);

    ;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4PoreParametrization::~G4PoreParametrization()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4PoreParametrization::ComputeTransformation(
    const G4int copyNo, G4VPhysicalVolume *physVol) const
{
  double C = (kNofEmRows - 1) / 2;
  G4double pore_angle = 2 * asin(pore_size / 2 / curvature_radius) * rad;

  G4double plusalpha = (curvature_radius - wafer_thickness / 2) * (1 - cos(sqrt(pow(C, 2) + pow(C, 2)) * pore_angle));

  G4RotationMatrix *myRot = new G4RotationMatrix();
  myRot->rotateX(rXCell[copyNo] + rErrXCell[copyNo]);
  myRot->rotateY(rYCell[copyNo] + rErrYCell[copyNo]);
  physVol->SetRotation(myRot);

  physVol->SetTranslation(G4ThreeVector(fXCell[copyNo], fYCell[copyNo], -fZCell[copyNo] + plusalpha / 2));
  delete myRot;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......