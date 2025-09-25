#pragma once

#include <Eigen/Dense> 

#include <string>
#include <map>


namespace ceres_geosandbox
{
    using Point2dEastingNorthing = Eigen::Vector2d;
    using Id = std::string;
    using CovarianceMatrix = Eigen::Matrix<double, 2, 2, Eigen::RowMajor>;

    struct AngleMeasurement
    {
        Id idCenter;
        Id idLeft;
        Id idRight;        
        double angleInRadians{}; // Angle in radians
        double angleUncertaintyInRadians{}; // Uncertainty in radians

    };

    struct DistanceMeasurement
    {
        Id idPointA;
        Id idPointB;        
        double distance{};
        double distanceUncertainty{};
    };

    struct GnssMeasurement
    {
        std::string idPoint;
        Point2dEastingNorthing coordinates;
        double uncertainty{};      
    };

    using Points2d= std::map<std::string, Point2dEastingNorthing>;
    using AngleMeasurements = std::vector<AngleMeasurement>;
    using DistanceMeasurements = std::vector<DistanceMeasurement>;
    using GnssMeasurements = std::vector<GnssMeasurement>;

    struct GeoDataset
    {
        Points2d points;
        AngleMeasurements angleMeasurements;
        DistanceMeasurements distanceMeasurements;
        GnssMeasurements gnssMeasurements;
    };

    using CovarianceData = std::map<Id, CovarianceMatrix>;


}
