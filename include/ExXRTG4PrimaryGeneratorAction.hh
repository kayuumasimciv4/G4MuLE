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

#ifndef EXXRTG4PRIMARYGENERATORACTION_HH
#define EXXRTG4PRIMARYGENERATORACTION_HH 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "IParticleSource.hh"
#include "PointSource.hh"

class G4ParticleDefinition;
class G4Event;
class G4ParticleGun;
class G4GenericMessenger;
class IParticleSource;

class ExXRTG4PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  ExXRTG4PrimaryGeneratorAction();
  virtual ~ExXRTG4PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event *);

  void SetMomentum(G4double val) { energy = val; }
  G4double GetMomentum() const { return energy; }

  void SetAngleX(G4double val) { angle_x = val; }
  G4double GetAngleX() const { return angle_x; }

  void SetAngleY(G4double val) { angle_y = val; }
  G4double GetAngleY() const { return angle_y; }

private:
  void DefineCommands();
  G4ParticleGun *particleGun;
  G4GenericMessenger *fMessenger;
  G4ParticleDefinition *fgamma;
  G4double energy;
  G4double angle_x;
  G4double angle_y;
  G4int plateid;
  IParticleSource *source;
};

#endif // EXXRTG4PRIMARYGENERATORACTION_HH
