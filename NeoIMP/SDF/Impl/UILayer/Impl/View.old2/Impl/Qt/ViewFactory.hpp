#ifndef SDF_IMPL_UILAYER_IMPL_VIEW_IMPL_QT_VIEWFACTORY_HPP
#define SDF_IMPL_UILAYER_IMPL_VIEW_IMPL_QT_VIEWFACTORY_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ViewFactory.hpp
 * PURPOSE: The Qt-based view factory implementation.
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

#include <SDF/Impl/UILayer/Impl/View/IViewFactory.hpp>

#include <fruit/fruit.h>

namespace SDF::Impl::UILayer {
  namespace AbstractModel::Services {
    class IImageInformationService;
    class IImageRenderingService;
  }

  namespace Impl::View::Impl::Qt {
    class ViewFactory : public IViewFactory {
    public:
      INJECT(ViewFactory(
        AbstractModel::Services::IImageInformationService *imageInformationService,
        AbstractModel::Services::IImageRenderingService *imageRenderingService
      ));

      std::unique_ptr<IApplicationView> createApplicationView();
      std::unique_ptr<INewDocumentDialogView> createNewDocumentDialogView();
      std::unique_ptr<IOpenDocumentsView> createOpenDocumentsView(IApplicationView *context);
      std::unique_ptr<IDocumentView> createDocumentView(AbstractModel::Handle documentHandle);
    private:
      AbstractModel::Services::IImageInformationService *m_imageInformationService;
      AbstractModel::Services::IImageRenderingService *m_imageRenderingService;
    };
  }
}

#endif