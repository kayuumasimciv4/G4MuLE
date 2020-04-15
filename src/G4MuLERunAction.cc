#include "G4MuLERunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4GeometryConstants.hh"
#include "IParticleSource.hh"
#include "PointSource.hh"
#include "ExXRTG4PrimaryGeneratorAction.hh"

#include <Randomize.hh>

#include <iostream>
#include <string>  // useful for reading and writing
#include <fstream> // ifstream, ofstream
#include <sys/stat.h>
#include <sys/types.h>

G4MuLERunAction::G4MuLERunAction()
    : G4UserRunAction(),
      fMessenger(nullptr),
      outputname("text.txt")

{
  DefineCommands();
}
G4MuLERunAction::~G4MuLERunAction() {}
void G4MuLERunAction::BeginOfRunAction(const G4Run *)
{
  struct stat st;
  dirname = "Data";

  int ret = stat(dirname.c_str(), &st);
  if (0 == ret)
  {
    std::cout << "Data Directory is already existed" << std::endl;
  }
  else
  {
    std::cout << "make Data Directory" << std::endl;
    mkdir(dirname.c_str(), 0777);
  }
  auto runmanager = G4RunManager::GetRunManager();
  auto Nevent = runmanager->GetCurrentRun()->GetNumberOfEventToBeProcessed();
  G4VUserPrimaryGeneratorAction *pgene = const_cast<G4VUserPrimaryGeneratorAction *>(runmanager->GetUserPrimaryGeneratorAction());
  ExXRTG4PrimaryGeneratorAction *pgenec = dynamic_cast<ExXRTG4PrimaryGeneratorAction *>(pgene);
  auto source = pgenec->GetSource();
  source->Update(pgenec->GetAngleX(), pgenec->GetAngleY(), pgenec->GetMomentum(), pgenec->GetPlateID());
  auto ax = source->GetCenterAngle_X();
  auto ay = source->GetCenterAngle_Y();
  auto en = source->GetParticleEnergy();
  auto pid = source->GetPlateID();

  auto filename = outputname;
  std::ofstream writing_file;
  writing_file.open(dirname + "/" + filename, std::ios::trunc);
  writing_file << "########## GeneratedPhotonInfo ##########" << std::endl;
  writing_file << "seed: " << G4Random::getTheSeed() << std::endl;
  writing_file << "TotalPhoton: " << Nevent << std::endl;
  writing_file << "IncidentAngleX[rad]: " << ax << std::endl;
  writing_file << "IncidentAngleY[rad]: " << ay << std::endl;
  writing_file << "SettingEnergy[MeV]: " << en << std::endl;
  writing_file << "FocusedPlateID: " << pid << std::endl;
  writing_file << "########## LEopticsGeometoryInfo [mm] ##########" << std::endl;
  writing_file << "FocalLength: " << G4GeometryConstants::Getfocal_length() << std::endl;
  writing_file << "WaferThickness: " << G4GeometryConstants::Getwafer_thickness() << std::endl;
  writing_file << "PoreSize: " << G4GeometryConstants::Getpore_size() << std::endl;
  writing_file << "HoleSize: " << G4GeometryConstants::Gethole_size() << std::endl;
  writing_file << "SpokeWidth: " << G4GeometryConstants::Getspoke_width() << std::endl;
  writing_file << "SpokeThickness: " << G4GeometryConstants::Getspoke_thickness() << std::endl;
  writing_file << "PlateSize: " << G4GeometryConstants::Getplate_size() << std::endl;
  writing_file << "LEopticsEffAreaSize: " << G4GeometryConstants::Geteffarea_size() << std::endl;
  writing_file << "RandomizeFraction: " << G4GeometryConstants::Getrandomize_fraction() << std::endl;
  writing_file << "########## PhotonData ##########" << std::endl;
}
void G4MuLERunAction::EndOfRunAction(const G4Run *)
{
}

void G4MuLERunAction::DefineCommands()
{

  fMessenger = new G4GenericMessenger(this,
                                      "/B1/stepaction/",
                                      "Primary stepping action control");

  auto &outnameCmd = fMessenger->DeclareProperty("outputname", outputname,
                                                 "output file name.");

  outnameCmd.SetParameterName("t", true);
  outnameCmd.SetDefaultValue("test.txt");
}
