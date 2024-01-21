/*****************************************************************************
 * FILE NAME    : StrongsReferenceDisplayDialog.h
 * DATE         : November 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferencedisplaydialog_h_
#define _strongsreferencedisplaydialog_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QPushButton>
#include <QLabel>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "InterlinearWord.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_DISPLAY_DIALOG_WIDTH  500
#define STRONGS_REFERENCE_DISPLAY_DIALOG_HEIGHT 430
#define STRONGS_REFERENCE_DISPLAY_HEADER_HEIGHT 25
#define STRONGS_REFERENCE_DISPLAY_LABEL_WIDTH   200

/*****************************************************************************!
 * exported Class : StrongsReferenceDisplayDialog
 *****************************************************************************/
class StrongsReferenceDisplayDialog : public QDialog
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceDisplayDialog (InterlinearWord* InWord);

 //! Destructor
 public :
  ~StrongsReferenceDisplayDialog ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              (void);
  void                          CreateConnections       (void);
  void                          CreateSubWindows        (void);
  void                          ReadStrongsDatabase     (void);
  void                          CreateHeaderBlock       (void);
  void                          CreateLabelBlock        (void);
  void                          CreateDataBlock         (void);
  QLabel*                       CreateDataBlockData     (int InY, int InWidth, int InHeight, QString InText);

 //! Private Data
 private :
  QPushButton*                  OKButton;

  QString                       StrongsReference;
  InterlinearWord*              interlinearWord;
  
  QWidget*                      LabelBlock;
  QWidget*                      DataBlock;
  QWidget*                      HeaderBlock;

  QColor                        GradientColorLight;
  QColor                        GradientColorDark;

  QFont                         DataFont;
  QFont                         LabelFont;
  QFont                         HeaderFont;
  QFont                         ContextualFont;
  
  QString                       IDText;
  QString                       LexicalFormText;
  QString                       TransliteratedFormText;
  QString                       PartOfSpeechText;
  QString                       PhoneticSpellingText;
  QString                       DefinitionText;
  QString                       OriginText;
  QString                       UsageText;
  QLabel*                       OriginLabel;
  QLabel*                       UsageLabel;
  QLabel*                       UsageNameLabel;

 //! Public Slots
 public slots :
  void                          SlotOKButtonPressed     ();

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _strongsreferencedisplaydialog_h_*/
