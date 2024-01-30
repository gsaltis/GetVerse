/*****************************************************************************
 FILE NAME      : main.cpp
 DATE           : September 10 2023
 PROJECT        : GetVerse
 COPYRIGHT      : Copyright (C) 2023 by Gregory R Saltis
******************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtGui>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "MainWindow.h"
#include "main.h"
#include "Formatting.h"
#include "SystemConfig.h"
#include "BookInfo.h"
#include "BookMark.h"
#include "BookMarkManager.h"
#include "BookInfoManager.h"
#include "ReaderViewFormatSet.h"
#include "main.h"
#include "SystemSettings.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/
#define DEFAULT_FILENAME                        "NASB.txt"
#define DEFAULT_DB_FILENAME                     "NASB.db"
#define DEFAULT_INTERLINEAR_DB_FILENAME         "HGIB.db"
#define DEFAULT_CONFIG_FILENAME                 "GetVerse.json"
#define DATABASE_ENV_LOCATION                   "GETVERSE_DATABASE"
#define VERSION					"1.0.1"
#define ALL_VERSES_STRING                       "1-1000"
#define MAIN_FORMAT_COUNT_MAX                   128

#define BOOK_NAME_LEN                           32
#define VERSE_RANGES_COUNT                      50
#define BOOK_COUNT                              66

#define SQL_STATEMENT_INSERT_FORMATTING                         \
  "INSERT INTO Formatting VALUES(%d, %d, %d, '', %d);\n"

#define MAIN_DOMAIN_NAME                        "www.gsaltis.com"

/*****************************************************************************!
 * Exported Type : VerseRange
 *****************************************************************************/
struct _VerseRange
{
  int                                   chapter;
  int                                   first;
  int                                   last;
};
typedef struct _VerseRange VerseRange;

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
static void
MainInitialize
();

void
ProcessCommandLine
(int argc, char** argv);

void
DisplayHelp
(void);

void
HandleCommandLineFormatAdd
(int InStart, int argc, char** argv);

void
MainDataBasePopulate
(void);

void
MainWordDataBasePopulate
(void);

int
MainWordDataBasePopulateCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames);

void
ProcessCommandLineVerseDeclaration
(int InChapter, QString InVerseDecl);

void
MainClearingDatabase
(void);

void
MainReadLines
();

bool
MainParseTextLine
(QString InLine, QString InBookName, int* InChapter, int* InVerse, QString InText);

void
MainDBInsertVerse
(int InBookIndex, QString Inbookname, int InChapter, int InVerse, QString InText);

void
MainDBInsertBookName
(QString InBookname, int InBookIndex, int InChapterCount);

void
MainDBInsertChapter
(int InBookIndex, int InChapter, int InVerses);

bool
StringIsInteger
(QString InString);

void
AddVerseRange
(int InChapter, int InVerseStart, int InVerseEnd);

QStringList
GetFileLinesListFromFile
(QString InFilename);

void
VerifyCommandLine
(void);

bool
ProcessFormatAdd
();

void
MainDBBReadBookInfo
();

int
MainDBBReadBookInfoCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames);

void
MainGetVerse
(void);

void
MainDBFindVerse
(int InRange);

void
MainPostProcess
(void);

int
MainDBBFindVerseInfoCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames);

QString
CapitalizeBookName
(QString InBookname);

QStringList
MainProcessVerseText
(QString InText);

int
MainInitializeGUI
(QApplication& InApplication);

void
InitializeSettings
();

void
ReadCommandLineGeometry
(QPoint& InPos, QSize& InSize);

void
DisplayErrorMessage
(QString InMessage);

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
QString
MainInitialView = "verse";

SystemConfig*
MainSystemConfig;

QString
MainConfigFilename = DEFAULT_CONFIG_FILENAME;

QString
MainFilename;

BookInfo*
MainSearchBook;

QString
MainDatabaseFilename;

QString
MainInterlinearDatabaseFilename;

QString
MainBook;

int
MainVerseRangesCount;

FormattingInfoList*
MainFormatInfos;

QString
MainBlockOutputText = QString("");

QString
ProgramName = "GetVerse";

bool
MainUseGUI = true;

bool
MainApplyFormatting = false;

bool
MainBlockOutput = false;

bool
MainDisplayReference = false;

bool
MainVerseTextSplit = false;

bool
MainVerseTextSimpleSplit = false;

bool
MainFormatAdd = false;

bool
MainVerbose = false;

int
VersionMajor = 1;

int
VersionMinor = 0;

int
VersionRelease = 1;

int
MainBookIndex = 0;

int
MainChapterNumber = 0;

int
MainVerse[MAIN_FORMAT_COUNT_MAX] = { 0 };;

int
MainFormatType[MAIN_FORMAT_COUNT_MAX] = { 0 };

int
MainFormatCount = 0;

sqlite3*
MainDatabase;

sqlite3*
MainInterlinearDatabase;

static QStringList
MainFileLines;;

static VerseRange
MainVerseRanges[VERSE_RANGES_COUNT];

BookInfoManager*
MainBookInfo;

BookMarkManager*
MainBookMarks;

ReaderViewFormatSet*
MainReaderViewFormats = NULL;

SystemSettings*
MainSystemSettings;

QString
MainGeometryString;

int
MainVerseNumber = 0;

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  QApplication 				application(argc, argv);

  MainInitialize();
  ProcessCommandLine(argc, argv);
  VerifyCommandLine();

  TRACE_COMMAND_CLEAR();
  MainSystemConfig->ReadJSON(MainConfigFilename);

  MainReaderViewFormats = new ReaderViewFormatSet();
  MainReaderViewFormats->ReadDB(MainDatabase);
  
  if ( MainFormatAdd ) {
    ProcessFormatAdd();
  }
  FormattingInfoListReadSQL(MainFormatInfos, MainDatabase);
  if ( ! MainUseGUI ) {
    MainGetVerse();
    MainPostProcess();
    return EXIT_SUCCESS;
  }
  return MainInitializeGUI(application);
}

/*****************************************************************************!
 * Function : MainInitializeGUI
 *****************************************************************************/
int
MainInitializeGUI
(QApplication& InApplication)
{
  QRect                                 screenGeometry;
  QScreen*                              screen;
  int                                   b;
  MainWindow* 				w;
  QSize                                 size;
  QPoint                                pos;

  if ( ! MainBook.isEmpty() ) {
    b = MainBookInfo->VerifyBookName(MainBook);
    switch (b) {
      case BOOK_NOT_FOUND : {
        fprintf(stderr, "%s was not found\n", MainBook.toStdString().c_str());
        exit(EXIT_FAILURE);
        break;
      }
      case DUPLICATE_BOOK : {
        fprintf(stderr, "%s references duplicate bookd\n", MainBook.toStdString().c_str());
        exit(EXIT_FAILURE);
        break;
      }
    }
    MainSearchBook = MainBookInfo->GetSearchableBookName(MainBook);
  }
    
  InApplication.setApplicationName(MAIN_APP_NAME);
  InApplication.setApplicationVersion(VERSION);
  InApplication.setOrganizationName(MAIN_ORG_NAME);
  InApplication.setOrganizationDomain(MAIN_DOMAIN_NAME);
  w = new MainWindow(MainSearchBook ? MainSearchBook->name : QString(""),
                     MainChapterNumber, MainVerseNumber);

  screen = w->screen();
  screenGeometry = screen->availableGeometry();
  size = QSize(MainSystemSettings->GetMainWindowWidth(),
               MainSystemSettings->GetMainWindowHeight());
  pos = QPoint(MainSystemSettings->GetMainWindowX(),
               MainSystemSettings->GetMainWindowY());

  if ( ! MainGeometryString.isEmpty() ) {
    ReadCommandLineGeometry(pos, size);
  }
  w->resize(size);
  w->move(pos);
  w->SetViewMode(MainInitialView);
  w->show();
  return InApplication.exec();
}

/*****************************************************************************!
 * Function : MainInitialize
 *****************************************************************************/
void
MainInitialize
()
{
  QString                               s;
  QSettings                             settings(MAIN_ORG_NAME, MAIN_APP_NAME);

  MainSystemConfig                      = new SystemConfig();
  MainSystemSettings                    = new SystemSettings();
  
  MainFilename                          = NULL;
  MainDatabaseFilename                  = QString(DEFAULT_DB_FILENAME);
  MainInterlinearDatabaseFilename       = QString(DEFAULT_INTERLINEAR_DB_FILENAME);
  
  MainBook                              = NULL;
  MainVerseRangesCount                  = 0;
  MainFormatInfos                       = FormattingInfoListCreate();
  MainBlockOutputText                   = QString("");

  MainBookInfo = new BookInfoManager();
  MainBookMarks = new BookMarkManager(MAIN_ORG_NAME, MAIN_APP_NAME);
  MainBookMarks->Read();

  InterlinearWord::GetValues();
  TextDisplayInterlinearItem::GetPartsDisplay();
  s = getenv(DATABASE_ENV_LOCATION);
  if ( ! s.isEmpty() ) {
    MainDatabaseFilename = s;
  }
}

/*****************************************************************************!
 * Function : ProcessCommandLine
 *****************************************************************************/
void
ProcessCommandLine
(int argc, char** argv)
{
  int                                   n;
  int                                   verseNumber;
  int                                   verseCount;
  BookInfo*                             bookInfo;
  int                                   chapterNumber;
  QString                               bookName;
  QString                               chapterString;
  QString                               verseString;
  QString                               command;
  int                                   i;
  QStringList                           st;
  QString                               s;
  
  for (i = 1; i < argc; i++) {
    command = argv[i];
    if ( command ==  "-v" || command == "--version" ) {
      printf("%s : %s\n", ProgramName.toStdString().c_str(), VERSION); 
      exit(EXIT_SUCCESS);
    }

    if ( command == "-h" || command == "--help" ) {
      DisplayHelp();
      exit(EXIT_SUCCESS);
    }

    if ( command == "-b" || command == "--block" ) {
      MainBlockOutput = true;
      continue;
    }

    if ( command == "-F" || command == "--format" ) {
      MainApplyFormatting = true;
      continue;
    }
    
    if ( command == "-n" || command == "--nogui" ) {
      MainUseGUI = false;
      continue;
    }
    
    if ( command == "-a" || command == "--addformatting" ) {
      HandleCommandLineFormatAdd(i + 1, argc, argv);
      MainFormatAdd = true;
      i += 4;
      continue;
    }
  
    if ( command == "-V" || command == "--version" ) {
      printf("%s Version : %02d.%02d.%02d\n", ProgramName.toStdString().c_str(), VersionMajor, VersionMinor, VersionRelease);
      exit(EXIT_SUCCESS);
    }
    //!
    if ( command == "-f" || command == "--file" ) {
      i++;
      if ( i == argc ) {
        fprintf(stderr, "Missing file name\n");
        DisplayHelp();
      }
      MainFilename = QString(argv[i]);
      continue;
    }
  
    //!
    if ( command == "-d" || command == "--database" ) {
      i++;
      if ( i == argc ) {
        fprintf(stderr, "Missing database file name\n");
        DisplayHelp();
      }
      MainDatabaseFilename = QString(argv[i]);
      continue;
    }
    
    //!
    if ( command == "-c" || command == "--config" ) {
      i++;
      if ( i == argc ) {
        fprintf(stderr, "Missing config file name\n");
        DisplayHelp();
      }
      MainConfigFilename = QString(argv[i]);
      continue;
    }
    
    if ( command == "-g" || command == "--geometry" ) {
      i++;
      if ( i == argc ) {
        fprintf(stderr, "Missing geometry string\n");
        DisplayHelp();
      }
      MainGeometryString = QString(argv[i]);
      continue;
    }
    
    //!
    if ( command == "-p" || command == "--populate" ) {
      MainDataBasePopulate();
      exit(EXIT_SUCCESS);
    }
    
    //!
    if ( command == "-w" || command == "--words" ) {
      MainWordDataBasePopulate();
      exit(EXIT_SUCCESS);
    }
    
    //!
    if ( command == "-r" || command == "--reference" ) {
      MainDisplayReference = true;
      continue;
    }
    //!
    if ( command == "-s" || command =="--split" ) {
      MainVerseTextSplit = true;
      continue;
    }
    //!
    if ( command == "-e" || command == "--easysplit" ) {
      MainVerseTextSimpleSplit = true;
      continue;
    }
    //!
    if ( command == "-V" || command == "--verbose" ) {
      MainVerbose = true;
      continue;
    }

    if ( command == "-S" || command == "--screenview" ) {
      i++;
      if ( i == argc ) {
        fprintf(stderr, "Missing config file name\n");
        DisplayHelp();
      }
      s = QString(argv[i]);
      if ( ! ( s == "verse" || s == "sentence" || s == "reader" || s == "interlinear" ) ) {
        fprintf(stderr, "%s is not a valid screen view\n", s.toStdString().c_str());
        DisplayHelp();
        exit(EXIT_FAILURE);
      }
      MainInitialView = s;
      continue;
    }
    break;
  }

  //!
  n = sqlite3_open(MainDatabaseFilename.toStdString().c_str(), &MainDatabase);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "Could not open database %s : %s\n", MainDatabaseFilename.toStdString().c_str(), sqlite3_errstr(n));
    exit(EXIT_FAILURE);
  }
  
  //! 
  QFileInfo                             fileInfo2(MainDatabaseFilename);
  if ( ! fileInfo2.exists() ) {
    fprintf(stderr, "File %s does not exist\n", MainDatabaseFilename.toStdString().c_str());
    exit(EXIT_FAILURE);
  }
  MainDBBReadBookInfo();

  //!
  if ( MainFormatAdd ) {
    // The remaining options have been consumedm
    return;
  }

  if ( i == argc ) {
    return;
  }
  
  //! 
  bookName = argv[i];
  i++;

  //! 
  bookInfo = MainBookInfo->GetBookByName(bookName, true);
  if ( NULL == bookInfo ) {
    DisplayErrorMessage(QString("Book %1 is not found").arg(bookName));
    exit(EXIT_FAILURE);
  }
  
  //! 
  if ( i == argc ) {
    MainBook = bookName;
    MainChapterNumber = 1;
    MainVerseNumber = 1;
    return;
  }
  
  //! 
  s = QString(argv[i]);
  st = s.split(":");
  chapterNumber = st[0].toInt();
  if ( chapterNumber == 0 || chapterNumber > bookInfo->GetChapterCount() ) {
    DisplayErrorMessage(QString("%1 is not a valid chapter for book %2")
                        .arg(chapterNumber)
                        .arg(bookName));
    exit(EXIT_FAILURE);
  }
  verseNumber = 1;
  MainBook = bookName;
  MainChapterNumber = chapterNumber;
  MainVerseNumber = 1;
  
  if ( st.size() == 2 ) {
    verseNumber = st[1].toInt();
    verseCount = bookInfo->GetChapterVerseCount(MainChapterNumber);
    if ( verseNumber == 0 || verseNumber > verseCount ) {
      DisplayErrorMessage(QString("%1 is not a valid verse for %2 %3 (max %4)")
                          .arg(verseNumber)
                          .arg(bookName)
                          .arg(chapterNumber)
                          .arg(verseCount));
      exit(EXIT_FAILURE);
    }
    MainVerseNumber = verseNumber;
  }
}

/*****************************************************************************!
 * Function : DisplayHelp
 *****************************************************************************/
void
DisplayHelp
(void)
{
  printf("Usage : %s options\n", ProgramName.toStdString().c_str());
  printf("options book chapter{:verse} \n");
  printf("  -a, --addformatting     : Add formatting to database\n");
  printf("  -b, --block             : Specify the block output style\n");
  printf("  -c, --config filename   : Specify the system configuration file\n");
  printf("  -d, --database          : Populates the database\n");
  printf("  -e, --easysplit         : Specifies whether to split lines only at end of sentence\n");
  printf("  -f, --file filename     : Specify the input filename\n");
  printf("  -F, --format            : Apply formatting\n");
  printf("  -g, --geometry string   : Set initial geometry (XxY:W+H)\n");
  printf("  -h, --help              : Display this information\n");
  printf("  -n, --nogui             : Don't use GUI\n");
  printf("  -p, --populate filename : Specify the database filename (Default %s)\n", DEFAULT_DB_FILENAME);
  printf("                            Requires that '-f, --filename' is specified\n");
  printf("  -r, --reference         : Specifies whether to display the verse reference\n");
  printf("  -s, --split             : Specifies whether to split lines at puncations\n");
  printf("  -S, --screen view       : Specify the initial view to begining with\n");
  printf("                            [verse sentence reader interlinear]\n");
  printf("  -e, --easysplit         : Specifies whether to split lines only at end of sentence\n");
  printf("  -V, --verbose           : Specifies 'verbose' operation\n");
  printf("  -v, --version           : Display the version information\n");
}

/*****************************************************************************!
 * Function : HandleCommandLineFormatAdd
 *****************************************************************************/
void
HandleCommandLineFormatAdd
(int InStart, int argc, char** argv)
{
  int                                   i;
  int                                   k;
  int                                   n;
  
  n = argc - InStart;
  if ( n < 4 ) {
    fprintf(stderr, "Missing formatting information.\n");
    exit(EXIT_FAILURE);
  }

  k = InStart;

  MainBookIndex = atoi(argv[k]);
  k++;

  MainChapterNumber = atoi(argv[k]);
  k++;

  for ( i = k ; i < argc; i += 2 ) {
    MainVerse[MainFormatCount] = atoi(argv[i]);
    if ( i + 1 == argc ) {
      fprintf(stderr, "Missing type at %d\n", i);
      exit(EXIT_FAILURE);
    }
    MainFormatType[MainFormatCount] = atoi(argv[i]);
    MainFormatCount++;
    if ( MainFormatCount >= MAIN_FORMAT_COUNT_MAX ) {
      fprintf(stderr, "Tool main formats on command line\n");
    }
  }
}

/*****************************************************************************!
 * Function : MainDataBasePopulate
 *****************************************************************************/
void
MainDataBasePopulate
(void)
{
  QString                               line;
  int                                   i;
  int                                   n;

  QString                               book;
  QString                               lastBook;
  int                                   bookIndex = 1;

  int                                   chapter;
  int                                   lastChapter = 0;

  int                                   verse;
  int                                   lastVerse   = 0;

  char                                  text[4096];
  
  if ( MainFilename.isEmpty() ) {
    fprintf(stderr, "'-p, --populate requires an input filename\n");
    DisplayHelp();
    exit(EXIT_FAILURE);
  }

  //!
  if ( MainVerbose ) {
    printf("Opening Database   : %s\n", MainDatabaseFilename.toStdString().c_str());
  }

  n = sqlite3_open(MainDatabaseFilename.toStdString().c_str(), &MainDatabase);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "Could not open database %s : %s\n", MainDatabaseFilename.toStdString().c_str(), sqlite3_errstr(n));
    exit(EXIT_FAILURE);
  }

  if ( MainVerbose ) {
    printf("Clearing Databases\n");
  }
  MainClearingDatabase();
  //!
  if ( MainVerbose ) {
    printf("Reading Input File : %s\n", MainFilename.toStdString().c_str());
  }

  MainReadLines();

  //!
  if ( MainVerbose ) {
    printf("Processing Booknames\n");
  }

  for ( i = 0 ; i < MainFileLines.count(); i++ ) {
    line = MainFileLines[i];
    memset(text, 0x00, sizeof(text));
    if ( !MainParseTextLine(line, book, &chapter, &verse, text) ) {
      fprintf(stderr, "Could not parse line\n");
      fprintf(stderr, "  %s\n", line.toStdString().c_str());
      exit(EXIT_FAILURE);
    }
    do {
      if ( lastBook.isEmpty() && (book != lastBook) ) {
        MainDBInsertBookName(lastBook, bookIndex, lastChapter);
        MainDBInsertChapter(bookIndex, lastChapter, lastVerse);
        bookIndex ++;
        lastBook = book;
        lastChapter = chapter;
        lastVerse = 0;
        break;
      }
      if ( chapter != lastChapter ) {
        MainDBInsertChapter(bookIndex, lastChapter, lastVerse);
        lastChapter = chapter;
      }
    } while (false);
    MainDBInsertVerse(bookIndex, book, chapter, verse, text);
    lastBook = book;
    lastChapter = chapter;
    lastVerse = verse;
  }
  MainDBInsertBookName(lastBook, bookIndex, chapter);
  MainDBInsertChapter(bookIndex, lastChapter, verse);
  MainDBInsertVerse(bookIndex, book, chapter, verse, text);
  sqlite3_close(MainDatabase);
}

/*****************************************************************************!
 * Function : MainWordDataBasePopulate
 *****************************************************************************/
void
MainWordDataBasePopulate
(void)
{
  int                                   book;
  char                                  sqlstmt[128];
  int                                   n;
  
  book = 45;  // Romans
  //!
  if ( MainVerbose ) {
    printf("Opening Database   : %s\n", MainDatabaseFilename.toStdString().c_str());
  }
  
  n = sqlite3_open(MainDatabaseFilename.toStdString().c_str(), &MainDatabase);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "Could not open database %s : %s\n", MainDatabaseFilename.toStdString().c_str(), sqlite3_errstr(n));
    exit(EXIT_FAILURE);
  }

  sprintf(sqlstmt, "SELECT * FROM Verses WHERE book is %d;", book);

  (void)sqlite3_exec(MainDatabase, sqlstmt, MainWordDataBasePopulateCB, NULL, NULL);
    
  //!
  if ( MainVerbose ) {
    printf("Closing Database   : %s\n", MainDatabaseFilename.toStdString().c_str());
  }
}

/*****************************************************************************!
 * Function : MainWordDataBasePopulateCB
 *****************************************************************************/
int
MainWordDataBasePopulateCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  int                                   m;
  QChar                                 ch2;
  int                                   k;
  int                                   start;
  QChar                                 ch;
  int                                   i;
  int                                   book;
  int                                   chapter;
  int                                   verse;
  QString                               text;
  int                                   n;
  QString                               word;

  verse = 0;
  book = 0;
  chapter = 0;
  
  enum {
    Start,
    InWord,
    InSpaces
  } state = Start;
  
  for (i = 0; i < InColumnCount; i++) {
    QString                             columnName  = QString(InColumnNames[i]);
    QString                             columnValue = QString(InColumnValues[i]);
    if ( columnName == "book") {
      book = columnValue.toInt();
      continue;
    }
    if ( columnName == "chapter") {
      chapter = columnValue.toInt();
      continue;
      
    }
    if ( columnName == "verse") {
      verse = columnValue.toInt();
      continue;      
    }
    if ( columnName == "text") {
      text = columnValue;
      continue;
    }
  }

  n = text.length();

  for (i = 0; i < n; i++) {
    ch = text[i];
    switch (state) {
      case Start : {
        if ( ch.isLetter() ) {
          start = i;
          state = InWord;
          break;
        }
        break;
      }

      case InSpaces : {
        if ( ch.isLetter() ) {
          start = i;
          state = InWord;
          break;
        }        
        break;
      }

      case InWord : {
        if ( ch.isLetter() ) {
          break;
        }
        if ( ch == '\'' ) {
          k = i + 1;
          if ( k < n ) {
            // Handle what looks like a contraction
            ch2 = text[k];
            if ( ch2.isLetter() ) {
              break;
            }
            break;
          }
        }
        m = i - start;
        word = text.sliced(start, m);
        printf("%2d %2d %2d : %s\n", book, chapter, verse, word.toStdString().c_str());
        state = InSpaces;
        break;
      }
    }
  }
  return 0;
}

/*****************************************************************************!
 * Function : ProcessCommandLineVerseDeclaration
 *****************************************************************************/
void
ProcessCommandLineVerseDeclaration
(int InChapter, QString InVerseDecl)
{
  int                                   i;
  QStringList                           st;
  QStringList                           st2;
  QString                               st3;

  st2 = InVerseDecl.split(",");

  for ( i = 0; i < st2.count(); i++ ) {
    st3 = st2[i];
    st = st3.split("-");
    if ( st.count() == 1 ) {
      if ( !StringIsInteger(st3) ) {
        fprintf(stderr, "Verse reference is not a number\n");
        exit(EXIT_FAILURE);
      }
      AddVerseRange(InChapter, st3.toInt(), st3.toInt());
      continue;
    }
    if ( st.count() == 2 ) {
      if ( ! (StringIsInteger(st[0]) && StringIsInteger(st[1]) ) ) {
        fprintf(stderr, "%s is not a valid verse reference\n", st3.toStdString().c_str());
        exit(EXIT_FAILURE);
      }
      AddVerseRange(InChapter, st[0].toInt(), st[1].toInt());
      if ( MainVerseRanges[MainVerseRangesCount].last < MainVerseRanges[MainVerseRangesCount].first ) {
        fprintf(stderr, "First Verse must be < Last Verse\n");
        exit(EXIT_FAILURE);
      }
      MainVerseRangesCount++;
    }
  }
}
  
/*****************************************************************************!
 * Function : MainClearingDatabase
 *****************************************************************************/
void
MainClearingDatabase
(void)
{
  char                                  sqlstmt[8192];
  char*                                 error;
  int                                   n;

  sprintf(sqlstmt, "DELETE FROM Books;\n");
  n = sqlite3_exec(MainDatabase, sqlstmt, NULL, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);

  sprintf(sqlstmt, "DELETE FROM Chapters;\n");
  n = sqlite3_exec(MainDatabase, sqlstmt, NULL, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);

  sprintf(sqlstmt, "DELETE FROM Verses;\n");
  n = sqlite3_exec(MainDatabase, sqlstmt, NULL, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);
}

/*****************************************************************************!
 * Function : MainReadLines
 *****************************************************************************/
void
MainReadLines
()
{
  MainFileLines = GetFileLinesListFromFile(MainFilename);
}

/*****************************************************************************!
 * Function : MainParseTextLine
 *****************************************************************************/
bool
MainParseTextLine
(QString InLine, QString InBookName, int* InChapter, int* InVerse, QString InText)
{
  QChar                                 ch2;
  int                                 k;
  QString                             s;;
  QChar                               ch;
  int                                 n;
  int                                 i;
  int                                 start;
  int                                 m;
  
  n = InLine.length();
  
  start = 0;
  i = 0;
  
  //! Get Book name
  ch = InLine[0];
  if ( ch.isDigit() ) {
    i = 1;
    ch2 = InLine[i];
    while ( ch2.isSpace() ) {
      i++;
      ch2 = InLine[i];
    }
  }

  for ( ; i < n ; i++ ) {
    ch = InLine[i];
    if ( ch.isDigit() ) {
      break;
    }
  }
  
  // Trim spaces between book and chapter
  k = i-1;
  while (InLine[k].isSpace() ) {
    k--;
  }
  k++;
  InBookName = InLine.sliced(0, k);

  //! Get chapter number
  start = i;
  ch = InLine[i];
  while (ch.isDigit() ) {
    i++;
    ch = InLine[i];
  }
  m = i - start;
  s = InLine.sliced(start, m);
  *InChapter = s.toInt();

  //! Make sure we have ':' separator
  ch = InLine[i];
  if ( ch != ':' ) {
    return false;
  }

  //! Get verse number
  i++;
  start = i;
  ch = InLine[i];
  while (ch.isDigit()) {
    i++;
    ch = InLine[i];
  }
  m = i - start;
  s = InLine.sliced(start, m);
  *InVerse = s.toInt();

  ch = InLine[i];
  while ( ch.isSpace() ) {
    i++;
    ch = InLine[i];
  }
  m = InLine.size() - i;
  
  InText = InLine.sliced(i, m);
  return true;
}

/*****************************************************************************!
 * Function : MainDBInsertBookName
 *****************************************************************************/
void
MainDBInsertBookName
(QString InBookName, int InBookIndex, int InChapterCount)
{
  char                                  sqlstmt[8192];
  int                                   n;

  if ( MainVerbose ) {
    printf("Inserting Book : %s : %d\n", InBookName.toStdString().c_str(), InChapterCount);
  }
  sprintf(sqlstmt, "INSERT INTO Books VALUES(%d, \"%s\", %d);\n",
          InBookIndex, InBookName.toStdString().c_str(), InChapterCount);
  n = sqlite3_exec(MainDatabase, sqlstmt, NULL, NULL, NULL);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, sqlite3_errstr(n));
}

/*****************************************************************************!
 * Function : GetFileLinesListFromFile
 *****************************************************************************/
QStringList
GetFileLinesListFromFile
(QString InFilename)
{
  QString                               st;
  QString                               st2;
  QByteArray                            buffer;
  QStringList                           fileLines;
  int                                   i;
  int                                   n;
  QString                               line;
  QFile                                 file(InFilename);

  if ( file.open(QIODevice::ReadOnly) ) {
    return fileLines;
  }

  buffer = file.readAll();

  st2 = QString(buffer);
  file.close();

  fileLines = st2.split("\n");
  n = fileLines.size();
  for ( i = 0 ; i < n ; i++ ) {
    line = fileLines[i];
    fileLines[i] = line.trimmed();
  }
  return fileLines;
}

/*****************************************************************************!
 * Function : StringIsInteger
 *****************************************************************************/
bool
StringIsInteger
(QString InString)
{
  bool                          b;

  InString.toInt(&b, 10);
  return b;
}

/*****************************************************************************!
 * Function : AddVerseRange
 *****************************************************************************/
void
AddVerseRange
(int InChapter, int InVerseStart, int InVerseEnd)
{
  MainVerseRanges[MainVerseRangesCount].chapter = InChapter;
  MainVerseRanges[MainVerseRangesCount].first = InVerseStart;
  MainVerseRanges[MainVerseRangesCount].last  = InVerseEnd;
  MainVerseRangesCount++;  
}

/*****************************************************************************!
 * Function : MainDBInsertChapter
 *****************************************************************************/
void
MainDBInsertChapter
(int InBookIndex, int InChapter, int InVerses)
{
  char                                  sqlstmt[8192];
  char*                                 error;
  int                                   n;

  sprintf(sqlstmt, "INSERT INTO Chapters VALUES(%d, %d, %d);\n",
          InBookIndex, InChapter, InVerses);
  n = sqlite3_exec(MainDatabase, sqlstmt, NULL, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);
}

/*****************************************************************************!
 * Function : MainDBInsertVerse
 *****************************************************************************/
void
MainDBInsertVerse
(int InBookIndex, QString InBookName, int InChapter, int InVerse, QString InText)
{
  char                                  insertText[8192];
  int                                   n, i;
  char                                  reference[32];
  char                                  sqlstmt[8192];
  char*                                 error;
  
  n = InText.length();
  for (i = 0; i < n; i++) {
    QChar                               ch = InText[i];
    insertText[i] = ch.toLatin1();
    if ( ch == '"' ) {
      insertText[i] = '`';
    }
  }
  insertText[i] = 0x00;
  sprintf(reference, "%s %d:%d", InBookName.toStdString().c_str(), InChapter, InVerse);

  sprintf(sqlstmt, "INSERT INTO Verses VALUES(\"%s\", %d, %d, %d, \"%s\");\n",
          reference, InBookIndex, InChapter, InVerse, insertText);
  n = sqlite3_exec(MainDatabase, sqlstmt, NULL, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);
}

/*****************************************************************************!
 * Function : VerifyCommandLine
 *****************************************************************************/
void
VerifyCommandLine
(void)
{
  int                                   b;
  int                                   n;
  
  if ( ! MainFilename.isEmpty() ) {
    QFileInfo                           fileInfo(MainFilename);
    if ( ! fileInfo.exists() ) {
      fprintf(stderr, "File %s  does not exist\n", MainFilename.toStdString().c_str());
      exit(EXIT_FAILURE);
    }
  }


  n = sqlite3_open(MainInterlinearDatabaseFilename.toStdString().c_str(), &MainInterlinearDatabase);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "Could not open database %s : %s\n", MainInterlinearDatabaseFilename.toStdString().c_str(), sqlite3_errstr(n));
    exit(EXIT_FAILURE);
  }
  
  n = sqlite3_open(MainDatabaseFilename.toStdString().c_str(), &MainDatabase);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "Could not open database %s : %s\n", MainDatabaseFilename.toStdString().c_str(), sqlite3_errstr(n));
    exit(EXIT_FAILURE);
  }

  if ( MainFormatAdd ) {
    exit(ProcessFormatAdd() ? EXIT_SUCCESS : EXIT_FAILURE);
  }

  if ( MainUseGUI ) {
    return;
  }
  b = MainBookInfo->VerifyBookName(MainBook);
  switch (b) {
    case BOOK_NOT_FOUND : {
      fprintf(stderr, "%s was not found\n", MainBook.toStdString().c_str());
      exit(EXIT_FAILURE);
      break;
    }
    case DUPLICATE_BOOK : {
      fprintf(stderr, "%s references duplicate bookd\n", MainBook.toStdString().c_str());
      exit(EXIT_FAILURE);
      break;
    }
  }
  MainSearchBook = MainBookInfo->GetSearchableBookName(MainBook);
  if ( MainVerseRangesCount == 0 ) {
    fprintf(stderr, "Missing verse\n");
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************!
 * Function : ProcessFormatAdd
 *****************************************************************************/
bool
ProcessFormatAdd
()
{
  int                                   i;
  int                                   m;
  char                                  sqlstatement[1024];

  for ( i = 0 ; i < MainFormatCount; i++ ) {
    sprintf(sqlstatement, SQL_STATEMENT_INSERT_FORMATTING,
            MainBookIndex, MainChapterNumber, MainVerse[i], MainFormatType[i]);
    m  = sqlite3_exec(MainDatabase, sqlstatement, NULL, NULL, NULL);
    if ( m != SQLITE_OK ) {
      fprintf(stderr, "sqlite_exec() failed\n %s\n %d : %s\n", sqlstatement, m, sqlite3_errstr(m));
      return false;
    }
  }
  return true;
}

/*****************************************************************************!
 * Function : MainDBBReadBookInfo
 *****************************************************************************/
void
MainDBBReadBookInfo
()
{
  char                                  sqlstmt[128];
  int                                   n;

  sprintf(sqlstmt, "SELECT *  FROM BookFormat;");
  n = sqlite3_exec(MainDatabase, sqlstmt, MainDBBReadBookInfoCB, NULL, NULL);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, sqlite3_errstr(n));
}

/*****************************************************************************!
 * Function : MainDBBReadBookInfoCB
 *****************************************************************************/
int
MainDBBReadBookInfoCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  int                                   rightToLeft = 0;
  BookInfo*                             bookInfo;
  int                                   chapterCount = 0;
  int                                   bookIndex = 0;
  QString                               bookName;
  QString                               nameAbbrev;
  int                                   bookOrder = 0;
  int                                   bookGroup = 0;
  int                                   hebrewBookOrder = 0;
  int                                   hebrewBookGroup = 0;
  int                                   groupEnd = 0;
  QString                               columnName;
  QString                               columnValue;

  for ( int i = 0 ; i < InColumnCount; i++ ) {
    columnName  = InColumnNames[i];
    columnValue = InColumnValues[i];

    if ( columnName == "BookIndex" ) {
      bookIndex = columnValue.toInt();
      continue;
    }
    if ( columnName == "Chapters" ) {
      chapterCount = columnValue.toInt();
      continue;
    }
    if ( columnName == "StandardBooksOrder" ) {
      bookOrder = columnValue.toInt();
      continue;
    }
    if ( columnName == "StandardBookGroup" ) {
      bookGroup = columnValue.toInt();
      continue;
    }
    if ( columnName == "HebrewBookOrder" ) {
      hebrewBookOrder = columnValue.toInt();
      continue;
    }
    if ( columnName == "HebrewBookGroup" ) {
      hebrewBookGroup = columnValue.toInt();
      continue;
    }
    if ( columnName == "GroupEnd" ) {
      groupEnd = columnValue.toInt();
      continue;
    }
    if ( columnName == "Name" ) {
      bookName = columnValue;
      continue;
    }
    if ( columnName == "NameAbbrev" ) {
      nameAbbrev = columnValue;
      continue;
    }

    if ( columnName == "RightToLeft" ) {
      rightToLeft = columnValue.toInt();
    }
  }

  bookInfo = new BookInfo();
  bookInfo->name                = bookName;
  bookInfo->nameAbbrev          = nameAbbrev;
  bookInfo->index               = bookIndex;
  bookInfo->chapters            = chapterCount;
  bookInfo->bookOrder           = bookOrder;
  bookInfo->bookGroup           = bookGroup;
  bookInfo->hebrewBookOrder     = hebrewBookOrder;
  bookInfo->hebrewBookGroup     = hebrewBookGroup;
  bookInfo->groupEnd            = groupEnd;
  bookInfo->RightToLeft         = rightToLeft;

  MainBookInfo->AddBookInfo(bookInfo);
  return 0;
}

/*****************************************************************************!
 * Function : MainGetVerse
 *****************************************************************************/
void
MainGetVerse
(void)
{
  int                                   i;
  for ( i = 0 ; i < MainVerseRangesCount ; i++ ) {
    MainDBFindVerse(i);
  }
}

/*****************************************************************************!
 * Function : MainDBFindVerse
 *****************************************************************************/
void
MainDBFindVerse
(int InRange)
{
  char                                  sqlstmt[256];
  int                                   n;

  sprintf(sqlstmt, "  SELECT * FROM Verses where book is %d AND chapter is %d AND verse >= %d AND verse <= %d;",
          MainSearchBook->index, MainVerseRanges[InRange].chapter, MainVerseRanges[InRange].first, MainVerseRanges[InRange].last);
  n = sqlite3_exec(MainDatabase, sqlstmt, MainDBBFindVerseInfoCB, NULL, NULL);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, sqlite3_errstr(n));
}


/*****************************************************************************!
 * Function : MainDBBFindVerseInfoCB
 *****************************************************************************/
int
MainDBBFindVerseInfoCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  QString                               text2;
  FormattingInfo*                       formatInfo;
  int                                   book;
  QString                               st2;
  int                                   verse;
  int                                   chapter;
  int                                   i;
  QStringList                           st;
  QString                               reference;
  QString                               text;
  QString                               bookNameCap;

  (void)InColumnCount;
  (void)InColumnNames;
  reference = QString(InColumnValues[0]);
  bookNameCap = CapitalizeBookName(reference);
  text = InColumnValues[4];
  book = atoi(InColumnValues[1]);
  chapter = atoi(InColumnValues[2]);
  verse = atoi(InColumnValues[3]);

  if ( MainBlockOutput ) {
    formatInfo = FormattingInfoListFind(MainFormatInfos, book, chapter, verse);
    if ( MainApplyFormatting && formatInfo ) {
      text2 = FormattingInfoApply(formatInfo, text);
    } else {
      text2 = text + QString(" ");
    }
    MainBlockOutputText += text2;
    return 0;
  }
  do {
    if ( MainDisplayReference ) {
      if ( MainBlockOutput ) {
        printf("%d:%d ", chapter, verse);
        break;
      }
      printf("%s\n", bookNameCap.toStdString().c_str());
      if ( !MainVerseTextSimpleSplit && !MainVerseTextSplit ) {
        printf("  ");
      }
    }
  }
  while (false);
  st = MainProcessVerseText(text);
  for ( i = 0; i < st.count() ; i++ ) {
    printf("%s", st[i].toStdString().c_str());
    printf("\n");
    if ( i + 1 < st.count() ) {
      if ( ! MainVerseTextSimpleSplit  && !MainVerseTextSplit ) {
        printf("  ");
      }
    }
  }
  if ( MainDisplayReference ) {
    printf("%s", MainBlockOutput ? " " : "\n");
  }
  return 0;
}

/*****************************************************************************!
 * Function : MainPostProcess
 *****************************************************************************/
void
MainPostProcess
(void)
{
  QChar                                 ch2;
  int                                   i2;
  QChar                                 ch;
  int                                   start;
  int                                   end;
  int                                   len;
  int                                   n;
  int                                   i;
  QString                               st;
  
  if ( ! MainBlockOutput ) {
    return;
  }

  if ( ! MainVerseTextSimpleSplit ) {
    printf("%s\n", MainBlockOutputText.toStdString().c_str());
    return;
  }

  n = MainBlockOutputText.length();
  start = 0;
  for ( i = 0; i < n ; i++ ) {
    ch = MainBlockOutputText[i];
    if ( ! ( ch == '.' || ch == '?' || ch == '!') ) {
      continue;
    }
    i2 = i + 1;
    ch2 = MainBlockOutputText[i2];
    if ( ch2 == ')' || ch == '\'' || ch == '`' ) {
      i2++;
    }
    end = i2;
    len = (end - start) + 1;
    st = MainBlockOutputText.sliced(start, len);
    printf("%s\n", st.toStdString().c_str());
    end++;
    ch = MainBlockOutputText[end];
    while (ch.isSpace() ) {
      end++;
      ch = MainBlockOutputText[end];
    }
    start = end;
  }
}

/*****************************************************************************!
 * Function : CapitalizeBookName
 *****************************************************************************/
QString
CapitalizeBookName
(QString InBookname)
{
  QChar                                 ch;
  int                                   i;
  int                                   n = InBookname.length();
  QString                               returnBookName;

  returnBookName = InBookname;
  for (i = 0; i < n; i++) {
    if ( i == 0 || returnBookName[i-1].isSpace() ) {
      ch = returnBookName[i];
      returnBookName[i] = ch.toUpper();
      continue;
    }
  }
  return returnBookName;
}

/*****************************************************************************!
 * Function : MainProcessVerseText
 *****************************************************************************/
QStringList
MainProcessVerseText
(QString InText)
{
  QChar                                 ch;
  QChar                                 ch2;
  QStringList                           strings;
  QString                               versePart;
  int                                   n;
  int                                   i;
  int                                   start;
  int                                   m;
  
  if ( ! MainVerseTextSplit && ! MainVerseTextSimpleSplit ) {
    strings.append(InText);
    return strings;
  }

  n = InText.length();

  start = 0;
  for ( i = 0 ; i < n ; i++ ) {
    ch = InText[i];
    if ( ch == '.' || ch == '?' || ch == '!' ) {
      ch2 = InText[i+1];
      if ( ch2 == '\'' || ch2 == ')' || ch2 == '`' ) {
        i++;
      }
      m = (i - start) + 1;
      versePart = InText.sliced(start, m);
      strings << versePart;
      i++;
      ch = InText[i];
      while ( i < n && ch.isSpace() ) {
        i++;
      }
      start = i;
      continue;
    }
    if ( MainVerseTextSimpleSplit ) {
      continue;
    }
    if ( ch ==  ':' || ch == ',' || ch == ';' ) {
      ch2 = InText[i+1];
      if ( ch2  == '\'' ) {
        i++;
      }
      if ( ch2 == '`') {
        i++;
      }
      m = (i - start) + 1;
      versePart = InText.sliced(start, m);
      strings << versePart;
      i++;
      ch2 = InText[i];
      while ( i < n && ch2.isSpace() ) {
        i++;
        ch2 = InText[i];
      }
      start = i;
      continue;
    }
  }
  if ( start < n ) {
    strings << InText.sliced(0, start);
  }
  return strings;
}

/*****************************************************************************!
 * Function : InitializeSettings
 *****************************************************************************/
void
InitializeSettings
()
{
  MainSetStartLocation(1, 1, 1);
}
  
/*****************************************************************************!
 * Function : SetStartLocation
 *****************************************************************************/
void
MainSetStartLocation
(int InBook, int InChapter, int InVerse)
{
  QSettings                             settings(MAIN_ORG_NAME, MAIN_APP_NAME);

  settings.setValue("StartLocation/book", InBook);
  settings.setValue("StartLocation/chapter", InChapter);
  settings.setValue("StartLocation/verse", InVerse);
  settings.setValue("StartLocation/View", "Reference");
}

  
/*****************************************************************************!
 * Function : MainGetStartLocation
 *****************************************************************************/
void
MainGetStartLocation
(int &InBook, int &InChapter, int &InVerse)
{
  int                                   book;
  int                                   chapter;
  int                                   verse;
  
  QSettings                             settings(MAIN_ORG_NAME, MAIN_APP_NAME);
  book = settings.value("StartLocation/book", 1).toInt();
  chapter = settings.value("StartLocation/chapter", 1).toInt();
  verse = settings.value("StartLocation/verse", 1).toInt();

  InBook = book;
  InChapter = chapter;
  InVerse = verse;
}

/*****************************************************************************!
 * Function : MainSetInterlinearWordDisplays
 *****************************************************************************/
void
MainSetInterlinearWordDisplays
(bool InContextualDisplay, bool InEnglishDisplay, bool InStrongsDisplay,
 bool InMorphologyDisplay, bool InTransliterateDisplay)
{
  QSettings                             settings(MAIN_ORG_NAME, MAIN_APP_NAME);

  settings.setValue("Interlinear/Values/Contextual/Display", InContextualDisplay);
  settings.setValue("Interlinear/Values/Strongs/Display", InStrongsDisplay);
  settings.setValue("Interlinear/Values/Transliterate/Display", InTransliterateDisplay);
  settings.setValue("Interlinear/Values/English/Display", InEnglishDisplay);
  settings.setValue("Interlinear/Values/Morphology/Display", InMorphologyDisplay);
}

/*****************************************************************************!
 * Function : MainGetInterlinearWordDisplays
 *****************************************************************************/
void
MainGetInterlinearWordDisplays
(bool &InContextualDisplay, bool &InEnglishDisplay, bool &InStrongsDisplay,
 bool &InMorphologyDisplay, bool &InTransliterateDisplay)
{
  QSettings                             settings(MAIN_ORG_NAME, MAIN_APP_NAME);

  InContextualDisplay = settings.value("Interlinear/Values/Contextual/Display", true).toBool();
  InStrongsDisplay = settings.value("Interlinear/Values/Strongs/Display", true).toBool();
  InTransliterateDisplay = settings.value("Interlinear/Values/Transliterate/Display", true).toBool();
  InEnglishDisplay = settings.value("Interlinear/Values/English/Display", true).toBool();
  InMorphologyDisplay = settings.value("Interlinear/Values/Morphology/Display", true).toBool();
}


/*****************************************************************************!
 * Function : ReadCommandLineGeometry
 *****************************************************************************/
void
ReadCommandLineGeometry
(QPoint& InPos, QSize& InSize)
{
  int                                   height;
  int                                   width;
  int                                   x;
  int                                   y;
  int                                   ss;
  int                                   ps;
  int                                   m;
  QStringList                           s1;
  QStringList                           posList;
  QStringList                           sizeList;

  s1 = MainGeometryString.split(":");
  m = s1.size();

  switch (m) {
    case 1 : {
      if ( MainGeometryString.contains("x") ) {
        sizeList = MainGeometryString.split("x");
        break;
      }
      if ( MainGeometryString.contains("+") ) {
        posList = MainGeometryString.split("+");
        break;
      }
      DisplayErrorMessage(QString("%1 is an invalid geometry string").arg(MainGeometryString));
      exit(EXIT_FAILURE);
      break;
    }
    case 2 : {
      posList  = s1[0].split("+");
      sizeList = s1[1].split("x");
      break;
    }
    default : {
      DisplayErrorMessage(QString("%1 is an invalid geometry string").arg(MainGeometryString));
      exit(EXIT_FAILURE);
      break;
    }
  }
  ps = posList.size();
  ss = sizeList.size();

  if ( ! (ps == 0 || ps == 2 || ss == 0 || ss == 2) ) {
    DisplayErrorMessage(QString("%1 is an invalid geometry string").arg(MainGeometryString));
    exit(EXIT_FAILURE);
  }

  if ( ps == 2 ) {
    x = posList[0].toInt();
    y = posList[1].toInt();
    InPos.setX(x);
    InPos.setY(y);
  }
  if ( ss == 2 ) {
    width = sizeList[0].toInt();
    height = sizeList[1].toInt();
    InSize.setWidth(width);
    InSize.setHeight(height);
  }
}

/*****************************************************************************!
 * Function : DisplayErrorMessage
 *****************************************************************************/
void
DisplayErrorMessage
(QString InMessage)
{
  fprintf(stderr, "%s\n", InMessage.toStdString().c_str());
}
