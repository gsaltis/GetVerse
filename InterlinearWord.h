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
  InterlinearWord               ();

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
  QString                       ContextualForm;
  QString                       TransliteratedContextualForm;
  QString                       MorphologyID;
  QString                       StrongsWordID;
  QString                       English;
};

#endif /* _interlinearword_h_*/
