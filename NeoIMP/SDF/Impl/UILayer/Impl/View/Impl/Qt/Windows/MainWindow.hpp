#ifndef SDF_IMPL_UILAYER_IMPL_VIEW_IMPL_QT_WINDOWS_MAINWINDOW_HPP
#define SDF_IMPL_UILAYER_IMPL_VIEW_IMPL_QT_WINDOWS_MAINWINDOW_HPP
/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    MainWindow.hpp
 * PURPOSE: The Qt object corresponding to the main window.
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

#include <QWidget>
#include <QMainWindow>

#include <QString>
#include <QPointer>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace SDF::Impl::UILayer::Impl::View::Impl::Qt::Windows {
  class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPrincipalWidget(QWidget *widget);

    void enableOptionsThatOnlyWorkOnOpenDocuments();
    void disableOptionsThatOnlyWorkOnOpenDocuments();
  signals:
    void newClicked();
    void openClicked();
    void saveAsClicked();
    void saveClicked();
    void exitClicked();
  private:
    std::unique_ptr<Ui::MainWindow> m_ui;
  };
}

#endif
