// xrtg4.cc
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

// This is an example showing how to make use of the X-ray grazing
// angle scattering process.
#include "G4MTRunManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIsession.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "G4XraySpecularReflectingSurface.hh"

#include "ExXRTG4DetectorConstruction.hh"
#include "ExXRTG4PhysicsList.hh"
#include "ExXRTG4ActionInitialization.hh"

#include "ExXRTG4SteppingAction.hh"
#include "ExXRTG4UserTrackingAction.hh"

int main(int argc, char *argv[])

{
      // Detect interactive mode (if no arguments) and define UI session
      //
      G4UIExecutive *ui = 0;
      if (argc == 1)
      {
            ui = new G4UIExecutive(argc, argv);
      }

      G4MTRunManager *runManager = new G4MTRunManager;
      runManager->SetNumberOfThreads(10);

      // micro-roughness reduces the reflectivity;
      const G4double micro_roughness = 1 * nm;

      // true sets the reflectivity to be 1 always: useful to debug the
      // geometry, also inconjunction with a large angle.
      const G4bool force_unit_reflectivity = false;

      // photon energy
      //const G4double energy = 1 * keV;

      G4XraySpecularReflectingSurface *xray_surface_property =
          new G4XraySpecularReflectingSurface("SpecularReflectionSurface", micro_roughness, force_unit_reflectivity);

      //Mandatory user initialization classes
      runManager->SetUserInitialization(new ExXRTG4DetectorConstruction(xray_surface_property));
      runManager->SetUserInitialization(new ExXRTG4PhysicsList);

      // User action initialization
      runManager->SetUserInitialization(new ExXRTG4ActionInitialization());
      //runManager->SetUserAction(new ExXRTG4SteppingAction);
      //runManager->SetUserAction(new ExXRTG4UserTrackingAction);
      runManager->Initialize();

      // Initialize visualization
      //
      G4VisManager *visManager = new G4VisExecutive;
      // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
      // G4VisManager* visManager = new G4VisExecutive("Quiet");
      visManager->Initialize();

      // Get the pointer to the User Interface manager
      G4UImanager *UImanager = G4UImanager::GetUIpointer();

      // Process macro or start UI session
      //
      if (!ui)
      {
            // batch mode
            G4String command = "/control/execute ";
            G4String fileName = argv[1];
            UImanager->ApplyCommand(command + fileName);
      }
      else
      {
            // interactive mode
            UImanager->ApplyCommand("/control/execute init_vis.mac");
            if (ui->IsGUI())
            {
                  UImanager->ApplyCommand("/control/execute gui.mac");
            }
            ui->SessionStart();
            delete ui;
      } // Job termination
      // Free the store: user actions, physics_list and detector_description are
      // owned and deleted by the run manager, so they should not be deleted
      // in the main() program !

      delete visManager;
      delete runManager;
      delete xray_surface_property;
}
