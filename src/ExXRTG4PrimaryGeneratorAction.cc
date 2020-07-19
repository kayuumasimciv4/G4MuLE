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
  source = new PointSource(angle_x, angle_y, energy, plateid);

  fgamma = particleTable->FindParticle("gamma");
  particleGun->SetParticleDefinition(fgamma);
  //DefineCommands();
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
  //source->Update(angle_x, angle_y, energy, plateid);

  auto dir = source->GetParticleMomentum();
  auto start = source->GetParticlePosition();
  //energy = (G4UniformRand() * 1.5 + 0.5) * keV;
  energy = 0.5 * keV;
  particleGun->SetParticleEnergy(energy);
  particleGun->SetParticlePosition(start);
  particleGun->SetParticleMomentumDirection(-dir);
  particleGun->GeneratePrimaryVertex(anEvent);
}
/*
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
*/
