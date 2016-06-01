#include "inspector.h"

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
