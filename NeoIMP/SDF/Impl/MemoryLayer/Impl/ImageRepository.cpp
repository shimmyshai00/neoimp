/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ImageRepository.cpp
 * PURPOSE: Implementation of an in-memory image repository linked to persistent backing storage.
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

#include <ImageRepository.hpp>

#include <ModelLayer/Services/Impl/DomainObjects/Image/AbstractImage.hpp>
#include <Exception/Exceptions.hpp>
#include <HandleGenerator.hpp>

namespace SDF::Impl::MemoryLayer::Impl {
  ImageRepository::ImageRepository() {}

  ModelLayer::Handle ImageRepository::addNewImage(
    std::string uri, std::unique_ptr<ModelLayer::Services::Impl::DomainObjects::Image::AbstractImage> image
  ) {
    ModelLayer::Handle newHandle(HandleGenerator::inst()->getNextHandle());

    m_uriStore[newHandle] = uri;
    m_imageStore[newHandle] = std::move(image);

    return newHandle;
  }

  void ImageRepository::persistImage(ModelLayer::Handle handle) {
    // getNumBaseUnits
  }

  ModelLayer::Services::Impl::DomainObjects::Image::AbstractImage *ImageRepository::access(ModelLayer::Handle handle) {
    if(m_imageStore.find(handle) == m_imageStore.end()) {
      throw Exception::InvalidHandleException(handle);
    } else {
      return m_imageStore[handle].get();
    }
  }
}
