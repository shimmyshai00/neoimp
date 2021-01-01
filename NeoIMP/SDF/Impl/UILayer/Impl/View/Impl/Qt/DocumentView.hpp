#ifndef SDF_IMPL_UILAYER_IMPL_VIEW_IMPL_QT_DOCUMENTVIEW_HPP
#define SDF_IMPL_UILAYER_IMPL_VIEW_IMPL_QT_DOCUMENTVIEW_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    DocumentView.hpp
 * PURPOSE: Headers for the Qt-based document view implementation.
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

#include <SDF/Impl/UILayer/Impl/View/IDocumentView.hpp>
#include <SDF/Impl/UILayer/AbstractModel/Handle.hpp>

#include <QPointer>
#include <memory>

namespace SDF::Impl::UILayer {
  namespace AbstractModel::Services {
    class IImageInformationService;
    class IImageRenderingService;
  }

  namespace Impl::View::Impl::Qt {
    namespace CustomWidgets {
      class DocumentWidget;
      class IImageDataSource;
    }

    namespace Windows {
      class MainWindow;
    }

    class DocumentView : public IDocumentView {
    public:
      DocumentView(
        AbstractModel::Services::IImageInformationService *imageInformationService,
        AbstractModel::Services::IImageRenderingService *imageRenderingService,
        QPointer<Windows::MainWindow> mainWindowContext,
        AbstractModel::Handle documentHandle
      );

      void updateDocumentName();
    private:
      AbstractModel::Services::IImageInformationService *m_imageInformationService;
      AbstractModel::Services::IImageRenderingService *m_imageRenderingService;

      QPointer<Windows::MainWindow> m_mainWindowContext;
      QPointer<CustomWidgets::DocumentWidget> m_documentWidget;

      AbstractModel::Handle m_documentHandle;
      std::unique_ptr<CustomWidgets::IImageDataSource> m_imageDataSource;
    };
  }
}

#endif