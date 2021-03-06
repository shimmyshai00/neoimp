#ifndef SDF_IMPL_FRAMEWORK_MVCVIEWNODE_HPP
#define SDF_IMPL_FRAMEWORK_MVCVIEWNODE_HPP

/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    MVCViewNode.hpp
 * PURPOSE: The hierarchical container for MVC views.
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

#include <memory>

namespace SDF::Impl::Framework {
  class MVCViewNode {
  public:
    MVCViewNode();
    virtual ~MVCViewNode() = 0;

    MVCViewNode *getParent();
    MVCViewNode *getFirstChild();
    MVCViewNode *getNextSibling();

    void addChildAtBeginning(std::unique_ptr<MVCViewNode> child);
    void addChildAfter(MVCViewNode *addAfter, std::unique_ptr<MVCViewNode> child);
    void addChildAtEnd(std::unique_ptr<MVCViewNode> child);

    std::unique_ptr<MVCViewNode> removeSelf();
  protected:
    virtual void onChildAdded(MVCViewNode *child); // called after add
    virtual void onChildRemoved(MVCViewNode *child); // called before remove
  private:
    MVCViewNode *m_parent;
    std::unique_ptr<MVCViewNode> m_firstChild;
    std::unique_ptr<MVCViewNode> m_nextSibling;
  };
}

#endif
