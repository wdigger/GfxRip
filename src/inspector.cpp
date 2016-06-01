/*
 * inspector.cpp - GxfRip
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

#include "src/inspector.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QGroupBox>
#include <QSpinBox>

Inspector::Inspector(gr_ripper_t *ripper, QWidget *parent) : QWidget(parent) {
  set_ripper(ripper);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  setLayout(mainLayout);

  QGroupBox *groupBox = new QGroupBox("Frame size:", this);
  mainLayout->addWidget(groupBox);
  QFormLayout *formLayout = new QFormLayout(groupBox);
  groupBox->setLayout(formLayout);

  spinWidth = new QSpinBox(groupBox);
  spinWidth->setMinimum(8);
  spinWidth->setMaximum(0x0FFFFFFF);
  spinWidth->setSingleStep(8);
  spinHeight = new QSpinBox(groupBox);
  spinHeight->setMinimum(1);
  spinHeight->setMaximum(0x0FFFFFFF);
  formLayout->addRow(new QLabel("Width:", this), spinWidth);
  formLayout->addRow(new QLabel("Height:", this), spinHeight);

  mainLayout->addStretch();

  image_updated();
}

void
Inspector::image_updated() {
  spinWidth->setValue(ripper->get_width() * 8);
  spinHeight->setValue(ripper->get_height());
}
