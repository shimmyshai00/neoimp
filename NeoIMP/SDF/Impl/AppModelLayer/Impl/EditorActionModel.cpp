/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    EditorActionModel.cpp
 * PURPOSE: Delegates all the actions possible in the editor to the appropriate (domain) model-layer services.
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

#include <EditorActionModel.hpp>

#include <AppModelLayer/Exceptions/Exceptions.hpp>

#include <AbstractModel/Services/IDocumentCreationService.hpp>
#include <AbstractModel/Services/IDocumentStorageService.hpp>
#include <AbstractModel/Services/IImageInformationService.hpp>
#include <AbstractModel/Services/IImageRenderingService.hpp>

#include <EditorStateModel.hpp>
#include <DocumentStateModel.hpp>

#include <iostream>

namespace SDF::Impl::AppModelLayer::Impl {
  EditorActionModel::EditorActionModel(AbstractModel::Services::IDocumentCreationService *documentCreationService,
                                       AbstractModel::Services::IDocumentStorageService *documentStorageService,
                                       AbstractModel::Services::IImageInformationService *imageInformationService,
                                       AbstractModel::Services::IImageRenderingService *imageRenderingService,
                                       EditorStateModel *editorStateModel
                                      )
    : m_documentCreationService(documentCreationService),
      m_documentStorageService(documentStorageService),
      m_imageInformationService(imageInformationService),
      m_imageRenderingService(imageRenderingService),
      m_editorStateModel(editorStateModel)
  {}

  UILayer::AbstractAppModel::Handle
  EditorActionModel::createDocument(UILayer::AbstractAppModel::Data::DocumentSpec spec) {
    std::cout << "create" << std::endl;
    AbstractModel::Data::DocumentSpec modelSpec {
      spec.documentName,
      spec.documentWidthPx,
      spec.documentHeightPx,
      spec.documentResolutionPpi,
      spec.colorModel,
      spec.bitDepth
    };

    UILayer::AbstractAppModel::Handle handle(m_documentCreationService->createDocument(modelSpec));
    AbstractModel::Handle renderingHandle(m_imageRenderingService->renderImage(handle));

    const unsigned char *renderedDataPtr(nullptr);
    std::ptrdiff_t rowStride(0);
    m_imageRenderingService->getRenderedRegion(
      renderedDataPtr, rowStride,
      renderingHandle,
      0, 0, spec.documentWidthPx-1, spec.documentHeightPx-1
    );

    std::cout << "rz" << std::endl;
    std::cout << (const void *)renderedDataPtr << std::endl;

    // NB: upgrade to reflect new rendering system setup w/different data access interface?
    m_editorStateModel->addDocument(handle, spec, renderedDataPtr);
    m_editorStateModel->setFocusDocument(handle);

    return handle;
  }

  void
  EditorActionModel::saveDocumentAs(std::string fileName, DataLayer::Properties::FileFormat fileFormat) {
    UILayer::AbstractAppModel::Handle handleOfDocumentToSave(m_editorStateModel->getFocusDocument());
    std::cout << "saving document " << handleOfDocumentToSave << " to " << fileName << " with format " << fileFormat << "..." << std::endl;
    m_documentStorageService->saveDocument(fileName, fileFormat, handleOfDocumentToSave);
    m_editorStateModel->getDocumentStateModel(handleOfDocumentToSave)->setDocumentName(fileName); // YES!!!!! Finally!
    m_editorStateModel->getDocumentStateModel(handleOfDocumentToSave)->setDocumentFileName(fileName);
    m_editorStateModel->getDocumentStateModel(handleOfDocumentToSave)->setDocumentFileFormat(fileFormat);
  }

  void
  EditorActionModel::saveDocument() {
    UILayer::AbstractAppModel::Handle handle(m_editorStateModel->getFocusDocument());
    if(m_editorStateModel->getDocumentStateModel(handle)->getDocumentFileName() == "") {
      throw AppModelLayer::Exceptions::FileNameNotSetException();
    } else {
      // save to the already-remembered file name and format
      std::string fileName(m_editorStateModel->getDocumentStateModel(handle)->getDocumentFileName());
      DataLayer::Properties::FileFormat fileFormat(
        m_editorStateModel->getDocumentStateModel(handle)->getDocumentFileFormat()
      );

      m_documentStorageService->saveDocument(fileName, fileFormat, handle);
    }
  }

  void
  EditorActionModel::openDocument(std::string fileName, DataLayer::Properties::FileFormat fileFormat) {
    std::cout << "opening document file " << fileName << " with format " << fileFormat << "..." << std::endl;
    UILayer::AbstractAppModel::Handle handle(m_documentStorageService->loadDocument(fileName, fileFormat));
    std::cout << "loaded" << std::endl;

    // Render the image (Note: spin this off into a separate method? - DRAFT of this method)
    AbstractModel::Handle renderingHandle(m_imageRenderingService->renderImage(handle));
    int imageWidth(m_imageInformationService->getImageWidth(handle));
    int imageHeight(m_imageInformationService->getImageHeight(handle));
    float imageResolutionPpi(m_imageInformationService->getImageResolutionPpi(handle));

    const unsigned char *renderedDataPtr(nullptr);
    std::ptrdiff_t rowStride(0);
    m_imageRenderingService->getRenderedRegion(
      renderedDataPtr, rowStride,
      renderingHandle,
      0, 0, imageWidth-1, imageHeight-1
    );

    m_editorStateModel->addDocument(handle, fileName, imageWidth, imageHeight, imageResolutionPpi, renderedDataPtr);
    m_editorStateModel->setFocusDocument(handle);
  }

  void
  EditorActionModel::setFocusDocument(UILayer::AbstractAppModel::Handle handle) {
    std::cout << "focus document changing to " << handle << "..." << std::endl;
    m_editorStateModel->setFocusDocument(handle);
  }
}
