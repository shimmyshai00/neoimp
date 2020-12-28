/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ImageBaseEditingService.cpp
 * PURPOSE: The implementation of the MVC base image editing service.
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

#include <ImageBaseEditingService.hpp>

#include <SDF/Impl/DataLayer/Exceptions/Exceptions.hpp>
#include <SDF/Impl/ModelLayer/Exceptions/Exceptions.hpp>

#include <AbstractData/IImageRepository.hpp>
#include <DomainObjects/Image/AbstractImage.hpp>

#include <Framework/Handle.hpp>

namespace SDF::Impl::ModelLayer::Impl::Services {
  ImageBaseEditingService::ImageBaseEditingService(AbstractData::IImageRepository *imageRepository)
    : m_imageRepository(imageRepository)
  {}

  void ImageBaseEditingService::setImageName(Framework::Handle handle, std::string newImageName) {
    try {
      m_imageRepository->retrieveNonOwning(handle)->get().setImageName(newImageName);
    } catch(DataLayer::Exceptions::ObjectNotFoundException &e) {
      throw ModelLayer::Exceptions::InvalidHandleException(handle);
    }
  }
}
