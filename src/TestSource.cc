#include "TestSource.hh"
#include "globals.hh"
#include "G4GeometryConstants.hh"
#include <G4ThreeVector.hh>
#include "Randomize.hh"

TestSource::TestSource(G4double pos_x, G4double pos_y, G4double pos_z, G4double dir_x, G4double dir_y, G4double dir_z)
{
  SetCenterAngle_X(0);
  SetCenterAngle_Y(0);
  SetPlateID(0);
  SetMonoEnergy(0.5);

  SetPos_X(pos_x);
  SetPos_Y(pos_y);
  SetPos_Z(pos_z);
  SetDir_X(dir_x);
  SetDir_Y(dir_y);
  SetDir_Z(dir_z);
};
void TestSource::Update(G4double ax, G4double ay, G4double en, G4int pi)
{
  SetCenterAngle_X(0);
  SetCenterAngle_Y(0);
  SetPlateID(0);
  SetMonoEnergy(0.5);
};

G4ThreeVector TesttSource::GetParticleMomentum()
{
  auto dir = G4ThreeVector(dir_x, dir_y, dir_z);
  return dir;
};

G4ThreeVector TestSource::GetParticlePosition()
{
  auto start = G4ThreeVector(pos_x, pos_y, pos_z);
  return start;
};
