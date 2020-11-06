#ifndef TESTSOURCE_hh
#define TESTSOURCE_hh 1
#include "IParticleSource.hh"
#include "globals.hh"
#include <G4ThreeVector.hh>
class TestSource : public IParticleSource
{
public:
  TestSource(G4double pos_x, G4double pos_y, G4double pos_z, G4double dir_x, G4double dir_y, G4double dir_z);
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

  void SetPos_X(G4double px) { pos_x = px; };
  void SetPos_Y(G4double py) { pos_y = py; };
  void SetPos_Z(G4double pz) { pos_z = pz; };
  void SetDir_X(G4double dx) { dir_x = dx; };
  void SetDir_Y(G4double dy) { dir_y = dy; };
  void SetDir_Z(G4double dz) { dir_z = dz; };

private:
  G4double centerangle_x;
  G4double centerangle_y;
  G4double energy;
  G4double pos_x;
  G4double pos_y;
  G4double pos_z;
  G4double dir_x;
  G4double dir_y;
  G4double dir_z;
  G4int plateid;
};

#endif