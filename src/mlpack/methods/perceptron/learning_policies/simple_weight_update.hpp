/**
 * @file simple_weight_update.hpp
 * @author Udit Saxena
 *
 * Simple weight update rule for the perceptron.
 */
#ifndef _MLPACK_METHODS_PERCEPTRON_LEARNING_POLICIES_SIMPLE_WEIGHT_UPDATE_HPP
#define _MLPACK_METHODS_PERCEPTRON_LEARNING_POLICIES_SIMPLE_WEIGHT_UPDATE_HPP

#include <mlpack/core.hpp>

/**
 * This class is used to update the weightVectors matrix according to the simple
 * update rule as discussed by Rosenblatt:
 *
 *  if a vector x has been incorrectly classified by a weight w,
 *  then w = w - x
 *  and  w'= w'+ x
 *
 *  where w' is the weight vector which correctly classifies x.
 */
namespace mlpack {
namespace perceptron {

class SimpleWeightUpdate
{
 public:
  /**
   * This function is called to update the weightVectors matrix.  It decreases
   * the weights of the incorrectly classified class while increasing the weight
   * of the correct class it should have been classified to.
   *
   * @param trainData The training dataset.
   * @param weightVectors Matrix of weight vectors.
   * @param rowIndex Index of the row which has been incorrectly predicted.
   * @param labelIndex Index of the vector in trainData.
   * @param vectorIndex Index of the class which should have been predicted.
   * @param D Cost of mispredicting the labelIndex instance.
   */
  void UpdateWeights(const arma::mat& trainData,
                     arma::mat& weightVectors,
                     const size_t labelIndex,
                     const size_t vectorIndex,
                     const size_t rowIndex,
                     const arma::rowvec& D)
  {
    weightVectors.row(rowIndex).subvec(1, weightVectors.n_cols - 1) -=
        D(labelIndex) * trainData.col(labelIndex).t();
    weightVectors(rowIndex, 0) -= D(labelIndex);

    weightVectors.row(vectorIndex).subvec(1, weightVectors.n_cols - 1) +=
        D(labelIndex) * trainData.col(labelIndex).t();
    weightVectors(vectorIndex, 0) += D(labelIndex);
  }
};

} // namespace perceptron
} // namespace mlpack

#endif
