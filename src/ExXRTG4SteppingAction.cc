// ExXRTPSteppingAction.hh
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

#include <iostream>
#include <string>  // useful for reading and writing
#include <fstream> // ifstream, ofstream

#include "ExXRTG4SteppingAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4XrayUserEventInformation.hh"
#include "G4XrayUserTrackInformation.hh"
#include "G4UserRunAction.hh"
#include "G4MuLERunAction.hh"
#include "ExXRTG4DetectorConstruction.hh"

ExXRTG4SteppingAction::ExXRTG4SteppingAction()
    : G4UserSteppingAction(),
      fScoringVolume(0)
{
  auto runmanager = G4RunManager::GetRunManager();
  auto runaction = const_cast<G4UserRunAction *>(runmanager->GetUserRunAction());
  runaction_u = dynamic_cast<G4MuLERunAction *>(runaction);
}
ExXRTG4SteppingAction::~ExXRTG4SteppingAction() {}
void ExXRTG4SteppingAction::UserSteppingAction(const G4Step *aStep)
{
  if (!fScoringVolume)
  {
    const ExXRTG4DetectorConstruction *detectorConstruction = static_cast<const ExXRTG4DetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
    std::cout << "Set ScoringVolume: " << fScoringVolume << std::endl;
  }

  G4LogicalVolume *volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  //std::cout << volume << std::endl;
  if (volume != fScoringVolume)
  {
    //std::cout << "ThisVolume: " << volume << " is NotTargetBox" << std::endl;
    return;
  }
  //std::cout << "ThisVolume: " << volume << " is TargetBox" << std::endl;

  const G4Track *aTrack = aStep->GetTrack();

  G4XrayUserTrackInformation *track_info = dynamic_cast<G4XrayUserTrackInformation *>(aTrack->GetUserInformation());
  const std::vector<G4XrayUserTrackInformation::interaction_data_t> &data = track_info->GetTrackInformation();

  auto filepath = runaction_u->GetDirName() + "/" + runaction_u->GetFileName();
  std::ofstream writing_file;
  writing_file.open(filepath, std::ios::app);
  double lx, ly;

  //std::cout << "DataSize" << std::endl;
  //std::cout << data.size() << std::endl;
  for (size_t k = 0; k != data.size(); ++k)
  {
    const G4XrayUserTrackInformation::interaction_data_t &idata = data[k];
    //std::cout << "data" << std::endl;
    //std::cout << idata.position[0] << " " << idata.position[1] << " " << idata.position[2] << " " << k << " " << idata.incidentDirection[0] << " " << idata.incidentDirection[1] << " " << idata.incidentDirection[2] << " " << k << " " << lx << " " << ly << std::endl;

    if (k == 0)
    {
      lx = idata.position[0];
      ly = idata.position[1];
    }

    if ((idata.position[2] <= 0. + 5) && (idata.position[2] >= 0. - 5))
    {
      writing_file << idata.position[0] << " " << idata.position[1] << " " << idata.position[2] << " " << k << " " << idata.incidentDirection[0] << " " << idata.incidentDirection[1] << " " << idata.incidentDirection[2] << " " << k << " " << lx << " " << ly << std::endl;
    }
  }
}
