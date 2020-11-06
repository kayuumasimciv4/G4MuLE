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
#include "G4GeometryConstants.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "IParticleSource.hh"
#include "PointSource.hh"
#include "CXBSource.hh"
#include "TestSource.hh"

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
      plateid(0),
      pos_x(0),
      pos_y(0),
      pos_z(0),
      dir_x(0),
      dir_y(0),
      dir_z(0)
{
  G4int nofParticles = 1;
  particleGun = new G4ParticleGun(nofParticles);
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  //source = new PointSource(angle_x, angle_y, energy, plateid);
  source = new CXBSource(angle_x, angle_y, energy, plateid);
  //source = new TestSource(pos_x, pos_y, pos_z, dir_x, dir_y, dir_z);

  fgamma = particleTable->FindParticle("gamma");
  particleGun->SetParticleDefinition(fgamma);
  DefineCommands();
}

ExXRTG4PrimaryGeneratorAction::~ExXRTG4PrimaryGeneratorAction()
{
  std::cout << "Destruct PrimaryGeneratorAction" << std::endl;
  std::cout << source << std::endl;

  delete source;
  delete particleGun;
  delete fMessenger;
}

void ExXRTG4PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  auto dir = source->GetParticleMomentum();
  auto start = source->GetParticlePosition();
  //auto dir = G4ThreeVector(dir_x, dir_y, dir_z);
  //auto start = G4ThreeVector(pos_x, pos_y, pos_z);

  energy = (G4UniformRand() * 1.5 + 0.5) * keV;
  //energy = source->GetParticleEnergy();
  particleGun->SetParticleEnergy(energy);
  particleGun->SetParticlePosition(start);
  particleGun->SetParticleMomentumDirection(-dir);
  particleGun->GeneratePrimaryVertex(anEvent);
}

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

  auto &posXCmd = fMessenger->DeclareProperty("pos_x", pos_x, "Initial position");
  posXCmd.SetParameterName("px", true);
  posXCmd.SetDefaultValue("0");
  auto &posYCmd = fMessenger->DeclareProperty("pos_y", pos_y, "Initial position");
  posYCmd.SetParameterName("py", true);
  posYCmd.SetDefaultValue("0");
  auto &posZCmd = fMessenger->DeclareProperty("pos_z", pos_z, "Initial position");
  posZCmd.SetParameterName("pz", true);
  posZCmd.SetDefaultValue("0");

  auto &dirXCmd = fMessenger->DeclareProperty("dir_x", dir_x, "Initial direction");
  dirXCmd.SetParameterName("dx", true);
  dirXCmd.SetDefaultValue("0");
  auto &dirYCmd = fMessenger->DeclareProperty("dir_y", dir_y, "Initial direction");
  dirYCmd.SetParameterName("dy", true);
  dirYCmd.SetDefaultValue("0");
  auto &dirZCmd = fMessenger->DeclareProperty("dir_z", dir_z, "Initial direction");
  dirZCmd.SetParameterName("dz", true);
  dirZCmd.SetDefaultValue("0");
}
