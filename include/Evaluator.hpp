#pragma once

#include "geosandbox_datatypes.hpp"

namespace ceres_geosandbox
{
    class Evaluator
    {
        public:
            void evaluate(ceres_geosandbox::GeoDataset& dataset) const;

        private:
            void evaluateAngleMeasurements(GeoDataset& dataset) const;
            void evaluateDistanceMeasurements(GeoDataset& dataset) const;
            void evaluateGnssMeasurements(GeoDataset& dataset) const;

    };


}