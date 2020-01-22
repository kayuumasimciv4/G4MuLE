
#ifndef G4SpokeParametrization_H
#define G4SpokeParametrization_H 1
#include "globals.hh"
#include "G4VPVParameterisation.hh"
#include <array>
#include "G4PoreN.hh"

class G4VPhysicalVolume;

/// EM Calorimeter cell parameterisation

class G4SpokeParametrization : public G4VPVParameterisation
{
public:
  G4SpokeParametrization();
  virtual ~G4SpokeParametrization();

  virtual void ComputeTransformation(
      const G4int copyNo, G4VPhysicalVolume *physVol) const;

private:
  std::array<G4double, kNofEmCells> fXCell;
  std::array<G4double, kNofEmCells> fYCell;
  std::array<G4double, kNofEmCells> fZCell;
  std::array<G4double, kNofEmCells> rXCell;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif