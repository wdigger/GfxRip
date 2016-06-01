#include "rippermodel.h"

#include <QModelIndex>
#include <QImage>
#include <QPixmap>

#include "gfxrip.h"

RipperModel::RipperModel(gr_ripper_t *ripper, QObject *parent) : QAbstractItemModel(parent) {
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

  switch(role) {
    case Qt::DisplayRole:
      result = QString::number(index.row());
      break;
    case Qt::DecorationRole: {
      gr_bitmap_t *img = ripper->get_image(index.row());
      QImage image(img->get_data(), img->get_width(), img->get_height(), QImage::Format_ARGB32);
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
