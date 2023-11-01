/*****************************************************************************
 * FILE NAME    : InterlinearDisplayElementSelectDialog.h
 * DATE         : October 30 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _interlineardisplayelementselectdialog_h_
#define _interlineardisplayelementselectdialog_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QPushButton>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define INTERLINEAR_DISPLAY_ELEMENT_SELECT_DIALOG_WIDTH 300
#define INTERLINEAR_DISPLAY_ELEMENT_SELECT_DIALOG_HEIGHT 400

/*****************************************************************************!
 * Exported Class : InterlinearDisplayElementSelectDialog
 *****************************************************************************/
class InterlinearDisplayElementSelectDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  InterlinearDisplayElementSelectDialog ();

 //! Destructor
 public :
  ~InterlinearDisplayElementSelectDialog ();

 //! Public Methods
 public :

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

 //! Private Data
 private :
  QPushButton*                  OKButton;
  QPushButton*                  CancelButton;

 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();
  void                          SlotCancelButtonPressed ();

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _interlineardisplayelementselectdialog_h_*/
