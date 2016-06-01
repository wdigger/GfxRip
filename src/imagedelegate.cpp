#include "imagedelegate.h"

#include <QPainter>

ImageDelegate::ImageDelegate() {
}

void
ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  QPixmap pixmap = index.data(Qt::DecorationRole).value<QPixmap>();
  painter->drawPixmap(option.rect, pixmap, QRectF(0, 0, pixmap.width(), pixmap.height()));
}

QSize
ImageDelegate::sizeHint(const QStyleOptionViewItem & /*option*/, const QModelIndex &index) const {
  QSize size = index.data(Qt::SizeHintRole).toSize();
  return size;
}
