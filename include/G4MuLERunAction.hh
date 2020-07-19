#ifndef G4MuLERunAction_h
#define G4MuLERunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4GenericMessenger.hh"
#include "time.h"

class G4MuLERunAction;
class G4Run;

class G4MuLERunAction : public G4UserRunAction
{
public:
  G4MuLERunAction();
  virtual ~G4MuLERunAction();

  virtual void BeginOfRunAction(const G4Run *);
  virtual void EndOfRunAction(const G4Run *);
  std::string GetFileName() { return outputname; };
  std::string GetDirName() { return dirname; };

private:
  void DefineCommands();
  G4GenericMessenger *fMessenger;
  std::string outputname;
  std::string dirname;
  clock_t start;
  clock_t end;
  G4double energy;
  G4double angle_x;
  G4double angle_y;
  G4int plateid;
};

#endif