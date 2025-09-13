#pragma once

#include "geosandbox_datatypes.hpp"
#include <filesystem>


namespace ceres_geosandbox
{
    Points2d readPoints2dFromFile(const std::filesystem::path& filePath);
    AngleMeasurements readAngleMeasurementsFromFile(const std::filesystem::path& filePath);
    DistanceMeasurements readDistanceMeasurementsFromFile(const std::filesystem::path& filePath);
    GnssMeasurements readGnssMeasurementsFromFile(const std::filesystem::path& filePath);


}