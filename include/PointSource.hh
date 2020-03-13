#ifndef POINTSOURCE_hh
#define POINTSOURCE_hh 1
#include "IParticleSource.hh"
#include "globals.hh"
#include <G4ThreeVector.hh>
class PointSource : public IParticleSource
{
public:
  PointSource(G4double anglex, G4double angley, G4int plateid);
  virtual void Update(G4double anglex, G4double angley, G4int plateid);
  virtual G4ThreeVector GetParticleMomentum();
  virtual G4ThreeVector GetParticlePosition();

  void SetCenterAngle_X(G4double ax) { centerangle_x = ax; };
  G4double GetCenterAngle_X() { return centerangle_x; };
  void SetCenterAngle_Y(G4double ay) { centerangle_y = ay; };
  G4double GetCenterAngle_Y() { return centerangle_y; };
  void SetPlateID(G4int n) { plateid = n; };
  G4int GetPlateID() { return plateid; };

private:
  G4double centerangle_x;
  G4double centerangle_y;
  G4int plateid;
};

#endif