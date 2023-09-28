/*****************************************************************************
 * FILE NAME    : SQLStatement.h
 * DATE         : September 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _sqlstatement_h_
#define _sqlstatement_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SQLStatement.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : SQLStatement
 *****************************************************************************/
class SQLStatement : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  SQLStatement                  ();

 //! Destructor
 public :
  ~SQLStatement                 ();

 //! Public Methods
 public :
  static QString                GetFormattingInsert             (void);
  static QString                GetWordFormattingDelete         (void);
  static QString                GetVerseFormattingDelete        (void);

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

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _sqlstatement_h_*/
