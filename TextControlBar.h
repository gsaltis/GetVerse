/*****************************************************************************
 * FILE NAME    : TextControlBar.h
 * DATE         : September 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textcontrolbar_h_
#define _textcontrolbar_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
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
#define TEXT_CONTROL_BAR_X              200
#define TEXT_CONTROL_BAR_Y              200
#define TEXT_CONTROL_BAR_WIDTH          200
#define TEXT_CONTROL_BAR_HEIGHT         25

/*****************************************************************************!
 * Exported Class : TextControlBar
 *****************************************************************************/
class TextControlBar : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextControlBar                ();

 //! Destructor
 public :
  ~TextControlBar               ();

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
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  QPushButton*                  ReferenceButton;
  QPushButton*                  EditButton;
  QPushButton*                  AnalyzeButton;
  QPushButton*                  BlockViewButton;
  QLabel*                       WordLabel;
  QLabel*                       WordCountLabel;
  int                           InterWordSkip;
  int                           RightMargin;
  
 //! Public Slots
 public slots :
  void                          SlotReferenceButtonPushed (void);
  void                          SlotEditButtonPushed    (void);
  void                          SlotAnalyzeButtonPushed (void);
  void                          SlotBlockViewButtonPushed (void);
  void                          SlotWordCountChanged    (int);

 //! Public Signals
 signals :

 //! Public Actions
 public :
  QAction*                      ActionReferenceButtonPushed;
  QAction*                      ActionEditButtonPushed;
  QAction*                      ActionAnalyzeButtonPushed;
  QAction*                      ActionBlockViewButtonPushed;

};

#endif /* _textcontrolbar_h_*/
