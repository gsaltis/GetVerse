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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayFormattingItem.h"

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
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  QStringList                   WordBreakTypeComboAddItems (void);
  void                          CreateConnections       ();
  
 //! Private Data
 private :
  QPushButton*                  ReferenceButton;
  QPushButton*                  EditButton;
  QPushButton*                  AnalyzeButton;
  QPushButton*                  BlockViewButton;
  QPushButton*                  InterlinearButton;
  QPushButton*                  SentenceViewButton;
  QLabel*                       WordLabel;
  QLabel*                       WordCountLabel;
  int                           InterWordSkip;
  int                           RightMargin;
  int                           ButtonWidth;
  int                           ButtonHeight;
  QLabel*                       GroupingLabel;
  QLabel*                       GroupingCountLabel;

  QSpinBox*                     ChapterSelect;
  QLabel*                       ChapterSelectLabel;
  
  QComboBox*                    WordBreakTypeCombo;
  QLabel*                       WordBreakTypeLabel;

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
  
 //! Public Actions
 public :
  QAction*                      ActionReferenceButtonPushed;
  QAction*                      ActionEditButtonPushed;
  QAction*                      ActionAnalyzeButtonPushed;
  QAction*                      ActionBlockViewButtonPushed;

};

#endif /* _textcontrolbar_h_*/
