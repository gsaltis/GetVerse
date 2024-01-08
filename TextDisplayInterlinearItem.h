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
#include <QFrame>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayItem.h"
#include "TextDisplayWordFormattingItem.h"
#include "InterlinearWord.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TextDisplayInterlinearItem
 *****************************************************************************/
class TextDisplayInterlinearItem : public QFrame
{
  Q_OBJECT;
  
  //! Constructors
public :
  TextDisplayInterlinearItem          (InterlinearWord* InWord, int InWordIndex, QWidget* InParent, int InRightToLeft);

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
  void                          Reset                   (void);
  void                          ReComputeSize           (void);
  
  //! Public Data
public :
  static bool                   DisplayEnglish;
  static bool                   DisplayContextual;
  static bool                   DisplayStrongs;
  static bool                   DisplayMorphology;
  static bool                   DisplayTransliterate;
  
  //! Protected Methods
protected :
  void                          enterEvent              (QEnterEvent* InEvent);
  void                          leaveEvent              (QEvent* InEvent);
  void                          mousePressEvent         (QMouseEvent* InEvent);
  
  //! Protected Data
protected :

  //! Private Methods
private :
  void                          CreateEnglishLabel      (void);
  void                          CreateStrongsLabel      (void);
  void                          CreateContextualLabel   (void);
  void                          CreateTransliterateLabel(void);
  void                          CreateMorphologyLabel   (void);
  void                          ComputeSize             (void);
  void                          DisplayStrongsReference (void);
  void                          DisplayStrongCrossReference (void);
  
  //! Private Data
private :
  InterlinearWord*              Word;
  int                           WordIndex;
  QSize                         Size;
  QPoint                        Location;
  QColor                        Background;
  QColor                        OverBackground;
  
  QLabel*                       EnglishLabel;
  QSize                         EnglishSize;

  QLabel*                       ContextualLabel;
  QSize                         ContextualSize;
  
  QLabel*                       StrongsLabel;
  QSize                         StrongsSize;
  
  QLabel*                       MorphologyLabel;
  QSize                         MorphologySize;
  
  QLabel*                       TransliterateLabel;
  QSize                         TransliterateSize;
  
  int                           RightToLeft;

 //! Public Signals
 signals :
  void                          SignalSelectStrongsWord (QString InStrongsWord);
};

#endif /* _textdisplayinterlinearitem_h_*/
