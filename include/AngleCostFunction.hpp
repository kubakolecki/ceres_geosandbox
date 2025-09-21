#pragma once

#include <ceres/ceres.h>

namespace ceres_geosandbox
{

class AngleCostFunction: public ceres::SizedCostFunction<1,2,2,2>
{
    public:
        AngleCostFunction(double angleInRadians, double angleUncertaintyInRadians): m_angleInRadians{angleInRadians}, m_angleUncertaintyInRadians{angleUncertaintyInRadians}
        {}
        
        bool Evaluate (double const* const* coordiantes, double* residuals, double** jacobian) const override
        {
            const double ce {coordiantes[0][0]};
            const double cn {coordiantes[0][1]};
            const double le {coordiantes[1][0]};
            const double ln {coordiantes[1][1]};
            const double re {coordiantes[2][0]};
            const double rn {coordiantes[2][1]};

            const double del {le - ce};
            const double der {re - ce};
            const double dnl {ln - cn};
            const double dnr {rn - cn};
            
            const double distSquaredL {del*del + dnl*dnl};
            const double distSquaredR {der*der + dnr*dnr};
            
            const auto angle = atan2(der,dnr) - atan2(del,dnl);


            residuals[0] =  angle - m_angleInRadians;           
            residuals[0]/= m_angleUncertaintyInRadians;

            if (jacobian != nullptr  && jacobian[0] != nullptr)
		    {
                //central point
                jacobian[0][0] = (dnl/distSquaredL - dnr/distSquaredR)/m_angleUncertaintyInRadians;
                jacobian[0][1] = (der/distSquaredR - del/distSquaredL)/m_angleUncertaintyInRadians; 
                
                //left point
                jacobian[1][0] = (-dnl/distSquaredL)/m_angleUncertaintyInRadians;
                jacobian[1][1] = (del/distSquaredL)/m_angleUncertaintyInRadians;
                
                //right point
                jacobian[2][0] = (dnr/distSquaredR)/m_angleUncertaintyInRadians;
                jacobian[2][1] = (-der/distSquaredR)/m_angleUncertaintyInRadians;           
            }
      
            return true;
        }

    private:
        double m_angleInRadians;
        double m_angleUncertaintyInRadians;


};

}