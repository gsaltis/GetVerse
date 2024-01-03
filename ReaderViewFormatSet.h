/*****************************************************************************
 * FILE NAME    : ReaderViewFormatSet.h
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _readerviewformatset_h_
#define _readerviewformatset_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <sqlite3.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "ReaderViewFormat.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : ReaderViewFormatSet
 *****************************************************************************/
class ReaderViewFormatSet : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  ReaderViewFormatSet           ();

 //! Destructor
 public :
  ~ReaderViewFormatSet          ();

 //! Public Methods
 public :
  ReaderViewFormat*             FindFormat              (int InBook, int InChapter, int InVerse, int InWordIndex);
  void                          ReadDB                  (sqlite3* InDatabase);
  static int                    ReadDBCB                (void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);
  void                          AddFormat               (ReaderViewFormat* InFormat);
  int                           GetFormatCount          (void);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  QList<ReaderViewFormat*>      Formats;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _readerviewformatset_h_*/
