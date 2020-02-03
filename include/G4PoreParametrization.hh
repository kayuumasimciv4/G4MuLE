
#ifndef G4PoreParametrization_H
#define G4PoreParametrization_H 1
#include "globals.hh"
#include "G4VPVParameterisation.hh"
#include <array>
#include "G4PoreN.hh"
#include "G4SystemOfUnits.hh"

class G4VPhysicalVolume;

/// EM Calorimeter cell parameterisation

class G4PoreParametrization : public G4VPVParameterisation
{
public:
  G4PoreParametrization(G4double phaseangle = 0 * deg);
  virtual ~G4PoreParametrization();

  virtual void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const;
  virtual G4double GetcellN() { return cellN; };

private:
  G4int cellN;
  G4double phase_angle;
  G4double *fxcell;
  G4double *fycell;
  G4double *fzcell;
  G4double *rxcell;
  G4double *rycell;
  G4double *rerrxcell;
  G4double *rerrycell;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif