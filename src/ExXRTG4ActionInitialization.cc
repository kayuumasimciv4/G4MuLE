#include "ExXRTG4ActionInitialization.hh"
#include "ExXRTG4PrimaryGeneratorAction.hh"
//#include "B5PrimaryGeneratorAction.hh"
#include "ExXRTG4SteppingAction.hh"
#include "ExXRTG4UserTrackingAction.hh"
#include "G4MuLERunAction.hh"

ExXRTG4ActionInitialization::ExXRTG4ActionInitialization()
    : G4VUserActionInitialization()
{
}

ExXRTG4ActionInitialization::~ExXRTG4ActionInitialization()
{
}

void ExXRTG4ActionInitialization::BuildForMaster() const
{
  SetUserAction(new G4MuLERunAction);
}

void ExXRTG4ActionInitialization::Build() const
{
  SetUserAction(new ExXRTG4PrimaryGeneratorAction);
  SetUserAction(new G4MuLERunAction);
  SetUserAction(new ExXRTG4SteppingAction);
  SetUserAction(new ExXRTG4UserTrackingAction);
}