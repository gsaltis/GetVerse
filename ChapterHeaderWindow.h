/*****************************************************************************
 * FILE NAME    : ChapterHeaderWindow.h
 * DATE         : November 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _chapterheaderwindow_h_
#define _chapterheaderwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CHAPTER_HEADER_WINDOW_HEIGHT    20

/*****************************************************************************!
 * Exported Class : ChapterHeaderWindow
 *****************************************************************************/
class ChapterHeaderWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  ChapterHeaderWindow           (QString InText, QWidget* InParent); 

 //! Destructor
 public :
  ~ChapterHeaderWindow          ();

 //! Public Methods
 public :
  void                          SetText                 (QString InText);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          paintEvent              (QPaintEvent* InEvent);
  
 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();

 //! Private Data
 private :
  QString                       text;
  QString                       fontName;
  bool                          fontBold;
  QString                       fontColorName;
  QString                       backgroundColorName;
  
 //! Public Slots
 public slots :
  void                          SlotTextChanged         (QString InText);
  
 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _chapterheaderwindow_h_*/
