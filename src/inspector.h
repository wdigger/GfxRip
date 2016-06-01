#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

#include "gfxrip.h"

class QSpinBox;

class Inspector : public QWidget, public gr_ripper_client {
  Q_OBJECT

 protected:
  QSpinBox *spinWidth;
  QSpinBox *spinHeight;

 public:
  explicit Inspector(gr_ripper_t *ripper, QWidget *parent = NULL);

  virtual void image_updated();

 signals:

 public slots:
};

#endif // INSPECTOR_H
