// Copyright 2018 The Simons Foundation, Inc. - All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NETKET_RBM_SPIN_PHASE_HPP
#define NETKET_RBM_SPIN_PHASE_HPP

#include "Machine/abstract_machine.hpp"

namespace netket {

/** Restricted Boltzmann machine class with spin 1/2 hidden units.
This version has real-valued weights and two RBMs parameterizing phase and
amplitude
 *
 */
class RbmSpinPhase : public AbstractMachine {
  // number of visible units
  int nv_;

  // number of hidden units
  int nh_;

  // number of parameters
  int npar_;

  // weights
  RealMatrixType W1_;

  // visible units bias
  RealVectorType a1_;

  // hidden units bias
  RealVectorType b1_;

  // weights
  RealMatrixType W2_;

  // visible units bias
  RealVectorType a2_;

  // hidden units bias
  RealVectorType b2_;

  RealVectorType thetas1_;
  RealVectorType thetas2_;
  RealVectorType lnthetas1_;
  RealVectorType lnthetas2_;
  RealVectorType thetasnew1_;
  RealVectorType lnthetasnew1_;
  RealVectorType thetasnew2_;
  RealVectorType lnthetasnew2_;

  bool usea_;
  bool useb_;

  const Complex I_;

 public:
  RbmSpinPhase(std::shared_ptr<const AbstractHilbert> hilbert, int nhidden = 0,
               int alpha = 0, bool usea = true, bool useb = true);

  int Npar() const override;
  int Nvisible() const override;
  /*constexpr*/ int Nhidden() const noexcept { return nh_; }

  VectorType DerLogSingle(VisibleConstType v, const any &lt) override;

  void LogVal(Eigen::Ref<const RowMatrix<double>> x,
              Eigen::Ref<Eigen::VectorXcd> out, const any &) override;

  VectorType GetParameters() override;
  void SetParameters(VectorConstRefType pars) override;

  // Value of the logarithm of the wave-function
  // using pre-computed look-up tables for efficiency
  Complex LogValSingle(VisibleConstType v, const any &lt) override;

  bool IsHolomorphic() const noexcept override;

  void Save(const std::string &filename) const override;
  void Load(const std::string &filename) override;

 private:
  inline void Init();
};

}  // namespace netket

#endif
