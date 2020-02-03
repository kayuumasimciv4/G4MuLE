

#include "G4PoreParametrization.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeometryConstants.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4PoreParametrization::G4PoreParametrization(G4double phaseangle)
    : G4VPVParameterisation()
{
  G4double pore_angle = G4GeometryConstants::Getpore_angle();
  G4double randomize_fraction = G4GeometryConstants::Getrandomize_fraction();
  G4double curvature_radius = G4GeometryConstants::Getcurvature_radius();
  G4double wafer_thickness = G4GeometryConstants::Getwafer_thickness();
  G4double p_size = G4GeometryConstants::Geteffarea_size();
  phase_angle = phaseangle;

  G4long seed = 1;
  G4double mu = 0;
  G4double sigma = pore_angle * randomize_fraction;

  CLHEP::HepRandom::setTheSeed(seed);
  cellN = 0;

  for (auto copyNo = 0; copyNo < kNofEmCells; copyNo++)
  {
    auto column = copyNo / kNofEmRows;
    auto row = copyNo % kNofEmRows;
    double C = (-column + (kNofEmRows - 1) / 2);
    double R = (row - (kNofEmRows - 1) / 2);
    auto _x = (curvature_radius - wafer_thickness / 2) * sin(R * pore_angle);
    auto _y = (curvature_radius - wafer_thickness / 2) * sin(C * pore_angle);
    auto x = _x * cos(phaseangle) - _y * sin(phaseangle);
    auto y = _y * cos(phaseangle) + _x * sin(phaseangle);
    if ((x < p_size / 2) && (x > -p_size / 2) && (y < p_size / 2) && (y > -p_size / 2))
    {
      cellN += 1;
    }
  }
  fxcell = new G4double[cellN];
  fycell = new G4double[cellN];
  fzcell = new G4double[cellN];
  rxcell = new G4double[cellN];
  rycell = new G4double[cellN];
  rerrxcell = new G4double[cellN];
  rerrycell = new G4double[cellN];
  G4int _copyNo = 0;
  for (auto copyNo = 0; copyNo < kNofEmCells; copyNo++)
  {
    auto column = copyNo / kNofEmRows;
    auto row = copyNo % kNofEmRows;
    double C = (-column + (kNofEmRows - 1) / 2);
    double R = (row - (kNofEmRows - 1) / 2);
    auto _x = (curvature_radius - wafer_thickness / 2) * sin(R * pore_angle);
    auto _y = (curvature_radius - wafer_thickness / 2) * sin(C * pore_angle);
    auto x = _x * cos(phaseangle) - _y * sin(phaseangle);
    auto y = _y * cos(phaseangle) + _x * sin(phaseangle);
    if ((x < p_size / 2) && (x > -p_size / 2) && (y < p_size / 2) && (y > -p_size / 2))
    {

      fxcell[_copyNo] = x;
      fycell[_copyNo] = y;
      fzcell[_copyNo] = (curvature_radius - wafer_thickness / 2) * (1 - cos(sqrt(pow(C, 2) + pow(R, 2)) * pore_angle));
      rxcell[_copyNo] = C * pore_angle;
      rycell[_copyNo] = -R * pore_angle;
      rerrxcell[_copyNo] = G4RandGauss::shoot(mu, sigma);
      rerrycell[_copyNo] = G4RandGauss::shoot(mu, sigma);
      _copyNo += 1;
    }
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
  G4double plusalpha = G4GeometryConstants::Getboxdiff_length();
  G4RotationMatrix *myRot = new G4RotationMatrix();
  myRot->rotateZ(-phase_angle);

  myRot->rotateX(rxcell[copyNo] + rerrxcell[copyNo]);
  myRot->rotateY(rycell[copyNo] + rerrycell[copyNo]);

  physVol->SetRotation(myRot);
  physVol->SetTranslation(G4ThreeVector(fxcell[copyNo], fycell[copyNo], -fzcell[copyNo] + plusalpha / 2));

  delete myRot;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......