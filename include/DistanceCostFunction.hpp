#pragma once

#include <ceres/ceres.h>

namespace ceres_geosandbox
{

class DistanceCostFunction: public ceres::SizedCostFunction<1,2,2>
{
    public:
        DistanceCostFunction(double distance, double distanceUncertainty): m_distance{distance}, m_distanceUncertainty{distanceUncertainty}
        {}

        bool Evaluate (double const* const* coordiantes, double* residuals, double** jacobian) const override
        {
            const double deltaEast {coordiantes[1][0] - coordiantes[0][0]};
            const double deltaNorth {coordiantes[1][1] - coordiantes[0][1]};
            const double predictedDistance {sqrt(deltaEast*deltaEast + deltaNorth*deltaNorth)};
            residuals[0] = predictedDistance - m_distance;
            residuals[0] /= m_distanceUncertainty;
            
            if (jacobian != nullptr  && jacobian[0] != nullptr)
		    {
                jacobian[0][0] = (-deltaEast/predictedDistance)/m_distanceUncertainty;
                jacobian[0][1] = (-deltaNorth/predictedDistance)/m_distanceUncertainty;

                jacobian[1][0] = (deltaEast/predictedDistance)/m_distanceUncertainty;
                jacobian[1][1] = (deltaNorth/predictedDistance)/m_distanceUncertainty;

            }

            return true;

        }

    private:
        double m_distance;
        double m_distanceUncertainty;

};

}