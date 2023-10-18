/*****************************************************************************
 * FILE NAME    : InterlinearWord.cpp
 * DATE         : October 15 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "InterlinearWord.h"

/*****************************************************************************!
 * Function : InterlinearWord
 *****************************************************************************/
InterlinearWord::InterlinearWord
(int InBookIndex, int InChapterNumber, int InVerseNumber, int InVerseID)
{
  BookIndex     = InBookIndex;
  ChapterNumber = InChapterNumber;
  VerseNumber   = InVerseNumber;
  VerseID       = InVerseID;

  ContextualForm                = new InterlinearWordText();
  TransliteratedContextualForm  = new InterlinearWordText();
  MorphologyID                  = new InterlinearWordText();
  StrongsWordID                 = new InterlinearWordText();
  English                       = new InterlinearWordText();
}

/*****************************************************************************!
 * Function : ~InterlinearWord
 *****************************************************************************/
InterlinearWord::~InterlinearWord
()
{
}

/*****************************************************************************!
 * Function : GetID
 *****************************************************************************/
int
InterlinearWord::GetID
()
{
  return ID;
}

/*****************************************************************************!
 * Function : GetVerseID
 *****************************************************************************/
int
InterlinearWord::GetVerseID
()
{
  return VerseID;
}

/*****************************************************************************!
 * Function : GetContextualForm
 *****************************************************************************/
QString
InterlinearWord::GetContextualForm
()
{
  return ContextualForm->GetText();
}

/*****************************************************************************!
 * Function : GetTransliteratedContextualForm
 *****************************************************************************/
QString
InterlinearWord::GetTransliteratedContextualForm
()
{
  return TransliteratedContextualForm->GetText();
}

/*****************************************************************************!
 * Function : GetMorphologyID
 *****************************************************************************/
QString
InterlinearWord::GetMorphologyID
()
{
  return MorphologyID->GetText();
}

/*****************************************************************************!
 * Function : GetStrongsWordID
 *****************************************************************************/
QString
InterlinearWord::GetStrongsWordID
()
{
  return StrongsWordID->GetText();
}

/*****************************************************************************!
 * Function : GetEnglish
 *****************************************************************************/
QString
InterlinearWord::GetEnglish
()
{
  return English->GetText();
}

/*****************************************************************************!
 * Function : SetID
 *****************************************************************************/
void
InterlinearWord::SetID
(int InID)
{
  ID = InID;
}

/*****************************************************************************!
 * Function : SetVerseID
 *****************************************************************************/
void
InterlinearWord::SetVerseID
(int InVerseID)
{
  VerseID = InVerseID;
}

/*****************************************************************************!
 * Function : SetContextualForm
 *****************************************************************************/
void
InterlinearWord::SetContextualForm
(QString InContextualForm)
{
  ContextualForm->SetText(InContextualForm);
}

/*****************************************************************************!
 * Function : SetTransliteratedContextualForm
 *****************************************************************************/
void
InterlinearWord::SetTransliteratedContextualForm
(QString InTransliteratedContextualForm)
{
  TransliteratedContextualForm->SetText(InTransliteratedContextualForm);
}

/*****************************************************************************!
 * Function : SetMorphologyID
 *****************************************************************************/
void
InterlinearWord::SetMorphologyID
(QString InMorphologyID)
{
  MorphologyID->SetText(InMorphologyID);
}

/*****************************************************************************!
 * Function : SetStrongsWordID
 *****************************************************************************/
void
InterlinearWord::SetStrongsWordID
(QString InStrongsWordID)
{
  StrongsWordID->SetText(InStrongsWordID);
}

/*****************************************************************************!
 * Function : SetEnglish
 *****************************************************************************/
void
InterlinearWord::SetEnglish
(QString InEnglish)
{
  English->SetText(InEnglish);
}

