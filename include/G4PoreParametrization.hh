
#ifndef G4PoreParametrization_H
#define G4PoreParametrization_H 1
#include "globals.hh"
#include "G4VPVParameterisation.hh"
#include <array>
#include "G4PoreN.hh"

class G4VPhysicalVolume;

/// EM Calorimeter cell parameterisation

class G4PoreParametrization : public G4VPVParameterisation
{
public:
  G4PoreParametrization();
  virtual ~G4PoreParametrization();

  virtual void ComputeTransformation(
      const G4int copyNo, G4VPhysicalVolume *physVol) const;

private:
  std::array<G4double, kNofEmCells> fXCell;
  std::array<G4double, kNofEmCells> fYCell;
  std::array<G4double, kNofEmCells> fZCell;
  std::array<G4double, kNofEmCells> rXCell;
  std::array<G4double, kNofEmCells> rYCell;
  std::array<G4double, kNofEmCells> rErrXCell;
  std::array<G4double, kNofEmCells> rErrYCell;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif