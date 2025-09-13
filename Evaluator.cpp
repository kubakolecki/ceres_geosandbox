#include "Evaluator.hpp"

#include "AngleCostFunction.hpp"
#include "DistanceCostFunction.hpp"
#include "GnssCostFunction.hpp"

#include <print>

void ceres_geosandbox::Evaluator::evaluate(ceres_geosandbox::GeoDataset& dataset) const
{
    evaluateAngleMeasurements(dataset);
    evaluateDistanceMeasurements(dataset);
    evaluateGnssMeasurements(dataset);
}


void ceres_geosandbox::Evaluator::evaluateAngleMeasurements(GeoDataset& dataset) const
{
    const auto dontWantJacobian {nullptr};
    for (const auto& measurement : dataset.angleMeasurements)
    {
        const auto& idCenter = measurement.idCenter;
        const auto& idLeft = measurement.idLeft;
        const auto& idRight = measurement.idRight;

        if (!dataset.points.contains(idCenter))
        {
            throw std::runtime_error("Point with ID " + idCenter + " not found in dataset.");
        }
        if (!dataset.points.contains(idLeft))
        {
            throw std::runtime_error("Point with ID " + idLeft + " not found in dataset.");
        }
        if (!dataset.points.contains(idRight))
        {
            throw std::runtime_error("Point with ID " + idRight + " not found in dataset.");
        }

        double residual;

        ceres::CostFunction* costFunction = new AngleCostFunction(measurement.angleInRadians, measurement.angleUncertaintyInRadians);
        double* coordinates[3] = {dataset.points.at(idCenter).data(), dataset.points.at(idLeft).data(), dataset.points.at(idRight).data()};
        costFunction->Evaluate(coordinates, &residual, dontWantJacobian );

        residual *= measurement.angleUncertaintyInRadians; //de-normalize

        std::print("residual of angle: center point: {}, left point: {}, right point: {}, residual:  {}[rad] = {}[deg]\n", idCenter, idLeft, idRight, residual, residual*180.0/M_PI);


    }
}

void ceres_geosandbox::Evaluator::evaluateDistanceMeasurements(GeoDataset& dataset) const
{

    for (const auto& measurement : dataset.distanceMeasurements)
    {
        const auto& idPointA = measurement.idPointA;
        const auto& idPointB = measurement.idPointB;

        if (!dataset.points.contains(idPointA))
        {
            throw std::runtime_error("Point with ID " + idPointA + " not found in dataset.");
        }
        if (!dataset.points.contains(idPointB))
        {
            throw std::runtime_error("Point with ID " + idPointB + " not found in dataset.");
        }

        double residual;

        const auto costFunction {DistanceCostFunction{measurement.distance, measurement.distanceUncertainty}};
        costFunction(dataset.points.at(idPointA).data(), dataset.points.at(idPointB).data(), &residual);
        residual *= measurement.distanceUncertainty; //de-normalize

        std::print("residual of distance: point A: {}, point B: {}, residual:  {}\n", idPointA, idPointB, residual);
    }


}

void ceres_geosandbox::Evaluator::evaluateGnssMeasurements(GeoDataset& dataset) const
{
    for (const auto& measurement : dataset.gnssMeasurements)
    {
        if (!dataset.points.contains(measurement.idPoint ))
        {
            throw std::runtime_error("Point with ID " + measurement.idPoint + " not found in dataset.");
        }

        double residual[2];
        const auto costFunction{GnssCostFunction{measurement.coordinates, measurement.uncertainty}};
        costFunction(dataset.points.at(measurement.idPoint).data(), residual);
        residual[0] *= measurement.uncertainty;
        residual[1] *= measurement.uncertainty;

        std::print("residual of GNSS measurement: point: {}, residual: [{},{}]\n", measurement.idPoint, residual[0], residual[1] );

    }


}
