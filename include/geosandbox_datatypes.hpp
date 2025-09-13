#pragma once

#include <Eigen/Dense> 

#include <string>
#include <unordered_map>


namespace ceres_geosandbox
{
    using Point2dEastingNorthing = Eigen::Vector2d; 

    struct AngleMeasurement
    {
        std::string idCenter;
        std::string idLeft;
        std::string idRight;        
        double angleInRadians; // Angle in radians
        double angleUncertaintyInRadians; // Uncertainty in radians

    };

    struct DistanceMeasurement
    {
        std::string idPointA;
        std::string idPointB;        
        double distance;
        double distanceUncertainty;
    };

    struct GnssMeasurement
    {
        std::string idPoint;
        Point2dEastingNorthing coordinates;
        double uncertainty;      
    };

    using Points2d= std::unordered_map<std::string, Point2dEastingNorthing>;
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


}
