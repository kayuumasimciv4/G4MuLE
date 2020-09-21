#ifndef TESTSOURCE_hh
#define TESTSOURCE_hh 1
#include "IParticleSource.hh"
#include "globals.hh"
#include <G4ThreeVector.hh>
class TesttSource : public IParticleSource
{
public:
  TestSource(G4double anglex, G4double angley, G4double energy, G4int plateid);
  virtual void Update(G4double anglex, G4double angley, G4double energy, G4int plateid);
  virtual G4ThreeVector GetParticleMomentum();
  virtual G4ThreeVector GetParticlePosition();

  void SetCenterAngle_X(G4double ax) { centerangle_x = ax; };
  virtual G4double GetCenterAngle_X() { return centerangle_x; };
  void SetCenterAngle_Y(G4double ay) { centerangle_y = ay; };
  virtual G4double GetCenterAngle_Y() { return centerangle_y; };
  void SetPlateID(G4int n) { plateid = n; };
  virtual G4int GetPlateID() { return plateid; };
  void SetMonoEnergy(G4double en) { energy = en; };
  virtual G4double GetParticleEnergy() { return energy; };

private:
  void DefineCommands();
  G4double centerangle_x;
  G4double centerangle_y;
  G4double energy;
  G4int plateid;
};

#endif