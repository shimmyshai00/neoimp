#ifndef SDF_IMPL_MEMORYLAYER_IMPL_IMAGEREPOSITORY_HPP
#define SDF_IMPL_MEMORYLAYER_IMPL_IMAGEREPOSITORY_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    ImageRepository.hpp
 * PURPOSE: Headers for the implementation of an in-memory image repository linked to persistent backing storage.
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

#include <SDF/Impl/MemoryLayer/IImageRepository.hpp>
#include <SDF/Impl/ModelLayer/Services/Impl/DomainObjects/Image/AbstractImage.hpp>

#include <map>
#include <string>
#include <memory>

#include <fruit/fruit.h>

namespace SDF::Impl {
  namespace MemoryLayer::Impl {
    class ImageRepository : public MemoryLayer::IImageRepository {
    public:
      INJECT(ImageRepository());

      ModelLayer::Handle addNewImage(
        std::string uri, std::unique_ptr<ModelLayer::Services::Impl::DomainObjects::Image::AbstractImage> image
      );
      void persistImage(ModelLayer::Handle handle);

      ModelLayer::Services::Impl::DomainObjects::Image::AbstractImage *access(ModelLayer::Handle handle);
    private:
      std::map<ModelLayer::Handle, std::string> m_uriStore;
      std::map<ModelLayer::Handle, std::unique_ptr<ModelLayer::Services::Impl::DomainObjects::Image::AbstractImage>>
        m_imageStore;
    };
  }
}

#endif