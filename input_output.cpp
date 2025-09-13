#include "input_output.hpp"

#include <fstream>
#include <vector>

ceres_geosandbox::Points2d ceres_geosandbox::readPoints2dFromFile(const std::filesystem::path& filePath)
{
    Points2d points;
    std::ifstream file(filePath);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Could not open file: " + filePath.string());
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token);
        }
        
        points.emplace(tokens.at(0), Point2dEastingNorthing{std::stod(tokens.at(1)) , std::stod(tokens.at(2))}) ;
    }
    return points;
}

ceres_geosandbox::AngleMeasurements ceres_geosandbox::readAngleMeasurementsFromFile(const std::filesystem::path& filePath)
{
    AngleMeasurements measurements;
    std::ifstream file(filePath);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Could not open file: " + filePath.string());
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token);
        }
        
        measurements.emplace_back(
            tokens.at(0),
            tokens.at(1),
            tokens.at(2),
            std::stod(tokens.at(3)),
            std::stod(tokens.at(4)));
    }
    return measurements;
}

ceres_geosandbox::DistanceMeasurements ceres_geosandbox::readDistanceMeasurementsFromFile(const std::filesystem::path& filePath)
{
    DistanceMeasurements measurements;
    std::ifstream file(filePath);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Could not open file: " + filePath.string());
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token);
        }
        
        measurements.emplace_back(
            tokens.at(0),
            tokens.at(1),
            std::stod(tokens.at(2)),
            std::stod(tokens.at(3)));
    }
    return measurements;
}

ceres_geosandbox::GnssMeasurements ceres_geosandbox::readGnssMeasurementsFromFile(const std::filesystem::path& filePath)
{
    GnssMeasurements measurements;
    std::ifstream file(filePath);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Could not open file: " + filePath.string());
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token);
        }
        
        measurements.emplace_back(
            tokens.at(0),
            Point2dEastingNorthing{std::stod(tokens.at(1)) , std::stod(tokens.at(2))},
            std::stod(tokens.at(3)));
    }
    return measurements;
}