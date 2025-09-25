#pragma once

#include <ceres/ceres.h>

namespace ceres_geosandbox
{

class GnssCostFunction: public ceres::SizedCostFunction<2,2>
{
    public:
    
    GnssCostFunction(const ceres_geosandbox::Point2dEastingNorthing& observedCoordinates, double uncertainty): m_observedCoordinates{observedCoordinates}, m_uncertainty{uncertainty}
    {}

    bool Evaluate (double const* const* coordiantes, double* residuals, double** jacobian) const override
    {
        residuals[0] = coordiantes[0][0] - m_observedCoordinates[0];
        residuals[1] = coordiantes[0][1] - m_observedCoordinates[1];
        residuals[0] /= m_uncertainty;
        residuals[1] /= m_uncertainty;

        if (jacobian != nullptr  && jacobian[0] != nullptr)
        {
            jacobian[0][0] = 1.0/m_uncertainty;
            jacobian[0][1] = 0.0;

            jacobian[1][0] = 0.0;
            jacobian[1][1] = 1.0/m_uncertainty;
        }

        return true;
    }

    private:
        ceres_geosandbox::Point2dEastingNorthing m_observedCoordinates;
        double m_uncertainty;

};

}
