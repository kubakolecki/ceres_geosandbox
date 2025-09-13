#pragma once

#include "geosandbox_datatypes.hpp"

namespace ceres_geosandbox
{


class GnssCostFunction
{
    public:
    
    GnssCostFunction(const ceres_geosandbox::Point2dEastingNorthing& observedCoordinates, double uncertainty): m_observedCoordinates{observedCoordinates}, m_uncertainty{uncertainty}
    {}

    template<typename T>
	bool operator() (const T* const coordinates, T* residual) const
    {
        residual[0] = coordinates[0] - static_cast<T>(m_observedCoordinates[0]);
        residual[1] = coordinates[1] - static_cast<T>(m_observedCoordinates[1]);
        residual[0] /= static_cast<T>(m_uncertainty);
        residual[1] /= static_cast<T>(m_uncertainty);
        return true;
    }

    private:
        ceres_geosandbox::Point2dEastingNorthing m_observedCoordinates;
        double m_uncertainty;
    
};

}