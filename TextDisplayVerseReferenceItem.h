/*****************************************************************************
 * FILE NAME    : TextDisplayVerseReferenceItem.h
 * DATE         : December 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayversereferenceitem_h_
#define _textdisplayversereferenceitem_h_

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
#define TEXT_DISPLAY_VERSE_REFERENCE_ITEM_WIDTH 40
#define TEXT_DISPLAY_VERSE_REFERENCE_ITEM_HEIGHT 15

/*****************************************************************************!
 * Exported Class : TextDisplayVerseReferenceItem
 *****************************************************************************/
class TextDisplayVerseReferenceItem : public QLabel
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayVerseReferenceItem (int InVerseNumber, int InX, int intY, QWidget* InParent);

 //! Destructor
 public :
  ~TextDisplayVerseReferenceItem ();

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
  void                          CreateConnections       ();
  void                          mousePressEvent         (QMouseEvent* InEvent);

 //! Private Data
 private :
  QFont                         DisplayFont;
  QColor                        DisplayColor;
  int                           VerseNumber;
 
 //! Public Slots
 public slots :

 //! Public Signals
 signals :
  void                          SignalSelected          (int InVerseNumber);

 //! Public Actions
 public :

};

#endif /* _textdisplayversereferenceitem_h_*/
