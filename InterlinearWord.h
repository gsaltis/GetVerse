/*****************************************************************************
 * FILE NAME    : InterlinearWord.h
 * DATE         : October 15 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _interlinearword_h_
#define _interlinearword_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "InterlinearWordText.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : InterlinearWord
 *****************************************************************************/
class InterlinearWord
{
 //! Constructors
 public :
  InterlinearWord               (int InBookIndex, int InChapterNumber, int InVerseNumber, int InVerseID);

 //! Destructor
 public :
  ~InterlinearWord              ();

 //! Public Methods
 public :
  int                           GetID                           ();
  int                           GetVerseID                      ();
  QString                       GetContextualForm               ();
  QString                       GetTransliteratedContextualForm ();
  QString                       GetMorphologyID                 ();
  QString                       GetStrongsWordID                ();
  QString                       GetEnglish                      ();

  void                          SetID                           (int InID);
  void                          SetVerseID                      (int InVerseID);
  void                          SetContextualForm               (QString InContextualForm);
  void                          SetTransliteratedContextualForm (QString InTransliteratedContextualForm);
  void                          SetMorphologyID                 (QString InMorphologyID);
  void                          SetStrongsWordID                (QString InStrongsWordID);
  void                          SetEnglish                      (QString InEnglish);
  int                           GetX                            () { return x; }
  void                          SetX                            (int InX) { x = InX; }
  int                           GetY                            () { return y; }
  void                          SetY                            (int InY) { y = InY; }
  QSize                         GetContextualFormSize           () { return contextualFormSize; }
  QFont                         GetContextualFormFont           () { return contextualFormFont; }
  QSize                         GetEnglishSize                  () { return englishSize; }
  QFont                         GetEnglishFont                  () { return englishFont; }
  void                          Paint                           (QPainter* InPainter);
  void							PaintSelected					(QPainter* InPainter);
  QSize                         GetSize                         ();
  static void                   SetLineskip                     (int InLineskip);
  bool                          ContainsPoint                   (QPoint InPoint);
  void							SetSelected						(bool InSelected);

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  int                           ID;
  int                           VerseID;
  int                           VerseNumber;
  int                           ChapterNumber;
  int                           BookIndex; 
  InterlinearWordText*          ContextualForm;
  InterlinearWordText*          TransliteratedContextualForm;
  InterlinearWordText*          MorphologyID;
  InterlinearWordText*          StrongsWordID;
  InterlinearWordText*          English;

  int                           x;
  int                           y;

  static QFont                  strongsFont;
  static QColor                 strongsColor;
  QSize                         strongsSize;
  static bool                   strongsDisplay;

  static QFont                  contextualFormFont;
  static QColor                 contextualFormColor;
  static bool                   contextualFormDisplay;
  QSize                         contextualFormSize;

  static QFont                  morphologyFont;
  static QColor                 morphologyColor;
  static bool                   morphologyDisplay;
  QSize                         morphologySize;

  static QFont                  transliterateFont;
  static QColor                 transliterateColor;
  static bool                   transliterateDisplay;
  QSize                         transliterateSize;

  static QFont                  englishFont;
  static QColor                 englishColor;
  static bool                   englishDisplay;
  static int                    Lineskip;
  QSize                         englishSize;
  bool							selected;
};

#endif /* _interlinearword_h_*/
