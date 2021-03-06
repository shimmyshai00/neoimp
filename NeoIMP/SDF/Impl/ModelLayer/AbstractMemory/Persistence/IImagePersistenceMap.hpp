#ifndef SDF_IMPL_MODELLAYER_ABSTRACTMEMORY_PERSISTENCE_IIMAGEPERSISTENCEMAP_HPP
#define SDF_IMPL_MODELLAYER_ABSTRACTMEMORY_PERSISTENCE_IIMAGEPERSISTENCEMAP_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    IImagePersistenceMap.hpp
 * PURPOSE: Interface for a map between document repository IDs (handles) and persistence-specific data such as file
 *          names and formats.
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

#include <SDF/Impl/ModelLayer/AbstractMemory/Handle.hpp>
#include <SDF/Impl/DataLayer/Properties/FileFormat.hpp>

#include <string>

namespace SDF::Impl::ModelLayer::AbstractMemory::Persistence {
  class IImagePersistenceMap {
  public:
    virtual ~IImagePersistenceMap() = default;

    virtual void assignFileSpec(Handle handle, std::string fileSpec) = 0;
    virtual void assignFileFormat(Handle handle, DataLayer::Properties::FileFormat fileFormat) = 0;
  };
}

#endif
