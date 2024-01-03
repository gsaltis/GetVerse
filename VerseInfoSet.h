/*****************************************************************************
 * FILE NAME    : VerseInfoSet.h
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _verseinfoset_h_
#define _verseinfoset_h_

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
#include "VerseInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : VerseInfoSet
 *****************************************************************************/
class VerseInfoSet : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  VerseInfoSet                  ();
  VerseInfoSet                  (int InBook);
  
 //! Destructor
 public :
  ~VerseInfoSet                 ();

 //! Public Methods
 public :
  void                          ReadDB                  (sqlite3* InDatabase);
  void                          AddVerse                (VerseInfo* InVerse);
  static int                    ReadDBCB                (void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);
  int                           GetVerseCount           (void);
  VerseInfo*                    GetVerseByIndex         (int InIndex);

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
  QList<VerseInfo*>             Verses;
  int                           Book;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _verseinfoset_h_*/
