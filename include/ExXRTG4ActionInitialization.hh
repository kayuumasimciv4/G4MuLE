#ifndef ExXRTG4ActionInitialization_h
#define ExXRTG4ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
/// Action initialization class

class ExXRTG4ActionInitialization : public G4VUserActionInitialization
{

public:
  ExXRTG4ActionInitialization();
  virtual ~ExXRTG4ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;
};

#endif