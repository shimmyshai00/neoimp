/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    QtNewDocumentParamsView.cpp
 * PURPOSE: The Qt-based new-document parameters view implementation.
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

#include <QtNewDocumentParamsView.hpp>

#include <INewDocumentParamsReceiver.hpp>

#include <Dialogs/NewDocumentDialog.hpp>

namespace SDF::Impl::UILayer::Impl::View::Impl::Qt {
  QtNewDocumentParamsView::QtNewDocumentParamsView(Dialogs::NewDocumentDialog *newDocumentDialog)
    : m_newDocumentDialog(newDocumentDialog)
  {}

  QtNewDocumentParamsView::~QtNewDocumentParamsView() {
    QObject::disconnect(m_newDocumentParamsReceiverConn);
  }

  void QtNewDocumentParamsView::getNewDocumentParams(INewDocumentParamsReceiver *recv) {
    m_newDocumentParamsReceiverConn = QObject::connect(m_newDocumentDialog, &QDialog::accepted, [=]() {
      m_newDocumentDialog->submit(recv);
    });

    m_newDocumentDialog->open();
  }
}