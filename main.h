/*****************************************************************************
 * FILE NAME    : main.h
 * DATE         : September 10 2023
 * PROJECT      : GetVerse
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _main_h_
#define _main_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QGuiApplication>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void
MainSetStartLocation
(int InBook, int InChapter, int InVerse);

void
MainGetStartLocation
(int &InBook, int &InChapter, int &InVerse);

void
MainGetInterlinearWordDisplays
(bool &InContextualDisplay, bool &InEnglishDisplay, bool &InStrongsDisplay,
 bool &InMorphologyDisplay, bool &InTransliterateDisplay);

void
MainSetInterlinearWordDisplays
(bool InContextualDisplay, bool InEnglishDisplay, bool InStrongsDisplay,
 bool InMorphologyDisplay, bool InTransliterateDisplay);
  
/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

#endif /* _main_h_*/
