/*****************************************************************************
 * FILE NAME    : TextDisplayViewWindowItem.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayviewwindowitem_h_
#define _textdisplayviewwindowitem_h_

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
#define TEXT_DISPLAY_VIEW_WINDOW_ITEM_X 200
#define TEXT_DISPLAY_VIEW_WINDOW_ITEM_Y 200
#define TEXT_DISPLAY_VIEW_WINDOW_ITEM_WIDTH 200
#define TEXT_DISPLAY_VIEW_WINDOW_ITEM_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayViewWindowItem
 *****************************************************************************/
class TextDisplayViewWindowItem : public QLabel
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayViewWindowItem     (QString InText, int InX, int InY, QSize InSize);

 //! Destructor
 public :
  ~TextDisplayViewWindowItem    ();

 //! Public Data
 public :
  enum LinePosition {
    LinePositionNone,
    LinePositionEOL,
    LinePositionBOL
  };
  
 //! Public Methods
 public :
  LinePosition                  GetLinePosition         ();
  void                          SetLinePosition         (LinePosition InPosition);
  
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
  void                          enterEvent              (QEnterEvent* InEvent);
  void                          leaveEvent              (QEvent* InEvent);
  void                          mousePressEvent         (QMouseEvent* InEvent);

 //! Private Data
 private :
  QColor                        textColor;
  QColor                        selectedColor;
  QColor                        selectedBackgroundColor;
  QColor                        textBackgroundColor;
  LinePosition                  linePosition;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayviewwindowitem_h_*/

