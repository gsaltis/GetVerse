QMAKE_CXX                       = @echo [C+] $@ && g++ 

QMAKE_CC                        = @echo [C+] $@ && gcc 

QMAKE_MOC                       = @echo [MO] $@ && moc 

QMAKE_LINK                      = @echo [LD] $@ && g++ 

QMAKE_RC                        = @echo [RC] $@ && windres 

#QMAKE_LFLAGS_WINDOWS            += -mwindows
QMAKE_LFLAGS_WINDOWS            += -Wl,--subsystem,console

QMAKE_CXXFLAGS                  += 

QMAKE_LIBS                      = 

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
				   BookNameTable.cpp                            \
				   BookNameTableInnerTable.cpp                  \
				   BookNameTableItem.cpp                        \
				   BookNameTableScrollArea.cpp                  \
				   BookNameWindow.cpp                           \
				   Formatting.cpp                               \
				   MainDisplayWindow.cpp                        \
				   MainMessageWindow.cpp                        \
				   MainWindow.cpp                               \
				   SectionHeader.cpp                            \
				   SystemConfig.cpp                             \
				   TextControlBar.cpp                           \
				   TextDisplayItem.cpp                          \
				   TextDisplayFormattingItem.cpp                \
				   TextDisplayOuterWindow.cpp                   \
				   TextDisplayReferenceItem.cpp                 \
				   TextDisplayReferenceWindow.cpp               \
				   TextDisplayViewScrollWindow.cpp              \
				   TextDisplayViewWindow.cpp                    \
				   TextDisplayViewWindowItem.cpp                \
				   TextDisplayViewWindowReferenceItem.cpp       \
				   main.cpp                                     \
				   sqlite3.c                                    \

HEADERS                         += \
				   BookInfo.h                                   \
				   BookNameTable.h                              \
				   BookNameTableInnerTable.h                    \
				   BookNameTableItem.h                          \
				   BookNameTableScrollArea.h                    \
				   BookNameWindow.h                             \
				   Formatting.h                                 \
				   MainDisplayWindow.h                          \
				   MainMessageWindow.h                          \
				   MainWindow.h                                 \
				   SectionHeader.h                              \
				   SystemConfig.h                               \
				   TextControlBar.h                             \
				   TextDisplayItem.h                            \
				   TextDisplayFormattingItem.h                  \
				   TextDisplayOuterWindow.h                     \
				   TextDisplayReferenceWindow.h                 \
				   TextDisplayReferenceItem.h                   \
				   TextDisplayViewScrollWindow.h                \
				   TextDisplayViewWindow.h                      \
				   TextDisplayViewWindowItem.h                  \
				   TextDisplayViewWindowReferenceItem.h         \
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
