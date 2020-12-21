#ifndef SDF_IMPL_UILAYER_IMPL_VIEW_IMPL_QT_APPLICATIONVIEW_HPP
#define SDF_IMPL_UILAYER_IMPL_VIEW_IMPL_QT_APPLICATIONVIEW_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ApplicationView.hpp
 * PURPOSE: The Qt-based application view object. This just wraps the main window.
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

#include <SDF/Impl/UILayer/Impl/View/IApplicationView.hpp>

#include <QPointer>
#include <vector>

namespace SDF::Impl::UILayer::Impl::View {
  namespace Observers {
    class INewDocumentCommandObserver;
    class ISaveDocumentCommandObserver;
    class ISaveDocumentAsCommandObserver;
    class IExitCommandObserver;
  }

  namespace Impl::Qt {
    namespace Windows {
      class MainWindow;
    }

    class ApplicationView : public IApplicationView {
    public:
      ApplicationView(QPointer<Windows::MainWindow> mainWindow);

      void show();
      void close();

      void addNewDocumentCommandObserver(Observers::INewDocumentCommandObserver *observer);
      void addSaveDocumentCommandObserver(Observers::ISaveDocumentCommandObserver *observer);
      void addSaveDocumentAsCommandObserver(Observers::ISaveDocumentAsCommandObserver *observer);
      void addExitCommandObserver(Observers::IExitCommandObserver *observer);
    private:
      QPointer<Windows::MainWindow> mainWindow;

      std::vector<Observers::INewDocumentCommandObserver *> m_newDocumentCommandObservers;
      std::vector<Observers::ISaveDocumentCommandObserver *> m_saveCommandObservers;
      std::vector<Observers::ISaveDocumentAsCommandObserver *> m_newDocumentCommandObservers;
      std::vector<Observers::IExitCommandObserver *> m_newDocumentCommandObservers;
    }
  }
}

#endif
