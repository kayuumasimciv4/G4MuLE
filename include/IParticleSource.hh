#ifndef IPARTICLESOURCE_hh
#define IPARTICLESOURCE_hh 1
#include <G4ThreeVector.hh>
class IParticleSource
{
public:
  virtual ~IParticleSource(){};

  virtual G4ThreeVector GetParticleMomentum() = 0;
  virtual G4ThreeVector GetParticlePosition() = 0;

private:
};
#endif