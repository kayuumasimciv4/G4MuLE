// ExXRTG4UserEventAction.cc
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

#include "ExXRTG4UserEventAction.hh"

#include "G4XrayUserEventInformation.hh"
#include "G4Event.hh"

ExXRTG4UserEventAction::ExXRTG4UserEventAction() : G4UserEventAction() {}

ExXRTG4UserEventAction::~ExXRTG4UserEventAction() {}

void ExXRTG4UserEventAction::BeginOfEventAction(const G4Event *anEvent)
{
  //anEvent->SetUserInformation(new G4XrayUserEventInformation);
}

void ExXRTG4UserEventAction::EndOfEventAction(const G4Event *)
{
}
