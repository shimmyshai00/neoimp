#ifndef SDF_IMPL_UILAYER_IMPL_CONTROLLER_NEWDOCUMENTDIALOGCONTROLLER_HPP
#define SDF_IMPL_UILAYER_IMPL_CONTROLLER_NEWDOCUMENTDIALOGCONTROLLER_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    NewDocumentDialogController.hpp
 * PURPOSE: The controller for the new-document dialog view.
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

#include <SDF/Impl/UILayer/Impl/Framework/IMVCController.hpp>
#include <SDF/Impl/UILayer/Impl/Framework/IMVCView.hpp>
#include <SDF/Impl/UILayer/Impl/Framework/MVCViewEvent.hpp>

namespace SDF::Impl::UILayer {
  namespace AbstractAppModel {
    class IDocumentCreator;
  }

  namespace Impl {
    class IViewSink;

    namespace View {
      class BaseNewDocumentView;
    }

    namespace Controller {
      class NewDocumentDialogController : public Framework::IMVCController {
      public:
        NewDocumentDialogController(AbstractAppModel::IDocumentCreator *documentCreator, IViewSink *viewSink);

        void onViewEvent(Framework::IMVCView *view, Framework::MVCViewEvent e);
      private:
        AbstractAppModel::IDocumentCreator *m_documentCreator;
        
        IViewSink *m_viewSink;
      };
    }
  }
}

#endif