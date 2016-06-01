#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QAbstractItemDelegate>

class ImageDelegate : public QAbstractItemDelegate {
 public:
  ImageDelegate();

  virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  virtual QSize	sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // IMAGEDELEGATE_H
