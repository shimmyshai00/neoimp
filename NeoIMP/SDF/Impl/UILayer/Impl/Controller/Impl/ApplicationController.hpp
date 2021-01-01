#ifndef SDF_IMPL_UILAYER_IMPL_CONTROLLER_APPLICATIONCONTROLLER_HPP
#define SDF_IMPL_UILAYER_IMPL_CONTROLLER_APPLICATIONCONTROLLER_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ApplicationController.hpp
 * PURPOSE: The MVC controller for the application view.
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

#include <SDF/Impl/UILayer/Impl/Framework/IMVCViewEventHook.hpp>

#include <SDF/Impl/UILayer/Impl/View/Events/ExitCommandEvent.hpp>

#include <map>

namespace SDF::Impl::UILayer::Impl {
  class IUIController;

  namespace Controller::Impl {
    class ApplicationController {
    public:
      ApplicationController(IUIController *uiController);
      ~ApplicationController();

      void hookExitCommandEvent(Framework::IMVCViewEventHook<View::Events::ExitCommandEvent> *hook);
      void removeExitCommandHook(Framework::IMVCViewEventHook<View::Events::ExitCommandEvent> *hook);
    private:
      IUIController *m_uiController;

      std::map<Framework::IMVCViewEventHook<View::Events::ExitCommandEvent> *, boost::signals2::connection>
        m_exitCommandHookMap;
    };
  }
}

#endif