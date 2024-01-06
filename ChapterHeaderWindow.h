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
  ChapterHeaderWindow           (QWidget* InParent); 

 //! Destructor
 public :
  ~ChapterHeaderWindow          ();

 //! Public Methods
 public :
  int                           GetChapter              (void);
  void                          SetChapter              (int InChapter);
  int                           GetTotalChapters        (void);
  void                          SetTotalChapters        (int InTotalChapters);
  
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
  void                          ResetText               (void);

 //! Private Data
 private :
  QString                       text;
  QString                       fontName;
  bool                          fontBold;
  QString                       fontColorName;
  QString                       backgroundColorName;
  int                           Chapter;
  int                           TotalChapters;

 //! Public Slots
 public slots :
  void                          SlotChapterSelected     (int InChapter);
  void                          SlotTotalChaptersChanged(int InTotalChapters);
  
 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _chapterheaderwindow_h_*/
