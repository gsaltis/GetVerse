/*****************************************************************************
 * FILE NAME    : InterlinearWordText.h
 * DATE         : October 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
 *****************************************************************************/
#ifndef _interlinearwordtext_h_
#define _interlinearwordtext_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : InterlinearWordText
 *****************************************************************************/
class InterlinearWordText 
{
 //! Constructors
 public :
  InterlinearWordText           ();

 //! Destructor
 public :
  ~InterlinearWordText          ();

 //! Public Methods
 public :
  QString                               GetText                 ();
  QFont                                 GetFont                 ();
  QColor                                GetTextColor            ();
  QColor                                GetBackgroundColor      ();

  void                                  SetText                 (QString InText);
  void                                  SetFont                 (QFont InFont);
  void                                  SetTextColor            (QColor InTextColor);
  void                                  SetBackgroundColor      (QColor InBackgroundColor);
  QSize                                 GetSize                 (QFont InFont);

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
  QString                               text;
  QFont                                 font;
  QColor                                textColor;
  QColor                                backgroundColor;
};

#endif /* _interlinearwordtext_h_*/
