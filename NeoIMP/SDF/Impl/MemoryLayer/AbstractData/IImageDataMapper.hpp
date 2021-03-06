#ifndef SDF_IMPL_MEMORYLAYER_ABSTRACTDATA_IIMAGEDATAMAPPER_HPP
#define SDF_IMPL_MEMORYLAYER_ABSTRACTDATA_IIMAGEDATAMAPPER_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    IImageDataMapper.hpp
 * PURPOSE: An interface for image data mappers.
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

#include <SDF/Impl/ModelLayer/Impl/DomainObjects/Image/AbstractImage.hpp>

#include <memory>
#include <string>

namespace SDF::Impl::MemoryLayer::AbstractData {
  class IImageDataMapper {
  public:
    // Stub:     ~IImageDataMapper()
    // Purpose:  Destructor
    virtual ~IImageDataMapper() = default;

    // Stub:     saveImage
    // Purpose:  Persists an image to a file system under the file specifier 'fileSpec'.
    virtual void saveImage(std::string fileSpec,
                           ModelLayer::Impl::DomainObjects::Image::AbstractImage *image
                          ) = 0;

    // Stub:    loadImage
    // Purpose: Attempts to retrieve an image from the file system through the file specifier 'fileSpec'.
    virtual std::unique_ptr<ModelLayer::Impl::DomainObjects::Image::AbstractImage> loadImage(std::string fileSpec) = 0;
  };
}

#endif
