#ifndef IPARTICLESOURCE_hh
#define IPARTICLESOURCE_hh 1
#include <G4ThreeVector.hh>
class IParticleSource
{
public:
  virtual ~IParticleSource(){};
  virtual void Update(G4double anglex, G4double angley, G4double energy, G4int plateid) = 0;

  virtual G4ThreeVector GetParticleMomentum() = 0;
  virtual G4ThreeVector GetParticlePosition() = 0;
  virtual G4double GetCenterAngle_X() = 0;
  virtual G4double GetCenterAngle_Y() = 0;
  virtual G4double GetParticleEnergy() = 0;
  virtual G4int GetPlateID() = 0;

private:
};
#endif