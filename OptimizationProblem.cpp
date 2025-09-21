#include "OptimizationProblem.hpp"

#include "AngleCostFunction.hpp"
#include "AngleCostFunctionAutodiff.hpp"
#include "DistanceCostFunction.hpp"
#include "DistanceCostFunctionAutodiff.hpp"
#include "GnssCostFunction.hpp"

#include <print>

ceres_geosandbox::OptimizationProblem::OptimizationProblem(ceres_geosandbox::GeoDataset& dataset)
{
    addAngleMeasurements(dataset);
    addDistanceMeasurements(dataset);
    addGnssMeasurements(dataset);

}

std::string ceres_geosandbox::OptimizationProblem::solve()
{
    ceres::Solver::Summary ceresSummary;
    ceres::Solver::Options ceresSolverOptions;

    //ceresSolverOptions.sparse_linear_algebra_library_type = ceres::NO_SPARSE;
    //ceresSolverOptions.linear_solver_type = ceres::DENSE_QR;
    
    ceresSolverOptions.sparse_linear_algebra_library_type = ceres::SUITE_SPARSE;
    ceresSolverOptions.linear_solver_type = ceres::SPARSE_NORMAL_CHOLESKY;
    ceresSolverOptions.minimizer_progress_to_stdout = true;   


    ceres::Solve(ceresSolverOptions, &m_problem, &ceresSummary);

    std::print("Ceres Solver report:\n{}\n", ceresSummary.FullReport());

    return ceresSummary.FullReport();

}

void ceres_geosandbox::OptimizationProblem::addAngleMeasurements(ceres_geosandbox::GeoDataset& dataset)
{
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


        ceres::CostFunction* costFunction = new AngleCostFunction(measurement.angleInRadians, measurement.angleUncertaintyInRadians);
        //ceres::CostFunction* costFunction = new ceres::AutoDiffCostFunction<AngleCostFunctionAutodiff,1,2,2,2>(
        //    new AngleCostFunctionAutodiff(measurement.angleInRadians, measurement.angleUncertaintyInRadians));
        
        ceres::LossFunction* lossFunction = nullptr; // No loss function
        //ceres::LossFunction* lossFunction = new ceres::HuberLoss(2.0);
        
        m_problem.AddResidualBlock(
        costFunction, lossFunction,
        dataset.points.at(idCenter).data(),
        dataset.points.at(idLeft).data(),
        dataset.points.at(idRight).data()
        );
    }

}

void ceres_geosandbox::OptimizationProblem::addDistanceMeasurements(ceres_geosandbox::GeoDataset& dataset)
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
        
        ceres::CostFunction* costFunction = new DistanceCostFunction(measurement.distance, measurement.distanceUncertainty);
        
        //ceres::CostFunction* costFunction = new ceres::AutoDiffCostFunction<DistanceCostFunctionAutodiff,1,2,2>(
        //    new DistanceCostFunctionAutodiff(measurement.distance, measurement.distanceUncertainty));

        ceres::LossFunction* lossFunction = nullptr; // No loss function
        //ceres::LossFunction* lossFunction = new ceres::HuberLoss(2.0);

        m_problem.AddResidualBlock(
        costFunction, lossFunction,
        dataset.points.at(idPointA).data(),
        dataset.points.at(idPointB).data()
        );
    }
}

void ceres_geosandbox::OptimizationProblem::addGnssMeasurements(ceres_geosandbox::GeoDataset& dataset)
{
    for (const auto& measurement : dataset.gnssMeasurements)
    {
        const auto& idPoint = measurement.idPoint;

        if (!dataset.points.contains(idPoint))
        {
            throw std::runtime_error("Point with ID " + idPoint + " not found in dataset.");
        }
        
        ceres::CostFunction* costFunction = new ceres::AutoDiffCostFunction<GnssCostFunction,2,2>(
            new GnssCostFunction(measurement.coordinates, measurement.uncertainty));

        ceres::LossFunction* lossFunction = nullptr; // No loss function
        //ceres::LossFunction* lossFunction = new ceres::HuberLoss(2.0);

        m_problem.AddResidualBlock(
        costFunction, lossFunction,
        dataset.points.at(idPoint).data()
        );
    }
}


ceres_geosandbox::CovarianceData ceres_geosandbox::OptimizationProblem::computeCovariance(ceres_geosandbox::Points2d& points) const
{


}