#ifndef RIPPERMODEL_H
#define RIPPERMODEL_H

#include <QAbstractItemModel>

#include "gfxrip.h"

class RipperModel : public QAbstractItemModel, public gr_ripper_client {
 public:
  RipperModel(gr_ripper_t *ripper, QObject *parent = NULL);

  virtual int	columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  virtual QModelIndex	index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
  virtual QModelIndex	parent(const QModelIndex &index) const;
  virtual int	rowCount(const QModelIndex &parent = QModelIndex()) const;

  virtual void image_updated();
};

#endif // RIPPERMODEL_H
