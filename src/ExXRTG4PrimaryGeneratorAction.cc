// ExXRTPrimaryGeneratorAction.hh
//
// Giuseppe Vacanti (cosine Science & Computing BV)
// October 14, 2009
//
// This file is part of the XRTG4 Geant4 extension.

//     The XRTG4 Geant4 extension is free software: you can
//     redistribute it and/or modify it under the terms of the GNU
//     General Public License as published by the Free Software
//     Foundation, either version 2 of the License, or (at your
//     option) any later version.

//     XRTG4 Geant4 extension is distributed in the hope that it will
//     be useful, but WITHOUT ANY WARRANTY; without even the implied
//     warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//     PURPOSE.  See the GNU General Public License for more details.

//     You should have received a copy of the GNU General Public
//     License along with XRTG4 Geant4 extension.  If not, see
//     <http://www.gnu.org/licenses/>.
//

#include "ExXRTG4PrimaryGeneratorAction.hh"
#include "G4Constants.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//--------------------------------------------------------------

//-----------------------------------------------------------------

ExXRTG4PrimaryGeneratorAction::ExXRTG4PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      particleGun(nullptr),
      fMessenger(nullptr),
      fgamma(nullptr),
      energy(0.5 * keV),
      angle_x(0),
      angle_y(0),
      plateid(0)
{

  G4int nofParticles = 1;
  particleGun = new G4ParticleGun(nofParticles);
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  fgamma = particleTable->FindParticle("gamma");
  particleGun->SetParticleDefinition(fgamma);
  DefineCommands();
}

ExXRTG4PrimaryGeneratorAction::~ExXRTG4PrimaryGeneratorAction()
{
  delete particleGun;
  delete fMessenger;
}

void ExXRTG4PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  //anEvent->SetUserInformation(new G4XrayUserEventInformation);
  G4double plate_angle = 10 * cm / curvature_radius * rad;

  //G4double pos_X = curvature_radius * sin((9 * cm) / (2 * curvature_radius)) * 2 * (G4UniformRand() - 0.5);
  //G4double pos_Y = curvature_radius * sin((9 * cm) / (2 * curvature_radius)) * 2 * (G4UniformRand() - 0.5);
  //G4double pos_X = 0;
  //G4double pos_Y = 0;

  /*
  G4double pos_X_id22 = pos_X * cos(2 * plate_angle) + focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2));
  G4double pos_Y_id22 = pos_Y * cos(2 * plate_angle) + focal_length * sin(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2));
  G4double pos_Z_id22 = focal_length * cos(2 * plate_angle) / sqrt(1 + pow(sin(2 * plate_angle), 2)) - tan(2 * plate_angle) * pos_X - tan(2 * plate_angle) * pos_Y;
  */

  //auto aim_at = G4ThreeVector(pos_X, pos_Y, focal_length);
  //auto aim_at = G4ThreeVector(pos_X_id22, pos_Y_id22, pos_Z_id22);

  G4ThreeVector p1, p2, p3, zeropoint;
  switch (plateid)
  {
  case 0:
    p1 = G4ThreeVector(-effarea_size / 2, -effarea_size / 2, 0);
    p2 = G4ThreeVector(effarea_size / 2, -effarea_size / 2, 0);
    p3 = G4ThreeVector(-effarea_size / 2, effarea_size / 2, 0);
    zeropoint = G4ThreeVector(0, 0, focal_length);
    break;
  case 1:
    p1 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2, effarea_size / 2 * sin(2 * plate_angle));
    p2 = G4ThreeVector(effarea_size / 2 * cos(2 * plate_angle), -effarea_size / 2, -effarea_size / 2 * sin(2 * plate_angle));
    p3 = G4ThreeVector(-effarea_size / 2 * cos(2 * plate_angle), effarea_size / 2, effarea_size * sin(2 * plate_angle));
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

  default:
    p1 = G4ThreeVector(0, 0, 0);
    p2 = G4ThreeVector(0, 0, 0);
    p3 = G4ThreeVector(0, 0, 0);
    zeropoint = G4ThreeVector(0, 0, 0);

    break;
  }

  auto aim_at = zeropoint + (G4UniformRand() - 0.5) * (p2 - p1) + (G4UniformRand() - 0.5) * (p3 - p1);
  auto dir = G4ThreeVector(tan(angle_x), tan(angle_y), 1);

  G4double path_length = 40 * cm;
  auto start = aim_at + path_length * dir;

  particleGun->SetParticleEnergy(energy);
  particleGun->SetParticlePosition(start);
  particleGun->SetParticleMomentumDirection(-dir);
  particleGun->GeneratePrimaryVertex(anEvent);
}

void ExXRTG4PrimaryGeneratorAction::DefineCommands()
{
  fMessenger = new G4GenericMessenger(this,
                                      "/B1/generator/",
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
