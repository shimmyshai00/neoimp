/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    DocumentView.cpp
 * PURPOSE: The Qt-based document view implementation.
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

#include <DocumentView.hpp>

/*
#include <Framework/MVCMessageEncoder.hpp>

#include <AbstractModel/Services/IImageInformationService.hpp>
#include <AbstractModel/Services/IImageRenderingService.hpp>
*/

#include <Windows/MainWindow.hpp>
#include <AbstractModel/Handle.hpp>

/*
#include <Controller/Messages.hpp>
*/

#include <CustomWidgets/DocumentWidget.hpp>
#include <CustomWidgets/IImageDataSource.hpp>

#include <iostream>

namespace SDF::Impl::UILayer::Impl::View::Impl::Qt {
  // Helper object
  class ImageDataSource : public CustomWidgets::IImageDataSource {
  public:
    ImageDataSource(AbstractAppModel::State::IDocumentAppModel *documentAppModel)
      : m_documentAppModel(documentAppModel)
    {}

    int getImageWidth() {
      return m_documentAppModel->getDocumentWidthPx();
    }

    int getImageHeight() {
      return m_documentAppModel->getDocumentHeightPx();
    }

    void accessImageData(const unsigned char *&origin,
                         std::ptrdiff_t &rowStride,
                         int x1, int y1, int x2, int y2
                        )
    {
      m_documentAppModel->getRenderedImageData(origin, rowStride, x1, y1, x2, y2);
    }
  private:
    AbstractAppModel::State::IDocumentAppModel *m_documentAppModel;
  };
}

namespace SDF::Impl::UILayer::Impl::View::Impl::Qt {
  DocumentView::DocumentView()
    : m_documentWidget(new CustomWidgets::DocumentWidget)
  {}

  DocumentView::~DocumentView() {}

  void
  DocumentView::addToTabWidget(QPointer<QTabWidget> tabWidget) {
    if(!m_tabWidget && getAppModel()) {
      m_tabWidget = tabWidget;
      m_tabWidget->addTab(m_documentWidget, getAppModel()->getDocumentName().c_str());
      hookTabFocusSignal();
    }
  }

  void
  DocumentView::acquireTabFocus() {
    if(m_tabWidget) {
      unhookTabFocusSignal();
      m_tabWidget->setCurrentWidget(m_documentWidget);
      hookTabFocusSignal();
    }
  }

  AbstractAppModel::Handle
  DocumentView::getViewedDocumentHandle() {
    return getAppModel()->getDocumentHandle();
  }

  // Protected members.
  void
  DocumentView::onAttachAppModel() {
    m_imageDataSource = std::make_unique<ImageDataSource>(getAppModel());
    m_documentWidget->setDataSource(m_imageDataSource.get());

    safeConnect(getAppModel()->onDocumentNameChanged, [=](std::string newName) {
      int ourDocumentWidgetIndex(m_tabWidget->indexOf(m_documentWidget));
      m_tabWidget->setTabText(ourDocumentWidgetIndex, newName.c_str());
    });
  }

  // Private members.
  // These members are needed to prevent infinite recursive looping when this widget is asked by the acquireTabFocus
  // method to get focus. That method is meant to be used for synchronizing the editor model focus state with the
  // view focus state. (NB: perh. would be better to move all this handling into ApplicationView and similar?)
  void
  DocumentView::hookTabFocusSignal() {
    m_tabFocusConnection = QObject::connect(m_tabWidget, &QTabWidget::currentChanged, [=](int newIndex) {
      if(m_tabWidget->widget(newIndex) == static_cast<QWidget *>(m_documentWidget)) {
        // this widget got focus
        onGetFocus(getAppModel()->getDocumentHandle());
      }
    });
  }

  void
  DocumentView::unhookTabFocusSignal() {
    QObject::disconnect(m_tabFocusConnection);
  }
}
