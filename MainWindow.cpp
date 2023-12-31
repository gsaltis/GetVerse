/*****************************************************************************
 * FILE NAME    : MainWindow.cpp
 * DATE         : September 10 2023
 * PROJECT      : GetVerse
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMenuBar>
#include <QStatusBar>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainWindow.h"
#include "Common.h"

/*****************************************************************************!
 * Function : MainWindow
 *****************************************************************************/
MainWindow::MainWindow
() : QMainWindow()
{
}

/*****************************************************************************!
 * Function : MainWindow
 *****************************************************************************/
MainWindow::MainWindow
(QWidget* parent) : QMainWindow(parent)
{
  Initialize();
  CreateActions();
  CreateMenus();
  InitializeSubWindows();
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : MainWindow
 *****************************************************************************/
MainWindow::MainWindow
(QString InBookName)
{
  BookName = InBookName;
  Initialize();
  CreateActions();
  CreateMenus();
  InitializeSubWindows();
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : ~MainWindow
 *****************************************************************************/
MainWindow::~MainWindow
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
MainWindow::Initialize()
{
  setWindowTitle(SystemConfig::SystemName);
  setWindowIcon(QIcon(":/Images/Book.png")); 
}

/*****************************************************************************!
 * Function : CreateSubWindows
 * Purpose  : Create Sub Windows
 *****************************************************************************/
void
MainWindow::CreateSubWindows()
{
  displayWindow = new MainDisplayWindow(BookName);
  displayWindow->setParent(this);
  statusbar = statusBar();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 * Purpose  : Create Sub Windows
 *****************************************************************************/
void
MainWindow::InitializeSubWindows()
{
  displayWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 * Purpose  : Handle Resize Event
 *****************************************************************************/
void
MainWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   width;
  int                                   height;
  QSize                                 size;
  QSize                                 statusbar_size;
  QSize                                 menu_size;
  size = InEvent->size();  
  menu_size = menubar->size();
  statusbar_size = statusbar->size();
  width = size.width();
  height = size.height() - (menu_size.height() + statusbar_size.height());
  if ( displayWindow ) {
    displayWindow->move(0, menu_size.height());
    displayWindow->resize(width, height);
  }
}

/*****************************************************************************!
 * Function : CreateActions
 * Purpose  : Create New Actions
 *****************************************************************************/
void
MainWindow::CreateActions()
{
  ActionExit = new QAction("E&xit", this);
  connect(ActionExit, SIGNAL(triggered()), this, SLOT(SlotExit()));
  ActionClearBookMarks = new QAction("&Clear BookMarks", this);
  connect(ActionClearBookMarks, SIGNAL(triggered()), this, SLOT(SlotClearBookMarks()));
}

/*****************************************************************************!
 * Function : CreateMenus
 * Purpose  : Create New Menus
 *****************************************************************************/
void
MainWindow::CreateMenus()
{
  menubar = menuBar();  
  fileMenu = menubar->addMenu("&File");
  fileMenu->addAction(ActionExit);
  settingsMenu = menubar->addMenu("&Settings");
  settingsMenu->addAction(ActionClearBookMarks);
}

/*****************************************************************************!
 * Function : SlotExit
 *****************************************************************************/
void
MainWindow::SlotExit(void)
{
  exit(EXIT_SUCCESS);  
}

/*****************************************************************************!
 * Function : SlotClearBookMarks
 *****************************************************************************/
void
MainWindow::SlotClearBookMarks(void)
{
  MainBookMarks->Clear();
  emit SignalClearBookMarks();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
MainWindow::CreateConnections
()
{
  connect(this,
          MainWindow::SignalClearBookMarks,
          displayWindow,
          MainDisplayWindow::SlotClearBookMarks);
}

/*****************************************************************************!
 * Function : SetViewMode
 *****************************************************************************/
void
MainWindow::SetViewMode
(QString InMode)
{
  if ( NULL == displayWindow ) {
    return;
  }
  displayWindow->SetViewMode(InMode);
}
