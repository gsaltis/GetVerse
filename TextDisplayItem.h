/*****************************************************************************
 * FILE NAME    : TextDisplayItem.h
 * DATE         : September 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayitem_h_
#define _textdisplayitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TextDisplayItem
 *****************************************************************************/
class TextDisplayItem
{
 //! Constructors
 public :
  TextDisplayItem               (int InBook, int InChapter, int InVerse,
                                 QString InText);

 //! Destructor
 public :
  ~TextDisplayItem              ();

 //! Public Types
  enum DisplayType {
    None                = 0,
    ReferenceType       = 1,
    TextType            = 2,
    FormattingType      = 3
  };
  enum ParagraphPosition {
    MidParagraph        = 0,
    StartOfParagraph,
    EndOfParagraph
  };
  
 //! Public Methods
 public :
  int                           GetBook                 (void);
  int                           GetChapter              (void);
  int                           GetVerse                (void);
  QString                       GetText                 (void);
  void                          SetText                 (QString InText);
  QSize                         GetSize                 (void);
  void                          SetSize                 (QSize InSize);
  QPoint                        GetLocation             (void);
  void                          SetLocation             (QPoint InLocation);
  void                          SetFont                 (QFont InFont);
  QColor                        GetBackground           (void);
  void                          SetBackground           (QColor InBackground);
  QColor                        GetForeground           (void);
  void                          SetForeground           (QColor InForeground);
  virtual void                  Draw                    (QPainter* InPainter);
  virtual void                  DrawSelected            (QPainter* InPainter);
  DisplayType                   GetType                 ();
  bool                          Contains                (QPoint InPaint);
  QRect                         GetBoundingRect         ();
  bool                          IsReference             (const int InBook, const int InChapter, const int InVerse);
  void                          SetParagraphPosition    (ParagraphPosition InPosition);
  ParagraphPosition             GetParagraphPosition    ();
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :
  int                           Book;
  int                           Chapter;
  int                           Verse;
  QString                       Text;
  QSize                         Size;
  QPoint                        Location;
  QFont                         Font;
  QColor                        Background;
  QColor                        Foreground;
  DisplayType                   Type;
  ParagraphPosition             position;
  
 //! Private Methods
 private :

 //! Private Data
 private :
};

#endif /* _textdisplayitem_h_*/
