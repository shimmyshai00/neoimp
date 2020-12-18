#ifndef SDF_IMPL_UILAYER_IMPL_VIEW_ABSTRACTCONTROLLER_IDOCUMENTGAINFOCUSOBSERVER_HPP
#define SDF_IMPL_UILAYER_IMPL_VIEW_ABSTRACTCONTROLLER_IDOCUMENTGAINFOCUSOBSERVER_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    IDocumentGainFocusObserver.hpp
 * PURPOSE: An interface to receive an event indicating a document has received the UI focus.
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

#include <SDF/Impl/ModelLayer/Handle.hpp>

namespace SDF::Impl::UILayer::Impl::View::AbstractController {
  class IDocumentGainFocusObserver {
  public:
    virtual ~IDocumentGainFocusObserver() = default;

    virtual void onDocumentGainedFocus(ModelLayer::Handle newFocusDocumentHandle) = 0;
  };
}

#endif
