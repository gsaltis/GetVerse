/*****************************************************************************
 * FILE NAME    : TextDisplayReaderToolBar.h
 * DATE         : February 03 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayreadertoolbar_h_
#define _textdisplayreadertoolbar_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QAction>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_READER_TOOL_BAR_X  200
#define TEXT_DISPLAY_READER_TOOL_BAR_Y  200
#define TEXT_DISPLAY_READER_TOOL_BAR_WIDTH 25
#define TEXT_DISPLAY_READER_TOOL_BAR_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayReaderToolBar
 *****************************************************************************/
class TextDisplayReaderToolBar : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayReaderToolBar      (QWidget* InParent);

 //! Destructor
 public :
  ~TextDisplayReaderToolBar     ();

 //! Public Methods
 public :
  QColor                        GetTextColor            (void);
  void                          SetTextColor            (QColor InTextColor);
  QColor                        GetTextBackgroundColor  (void);
  void                          SetTextBackgroundColor  (QColor InTextBackgroundColor);
  QFont                         GetTextFont             (void);
  void                          SetTextFont             (QFont InTextFont);

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
  QPushButton*                  FontButton;
  QPushButton*                  ParagraphButton;
  QPushButton*                  TextColorButton;
  QPushButton*                  TextBackgroundColorButton;
  QPushButton*                  ExtraButton;
  
  QColor                        TextColor;
  QColor                        TextBackgroundColor;
  QFont                         TextFont;

 //! Public Slots
 public slots :
  void                          SlotFontPushed                  (void);
  void                          SlotParagraphPushed             (void);
  void                          SlotTextColorPushed             (void);
  void                          SlotTextBackgroundColorPushed   (void);
  void                          SlotExtraPushed         (void);

 //! Public Signals
 signals :
  void                          SignalGetTextColor              (void);
  void                          SignalParagraphSet              (int InLeftIndent, int InRightIndent,
                                                                 int InTopIndent, int InBottomIndent);
  void                          SignalTextColorSet              (QColor InTextColor);
  void                          SignalTextBackgroundColorSet    (QColor InTextBackgroundColor);
  void                          SignalTextFontSet               (QFont InTextFont);
  void                          SignalExtraPushed       (void);
  
 //! Public Actions
 public :
  QAction*                      ActionFontPushed;
  QAction*                      ActionParagraphPushed;
  QAction*                      ActionTextColorPushed;
  QAction*                      ActionTextBackgroundColorPushed;

};

#endif /* _textdisplayreadertoolbar_h_*/
