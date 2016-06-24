/*
 * imagedelegate.cpp - GxfRip
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

#include "src/imagedelegate.h"

#include <QPainter>

ImageDelegate::ImageDelegate() {
}

void
ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                     const QModelIndex &index) const {
  QPixmap pixmap = index.data(Qt::DecorationRole).value<QPixmap>();
  QRect r;
  r.setLeft(option.rect.left() + 5);
  r.setTop(option.rect.top() + 5);
  r.setWidth(pixmap.width());
  r.setHeight(pixmap.height());
  painter->drawPixmap(r, pixmap, QRectF(0, 0, pixmap.width(),
                                        pixmap.height()));
}

QSize
ImageDelegate::sizeHint(const QStyleOptionViewItem & /*option*/,
                        const QModelIndex &index) const {
  QSize size = index.data(Qt::SizeHintRole).toSize();
  size += QSize(10, 10);
  return size;
}
