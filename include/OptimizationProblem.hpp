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
        void solve();


    private:
        ceres::Problem m_problem;
        void addAngleMeasurements(GeoDataset& dataset);
        void addDistanceMeasurements(GeoDataset& dataset);
        void addGnssMeasurements(GeoDataset& dataset);
    
};

}