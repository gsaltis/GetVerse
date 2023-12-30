/*****************************************************************************
 * FILE NAME    : StrongsReferenceVerseWindow.h
 * DATE         : December 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferenceversewindow_h_
#define _strongsreferenceversewindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTableWidget>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_VERSE_WINDOW_X 200
#define STRONGS_REFERENCE_VERSE_WINDOW_Y 200
#define STRONGS_REFERENCE_VERSE_WINDOW_WIDTH 200
#define STRONGS_REFERENCE_VERSE_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : StrongsReferenceVerseWindow
 *****************************************************************************/
class StrongsReferenceVerseWindow : public QTableWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  StrongsReferenceVerseWindow   ();

 //! Destructor
 public :
  ~StrongsReferenceVerseWindow  ();

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
  void                          CreateConnections       ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          Clear                   (void);

 //! Private Data
 private :

 //! Public Slots
 public slots :
  void                          SlotVerseReferenceClear (void);
  void                          SlotVerseReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);
  void                          SlotItemSelected        (QTableWidgetItem* InItem);

 //! Public Signals
 signals :
  void                          SignalVerseReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);
  void                          SignalStrongsReferenceSelected (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Public Actions
 public :

};

#endif /* _strongsreferenceversewindow_h_*/
