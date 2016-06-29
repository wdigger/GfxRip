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
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>

Inspector::Inspector(gr_ripper_t *ripper, QWidget *parent) : QWidget(parent) {
  set_ripper(ripper);

  QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
  setLayout(mainLayout);

  QGroupBox *groupBox = new QGroupBox("Global:", this);
  mainLayout->addWidget(groupBox);
  QFormLayout *formLayout = new QFormLayout(groupBox);
  formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  groupBox->setLayout(formLayout);
  labelSize = new QLabel(groupBox);
  labelSize->setAlignment(Qt::AlignRight);
  formLayout->addRow(new QLabel("Size:", this), labelSize);
  labelFrames = new QLabel(groupBox);
  labelFrames->setAlignment(Qt::AlignRight);
  formLayout->addRow(new QLabel("Frames:", this), labelFrames);
  spinOffset = new QSpinBox(groupBox);
  spinOffset->setAlignment(Qt::AlignRight);
  formLayout->addRow(new QLabel("Offset:", this), spinOffset);

  groupBox = new QGroupBox("Frame size:", this);
  mainLayout->addWidget(groupBox);
  formLayout = new QFormLayout(groupBox);
  formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  groupBox->setLayout(formLayout);
  spinWidth = new QSpinBox(groupBox);
  spinWidth->setMinimum(8);
  spinWidth->setMaximum(0x0FFFFFFF);
  spinWidth->setSingleStep(8);
  spinWidth->setAlignment(Qt::AlignRight);
  spinHeight = new QSpinBox(groupBox);
  spinHeight->setMinimum(1);
  spinHeight->setMaximum(0x0FFFFFFF);
  spinHeight->setAlignment(Qt::AlignRight);
  formLayout->addRow(new QLabel("Width:", this), spinWidth);
  formLayout->addRow(new QLabel("Height:", this), spinHeight);

  groupBox = new QGroupBox("Mode:", this);
  mainLayout->addWidget(groupBox);
  QVBoxLayout *groupLayout = new QVBoxLayout(groupBox);
  groupBox->setLayout(groupLayout);
  modeGroup = new QButtonGroup(groupBox);
  QRadioButton *button = new QRadioButton("AM", groupBox);
  modeGroup->addButton(button, gr_ripper_t::mode_am);
  groupLayout->addWidget(button);
  button = new QRadioButton("ST", groupBox);
  modeGroup->addButton(button, gr_ripper_t::mode_st);
  groupLayout->addWidget(button);
  button = new QRadioButton("SP", groupBox);
  modeGroup->addButton(button, gr_ripper_t::mode_sp);
  groupLayout->addWidget(button);
  button = new QRadioButton("C+", groupBox);
  modeGroup->addButton(button, gr_ripper_t::mode_cp);
  groupLayout->addWidget(button);
  button = new QRadioButton("C-", groupBox);
  modeGroup->addButton(button, gr_ripper_t::mode_cm);
  groupLayout->addWidget(button);
  modeGroup->button(gr_ripper_t::mode_am)->setChecked(true);
  connect(modeGroup, SIGNAL(buttonClicked(int)),
          this, SLOT(on_mode_changed(int)));

  groupBox = new QGroupBox("Bitplains:", this);
  mainLayout->addWidget(groupBox);
  groupLayout = new QVBoxLayout(groupBox);
  groupBox->setLayout(groupLayout);
  formLayout = new QFormLayout(groupBox);
  formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  groupLayout->addLayout(formLayout);
  spinBits = new QSpinBox(groupBox);
  formLayout->addRow(new QLabel("Bits:", groupBox), spinBits);
  labelColors = new QLabel(groupBox);
  formLayout->addRow(new QLabel("Colors:", groupBox), labelColors);
  groupLayout->addWidget(new QLabel("Skip bits:", groupBox));
  QHBoxLayout *bitsSkipLayout = new QHBoxLayout(groupBox);
  groupLayout->addLayout(bitsSkipLayout);
  groupLayout->addWidget(new QLabel("Fill bits:", groupBox));
  QHBoxLayout *bitsFillLayout = new QHBoxLayout(groupBox);
  groupLayout->addLayout(bitsFillLayout);
  for (size_t i = 0; i < 8; i++) {
    QCheckBox *checkBox = new QCheckBox(groupBox);
    bitsSkipLayout->addWidget(checkBox);
    bitsSkip.push_back(checkBox);
    checkBox = new QCheckBox(groupBox);
    bitsFillLayout->addWidget(checkBox);
    bitsFill.push_back(checkBox);
  }
  bitsSkipLayout->addStretch();
  bitsFillLayout->addStretch();

  mainLayout->addStretch();

  image_updated();

  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void
Inspector::image_updated() {
  labelSize->setText(QString::number(ripper->get_size()));
  labelFrames->setText(QString::number(ripper->get_image_count()));
  spinOffset->setValue(ripper->get_offset());
  spinOffset->setMinimum(0);
  spinOffset->setMaximum(ripper->get_size() - 1);
  spinWidth->setValue(ripper->get_width() * 8);
  spinHeight->setValue(ripper->get_height());

  size_t bits = ripper->get_bits();
  for (size_t i = 0; i < 8; i++) {
    bool visible = (i < bits);
    bitsSkip[i]->setVisible(visible);
    bitsFill[i]->setVisible(visible);
  }
}

void
Inspector::on_mode_changed(int mode) {
  ripper->set_mode((gr_ripper_t::mode_t)mode);
}
