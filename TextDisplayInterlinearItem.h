/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearItem.h
 * DATE         : September 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayinterlinearitem_h_
#define _textdisplayinterlinearitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayItem.h"
#include "TextDisplayWordFormattingItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TextDisplayInterlinearItem
 *****************************************************************************/
class TextDisplayInterlinearItem : public QLabel
{
  //! Constructors
public :
  TextDisplayInterlinearItem          (int InBook, int InChapter, int InVerse, QString InWord, int InWordIndex, QFont InFont);

  //! Destructor
public :
  ~TextDisplayInterlinearItem         ();

  //! Public Methods
public :
  int                           GetWordIndex            (void);
  void                          SetWordIndex            (int InWordIndex);
  void                          SetFont                 (QFont InFont);
  bool                          Contains                (QPoint InPaint);
  QString                       GetText                 (void);
  bool                          IsReference             (const int InBook, const int InChapter, const int InVerse, const int InWord);
  QString                       GetWord                 (void);
  void                          SetWord                 (QString InWord);
  QSize                         GetSize                 ();
  int                           GetVerseNumber          (void);

  //! Public Data
public :

  //! Protected Methods
protected :
  void                          enterEvent              (QEnterEvent* InEvent);
  void                          leaveEvent              (QEvent* InEvent);
  
  //! Protected Data
protected :

  //! Private Methods
private :
  void                          CreateStrippedWord      ();
  
  //! Private Data
private :
  bool                          StripQuotes;
  int                           WordIndex;
  QString                       Word;
  QString                       StrippedWord;
  int                           Book;
  int                           Chapter;
  int                           Verse;
  QString                       Text;
  QSize                         Size;
  QPoint                        Location;
  QFont                         Font;
  QColor                        Background;
  QColor                        Foreground;
  QColor                        OverBackground;

};

#endif /* _textdisplayinterlinearitem_h_*/
