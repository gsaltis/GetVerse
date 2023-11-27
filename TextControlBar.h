/*****************************************************************************
 * FILE NAME    : TextControlBar.h
 * DATE         : September 14 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textcontrolbar_h_
#define _textcontrolbar_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include <QAction>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayFormattingItem.h"
#include "TextControlBarCheckBox.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_CONTROL_BAR_X              200
#define TEXT_CONTROL_BAR_Y              200
#define TEXT_CONTROL_BAR_WIDTH          200
#define TEXT_CONTROL_BAR_HEIGHT         25

/*****************************************************************************!
 * Exported Class : TextControlBar
 *****************************************************************************/
class TextControlBar : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextControlBar                ();

 //! Destructor
 public :
  ~TextControlBar               ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize                      ();
  void                          CreateSubWindows                ();
  void                          InitializeSubWindows            ();
  void                          resizeEvent                     (QResizeEvent* InEvent);
  QStringList                   WordBreakTypeComboAddItems      (void);
  void                          CreateConnections               ();
  void                          InterlinearElementsDisplay      (bool InDisplay);
  
 //! Private Data
 private :
  QPushButton*                  ReferenceButton;
  QPushButton*                  EditButton;
  QPushButton*                  AnalyzeButton;
  QPushButton*                  BlockViewButton;
  QPushButton*                  InterlinearButton;
  QPushButton*                  SentenceViewButton;
  QPushButton*                  BookmarkButton;
  
  QLabel*                       WordLabel;
  QLabel*                       WordCountLabel;
  int                           InterWordSkip;
  int                           RightMargin;
  int                           ButtonWidth;
  int                           ButtonHeight;
  QLabel*                       GroupingLabel;
  QLabel*                       GroupingCountLabel;

  int                           currentChapter;
  int                           currentBook;

  QSpinBox*                     ChapterSelect;
  QLabel*                       ChapterSelectLabel;
  
  QComboBox*                    WordBreakTypeCombo;
  QLabel*                       WordBreakTypeLabel;

  QLabel*                       InterlinearContextualNameLabel;
  QLabel*                       InterlinearEnglishNameLabel;
  QLabel*                       InterlinearStrongsNameLabel;
  QLabel*                       InterlinearMorphologyNameLabel;
  QLabel*                       InterlinearTransliterateNameLabel;
  
  TextControlBarCheckBox*       InterlinearContextualCheckBox;
  TextControlBarCheckBox*       InterlinearEnglishCheckBox;
  TextControlBarCheckBox*       InterlinearStrongsCheckBox;
  TextControlBarCheckBox*       InterlinearMorphologyCheckBox;
  TextControlBarCheckBox*       InterlinearTransliterateCheckBox;
  
 //! Public Slots
 public slots :
  void                          SlotReferenceButtonPushed       (void);
  void                          SlotEditButtonPushed            (void);
  void                          SlotAnalyzeButtonPushed         (void);
  void                          SlotBlockViewButtonPushed       (void);
  void                          SlotInterlinearButtonPushed     (void);
  void                          SlotSentenceViewButtonPushed    (void);
  void                          SlotWordCountChanged            (int);
  void                          SlotVerseCountChanged           (int);
  void                          SlotSentenceCountChanged        (int);
  void                          SlotSetChapter                  (int InChapter);
  void                          SlotSetChapterSelectMax         (int InChapter);
  void                          SlotWordBreakTypeComboSelectedItem (int InSelectedIndex);
  void                          SlotChapterChanged              (int InNewChapter);
  void                          SlotChapterArrowSelected        (int InNewChapter);
  void                          SlotBookmarkButtonPushed        (void);
  void                          SlotBookSelected                (int InBookIndex);
  void                          SlotWindowChange                (int InWindow);
  void                          SlotContextualChecked           (bool InChecked);
  void                          SlotTransliterateChecked        (bool InChecked);
  void                          SlotMorphologyChecked           (bool InChecked);
  void                          SlotEnglishChecked              (bool InChecked);
  void                          SlotStrongsChecked              (bool InChecked);
  
 //! Public Signals
 signals :
  void                          SignalSetSentenceMode           (void);
  void                          SignalSetReferenceMode          (void);
  void                          SignalSetBlockMode              (void);
  void                          SignalSetInterlinearMode        (void);
  void                          SignalSetEditMode               (void);
  void                          SignalVerseCountChanged         (int InVerseCount);
  void                          SignalSentenceCountChanged      (int InVerseCount);
  void                          SignalSetFormattingType         (TextDisplayFormattingItem::FormatType InFormattingType);
  void                          SignalChapterChanged            (int InChapter);
  void                          SignalSetBookmark               (int InBook, int InChapter, int InVerse);
  void                          SignalInterlinearWordChanged (int InWord, bool InChecked);
  
 //! Public Actions
 public :
  QAction*                      ActionReferenceButtonPushed;
  QAction*                      ActionEditButtonPushed;
  QAction*                      ActionAnalyzeButtonPushed;
  QAction*                      ActionBlockViewButtonPushed;

};

#endif /* _textcontrolbar_h_*/
