#ifndef SDF_IMPL_APPMODELLAYER_IMPL_EDITORMODEL_HPP
#define SDF_IMPL_APPMODELLAYER_IMPL_EDITORMODEL_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    EditorModel.hpp
 * PURPOSE: Provides an abstracted "user interface" for the core editor functionality - loading, saving, managing and
 *          selecting documents for editing, including transient state such as which document is currently selected for
 *          editing.
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

#include <SDF/Impl/UILayer/AbstractAppModel/IEditorState.hpp>
#include <SDF/Impl/UILayer/AbstractAppModel/ICreateDocumentCommand.hpp>
#include <SDF/Impl/UILayer/AbstractAppModel/DocumentHandle.hpp>
#include <SDF/Impl/UILayer/AbstractAppModel/Data/DocumentSpec.hpp>

#include <SDF/Impl/DataLayer/Properties/FileFormat.hpp>

#include <fruit/fruit.h>
#include <string>

namespace SDF::Impl::AppModelLayer {
  namespace AbstractModel::Services {
    class IDocumentCreationService;
    class IDocumentStorageService;
    class IImageInformationService;
    class IImageBaseEditingService;
  }

  namespace Impl {
    class EditorModel : public UILayer::AbstractAppModel::IEditorState,
      public UILayer::AbstractAppModel::ICreateDocumentCommand
    {
    public:
      INJECT(EditorModel(
        AbstractModel::Services::IDocumentCreationService *documentCreationService,
        AbstractModel::Services::IDocumentStorageService *documentStorageService,
        AbstractModel::Services::IImageInformationService *imageInformationService,
        AbstractModel::Services::IImageBaseEditingService *imageBaseEditingService
      ));
      ~EditorModel();

      UILayer::AbstractAppModel::DocumentHandle createDocument(UILayer::AbstractAppModel::Data::DocumentSpec spec);
      void saveDocument(
        UILayer::AbstractAppModel::DocumentHandle handle,
        std::string fileName, DataLayer::Properties::FileFormat fileFormat
      );
      UILayer::AbstractAppModel::DocumentHandle loadDocument(
        std::string fileName, DataLayer::Properties::FileFormat fileFormat
      );

      std::vector<UILayer::AbstractAppModel::DocumentHandle> getOpenDocuments();
      UILayer::AbstractAppModel::DocumentHandle getEditingFocusDocument();
      void setEditingFocusDocument(UILayer::AbstractAppModel::DocumentHandle focusDocument);
    private:
      AbstractModel::Services::IDocumentCreationService *m_documentCreationService;
      AbstractModel::Services::IDocumentStorageService *m_documentStorageService;
      AbstractModel::Services::IImageInformationService *m_imageInformationService;
      AbstractModel::Services::IImageBaseEditingService *m_imageBaseEditingService;

      std::vector<UILayer::AbstractAppModel::DocumentHandle> m_openDocuments;
      UILayer::AbstractAppModel::DocumentHandle m_focusDocumentHandle;
    };
  }
}

#endif