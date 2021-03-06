/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ViewFactory.cpp
 * PURPOSE: The Qt-based view factory.
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

#include <ViewFactory.hpp>

#include <IUIControl.hpp>
#include <IViewSink.hpp>

#include <AbstractAppModel/Actions/ICreateDocumentAction.hpp>
#include <AbstractAppModel/Actions/ISaveDocumentAsAction.hpp>
#include <AbstractAppModel/Actions/ISaveDocumentAction.hpp>
#include <AbstractAppModel/Actions/IOpenDocumentAction.hpp>
#include <AbstractAppModel/Actions/ISetFocusDocumentAction.hpp>

#include <AbstractAppModel/State/IOpenDocumentsAppModel.hpp>

#include <ApplicationView.hpp>
#include <NewDocumentView.hpp>
#include <SaveDocumentView.hpp>
#include <OpenDocumentView.hpp>
#include <DocumentView.hpp>

//#include <Controller/ControllerFactory.hpp>
#include <Controller/ApplicationController.hpp>
#include <Controller/NewDocumentDialogController.hpp>
#include <Controller/SaveDocumentDialogController.hpp>
#include <Controller/OpenDocumentDialogController.hpp>
#include <Controller/DocumentController.hpp>

#include <iostream>

namespace SDF::Impl::UILayer::Impl::View::Impl::Qt {
  ViewFactory::ViewFactory(IViewSink *viewSink,
                           AbstractAppModel::Actions::ICreateDocumentAction *createDocumentAction,
                           AbstractAppModel::Actions::ISaveDocumentAsAction *saveDocumentAsAction,
                           AbstractAppModel::Actions::ISaveDocumentAction *saveDocumentAction,
                           AbstractAppModel::Actions::IOpenDocumentAction *openDocumentAction,
                           AbstractAppModel::Actions::ISetFocusDocumentAction *setFocusDocumentAction,
                           AbstractAppModel::State::IOpenDocumentsAppModel *openDocumentsAppModel
                          )
    //: m_controllerFactory(new Controller::ControllerFactory(documentCreator, this))
    : m_viewSink(viewSink),
      m_createDocumentAction(createDocumentAction),
      m_saveDocumentAsAction(saveDocumentAsAction),
      m_saveDocumentAction(saveDocumentAction),
      m_openDocumentAction(openDocumentAction),
      m_setFocusDocumentAction(setFocusDocumentAction),
      m_openDocumentsAppModel(openDocumentsAppModel)
  {}

  ViewFactory::~ViewFactory() {}

  std::unique_ptr<IApplicationView>
  ViewFactory::createApplicationView(IUIControl *uiControl) {
    std::unique_ptr<IApplicationView> view(new ApplicationView(this));
    std::unique_ptr<Controller::ApplicationController> controller(
      new Controller::ApplicationController(uiControl, this, m_saveDocumentAction)
    );

    view->setAppModel(m_openDocumentsAppModel);
    view->addController(std::move(controller));

    return std::move(view);
  }

  std::unique_ptr<INewDocumentView>
  ViewFactory::createNewDocumentView() {
    std::unique_ptr<INewDocumentView> view(new NewDocumentView());
    std::unique_ptr<Controller::NewDocumentDialogController> controller(
      new Controller::NewDocumentDialogController(m_viewSink, m_createDocumentAction)
    );

    controller->setView(view.get());
    view->addController(std::move(controller));

    return std::move(view);
  }

  std::unique_ptr<ISaveDocumentView>
  ViewFactory::createSaveDocumentView() {
    std::unique_ptr<ISaveDocumentView> view(new SaveDocumentView());
    std::unique_ptr<Controller::SaveDocumentDialogController> controller(
      new Controller::SaveDocumentDialogController(m_viewSink, m_saveDocumentAsAction)
    );

    controller->setView(view.get());
    view->addController(std::move(controller));

    return std::move(view);
  }

  std::unique_ptr<IOpenDocumentView>
  ViewFactory::createOpenDocumentView() {
    std::unique_ptr<IOpenDocumentView> view(new OpenDocumentView());
    std::unique_ptr<Controller::OpenDocumentDialogController> controller(
      new Controller::OpenDocumentDialogController(m_viewSink, m_openDocumentAction)
    );

    controller->setView(view.get());
    view->addController(std::move(controller));

    return std::move(view);
  }

  std::unique_ptr<IDocumentView>
  ViewFactory::createDocumentView(AbstractAppModel::Handle handle) {
    std::unique_ptr<IDocumentView> view(new DocumentView());
    std::unique_ptr<Controller::DocumentController> controller(
      new Controller::DocumentController(m_setFocusDocumentAction)
    );

    controller->setView(view.get());

    view->setAppModel(m_openDocumentsAppModel->getDocumentModel(handle));
    view->addController(std::move(controller));

    return std::move(view);
  }

/*
  std::unique_ptr<INewDocumentView> ViewFactory::createNewDocumentView() {
    std::unique_ptr<INewDocumentView> view(new NewDocumentView());
    view->addController(m_controllerFactory->createNewDocumentDlgController());

    return std::move(view);
  }

  std::unique_ptr<IDocumentView> ViewFactory::createDocumentView() {
    std::unique_ptr<IDocumentView> view(new DocumentView());

    return std::move(view);
  }
  */
}
