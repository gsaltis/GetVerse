/*****************************************************************************
 * FILE NAME    : StrongsReferenceToolBar.h
 * DATE         : December 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferencetoolbar_h_
#define _strongsreferencetoolbar_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QAction>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_TOOL_BAR_HEIGHT 24
/*****************************************************************************!
 * Exported Class : StrongsReferenceToolBar
 *****************************************************************************/
class StrongsReferenceToolBar : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceToolBar       ();

 //! Destructor
 public :
  ~StrongsReferenceToolBar      ();

 //! Public Methods
 public :
  QString                       GetStrongsReference     (void);
  void                          SetStrongsReference     (QString InStrongsReference);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          CreateConnections       ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QPushButton*                  Close;
  QString                       StrongsReference;
  QLabel*                       StrongsReferenceLabel;

 //! Public Slots
 public slots :
  void                          SlotClosePushed         (void);

 //! Public Signals
 signals :
  void                          SignalClose             (void);

 //! Public Actions
 public :
  QAction*                      ActionClosePushed;

};

#endif /* _strongsreferencetoolbar_h_*/
