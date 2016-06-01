/*
 * imagedelegate.h - GxfRip
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

#ifndef SRC_IMAGEDELEGATE_H_
#define SRC_IMAGEDELEGATE_H_

#include <QAbstractItemDelegate>

class ImageDelegate : public QAbstractItemDelegate {
 public:
  ImageDelegate();

  virtual void paint(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const;
  virtual QSize sizeHint(const QStyleOptionViewItem &option,
                         const QModelIndex &index) const;
};

#endif  // SRC_IMAGEDELEGATE_H_
