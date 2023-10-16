/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearItem.cpp
 * DATE         : October 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
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
#include "TextDisplayInterlinearItem.h"

/*****************************************************************************!
 * Function : TextDisplayInterlinearItem
 *****************************************************************************/
TextDisplayInterlinearItem::TextDisplayInterlinearItem
(int InBook, int InChapter, int InVerse, QString InText,
 QString InEnglish, QString InMorphology, QString InStrongsReference) :
  TextDisplayItem(InBook, InChapter, InVerse, InText)
{
  English               = InEnglish;
  Morphology            = InMorphology;
  StrongsReference      = InStrongsReference;
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayInterlinearItem
 *****************************************************************************/
TextDisplayInterlinearItem::~TextDisplayInterlinearItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayInterlinearItem::initialize()
{
}

