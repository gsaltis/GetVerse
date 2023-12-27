/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearReferenceItem.h
 * DATE         : December 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayinterlinearreferenceitem_h_
#define _textdisplayinterlinearreferenceitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_INTERLINEAR_REFERENCE_ITEM_WIDTH 40
#define TEXT_DISPLAY_INTERLINEAR_REFERENCE_ITEM_HEIGHT 15

/*****************************************************************************!
 * Exported Class : TextDisplayInterlinearReferenceItem
 *****************************************************************************/
class TextDisplayInterlinearReferenceItem : public QLabel
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayInterlinearReferenceItem (int InVerseNumber, int InX, int intY, QWidget* InParent, int InRightToLeft);

 //! Destructor
 public :
  ~TextDisplayInterlinearReferenceItem ();

 //! Public Methods
 public :
  int                           GetVerseNumber          ();

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateConnections       ();
  void                          mousePressEvent         (QMouseEvent* InEvent);

 //! Private Data
 private :
  QFont                         DisplayFont;
  QColor                        DisplayColor;
  int                           VerseNumber;
  int                           RightToLeft;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :
  void                          SignalSelected          (int InVerseNumber);

 //! Public Actions
 public :

};

#endif /* _textdisplayinterlinearreferenceitem_h_*/
