QMAKE_CXX                       = @echo [C+] $@ && g++ 

QMAKE_CC                        = @echo [C+] $@ && gcc 

QMAKE_MOC                       = @echo [MO] $@ && moc 

QMAKE_LINK                      = @echo [LD] $@ && g++ 

QMAKE_RC                        = @echo [RC] $@ && windres 

#QMAKE_LFLAGS_WINDOWS            += -mwindows
QMAKE_LFLAGS_WINDOWS            += -Wl,--subsystem,console -L../Trace/Client

QMAKE_CXXFLAGS                  +=  -I../Trace/Client

QMAKE_LIBS                      = -lwsock32 -ltraceclient

TARGET                          = GetVerse

VERSION                         = "0.0.0"
QMAKE_TARGET_COMPANY            = "Greg Saltis"

QMAKE_TARGET_PRODUCT            = "GetVerse"

QMAKE_TARGET_COPYRIGHT          = "Copyright (C) 2023 Greg Saltis"

QT                              += core gui widgets svg svgwidgets

RESOURCES                       += GetVerse.qrc

DEFINES                         += \

SOURCES                         += \
				   BookInfo.cpp                                 \
				   BookInfoManager.cpp                          \
				   BookInfoWord.cpp                             \
				   BookMark.cpp                                 \
				   BookMarkManager.cpp                          \
				   BookMarkSet.cpp                              \
				   BookNameTable.cpp                            \
				   BookNameTableInnerTable.cpp                  \
				   BookNameTableItem.cpp                        \
				   BookNameTableScrollArea.cpp                  \
				   BookNameWindow.cpp                           \
				   BookmarkButton.cpp                           \
				   ChapterHeaderWindow.cpp                      \
				   CreateParagraphDialog.cpp                    \
				   Formatting.cpp                               \
				   InterlinearChapter.cpp                       \
				   InterlinearDisplayElementSelectDialog.cpp    \
				   InterlinearVerse.cpp                         \
				   InterlinearWord.cpp                          \
				   InterlinearWordText.cpp                      \
				   InterlinearWordTextDisplay.cpp               \
				   MainDisplayWindow.cpp                        \
				   MainMessageWindow.cpp                        \
				   MainWindow.cpp                               \
				   ReaderViewFormat.cpp                         \
				   ReaderViewFormatSet.cpp                      \
				   SQLStatement.cpp                             \
				   SectionHeader.cpp                            \
				   StrongsReferenceDisplayDialog.cpp            \
				   StrongsReferenceDisplayScrollWindow.cpp      \
				   StrongsReferenceDisplayWindow.cpp            \
				   StrongsReferenceDisplayWord.cpp              \
				   StrongsReferenceDisplayWordsWindow.cpp       \
				   StrongsReferenceForm.cpp                     \
				   StrongsReferenceFormSplitter.cpp             \
				   StrongsReferenceToolBar.cpp                  \
				   StrongsReferenceVerseItem.cpp                \
				   StrongsReferenceVerseWindow.cpp              \
				   SystemConfig.cpp                             \
				   SystemSettings.cpp                           \
				   TextControlBar.cpp                           \
				   TextControlBarCheckBox.cpp                   \
				   TextDisplayFormattingItem.cpp                \
				   TextDisplayInterlinearContainerWindow.cpp    \
				   TextDisplayInterlinearItem.cpp               \
				   TextDisplayInterlinearReferenceItem.cpp      \
				   TextDisplayInterlinearScrollWindow.cpp       \
				   TextDisplayInterlinearWindow.cpp             \
				   TextDisplayInterlinearWordSelect.cpp         \
				   TextDisplayItem.cpp                          \
				   TextDisplayOuterWindow.cpp                   \
				   TextDisplayReaderToolBar.cpp                 \
				   TextDisplayReaderViewContainerWindow.cpp     \
				   TextDisplayReaderViewWindow.cpp              \
				   TextDisplayReferenceItem.cpp                 \
				   TextDisplayReferenceWindow.cpp               \
				   TextDisplaySentenceContainterWindow.cpp      \
				   TextDisplaySentenceItem.cpp                  \
				   TextDisplaySentenceScrollWindow.cpp          \
				   TextDisplaySentenceWindow.cpp                \
				   TextDisplayVerseContainerWindow.cpp          \
				   TextDisplayVerseItem.cpp                     \
				   TextDisplayVerseReferenceItem.cpp            \
				   TextDisplayVerseScrollWindow.cpp             \
				   TextDisplayVerseWindow.cpp                   \
				   TextDisplayViewScrollBar.cpp                 \
				   TextDisplayViewScrollWindow.cpp              \
				   TextDisplayViewWindow.cpp                    \
				   TextDisplayViewWindowItem.cpp                \
				   TextDisplayViewWindowReferenceItem.cpp       \
				   TextDisplayWordFormattingItem.cpp            \
				   TextDisplayWordItem.cpp                      \
				   VerseInfo.cpp                                \
				   VerseInfoSet.cpp                             \
                                   WindowHeader.cpp                             \
				   main.cpp                                     \
				   sqlite3.c                                    \

HEADERS                         += \
				   BookInfo.h                                   \
				   BookInfoManager.h                            \
				   BookInfoWord.h                               \
				   BookMark.h                                   \
				   BookMarkManager.h                            \
				   BookMarkSet.h                                \
				   BookNameTable.h                              \
				   BookNameTableInnerTable.h                    \
				   BookNameTableItem.h                          \
				   BookNameTableScrollArea.h                    \
				   BookNameWindow.h                             \
				   BookmarkButton.h                             \
				   ChapterHeaderWindow.h                        \
				   CreateParagraphDialog.h                      \
				   Formatting.h                                 \
				   InterlinearChapter.h                         \
				   InterlinearDisplayElementSelectDialog.h      \
				   InterlinearVerse.h                           \
				   InterlinearWord.h                            \
				   InterlinearWordText.h                        \
				   InterlinearWordTextDisplay.h                 \
				   MainDisplayWindow.h                          \
				   MainMessageWindow.h                          \
				   MainWindow.h                                 \
				   ReaderViewFormat.h                           \
				   ReaderViewFormatSet.h                        \
				   SQLStatement.h                               \
				   SectionHeader.h                              \
				   StrongsReferenceDisplayDialog.h              \
				   StrongsReferenceDisplayScrollWindow.h        \
				   StrongsReferenceDisplayWindow.h              \
				   StrongsReferenceDisplayWord.h                \
				   StrongsReferenceDisplayWordsWindow.h         \
				   StrongsReferenceForm.h                       \
				   StrongsReferenceFormSplitter.h               \
				   StrongsReferenceToolBar.h                    \
				   StrongsReferenceVerseItem.h                  \
				   StrongsReferenceVerseWindow.h                \
				   SystemConfig.h                               \
				   SystemSettings.h                             \
				   TextControlBar.h                             \
				   TextControlBarCheckBox.h                     \
				   TextDisplayFormattingItem.h                  \
				   TextDisplayInterlinearContainerWindow.h      \
				   TextDisplayInterlinearItem.h                 \
				   TextDisplayInterlinearReferenceItem.h        \
				   TextDisplayInterlinearScrollWindow.h         \
				   TextDisplayInterlinearWindow.h               \
				   TextDisplayInterlinearWordSelect.h           \
				   TextDisplayItem.h                            \
				   TextDisplayOuterWindow.h                     \
				   TextDisplayReaderToolBar.h                   \
				   TextDisplayReaderViewContainerWindow.h       \
				   TextDisplayReaderViewWindow.h                \
				   TextDisplayReferenceItem.h                   \
				   TextDisplayReferenceWindow.h                 \
				   TextDisplaySentenceContainterWindow.h        \
				   TextDisplaySentenceItem.h                    \
				   TextDisplaySentenceScrollWindow.h            \
				   TextDisplaySentenceWindow.h                  \
				   TextDisplayVerseContainerWindow.h            \
				   TextDisplayVerseItem.h                       \
				   TextDisplayVerseReferenceItem.h              \
				   TextDisplayVerseScrollWindow.h               \
				   TextDisplayVerseWindow.h                     \
				   TextDisplayViewScrollBar.h                   \
				   TextDisplayViewScrollWindow.h                \
				   TextDisplayViewWindow.h                      \
				   TextDisplayViewWindowItem.h                  \
				   TextDisplayViewWindowReferenceItem.h         \
				   TextDisplayWordFormattingItem.h              \
				   TextDisplayWordItem.h                        \
				   VerseInfo.h                                  \
				   VerseInfoSet.h                               \
                                   WindowHeader.h                               \
				   sqlite3.h                                    \

FORMS                           += \

QMAKE_EXTRA_TARGETS             += junkclean
junkclean.target                = junkclean
junkclean.commands              = @echo Removing junk                           \
                                  && rm -rf $(wildcard core* *~)
junkclean.depends               = 

QMAKE_EXTRA_TARGETS             += cleanall
cleanall.target                 = cleanall
cleanall.commands               = 
cleanall.depends                = junkclean                                     \
                                  clean
