/*****************************************************************************
 * FILE NAME    : ReaderViewFormat.h
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _readerviewformat_h_
#define _readerviewformat_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define ReaderViewFormatParagraph       1
#define ReaderViewFormatTitle           2
#define ReaderViewFormatLineBreak       3

/*****************************************************************************!
 * Exported Class : ReaderViewFormat
 *****************************************************************************/
class ReaderViewFormat : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  ReaderViewFormat              ();
  ReaderViewFormat              (BookInfo* InBook, int InChatper, int InVerse, int InWordIndex);
  
 //! Destructor
 public :
  ~ReaderViewFormat             ();

 //! Public Methods
 public :
  BookInfo*                     GetBook                 (void);
  void                          SetBook                 (BookInfo* InBook);
  int                           GetChapter              (void);
  void                          SetChapter              (int InChapter);
  int                           GetVerse                (void);
  void                          SetVerse                (int InVerse);
  int                           GetWordIndex            (void);
  void                          SetWordIndex            (int InWordIndex);
  QColor                        GetColor                (void);
  void                          SetColor                (QColor InColor);
  QString                       GetTitle                (void);
  void                          SetTitle                (QString InTitle);
  int                           GetBookIndex            (void);
  bool                          IsEqual                 (int InBook, int InChapter, int InVerse, int InWordIndex);
  int                           Compare                 (int InBook, int InChapter, int InVerse, int InWordIndex);
  int                           GetFormat               (void);
  void                          SetFormat               (int InFormat);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);

 //! Private Data
 private :
  BookInfo*                     Book;
  int                           Chapter;
  int                           Verse;
  int                           WordIndex;
  QColor                        Color;
  QString                       Title;
  int                           Format;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _readerviewformat_h_*/
