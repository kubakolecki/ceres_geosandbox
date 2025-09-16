#pragma once 

namespace ceres_geosandbox
{
    class AngleCostFunctionAutodiff
    {
        public:
            explicit AngleCostFunctionAutodiff(double angle, double angleUncertainty): m_angle{angle}, m_angleUncertainty{angleUncertainty}
            { }

            template<typename T>
            bool operator() (const T* const coordinatesCenter, const T* const coordinatesLeft, const T* const coordinatesRight, T* residual ) const
            {
                T deltaEastRigth = coordinatesRight[0] - coordinatesCenter[0];
                T deltaEastLeft = coordinatesLeft[0] - coordinatesCenter[0];
                T deltaNorthRight = coordinatesRight[1] - coordinatesCenter[1];
                T deltaNorthLeft = coordinatesLeft[1] - coordinatesCenter[1];
                residual[0] = atan2(deltaEastRigth,deltaNorthRight) - atan2(deltaEastLeft,deltaNorthLeft) - static_cast<T>(m_angle);
                residual[0] /= m_angleUncertainty;
                return true;
            }

        private:
            double m_angle;
            double m_angleUncertainty;

    };
}