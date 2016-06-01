#include "mainwindow.h"
#include "rippermodel.h"
#include "imagedelegate.h"
#include "inspector.h"

#include <QLabel>
#include <QFileDialog>
#include <QBitmap>
#include <QTableView>
#include <QAction>
#include <QStatusBar>
#include <QToolBar>
#include <QDockWidget>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  statusBar = new QStatusBar(this);
  setStatusBar(statusBar);
  statusBar->setSizeGripEnabled(true);
  labelStatus = new QLabel(this);
  statusBar->addWidget(labelStatus);

  toolBar = new QToolBar(this);
  addToolBar(toolBar);

  tableView = new QTableView(this);
  tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  tableView->setBackgroundRole(QPalette::Base);

  setCentralWidget(tableView);

  ripper = new gr_ripper_t();

  RipperModel *model = new RipperModel(ripper);
  tableView->setModel(model);
  tableView->setItemDelegate(new ImageDelegate());

  QString file_path = QFileDialog::getOpenFileName(this, "Input file");
  if (!file_path.isEmpty()) {
    QFile file(file_path);
    if (file.open(QIODevice::ReadOnly)) {
      data = file.readAll();
      if (data.size() > 0) {
        ripper->set_source(data.data(), data.size());
      }
    }
  }

  connect(model, SIGNAL(modelReset()), SLOT(dataChanged()));

  dataChanged();

  addRipperAction("Q", ":/res/width_increase.svg", SLOT(widthIncrease()));
  addRipperAction("A", ":/res/width_decrease.svg", SLOT(widthDecrease()));

  addRipperAction("W", ":/res/height_increase.svg", SLOT(heightIncrease()));
  addRipperAction("S", ":/res/height_decrease.svg", SLOT(heightDecrease()));

  addRipperAction("Shift+W", ":/res/height_increase8.svg", SLOT(heightIncrease8()));
  addRipperAction("Shift+S", ":/res/height_decrease8.svg", SLOT(heightDecrease8()));

  addRipperAction("E", ":/res/width_increase.svg", SLOT(bitsIncrease()));
  addRipperAction("D", ":/res/width_increase.svg", SLOT(bitsDecrease()));

  QDockWidget *propsDock = new QDockWidget(this);
  addDockWidget(Qt::RightDockWidgetArea, propsDock);

  inspector = new Inspector(ripper, this);
  propsDock->setWidget(inspector);

  QMenu *menuView = menuBar()->addMenu("View");
  QAction *actionProperties = menuView->addAction("Properties");
  actionProperties->setCheckable(true);
  actionProperties->setChecked(!propsDock->isHidden());
  connect(propsDock, SIGNAL(visibilityChanged(bool)), actionProperties, SLOT(setChecked(bool)));
  connect(actionProperties, SIGNAL(toggled(bool)), propsDock, SLOT(setVisible(bool)));
}

MainWindow::~MainWindow() {
}

void
MainWindow::addRipperAction(const QString &key, const QString &icon_path, const char *method) {
  QAction *action = toolBar->addAction(QIcon(icon_path), key, this, method);
  action->setShortcut(QKeySequence(key));
}

void
MainWindow::dataChanged() {
  tableView->resizeColumnsToContents();
  tableView->resizeRowsToContents();
  char *status = ripper->get_status();
  labelStatus->setText(status);
  free(status);
}

void
MainWindow::widthIncrease() {
  size_t width = ripper->get_width();
  ripper->set_width(++width);
}

void
MainWindow::widthDecrease() {
  size_t width = ripper->get_width();
  ripper->set_width(--width);
}

void
MainWindow::heightIncrease() {
  size_t height = ripper->get_height();
  ripper->set_height(++height);
}

void
MainWindow::heightDecrease() {
  size_t height = ripper->get_height();
  ripper->set_height(--height);
}

void
MainWindow::heightIncrease8() {
  size_t height = ripper->get_height();
  ripper->set_height(height + 8);
}

void
MainWindow::heightDecrease8() {
  size_t height = ripper->get_height();
  ripper->set_height(height - 8);
}

void
MainWindow::bitsIncrease() {
  size_t bits = ripper->get_bits();
  ripper->set_bits(++bits);
}

void
MainWindow::bitsDecrease() {
  size_t bits = ripper->get_bits();
  ripper->set_bits(--bits);
}
