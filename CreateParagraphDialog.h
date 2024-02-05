/*****************************************************************************
 * FILE NAME    : CreateParagraphDialog.h
 * DATE         : February 04 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _createparagraphdialog_h_
#define _createparagraphdialog_h_

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
#include "WindowHeader.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define CREATE_PARAGRAPH_DIALOG_WIDTH           220
#define CREATE_PARAGRAPH_DIALOG_HEIGHT          200

/*****************************************************************************!
 * Exported Class : CreateParagraphDialog
 *****************************************************************************/
class CreateParagraphDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  CreateParagraphDialog         ();

 //! Destructor
 public :
  ~CreateParagraphDialog        ();

 //! Public Methods
 public :
  int                           GetLeftIndent           ();
  int                           GetRightIndent          ();
  int                           GetTopIndent            ();
  int                           GetBottomIndent         ();

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
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QPushButton*                  OKButton;
  QPushButton*                  CancelButton;
  QComboBox*                    LeftIndentCombo;
  QComboBox*                    RightIndentCombo;
  QComboBox*                    TopIndentCombo;
  QComboBox*                    BottomIndentCombo;
  WindowHeader*                 header;
  
 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();
  void                          SlotCancelButtonPressed ();

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _createparagraphdialog_h_*/
