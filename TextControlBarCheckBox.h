/*****************************************************************************
 * FILE NAME    : TextControlBarCheckBox.h
 * DATE         : November 27 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textcontrolbarcheckbox_h_
#define _textcontrolbarcheckbox_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QFrame>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_CONTROL_BAR_CHECK_BOX_X    200
#define TEXT_CONTROL_BAR_CHECK_BOX_Y    200
#define TEXT_CONTROL_BAR_CHECK_BOX_WIDTH 200
#define TEXT_CONTROL_BAR_CHECK_BOX_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextControlBarCheckBox
 *****************************************************************************/
class TextControlBarCheckBox : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  TextControlBarCheckBox        (QWidget* InParent, bool InChecked = false);

 //! Destructor
 public :
  ~TextControlBarCheckBox       ();

 //! Public Methods
 public :
  void                          SetChecked              (bool InChecked);
  void                          CheckChanged            (bool InChecked);

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          paintEvent              (QPaintEvent* InEvent);
  void                          mousePressEvent         (QMouseEvent* InEvent);

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          ToggleCheck             ();
  
 //! Private Data
 private :
  QColor                        CheckedColor;
  bool                          Checked;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :
  void                          SignalChecked           (bool InChecked);
  
 //! Public Actions
 public :

};

#endif /* _textcontrolbarcheckbox_h_*/
