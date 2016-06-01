#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class gr_ripper_t;
class QTableView;
class QStatusBar;
class QLabel;
class Inspector;

class MainWindow : public QMainWindow {
  Q_OBJECT

 protected:
  gr_ripper_t *ripper;
  QByteArray data;
  QTableView *tableView;
  QStatusBar *statusBar;
  QLabel *labelStatus;
  QToolBar *toolBar;
  Inspector *inspector;

 public:
  MainWindow(QWidget *parent = NULL);
  ~MainWindow();

 protected:
  void addRipperAction(const QString &key, const QString &icon_path, const char *method);

 public slots:
  void dataChanged();

  void widthIncrease();
  void widthDecrease();
  void heightIncrease();
  void heightDecrease();
  void heightIncrease8();
  void heightDecrease8();
  void bitsIncrease();
  void bitsDecrease();
};

#endif // MAINWINDOW_H
