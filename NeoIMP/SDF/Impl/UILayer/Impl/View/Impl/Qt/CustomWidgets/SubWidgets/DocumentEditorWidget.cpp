/*
 * NeoIMP version 1.0.0 (STUB) - toward an easier-to-maintain GIMP alternative.
 * (C) 2020 Shimrra Shai. Distributed under both GPLv3 and MPL licenses.
 *
 * FILE:    DocumentEditorWidget.cpp
 * PURPOSE: Implementation of the custom Qt UI widget that actually displays an image document.
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

#include <DocumentEditorWidget.hpp>

#include <IImageDataSource.hpp>

#include <iostream>

namespace SDF::Impl::UILayer::Impl::View::Impl::Qt::CustomWidgets::SubWidgets {
  DocumentEditorWidget::DocumentEditorWidget(QWidget *parent)
    : QWidget(parent),
      m_dataSource(nullptr),
      m_magnification(1.0f)
  {}

  QSize
  DocumentEditorWidget::sizeHint() const {
    if(m_dataSource != nullptr) {
      return QSize(m_dataSource->getImageWidth(), m_dataSource->getImageHeight());
    } else {
      return QSize(-1, -1);
    }
  }

  void
  DocumentEditorWidget::setDataSource(IImageDataSource *dataSource) {
    m_dataSource = dataSource;
  }

  void
  DocumentEditorWidget::setMagnification(float newMagnification) {
    m_magnification = newMagnification;
  }

  // Private members.
  void
  DocumentEditorWidget::paintEvent(QPaintEvent *event) {
    QPainter qp(this);

    paintWidgetRegion(qp, event->rect());
  }

  void
  DocumentEditorWidget::paintWidgetRegion(QPainter &qp, QRect rect) {
    if(m_dataSource != nullptr) {
      QRect imageRect(0, 0, m_dataSource->getImageWidth(), m_dataSource->getImageHeight());
      QRect clipped(rect.intersected(imageRect));

      // Draw the image data within the clipped rectangle. NB: Magnification (zoom) not yet implemented.
      std::cout << "paint: " << clipped.width() << " " << clipped.height() << std::endl;
      if((clipped.width() > 0) && (clipped.height() > 0)) {
        const unsigned char *imageData(nullptr);
        std::ptrdiff_t rowStride(0);

        m_dataSource->accessImageData(
          imageData, rowStride,
          clipped.x(), clipped.y(),
          clipped.x() + clipped.width() - 1, clipped.y() + clipped.height() - 1
        );

        QImage qImage(imageData, clipped.width(), clipped.height(), rowStride, QImage::Format_RGB32);
        qp.drawImage(clipped, qImage);
      }
    }
  }
}
