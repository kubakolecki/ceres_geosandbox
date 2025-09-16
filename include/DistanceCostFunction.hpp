#pragma once

namespace ceres_geosandbox
{

class DistanceCostFunction
{
    public:
        explicit DistanceCostFunction(double distance, double distanceUncertainy): m_distance(distance), m_distanceUncertainty(distanceUncertainy)
        { }

        template<typename T>
	    bool operator() (const T* const coordinates1, const T* const coordinates2 , T* residual) const
	    {
            residual[0] =  sqrt((coordinates1[0] - coordinates2[0])*(coordinates1[0] - coordinates2[0]) + (coordinates1[1] - coordinates2[1])*(coordinates1[1] - coordinates2[1])) - static_cast<T>(m_distance);
            residual[0] /= static_cast<T>(m_distanceUncertainty);         
            return true;
        }

    private:
        double m_distance;
        double m_distanceUncertainty;

};

}