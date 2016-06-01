/*
 * rippermodel.h - GxfRip
 *
 * Copyright (C) 2016  Wicked_Digger <wicked_digger@mail.ru>
 *
 * This file is part of gfxrip.
 *
 * gfxrip is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gfxrip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gfxrip.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "src/rippermodel.h"

#include <QModelIndex>
#include <QImage>
#include <QPixmap>

#include "src/gfxrip.h"

RipperModel::RipperModel(gr_ripper_t *ripper, QObject *parent)
  : QAbstractItemModel(parent) {
  set_ripper(ripper);
}

int
RipperModel::columnCount(const QModelIndex &parent) const {
  if (!parent.isValid()) {
    return 1;
  }

  return 0;
}

QVariant
RipperModel::data(const QModelIndex &index, int role) const {
  QVariant result;

  switch (role) {
    case Qt::DisplayRole:
      result = QString::number(index.row());
      break;
    case Qt::DecorationRole: {
      gr_bitmap_t *img = ripper->get_image(index.row());
      QImage image(img->get_data(), img->get_width(), img->get_height(),
                   QImage::Format_ARGB32);
      delete img;
      result = QPixmap::fromImage(image);
      break;
    }
    case Qt::SizeHintRole: {
      gr_size_t size = ripper->get_image_size(index.row());
      result = QSize(size.width, size.height);
      break;
    }
  }

  return result;
}

QModelIndex
RipperModel::index(int row, int column, const QModelIndex & /*parent*/) const {
  return createIndex(row, column);
}

QModelIndex
RipperModel::parent(const QModelIndex & /*index*/) const {
  return QModelIndex();
}

int
RipperModel::rowCount(const QModelIndex &parent) const {
  if (!parent.isValid()) {
    return ripper->get_image_count();
  }

  return 0;
}

void
RipperModel::image_updated() {
  beginResetModel();
  endResetModel();
}
