// SPDX-FileCopyrightText: 2022 Javier O. Cordero Pérez
//
// SPDX-License-Identifier: AGPL-3.0-only

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SignVec sign;
    signs.append(sign);
}

MainWindow::~MainWindow()
{
    delete ui;
}

