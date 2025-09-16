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
            

            //auto angle = atan2(dnl,del) - atan2(dnr,der);
            auto angle = atan2(der,dnr) - atan2(del,dnl);
            //if (angle < 0)
            //{
            //    angle += 2.0*M_PI;
            //}    

            residuals[0] =  m_angleInRadians - angle;
            
            residuals[0]/= m_angleUncertaintyInRadians;

            if (jacobian != nullptr  && jacobian[0] != nullptr)
		    {
                //central point
                jacobian[0][0] = der/distSquaredR - del/distSquaredL; 
                jacobian[0][1] = dnl/distSquaredL - dnr/distSquaredR;

                //left point
                jacobian[1][0] = del/distSquaredL;
                jacobian[1][1] = -dnl/distSquaredL;
 
                //right point
                jacobian[2][0] = -der/distSquaredR;
                jacobian[2][1] = dnr/distSquaredR;
            }
      
            return true;
        }

    private:
        double m_angleInRadians;
        double m_angleUncertaintyInRadians;


};

}