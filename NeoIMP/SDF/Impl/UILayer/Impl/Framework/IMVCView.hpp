#ifndef SDF_IMPL_UILAYER_IMPL_VIEW_IMVCVIEW_HPP
#define SDF_IMPL_UILAYER_IMPL_VIEW_IMVCVIEW_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    IMVCView.hpp
 * PURPOSE: Provides an interface for MVC views.
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

 #include <memory>

 namespace SDF::Impl::UILayer::Impl::Framework {
   class IMVCController;

   class IMVCView {
   public:
     virtual ~IMVCView() = default;

     virtual IMVCView *getParent() = 0;
     virtual IMVCView *getFirstChild() = 0;
     virtual IMVCView *getNextSibling() = 0;

     virtual IMVCView *addChildAtBeginning(std::unique_ptr<IMVCView> child) = 0;
     virtual IMVCView *addSiblingAfter(std::unique_ptr<IMVCView> sibling) = 0;
     virtual std::unique_ptr<IMVCView> removeChild(IMVCView *child) = 0;

     virtual void addController(std::unique_ptr<IMVCController> controller) = 0;
   };
 }

#endif
