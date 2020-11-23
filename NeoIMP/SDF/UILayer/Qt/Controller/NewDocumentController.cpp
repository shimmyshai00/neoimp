/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    NewDocumentController.cpp
 * PURPOSE: Implementation of the NewDocumentController class.
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

#include <NewDocumentController.hpp>

#include <INewDocumentParameterReceiver.hpp>
#include <INewDocumentView.hpp>
#include <View/NewDocumentView.hpp>

#include <iostream>

namespace SDF::UILayer::Qt::Controller {
  class NewDocumentController : public INewDocumentController, public INewDocumentParameterReceiver {
  public:
    INJECT(NewDocumentController(INewDocumentView *NewDocumentView)) :
    m_newDocumentView(NewDocumentView) {}

    ~NewDocumentController() {}

    void startNewDocumentRequest() {
      m_newDocumentView->requestNewDocumentParamsFromUser(this);
    }

    void receiveNewDocumentSpecification(
      int documentWidthPx, int documentHeightPx, float resolutionPpi,
      ModelLayer::DomainObjects::Color::ColorModel colorModel, ModelLayer::DomainObjects::Color::BitDepth bitDepth
    ) {
      // TBA: pass this on to the model layer.
      std::cout << "New document requested: " << std::endl;
      std::cout << " Dimensions: " << documentWidthPx << "px x " << documentHeightPx << " px" << std::endl;
      std::cout << " Resolution: " << resolutionPpi << " PPI" << std::endl;
      std::cout << " Color model index: " << colorModel << std::endl;
      std::cout << " Bit depth index: " << bitDepth << std::endl;
      std::cout << std::endl;
    }
  private:
    INewDocumentView *m_newDocumentView;
  };
}

namespace SDF::UILayer::Qt::Controller {
  fruit::Component<INewDocumentController> getNewDocumentControllerComponent() {
    return fruit::createComponent()
      .bind<INewDocumentController, NewDocumentController>()
      .install(View::getNewDocumentViewComponent);
  }
}
