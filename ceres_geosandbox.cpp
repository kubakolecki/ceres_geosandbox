#include "input_output.hpp"
#include "OptimizationProblem.hpp"
#include "Evaluator.hpp"

#include <print>
#include <filesystem>
#include <fstream>


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

    const auto pathFileReport{ pathDirectoryDataset / std::filesystem::path{"report.txt"s}};
    auto fileReport{std::ofstream{pathFileReport}};
    std::print(fileReport,"Ceres Geosandbox optimization report\n\n");

    ceres_geosandbox::GeoDataset dataset;
    dataset.points = ceres_geosandbox::readPoints2dFromFile(pathFileCoordinates);
    std::print("Read {} points.\n", dataset.points.size());
    std::print(fileReport, "Number of points: {}\n", dataset.points.size());
    dataset.angleMeasurements = ceres_geosandbox::readAngleMeasurementsFromFile(pathFileObsAngles);
    std::print("Read {} angle measurements.\n", dataset.angleMeasurements.size());
    std::print(fileReport, "Number of angles: {}\n", dataset.angleMeasurements.size());
    dataset.distanceMeasurements = ceres_geosandbox::readDistanceMeasurementsFromFile(pathFileObsDistances);
    std::print("Read {} distance measurements.\n", dataset.distanceMeasurements.size());
    std::print(fileReport, "Number of distances: {}\n", dataset.distanceMeasurements.size());
    dataset.gnssMeasurements = ceres_geosandbox::readGnssMeasurementsFromFile(pathFileObsGnss);
    std::print("Read {} GNSS measurements.\n", dataset.gnssMeasurements.size());
    std::print(fileReport, "Number of points measured with GNSS: {}\n", dataset.gnssMeasurements.size());

    ceres_geosandbox::Evaluator evaluator;
    std::print(fileReport,"\nEvaluation of residuals before optimization:\n");
    evaluator.evaluate(dataset, fileReport);

    ceres_geosandbox::OptimizationProblem problem{dataset};
    const auto solverSummary{problem.solve()};
    fileReport << solverSummary.FullReport();

    const auto sigmaZero {sqrt(2.0 * solverSummary.final_cost / (solverSummary.num_residuals - solverSummary.num_effective_parameters))};
    std::print(fileReport, "Sigma0: {:10.7f}\n", sigmaZero);

    std::print("\n\nSigma0 = {}\n", sigmaZero);

    std::print(fileReport,"\nEvaluation of residuals after optimization:\n");

    evaluator.evaluate(dataset, fileReport);

    std::print(fileReport, "\nOptimized coordinates of points:\n");
    ceres_geosandbox::printPoints(fileReport, dataset.points);

    const auto covarianceData{problem.computeCovariance(dataset.points, sigmaZero)};
    std::print(fileReport,"\nComputed covariances for {} points:\n", covarianceData.size());
    ceres_geosandbox::printCovariances(fileReport, covarianceData);

    
    
    return EXIT_SUCCESS;
}
