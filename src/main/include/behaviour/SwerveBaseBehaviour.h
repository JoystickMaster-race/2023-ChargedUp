#pragma once

#include "drivetrain/SwerveDrive.h"
#include "behaviour/Behaviour.h"
#include <ctre/Phoenix.h>
#include <frc/XboxController.h>
#include <networktables/NetworkTableInstance.h>

#include <vector>

// ArmavatorPosition Armavator::GetCurrentPosition()

class ManualDrivebase : public behaviour::Behaviour{
 public:
  ManualDrivebase(wom::SwerveDrive *swerveDrivebase, frc::XboxController *driverController);

  void OnTick(units::second_t deltaTime) override;

 private:
  wom::SwerveDrive *_swerveDrivebase;
  frc::XboxController *_driverController;
  const double driverDeadzone = 0.08;
  const double turningDeadzone = 0.1;
  const units::meters_per_second_t maxMovementMagnitude = 6.5_ft / 1_s;

  nt::NetworkTableInstance _defaultTable = nt::NetworkTableInstance::GetDefault();
  std::shared_ptr<nt::NetworkTable> _swerveDriveTable = _defaultTable.GetTable("swerve");

  //std::shared_ptr<nt::NetworkTable> _swerveDriveTable;
};

class DrivebasePoseBehaviour : public behaviour::Behaviour{
 public:
  DrivebasePoseBehaviour(wom::SwerveDrive *swerveDrivebase, frc::Pose2d pose);
  void OnTick(units::second_t deltaTime) override;
 
 private:
  wom::SwerveDrive *_swerveDrivebase;
  frc::Pose2d _pose; // storing it directly, so not a pointer
};

class DrivebaseBalance : public behaviour::Behaviour{
 public:
  DrivebaseBalance(wom::SwerveDrive *swerveDrivebase);

  void OnTick(units::second_t deltaTime) override;

 private:
  wom::SwerveDrive *_swerveDrivebase;
  double *_gyroAngle;
};
