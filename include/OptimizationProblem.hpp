#pragma once

#include "geosandbox_datatypes.hpp"

#include <ceres/ceres.h>
#include <ceres/problem.h>

namespace ceres_geosandbox
{


class OptimizationProblem
{
    public:
        OptimizationProblem(GeoDataset& dataset);
        ceres::Solver::Summary solve();
        CovarianceData computeCovariance(const Points2d& points, const double sigmaZero);

    private:
        ceres::Problem m_problem;
        void addAngleMeasurements(GeoDataset& dataset);
        void addDistanceMeasurements(GeoDataset& dataset);
        void addGnssMeasurements(GeoDataset& dataset);
    
};

}