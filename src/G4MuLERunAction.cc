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
#include <time.h>

G4MuLERunAction::G4MuLERunAction()
    : G4UserRunAction(),
      fMessenger(nullptr),
      outputname("text.txt"),
      energy(0.5),
      angle_x(0),
      angle_y(0),
      plateid(0)
{
  DefineCommands();
}
G4MuLERunAction::~G4MuLERunAction() {}
void G4MuLERunAction::BeginOfRunAction(const G4Run *)
{

  if (IsMaster())
  {
    auto runmanager = G4RunManager::GetRunManager();

    std::cout << "Master Thread Start" << std::endl;

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
    auto Nevent = runmanager->GetCurrentRun()->GetNumberOfEventToBeProcessed();

    auto filename = outputname;
    std::ofstream writing_file;
    writing_file.open(dirname + "/" + filename, std::ios::trunc);
    writing_file << "########## GeneratedPhotonInfo ##########" << std::endl;
    writing_file << "seed: " << G4Random::getTheSeed() << std::endl;
    writing_file << "TotalPhoton: " << Nevent << std::endl;
    writing_file << "IncidentAngleX[rad]: " << angle_x << std::endl;
    writing_file << "IncidentAngleY[rad]: " << angle_y << std::endl;
    writing_file << "SettingEnergy[MeV]: " << energy << std::endl;
    writing_file << "FocusedPlateID: " << plateid << std::endl;
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
    start = clock();
  }
  else
  {
    auto runmanager = G4RunManager::GetRunManager();

    G4VUserPrimaryGeneratorAction *pgene = const_cast<G4VUserPrimaryGeneratorAction *>(runmanager->GetUserPrimaryGeneratorAction());
    ExXRTG4PrimaryGeneratorAction *pgenec = dynamic_cast<ExXRTG4PrimaryGeneratorAction *>(pgene);
    auto source = pgenec->GetSource();
    source->Update(angle_x, angle_y, energy, plateid);
  }
}
void G4MuLERunAction::EndOfRunAction(const G4Run *)
{
  if (IsMaster())
  {
    time_t timer;
    struct tm *t_st;
    time(&timer);
    printf("現在時刻: %s\n", ctime(&timer));
  }
  else
  {
  }
}

void G4MuLERunAction::DefineCommands()
{

  fMessenger = new G4GenericMessenger(this,
                                      "/G4MuLE/runaction/",
                                      "Primary stepping action control");

  auto &outnameCmd = fMessenger->DeclareProperty("outputname", outputname,
                                                 "output file name.");

  outnameCmd.SetParameterName("t", true);
  outnameCmd.SetDefaultValue("test.txt");

  // momentum command
  auto &momentumCmd = fMessenger->DeclarePropertyWithUnit("energy", "keV", energy,
                                                          "Mean momentum of primaries.");

  momentumCmd.SetParameterName("p", true);
  momentumCmd.SetRange("p>=0.");
  momentumCmd.SetDefaultValue("0.5");

  auto &angleXCmd = fMessenger->DeclarePropertyWithUnit("angle_x", "deg", angle_x,
                                                        "Mean momentum of angle X.");
  angleXCmd.SetParameterName("ax", true);
  //angleXCmd.SetRange("ax>=0.");
  angleXCmd.SetDefaultValue("0.");

  auto &angleYCmd = fMessenger->DeclarePropertyWithUnit("angle_y", "deg", angle_y,
                                                        "Mean momentum of angle Y.");
  angleYCmd.SetParameterName("ay", true);
  //angleYCmd.SetRange("ay>=0.");
  angleYCmd.SetDefaultValue("0.");

  auto &plateIDCmd = fMessenger->DeclareProperty("plateid", plateid, "Irradiated plate ID");
  plateIDCmd.SetParameterName("pID", true);
  plateIDCmd.SetDefaultValue("0");
}
