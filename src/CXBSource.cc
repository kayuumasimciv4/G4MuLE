#include "CXBSource.hh"
#include "globals.hh"
#include "G4GeometryConstants.hh"
#include <G4ThreeVector.hh>
#include "Randomize.hh"
#include "G4RandomDirection.hh"

CXBSource::CXBSource(G4double ax, G4double ay, G4double en, G4int pi)
{
  SetCenterAngle_X(ax);
  SetCenterAngle_Y(ay);
  SetPlateID(pi);
  SetMonoEnergy(en);
};
void CXBSource::Update(G4double ax, G4double ay, G4double en, G4int pi)
{
  //SetCenterAngle_X(ax);
  //SetCenterAngle_Y(ay);
  //SetPlateID(pi);
  SetMonoEnergy(en);
};

G4ThreeVector CXBSource::GetParticleMomentum()
{
  auto __dir = G4RandomDirection();
  auto x = __dir.getX();
  auto y = __dir.getY();
  auto z = __dir.getZ();

  SetCenterAngle_X(atan(x / z));
  SetCenterAngle_Y(atan(y / z));
  auto _dir = G4ThreeVector(tan(centerangle_x), tan(centerangle_y), 1);
  auto dir = G4ThreeVector(tan(centerangle_x) / _dir.mag(), tan(centerangle_y) / _dir.mag(), 1 / _dir.mag());

  return dir;
};

G4ThreeVector CXBSource::GetParticlePosition()
{
  G4double effarea_size = G4GeometryConstants::Geteffarea_size();
  G4double focal_length = G4GeometryConstants::Getfocal_length();
  G4ThreeVector p1, p2, p3, zeropoint;

  p1 = G4ThreeVector(-effarea_size / 2, -effarea_size / 2, 0);
  p2 = G4ThreeVector(effarea_size / 2, -effarea_size / 2, 0);
  p3 = G4ThreeVector(-effarea_size / 2, effarea_size / 2, 0);
  zeropoint = G4ThreeVector(0, 0, focal_length);

  //auto aim_at = zeropoint + (G4UniformRand() - 0.5) * (p2 - p1) + (G4UniformRand() - 0.5) * (p3 - p1);
  auto aim_at = zeropoint;

  //auto dir = GetParticleMomentum();
  auto _dir = G4ThreeVector(tan(centerangle_x), tan(centerangle_y), 1);
  auto dir = G4ThreeVector(tan(centerangle_x) / _dir.mag(), tan(centerangle_y) / _dir.mag(), 1 / _dir.mag());
  auto dir2 = dir.orthogonal();
  dir2.setR(effarea_size * 4 / 2 * sqrt(G4UniformRand()));
  dir2.rotate(2 * CLHEP::pi * G4UniformRand(), dir);

  G4double path_length = 40 * cm;

  auto start = aim_at + path_length * dir + dir2;
  //std::cout << "X= " << dir.x() << " Y= " << dir.y() << " Z= " << dir.z() << std::endl;
  //std::cout << "X= " << start.x() << " Y= " << start.y() << " Z= " << start.z() << std::endl;
  return start;
};