#ifndef SDF_UILAYER_VIEW_QT_APPLICATIONVIEW_HPP
#define SDF_UILAYER_VIEW_QT_APPLICATIONVIEW_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ApplicationView.hpp
 * PURPOSE: Headers for the Qt-based application view implementation.
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

#include <SDF/UILayer/View/IApplicationView.hpp>

#include <SDF/UILayer/View/Qt/Windows/MainWindow.hpp>
#include <QPointer>

#include <fruit/fruit.h>

namespace SDF::UILayer::View::Qt {
  class ApplicationView : public IApplicationView {
  public:
    INJECT(ApplicationView());

    void showApplicationView();
  private:
    QPointer<Windows::MainWindow> m_mainWindow;
  };
}

#endif
