/*
slowmoUI is a user interface for slowmoVideo.
Copyright (C) 2011  Simon A. Eugster (Granjow)  <simon.eu@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QShortcut>
#include <QSignalMapper>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up shortcut bindings
    m_keyList.insert(MainWindow::Add, "a");
    m_keyList.insert(MainWindow::Add_Clip, "a");
    m_keyList.insert(MainWindow::Add_Color, "c");
    m_keyList.insert(MainWindow::Add_Text, "t");
    m_keyList.insert(MainWindow::Quit, "q");
    m_keyList.insert(MainWindow::Quit_Quit, "q");
    m_keyList.insert(MainWindow::Help, "h");
    m_keyList.insert(MainWindow::Help_Help, "h");

    QList<QString> uniqueKeys;
    QList<QString> keys = m_keyList.values();
    for (int i = 0; i < keys.size(); i++) {
        if (!uniqueKeys.contains(keys[i])) {
            uniqueKeys.append(keys[i]);
            qDebug() << "Added to key list: " << keys[i];
        }
    }


    bool b = true;

    m_signalMapper = new QSignalMapper(this);
    for (int i = 0; i < uniqueKeys.length(); i++) {

        // Create a new shortcut for each unique key
        QShortcut *shortcut = new QShortcut(QKeySequence(uniqueKeys[i]), this);

        m_shortcutList.append(shortcut);
        m_signalMapper->setMapping(shortcut, uniqueKeys[i]);

        // Connect shortcut to the signal mapper
        b &= connect(shortcut, SIGNAL(activated()), m_signalMapper, SLOT(map()));
    }

    b &= connect(m_signalMapper, SIGNAL(mapped(QString)), this, SLOT(shortcutUsed(QString)));

    Q_ASSERT(b);

}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_signalMapper;
    for (int i = 0; i < m_shortcutList.length(); i++) {
        delete m_shortcutList[i];
    }
}


void MainWindow::shortcutUsed(QString which)
{
    TimedShortcut ts;
    ts.shortcut = which;
    ts.start = QTime::currentTime();

    qDebug() << which << " pressed. Last shortcut: " << m_lastShortcut.start.elapsed();

//    QString at = QString(" @ %1.%2::%3")
//            .arg(ts.start.minute())
//            .arg(ts.start.second())
//            .arg(ts.start.msec());

    // Use a timeout. Otherwise pressing a key may lead to unpredictable results
    // since it may depend on the key you pressed several minutes ago.
    if (m_lastShortcut.start.elapsed() < 600) {

        // Handle combined shortcuts here.

        if (m_lastShortcut.shortcut == m_keyList[MainWindow::Quit]) {
            if (which == m_keyList[MainWindow::Quit_Quit]) {
                qApp->quit();
            }
        }

    } else {
        qDebug() << "(Shortcut timed out.)";
    }

    m_lastShortcut = ts;
}
