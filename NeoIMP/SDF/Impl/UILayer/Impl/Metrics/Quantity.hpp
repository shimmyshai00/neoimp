#ifndef SDF_IMPL_UILAYER_IMPL_METRICS_QUANTITY_HPP
#define SDF_IMPL_UILAYER_IMPL_METRICS_QUANTITY_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    Quantity.hpp
 * PURPOSE: A class representing measurable quantities with units and measure dimensions.
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

#include <SDF/Impl/UILayer/Impl/Metrics/Unit.hpp>

namespace SDF::Impl::UILayer::Impl::Metrics {
  // The available dimensions are length and angle.
  template<int L, int A>
  class Quantity {
  public:
    Quantity() :
    m_val(0.0f),
    m_unit(1.0f) {}

    Quantity(float val, const Unit<L, A> inUnit) :
    m_val(val),
    m_unit(inUnit) {}

    ~Quantity() {}

    float inUnitsOf(const Unit<L, A> unit) {
      return m_val * m_unit.getConversionTo(unit);
    }

    Quantity<L, A> &operator+=(const Quantity<L, A> &rhs) {
      m_val += rhs.inUnitsOf(m_unit);
      return *this;
    }

    Quantity<L, A> &operator-=(const Quantity<L, A> &rhs) {
      m_val -= rhs.inUnitsOf(m_unit);
      return *this;
    }

    // Non-member operators.
    friend bool operator==(const Quantity<L, A> &lhs, const Quantity<L, A> &rhs) {
      return lhs.m_val == rhs.convertUnits(lhs.m_unit).m_val;
    }

    friend bool operator!=(const Quantity<L, A> &lhs, const Quantity<L, A> &rhs) {
      return !(lhs == rhs);
    }

    friend Quantity<L, A> operator+(const Quantity<L, A> &q1, const Quantity<L, A> &q2) {
      return Quantity<L, A>(q1) += q2;
    }

    friend Quantity<L, A> operator-(const Quantity<L, A> &q1, const Quantity<L, A> &q2) {
      return Quantity<L, A>(q1) -= q2;
    }

    template<int L2, int A2>
    friend Quantity<L + L2, A + A2> operator*(const Quantity<L, A> &q1, const Quantity<L2, A2> &q2) {
      return q1.multiplyBy(q2);
    }

    template<int L2, int A2>
    friend Quantity<L - L2, A - A2> operator/(const Quantity<L, A> &q1, const Quantity<L2, A2> &q2) {
      return q1.divideBy(q2);
    }
  private:
    // The size of the quantity in the given units.
    float m_val;
    Unit<L, A> m_unit;

    template<int, int>
    friend class Quantity;

    // Internal operators.
    template<int L2, int A2>
    Quantity<L + L2, A + A2> multiplyBy(const Quantity<L2, A2> &rhs) const {
      return Quantity<L + L2, A + A2>(m_val * rhs.m_val, m_unit * rhs.m_unit);
    }

    template<int L2, int A2>
    Quantity<L - L2, A - A2> divideBy(const Quantity<L2, A2> &rhs) const {
      return Quantity<L - L2, A - A2>(m_val / rhs.m_val, m_unit / rhs.m_unit);
    }
  };

  // Non-member operators.
  template<int L, int A>
  static Quantity<L, A> operator*(float val, const Unit<L, A> &unit) {
    return Quantity<L, A>(val, unit);
  }
}

#endif
