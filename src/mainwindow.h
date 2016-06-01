/*
 * mainwindow.h - GxfRip
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

#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

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
  explicit MainWindow(QWidget *parent = NULL);
  virtual ~MainWindow();

 protected:
  void addRipperAction(const QString &key, const QString &icon_path,
                       const char *method);

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

#endif  // SRC_MAINWINDOW_H_
