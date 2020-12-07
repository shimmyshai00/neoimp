/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ImageRepository.tpp
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

namespace SDF::Impl::MemoryLayer::Impl {
  template<class ImageType>
  ImageRepository<ImageType>::ImageRepository() {}

  template<class ImageType>
  ModelLayer::Handle ImageRepository<ImageType>::addNewImage(std::string uri, std::unique_ptr<ImageType> image) {
    ModelLayer::Handle handle(HandleGenerator::inst()->getNextHandle());

    m_uriStore[handle] = uri;
    m_imageStore[handle] = std::move(image);

    return handle;
  }

  template<class ImageType>
  void ImageRepository<ImageType>::persistImage(ModelLayer::Handle handle) {
    // TBA
  }

  template<class ImageType>
  ImageType *ImageRepository<ImageType>::access(ModelLayer::Handle handle) {
    if(m_imageStore.find(handle) == m_imageStore.end()) {
      throw MemoryLayer::Exception::InvalidHandleException(handle);
    } else {
      return m_imageStore[handle].get();
    }
  }
}
