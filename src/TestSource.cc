#include "TestSource.hh"
#include "globals.hh"
#include "G4GeometryConstants.hh"
#include <G4ThreeVector.hh>
#include "Randomize.hh"

PointSource::PointSource(G4double ax, G4double ay, G4double en, G4int pi)
{
  SetCenterAngle_X(ax);
  SetCenterAngle_Y(ay);
  SetPlateID(pi);
  SetMonoEnergy(en);
  DefineCommands();
};
void PointSource::Update(G4double ax, G4double ay, G4double en, G4int pi)
{
  SetCenterAngle_X(ax);
  SetCenterAngle_Y(ay);
  SetPlateID(pi);
  SetMonoEnergy(en);
};

G4ThreeVector PointSource::GetParticleMomentum()
{
  auto dir = G4ThreeVector(tan(centerangle_x), tan(centerangle_y), 1);
  return dir;
};

G4ThreeVector PointSource::GetParticlePosition()
{
  G4double plate_angle = G4GeometryConstants::Getplate_angle();
  G4double effarea_size = G4GeometryConstants::Geteffarea_size();
  G4double focal_length = G4GeometryConstants::Getfocal_length();
  G4ThreeVector p1, p2, p3, zeropoint;
  switch (plateid)
  {
  default:
  case 0:
    p1 = G4ThreeVector(-effarea_size / 2, -effarea_size / 2, 0);
    p2 = G4ThreeVector(effarea_size / 2, -effarea_size / 2, 0);
    p3 = G4ThreeVector(-effarea_size / 2, effarea_size / 2, 0);
    zeropoint = G4ThreeVector(0, 0, focal_length);
    break;
  case 1:
    p1 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2, effarea_size / 2 * sin(2 * plate_angle));
    p2 = G4ThreeVector(effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2, -effarea_size / 2 * sin(2 * plate_angle));
    p3 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2, effarea_size / 2 * sin(2 * plate_angle));
    zeropoint = G4ThreeVector(focal_length * sin(2 * plate_angle),
                              0,
                              focal_length * cos(2 * plate_angle));
    break;
  case 2:
    p1 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2 * sqrt(2) * sin(2 * plate_angle));
    p2 = G4ThreeVector(effarea_size / 2, -effarea_size / 2, 0);
    p3 = G4ThreeVector(-effarea_size / 2, effarea_size / 2, 0);
    zeropoint = G4ThreeVector(focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                              focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                              focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));
    break;

  case 3:
    p1 = G4ThreeVector(-effarea_size / 2, -effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2 * sin(2 * plate_angle));
    p2 = G4ThreeVector(-effarea_size / 2, effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2 * sin(2 * plate_angle));
    p3 = G4ThreeVector(effarea_size / 2, -effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2 * sin(2 * plate_angle));
    zeropoint = G4ThreeVector(0,
                              focal_length * sin(2 * plate_angle),
                              focal_length * cos(2 * plate_angle));
    break;

  case 4:
    p1 = G4ThreeVector(effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2 * sqrt(2) * sin(2 * plate_angle));
    p2 = G4ThreeVector(effarea_size / 2, effarea_size / 2, 0);
    p3 = G4ThreeVector(-effarea_size / 2, -effarea_size / 2, 0);
    zeropoint = G4ThreeVector(-focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                              focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                              focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));
    break;

  case 5:
    p1 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2, -effarea_size / 2 * sin(2 * plate_angle));
    p2 = G4ThreeVector(effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2, effarea_size / 2 * sin(2 * plate_angle));
    p3 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2, -effarea_size / 2 * sin(2 * plate_angle));
    zeropoint = G4ThreeVector(-focal_length * sin(2 * plate_angle),
                              0,
                              focal_length * cos(2 * plate_angle));
    break;

  case 6:
    p1 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2 * sqrt(2) * sin(2 * plate_angle));
    p2 = G4ThreeVector(effarea_size / 2, -effarea_size / 2, 0);
    p3 = G4ThreeVector(-effarea_size / 2, effarea_size / 2, 0);
    zeropoint = G4ThreeVector(-focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                              -focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                              focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));
    break;

  case 7:
    p1 = G4ThreeVector(-effarea_size / 2, -effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2 * sin(2 * plate_angle));
    p2 = G4ThreeVector(-effarea_size / 2, effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2 * sin(2 * plate_angle));
    p3 = G4ThreeVector(effarea_size / 2, -effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2 * sin(2 * plate_angle));
    zeropoint = G4ThreeVector(0,
                              -focal_length * sin(2 * plate_angle),
                              focal_length * cos(2 * plate_angle));
    break;

  case 8:
    p1 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2 * sqrt(2) * sin(2 * plate_angle));
    p2 = G4ThreeVector(effarea_size / 2, effarea_size / 2, 0);
    p3 = G4ThreeVector(-effarea_size / 2, -effarea_size / 2, 0);
    zeropoint = G4ThreeVector(focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                              -focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)),
                              focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)));
    break;
  }

  auto aim_at = zeropoint + (G4UniformRand() - 0.5) * (p2 - p1) + (G4UniformRand() - 0.5) * (p3 - p1);
  auto dir = GetParticleMomentum();
  G4double path_length = 40 * cm;
  auto start = aim_at + path_length * dir;
  return start;
};

void ExXRTG4PrimaryGeneratorAction::DefineCommands()
{
  fMessenger = new G4GenericMessenger(this,
                                      "/G4MuLE/generator/",
                                      "Primary generator control");

  // momentum command
  auto &momentumCmd = fMessenger->DeclarePropertyWithUnit("energy", "keV", energy,
                                                          "Mean momentum of primaries.");

  momentumCmd.SetParameterName("p", true);
  momentumCmd.SetRange("p>=0.");
  momentumCmd.SetDefaultValue("0.5");

  auto &angleXCmd = fMessenger->DeclarePropertyWithUnit("angleX", "deg", angle_x,
                                                        "Mean momentum of angle X.");
  angleXCmd.SetParameterName("ax", true);
  //angleXCmd.SetRange("ax>=0.");
  angleXCmd.SetDefaultValue("0.");

  auto &angleYCmd = fMessenger->DeclarePropertyWithUnit("angleY", "deg", angle_y,
                                                        "Mean momentum of angle Y.");
  angleYCmd.SetParameterName("ay", true);
  //angleYCmd.SetRange("ay>=0.");
  angleYCmd.SetDefaultValue("0.");

  auto &plateIDCmd = fMessenger->DeclareProperty("plateID", plateid, "Irradiated plate ID");
  plateIDCmd.SetParameterName("pID", true);
  plateIDCmd.SetDefaultValue("0");
}