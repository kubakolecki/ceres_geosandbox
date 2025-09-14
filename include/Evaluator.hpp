#pragma once

#include "geosandbox_datatypes.hpp"

#include <ostream>

namespace ceres_geosandbox
{
    class Evaluator
    {
        public:
            void evaluate(ceres_geosandbox::GeoDataset& dataset, std::ostream& outputStream) const;

        private:
            void evaluateAngleMeasurements(GeoDataset& dataset, std::ostream& outputStream) const;
            void evaluateDistanceMeasurements(GeoDataset& dataset, std::ostream& outputStream) const;
            void evaluateGnssMeasurements(GeoDataset& dataset, std::ostream& outputStream) const;

    };


}