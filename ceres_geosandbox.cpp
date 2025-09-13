#include "input_output.hpp"
#include "OptimizationProblem.hpp"
#include "Evaluator.hpp"

#include <print>
#include <filesystem>

using namespace std::literals;

int main(int argc, char* argv[])
{
    // Your code implementation here
    std::print("Hello in Ceres Geosandbox!\n");

    if (argc != 3)
    {
        std::print("You need to specify the -d command line parameter to indicate the input directory.\n");
        return EXIT_FAILURE;
    }

    if (std::string{argv[1]} != "-d"s)
    {
        std::print("You need to specify the -d command line parameter to indicate the input directory.\n");
        return EXIT_FAILURE;
    }

    const auto pathDirectoryDataset{std::filesystem::path{std::string{argv[2]}} };
    const auto pathFileCoordinates{ pathDirectoryDataset / std::filesystem::path{"coordinates.txt"s}};
    const auto pathFileObsDistances{ pathDirectoryDataset / std::filesystem::path{"distances_observations.txt"s}};
    const auto pathFileObsAngles{ pathDirectoryDataset / std::filesystem::path{"angles_observations.txt"s}};
    const auto pathFileObsGnss{ pathDirectoryDataset / std::filesystem::path{"gnss_observations.txt"s}};

    ceres_geosandbox::GeoDataset dataset;
    dataset.points = ceres_geosandbox::readPoints2dFromFile(pathFileCoordinates);
    std::print("Read {} points.\n", dataset.points.size());
    dataset.angleMeasurements = ceres_geosandbox::readAngleMeasurementsFromFile(pathFileObsAngles);
    std::print("Read {} angle measurements.\n", dataset.angleMeasurements.size());
    dataset.distanceMeasurements = ceres_geosandbox::readDistanceMeasurementsFromFile(pathFileObsDistances);
    std::print("Read {} distance measurements.\n", dataset.distanceMeasurements.size());
    dataset.gnssMeasurements = ceres_geosandbox::readGnssMeasurementsFromFile(pathFileObsGnss);
    std::print("Read {} GNSS measurements.\n", dataset.gnssMeasurements.size());

    ceres_geosandbox::Evaluator evaluator;
    evaluator.evaluate(dataset);

    ceres_geosandbox::OptimizationProblem problem{dataset};
    problem.solve();

    evaluator.evaluate(dataset);

    
    
    return EXIT_SUCCESS;
}
