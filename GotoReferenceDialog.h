/*****************************************************************************
 * FILE NAME    : GotoReferenceDialog.h
 * DATE         : February 06 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _gotoreferencedialog_h_
#define _gotoreferencedialog_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QPushButton>
#include <QComboBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define GOTO_REFERENCE_DIALOG_WIDTH             295
#define GOTO_REFERENCE_DIALOG_HEIGHT            30

/*****************************************************************************!
 * Exported Class : GotoReferenceDialog
 *****************************************************************************/
class GotoReferenceDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  GotoReferenceDialog           (BookInfo* InBook, int InChapter);

 //! Destructor
 public :
  ~GotoReferenceDialog          ();

 //! Public Methods
 public :
  BookInfo*                     GetBook                 (void);
  int                           GetChapter              (void);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);
  void                          CreateConnections       (void);
  void                          CreateSubWindows        (void);
  void                          PopulateBookCombo       (void);

 //! Private Data
 private :
  QPushButton*                  OKButton;
  QPushButton*                  CancelButton;
  QComboBox*                    BookComboBox;
  QComboBox*                    ChapterComboBox;
  BookInfo*                     book;
  int                           chapter;

 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();
  void                          SlotCancelButtonPressed ();
  void                          SlotBookComboIndexChanged (int InIndex);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _gotoreferencedialog_h_*/
