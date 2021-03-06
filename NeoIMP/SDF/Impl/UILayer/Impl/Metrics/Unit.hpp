#ifndef SDF_IMPL_UILAYER_IMPL_METRICS_UNIT_HPP
#define SDF_IMPL_UILAYER_IMPL_METRICS_UNIT_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    Unit.hpp
 * PURPOSE: A template for defining units of a quantity of some dimension.
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cmath>

namespace SDF::Impl::UILayer::Impl::Metrics {
  template<int L, int A>
  class Unit {
  public:
    Unit(float numBaseUnits) :
    m_numBaseUnits(numBaseUnits) {}

    ~Unit() {}

    float getNumBaseUnits() const {
      return m_numBaseUnits;
    }

    // Synthesize a multiplicative conversion factor for this unit and another unit of this same dimensional quantity.
    float getConversionTo(const Unit<L, A> toUnit) const {
      return(m_numBaseUnits / toUnit.m_numBaseUnits);
    }
  private:
    // The size of this unit as a number of arbitrary base units for this quantity.
    float m_numBaseUnits;
  };

  // Non-member operators.
  template<int L, int A, int Exp>
  static Unit<L + Exp, A + Exp> pow(const Unit<L, A> &u) {
    return Unit<L + Exp, A + Exp>(pow(u.getNumBaseUnits(), Exp));
  }

  template<int L1, int A1, int L2, int A2>
  static Unit<L1 + L2, A1 + A2> operator*(const Unit<L1, A1> &u1, const Unit<L2, A2> &u2) {
    return Unit<L1 + L2, A1 + A2>(u1.getNumBaseUnits() * u2.getNumBaseUnits());
  }

  template<int L1, int A1, int L2, int A2>
  static Unit<L1 - L2, A1 - A2> operator/(const Unit<L1, A1> &u1, const Unit<L2, A2> &u2) {
    return Unit<L1 - L2, A1 - A2>(u1.getNumBaseUnits() / u2.getNumBaseUnits());
  }
}

#endif
