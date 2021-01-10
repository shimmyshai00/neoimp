/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    OpenDocumentsView.cpp
 * PURPOSE: The Qt-based open-documents view.
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

#include <OpenDocumentsView.hpp>

#include <UILayer/Exceptions/Exceptions.hpp>
#include <Framework/MVCMessageEncoder.hpp>

#include <AbstractModel/Services/IImageInformationService.hpp>
#include <AbstractModel/Services/IImageRenderingService.hpp>

#include <Controller/Messages.hpp>

#include <IDocumentView.hpp>

#include <Windows/MainWindow.hpp>

#include <DocumentView.hpp>

namespace SDF::Impl::UILayer::Impl::View::Impl::Qt {
  OpenDocumentsView::OpenDocumentsView(
    QPointer<Windows::MainWindow> mainWindow,
    AbstractModel::Services::IImageInformationService *imageInformationService,
    AbstractModel::Services::IImageRenderingService *imageRenderingService
  )
    : m_imageInformationService(imageInformationService),
      m_imageRenderingService(imageRenderingService),
      m_tabWidget(new QTabWidget)
  {
    mainWindow->addPrincipalWidget(m_tabWidget);
  }

  OpenDocumentsView::~OpenDocumentsView() {

  }

  QTabWidget *OpenDocumentsView::getDetail() {
    return m_tabWidget;
  }

  void OpenDocumentsView::activate() {}

  void OpenDocumentsView::update(std::string updateEvent) {
    std::pair<std::string, int> decodedMessage(Framework::decodeExtra(updateEvent));
    if(decodedMessage.first == Controller::Messages::DocumentCreated) {
      AbstractModel::Handle handle(decodedMessage.second);

      if(m_documentViews.find(handle) == m_documentViews.end()) {
        m_documentViews[handle] = std::make_unique<DocumentView>(
          m_tabWidget,
          m_imageInformationService, m_imageRenderingService,
          handle
        );
      }
    } else if(decodedMessage.first == Controller::Messages::DocumentRemoved) {
      AbstractModel::Handle handle(decodedMessage.second);

      if(m_documentViews.find(handle) != m_documentViews.end()) {
        m_documentViews.erase(handle);
      }
    }
  }

  void OpenDocumentsView::shutdown() {}

  IDocumentView *OpenDocumentsView::getDocumentView(AbstractModel::Handle handle) {
    if(m_documentViews.find(handle) == m_documentViews.end()) {
      throw UILayer::Exceptions::InvalidHandleException(handle);
    }

    return m_documentViews[handle].get();
  }
}