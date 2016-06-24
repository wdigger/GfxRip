/*
 * inspector.h - GxfRip
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

#ifndef SRC_INSPECTOR_H_
#define SRC_INSPECTOR_H_

#include <QWidget>
#include <QVector>

#include "src/gfxrip.h"

class QSpinBox;
class QLabel;
class QCheckBox;

class Inspector : public QWidget, public gr_ripper_client {
  Q_OBJECT

 protected:
  QLabel *labelSize;
  QLabel *labelFrames;
  QSpinBox *spinOffset;

  QSpinBox *spinWidth;
  QSpinBox *spinHeight;

  QSpinBox *spinBits;
  QLabel *labelColors;
  QVector<QCheckBox*> bitsSkip;
  QVector<QCheckBox*> bitsFill;

 public:
  explicit Inspector(gr_ripper_t *ripper, QWidget *parent = NULL);

  virtual void image_updated();

 signals:

 public slots:
};

#endif  // SRC_INSPECTOR_H_
