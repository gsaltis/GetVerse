/*****************************************************************************
 * FILE NAME    : main.c
 * DATE         : July 21 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <StringUtils.h>
#include <MemoryManager.h>
#include <errno.h>
#include <error.h>
#include <FileUtils.h>
#include <ctype.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "sqlite3.h"
#include "main.h"
#include "Formatting.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/
#define DEFAULT_FILENAME                        "NASB.txt"
#define DEFAULT_DB_FILENAME                     "NASB.db"
#define DATABASE_ENV_LOCATION                   "GETVERSE_DATABASE"
#define DUPLICATE_BOOK                          1
#define BOOK_NOT_FOUND                          2
#define BOOK_FOUND                              3

#define BOOK_NAME_LEN                           32
#define BOOK_COUNT                              66
#define VERSE_RANGES_COUNT                      50

#define ALL_VERSES_STRING                       "1-1000"

#define FORMAT_INFO_TYPE_VERSE_SPLIT            1

#define VERSION									"1.0.0"

#define SQL_STATEMENT_INSERT_FORMATTING         \
  "INSERT INTO Formatting VALUES(%d, %d, %d, '', %d);\n"

#define MAIN_FORMAT_COUNT_MAX                   128

/*****************************************************************************!
 * Exported Type : BookInfo
 *****************************************************************************/
struct _BookInfo
{
  char                                  name[BOOK_NAME_LEN];
  int                                   chapters;
  int                                   index;
};
typedef struct _BookInfo BookInfo;

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
 * Local Data
 *****************************************************************************/
static string
MainBlockOutputText = NULL;

static bool
MainFormatAdd = false;

static bool
MainBlockOutput = false;

bool
MainVerbose = false;

bool
MainVerseTextSplit = false;

bool
MainVerseTextSimpleSplit = false;

bool
MainDisplayReference = false;

sqlite3*
MainDatabase;

static StringList*
MainFileLines = NULL;

static string
ProgramName = "getverse";

static BookInfo*
MainSearchBook = NULL;

static VerseRange
MainVerseRanges[VERSE_RANGES_COUNT];

static int
MainVerseRangesCount = 0;

static string
MainFilename = NULL;

static string
MainDatabaseFilename = NULL;

int
MainBookIndex = 0;

int
MainChapter = 0;

int
MainVerse[MAIN_FORMAT_COUNT_MAX] = { 0 };

int
MainFormatType[MAIN_FORMAT_COUNT_MAX] = { 0 } ;

int
MainFormatCount = 0;

static string
MainBook = NULL;

BookInfo
MainBookInfo[BOOK_COUNT] =
{ 0 };

FormattingInfoList*
MainFormatInfos;

int
VersionMajor = 1;

int
VersionMinor = 0;

int
VersionRelease = 1;

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
void
MainPostProcess
(void);

void
AddVerseRange
(int InChapter, int InVerseStart, int InVerseEnd);

void
MainWordDataBasePopulate
(void);

StringList*
MainProcessVerseText
(string InText);

void
MainClearingDatabase
(void);

void
MainDBInsertVerse
(int InBookIndex, string InBookName, int InChapter, int InVerse, string InText);

void
MainDBInsertBookName
(string InBookname, int InBookIndex, int InChapterCount);

void
MainDBInsertChapter
(int InBookIndex, int InChapter, int InVerses);

bool
MainParseTextLine
(string InLine, string InBookName, int* InChapter, int* InVerse, string InText);

void
MainDataBasePopulate
(void);

BookInfo*
MainGetSearchableBookName
(string InBookName);

int
MainVerifyBookName
(string InBookName);

void
DisplayHelp
(void);

void
MainGetVerse
(void);

void
VerifyCommandLine
(void);

void
ProcessCommandLine
(int argc, char** argv);

void
MainInitialize
(void);

void
MainReadLines
();

void
MainSearchLines
();

void
MainDBBReadBookInfo
();

void
MainDBBReadBookInfo
();

int
MainDBBReadBookInfoCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames);

int
MainWordDataBasePopulateCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames);

void
MainDBFindVerse
(int InRange);

int
MainDBBFindVerseInfoCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames);

void
ProcessCommandLineVerseDeclaration
(int InChapter, string InVerseDecl);

string
CapitalizeBookName
(string InBookname);

int
GetBookIndexFromName
(string InBookName);

void
HandleCommandLineFormatAdd
(int InStart, int argc, char** argv);

bool
ProcessFormatAdd
();

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  MainInitialize();
  ProcessCommandLine(argc, argv);
  VerifyCommandLine();
  MainDBBReadBookInfo();
  if ( MainFormatAdd ) {
    ProcessFormatAdd();
  }
  FormattingInfoListReadSQL(MainFormatInfos, MainDatabase);
  MainGetVerse();
  MainPostProcess();
  return (EXIT_SUCCESS);
}

/*****************************************************************************!
 * Function : MainInitialize
 *****************************************************************************/
void
MainInitialize
(void)
{
  string                                s;
  
  MainFilename          = NULL;
  MainDatabaseFilename  = StringCopy(DEFAULT_DB_FILENAME);
  MainBook              = NULL;
  MainVerseRangesCount  = 0;
  MainFormatInfos       = FormattingInfoListCreate();
  MainBlockOutputText   = StringCopy("");
  
  s = getenv(DATABASE_ENV_LOCATION);
  if ( s ) {
    FreeMemory(MainDatabaseFilename);
    MainDatabaseFilename = StringCopy(s);
  }
}

/*****************************************************************************!
 * Function : ProcessCommandLine
 *****************************************************************************/
void
ProcessCommandLine
(int argc, char** argv)
{
  int                                   chapterNumber;
  int                                   k;
  string                                chapterString;
  string                                verseString;
  string                                command;
  int                                   i;
  StringList*                           st;
  
  for (i = 1; i < argc; i++) {
    command = argv[i];
    if ( StringEqualsOneOf(command, "-v", "--version", NULL) ) {
      printf("%s : %s\n", ProgramName, VERSION); 
      exit(EXIT_SUCCESS);
    }

    if ( StringEqualsOneOf(command, "-h", "--help", NULL) ) {
      DisplayHelp();
      exit(EXIT_SUCCESS);
    }

    if ( StringEqualsOneOf(command, "-b", "--block", NULL) ) {
      MainBlockOutput = true;
      continue;
    }

    if ( StringEqualsOneOf(command, "-a", "--addformatting", NULL) ) {
      HandleCommandLineFormatAdd(i + 1, argc, argv);
      MainFormatAdd = true;
      i += 4;
      continue;
    }

    if ( StringEqualsOneOf(command, "-V", "--version", NULL) ) {
      printf("%s Version : %02d.%02d.%02d\n", ProgramName, VersionMajor, VersionMinor, VersionRelease);
      exit(EXIT_SUCCESS);
    }
    //!
    if ( StringEqualsOneOf(command, "-f", "--file", NULL) ) {
      i++;
      if ( i == argc ) {
        fprintf(stderr, "Missing file name\n");
        DisplayHelp();
      }
      if ( MainFilename ) {
        FreeMemory(MainFilename);
      }
      MainFilename = StringCopy(argv[i]);
      continue;
    }

    //!
    if ( StringEqualsOneOf(command, "-d", "--database", NULL) ) {
      i++;
      if ( i == argc ) {
        fprintf(stderr, "Missing database file name\n");
        DisplayHelp();
      }
      FreeMemory(MainDatabaseFilename);
      MainDatabaseFilename = StringCopy(argv[i]);
      continue;
    }

    //!
    if ( StringEqualsOneOf(command, "-p", "--populate", NULL) ) {
      MainDataBasePopulate();
      exit(EXIT_SUCCESS);
    }

    //!
    if ( StringEqualsOneOf(command, "-w", "--words", NULL) ) {
      MainWordDataBasePopulate();
      exit(EXIT_SUCCESS);
    }
    
    //!
    if ( StringEqualsOneOf(command, "-r", "--reference", NULL) ) {
      MainDisplayReference = true;
      continue;
    }
    //!
    if ( StringEqualsOneOf(command, "-s", "--split", NULL) ) {
      MainVerseTextSplit = true;
      continue;
    }
    //!
    if ( StringEqualsOneOf(command, "-e", "--easysplit", NULL) ) {
      MainVerseTextSimpleSplit = true;
      continue;
    }
    //!
    if ( StringEqualsOneOf(command, "-v", "--verbose", NULL) ) {
      MainVerbose = true;
      continue;
    }
    break;
  }

  if ( MainFormatAdd ) {
    // The remaining options have been consumedm
    return;
  }
  
  if ( i == argc ) {
    fprintf(stderr, "Missing book reference\n");
    exit(EXIT_FAILURE);
  }
  FreeMemory(MainBook);
  MainBook = StringCopy(argv[i]);
  i++;

  //!
  for ( k = i; k < argc; k++ ) {
    st = StringSplit(argv[k], ":", false);
    if ( st->stringCount < 1 || st->stringCount > 2 ) {
      fprintf(stderr, "Invalid chapter/verse reference\n");
      exit(EXIT_FAILURE);
    }
    do {
      if ( st->stringCount == 2 ) {
        chapterString = st->strings[0];
        verseString = st->strings[1];
        break;
      }
      chapterString = argv[k];
      k++;
      
      if ( k == argc ) {
        verseString = ALL_VERSES_STRING;
        break;
      }
      verseString = argv[k];
    } while (false);
    if ( !StringIsInteger(chapterString) ) {
      fprintf(stderr, "Chapter reference is not a number\n");
      exit(EXIT_FAILURE);
    }
    chapterNumber = atoi(chapterString);
    ProcessCommandLineVerseDeclaration(chapterNumber, verseString);
  }
  StringListDestroy(st);
}

/*****************************************************************************!
 * Function : ProcessCommandLineVerseDeclaration
 *****************************************************************************/
void
ProcessCommandLineVerseDeclaration
(int InChapter, string InVerseDecl)
{
  int                                   i;
  StringList*                           st;     // Destroy Me
  StringList*                           st2;    // Destroy Me
  string                                st3;

  st2 = StringSplit(InVerseDecl, ",", false);

  for ( i = 0; i < st2->stringCount; i++ ) {
    st3 = st2->strings[i];
    st = StringSplit(st3, "-", false);
    if ( st->stringCount == 1 ) {
      if ( !StringIsInteger(st3) ) {
        fprintf(stderr, "Verse reference is not a number\n");
        exit(EXIT_FAILURE);
      }
      AddVerseRange(InChapter, atoi(st3), atoi(st3));
      StringListDestroy(st);
      continue;
    }
    if ( st->stringCount == 2 ) {
      if ( ! (StringIsInteger(st->strings[0]) && StringIsInteger(st->strings[1]) ) ) {
        fprintf(stderr, "%s is not a valid verse reference\n", st3);
        exit(EXIT_FAILURE);
      }
      AddVerseRange(InChapter, atoi(st->strings[0]), atoi(st->strings[1]));
      if ( MainVerseRanges[MainVerseRangesCount].last < MainVerseRanges[MainVerseRangesCount].first ) {
        fprintf(stderr, "First Verse must be < Last Verse\n");
        exit(EXIT_FAILURE);
      }
      MainVerseRangesCount++;
      StringListDestroy(st);
    }
  }
  StringListDestroy(st2);
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
  
  if ( MainFilename ) {
    if ( ! FileExists(MainFilename) ) {
      fprintf(stderr, "File %s  does not exist\n", MainFilename);
      exit(EXIT_FAILURE);
    }
  }

  if ( ! FileExists(MainDatabaseFilename) ) {
    fprintf(stderr, "File %s does not exist\n", MainDatabaseFilename);
    exit(EXIT_FAILURE);
  }

  n = sqlite3_open(MainDatabaseFilename, &MainDatabase);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "Could not open database %s : %s\n", MainDatabaseFilename, sqlite3_errstr(n));
    exit(EXIT_FAILURE);
  }

  if ( MainFormatAdd ) {
    exit(ProcessFormatAdd() ? EXIT_SUCCESS : EXIT_FAILURE);
  }
  
  MainDBBReadBookInfo();
  b = MainVerifyBookName(MainBook);
  switch (b) {
    case BOOK_NOT_FOUND : {
      fprintf(stderr, "%s was not found\n", MainBook);
      exit(EXIT_FAILURE);
      break;
    }
    case DUPLICATE_BOOK : {
      fprintf(stderr, "%s references duplicate bookd\n", MainBook);
      exit(EXIT_FAILURE);
      break;
    }
  }
  MainSearchBook = MainGetSearchableBookName(MainBook);
  if ( MainVerseRangesCount == 0 ) {
    fprintf(stderr, "Missing verse\n");
    exit(EXIT_FAILURE);
  }
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
 * Function : DisplayHelp
 *****************************************************************************/
void
DisplayHelp
(void)
{
  printf("Usage : %s options\n", ProgramName);
  printf("options book chapter verse \n");
  printf("  -a, --addformatting     : Add formatting to database\n");
  printf("  -b, --block             : Specify the block output style\n");
  printf("  -d, --database          : Populates the database\n");
  printf("  -e, --easysplit         : Specifies whether to split lines only at end of sentence\n");
  printf("  -f, --file filename     : Specify the input filename\n");
  printf("  -h, --help              : Display this information\n");
  printf("  -p, --populate filename : Specify the database filename (Default %s)\n", DEFAULT_DB_FILENAME);
  printf("                            Requires that '-f, --filename' is specified\n");
  printf("  -r, --reference         : Specifies whether to display the verse reference\n");
  printf("  -s, --split             : Specifies whether to split lines at puncations\n");
  printf("  -e, --easysplit         : Specifies whether to split lines only at end of sentence\n");
  printf("  -d, --database          : Populates the database\n");
  printf("  -v, --verbose           : Specifies 'verbose' operation\n");
  printf("  -v, --version           : Display the version information\n");
}

/*****************************************************************************!
 * Function : MainVerifyBookName
 *****************************************************************************/
int
MainVerifyBookName
(string InBookName)
{
  string                                bookName;
  string                                name;
  int                                   i;
  int                                   candidate = -1;
  BookInfo*                             bookInfo;
  int                                   n;

  bookName = StringToLowerCase(InBookName);
  n = sizeof(MainBookInfo) / sizeof(MainBookInfo[0]);
  for (i = 0; i < n; i++) {
    bookInfo = &(MainBookInfo[i]);
    name = StringToLowerCase(bookInfo->name);
    if ( StringBeginsWith(name, bookName) ) {
      if ( candidate != -1 ) {
        FreeMemory(bookName);
        FreeMemory(name);
        return DUPLICATE_BOOK;
      }
      candidate = i;
      FreeMemory(name);
    }
  }
  if ( candidate == -1 ) {
    FreeMemory(bookName);
    return BOOK_NOT_FOUND;
  }
  FreeMemory(bookName);
  return BOOK_FOUND;
}

/*****************************************************************************!
 * Function : MainGetSearchableBookName
 *****************************************************************************/
BookInfo*
MainGetSearchableBookName
(string InBookName)
{
  string                                bookName;
  string                                name;
  int                                   i;
  int                                   candidate = -1;
  BookInfo*                             bookInfo;
  int                                   n;

  bookName = StringToLowerCase(InBookName);
  n = sizeof(MainBookInfo) / sizeof(MainBookInfo[0]);
  for (i = 0; i < n; i++) {
    bookInfo = &(MainBookInfo[i]);
    name = StringToLowerCase(bookInfo->name);
    if ( StringBeginsWith(name, bookName) ) {
      if ( candidate != -1 ) {
        FreeMemory(bookName);
        FreeMemory(name);
        return NULL;
      }
      candidate = i;
      FreeMemory(name);
    }
  }
  if ( candidate == -1 ) {
    FreeMemory(bookName);
    return NULL;
  }
  FreeMemory(bookName);
  return &(MainBookInfo[candidate]);
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
 * Function : MainDataBasePopulate
 *****************************************************************************/
void
MainDataBasePopulate
(void)
{
  string                                line;
  int                                   i;
  int                                   n;

  char                                  book[32];
  char                                  lastBook[32] = { 0 };
  int                                   bookIndex = 1;

  int                                   chapter;
  int                                   lastChapter = 0;

  int                                   verse;
  int                                   lastVerse   = 0;

  char                                  text[4096];
  
  if ( MainFilename == NULL ) {
    fprintf(stderr, "'-p, --populate requires an input filename\n");
    DisplayHelp();
    exit(EXIT_FAILURE);
  }

  //!
  if ( MainVerbose ) {
    printf("Opening Database   : %s\n", MainDatabaseFilename);
  }

  n = sqlite3_open(MainDatabaseFilename, &MainDatabase);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "Could not open database %s : %s\n", MainDatabaseFilename, sqlite3_errstr(n));
    exit(EXIT_FAILURE);
  }

  if ( MainVerbose ) {
    printf("Clearing Databases\n");
  }
  MainClearingDatabase();
  //!
  if ( MainVerbose ) {
    printf("Reading Input File : %s\n", MainFilename);
  }

  MainReadLines();

  //!
  if ( MainVerbose ) {
    printf("Processing Booknames\n");
  }

  for ( i = 0 ; i < MainFileLines->stringCount; i++ ) {
    line = MainFileLines->strings[i];
    memset(text, 0x00, sizeof(text));
    if ( !MainParseTextLine(line, book, &chapter, &verse, text) ) {
      fprintf(stderr, "Could not parse line\n");
      fprintf(stderr, "  %s\n", line);
      exit(EXIT_FAILURE);
    }
    do {
      if ( lastBook[0] && !StringEqual(book, lastBook) ) {
        MainDBInsertBookName(lastBook, bookIndex, lastChapter);
        MainDBInsertChapter(bookIndex, lastChapter, lastVerse);
        bookIndex ++;
        strcpy(lastBook, book);
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
    strcpy(lastBook, book);
    lastChapter = chapter;
    lastVerse = verse;
  }
  MainDBInsertBookName(lastBook, bookIndex, chapter);
  MainDBInsertChapter(bookIndex, lastChapter, verse);
  MainDBInsertVerse(bookIndex, book, chapter, verse, text);
  sqlite3_close(MainDatabase);
}

/*****************************************************************************!
 * Function : MainParseTextLine
 *****************************************************************************/
bool
MainParseTextLine
(string InLine, string InBookName, int* InChapter, int* InVerse, string InText)
{
  int                                 k;
  char                                s[8];
  char                                ch;
  int                                 n;
  int                                 i;
  int                                 start;
  int                                 m;

  n = strlen(InLine);

  start = 0;
  i = 0;

  //! Get Book name
  ch = InLine[0];
  if ( isdigit(ch) ) {
    i = 1;
    while (isspace(InLine[i]) ) {
      i++;
    }
  }

  for ( ; i < n ; i++ ) {
    ch = InLine[i];
    if ( isdigit(ch) ) {
      break;
    }
  }

  // Trim spaces between book and chapter
  k = i-1;
  while (isspace(InLine[k]) ) {
    k--;
  }
  k++;
  strncpy(InBookName, InLine, k);
  InBookName[k] = 0x00;

  //! Get chapter number
  start = i;
  ch = InLine[i];
  while (isdigit(ch)) {
    i++;
    ch = InLine[i];
  }
  m = i - start;
  strncpy(s, &(InLine[start]), m);
  s[m] = 0x00;
  *InChapter = atoi(s);

  //! Make sure we have ':' separator
  ch = InLine[i];
  if ( ch != ':' ) {
    return false;
  }

  //! Get verse number
  i++;
  start = i;
  ch = InLine[i];
  while (isdigit(ch)) {
    i++;
    ch = InLine[i];
  }
  m = i - start;
  strncpy(s, &(InLine[start]), m);
  s[m] = 0x00;
  *InVerse = atoi(s);

  while (isspace(InLine[i])) {
    i++;
  }
  strcpy(InText, &(InLine[i]));
  return true;
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
 * Function : MainDBInsertBookName
 *****************************************************************************/
void
MainDBInsertBookName
(string InBookName, int InBookIndex, int InChapterCount)
{
  char                                  sqlstmt[8192];
  char*                                 error;
  int                                   n;

  if ( MainVerbose ) {
    printf("Inserting Book : %s : %d\n", InBookName, InChapterCount);
  }
  sprintf(sqlstmt, "INSERT INTO Books VALUES(%d, \"%s\", %d);\n",
          InBookIndex, InBookName, InChapterCount);
  n = sqlite3_exec(MainDatabase, sqlstmt, NULL, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);
}

/*****************************************************************************!
 * Function : MainDBBReadBookInfo
 *****************************************************************************/
void
MainDBBReadBookInfo
()
{
  char                                  sqlstmt[128];
  char*                                 error;
  int                                   n;

  sprintf(sqlstmt, "SELECT bookIndex, bookName, chapterCount FROM Books;");
  n = sqlite3_exec(MainDatabase, sqlstmt, MainDBBReadBookInfoCB, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);
}

/*****************************************************************************!
 * Function : MainDBBReadBookInfoCB
 *****************************************************************************/
int
MainDBBReadBookInfoCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  int                                   n;
  int                                   chapterCount;
  int                                   bookIndex;
  string                                bookName;
  
  bookIndex = atoi(InColumnValues[0]);
  bookName = InColumnValues[1];
  chapterCount = atoi(InColumnValues[2]);
  n = bookIndex-1;
  strcpy(MainBookInfo[n].name, bookName);
  MainBookInfo[n].index = bookIndex;
  MainBookInfo[n].chapters = chapterCount;
  return 0;
}

/*****************************************************************************!
 * Function : MainDBInsertVerse
 *****************************************************************************/
void
MainDBInsertVerse
(int InBookIndex, string InBookName, int InChapter, int InVerse, string InText)
{
  char                                  insertText[8192];
  int                                   n, i;
  char                                  reference[32];
  char                                  sqlstmt[8192];
  char*                                 error;
  
  n = strlen(InText);

  for (i = 0; i < n; i++) {
    insertText[i] = InText[i];
    if ( InText[i] == '"' ) {
      insertText[i] = '`';
    }
  }
  insertText[i] = 0x00;
  sprintf(reference, "%s %d:%d", InBookName, InChapter, InVerse);

  sprintf(sqlstmt, "INSERT INTO Verses VALUES(\"%s\", %d, %d, %d, \"%s\");\n",
          reference, InBookIndex, InChapter, InVerse, insertText);
  n = sqlite3_exec(MainDatabase, sqlstmt, NULL, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);
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
 * Function : MainDBFindVerse
 *****************************************************************************/
void
MainDBFindVerse
(int InRange)
{
  char                                  sqlstmt[256];
  char*                                 error;
  int                                   n;

  sprintf(sqlstmt, "  SELECT * FROM Verses where book is %d AND chapter is %d AND verse >= %d AND verse <= %d;",
          MainSearchBook->index, MainVerseRanges[InRange].chapter, MainVerseRanges[InRange].first, MainVerseRanges[InRange].last);
  n = sqlite3_exec(MainDatabase, sqlstmt, MainDBBFindVerseInfoCB, NULL, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, sqlstmt, error);
}


/*****************************************************************************!
 * Function : MainDBBFindVerseInfoCB
 *****************************************************************************/
int
MainDBBFindVerseInfoCB
(void*, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  string                                text2;
  FormattingInfo*                       formatInfo;
  int                                   book;
  string                                st2;
  int                                   verse;
  int                                   chapter;
  int                                   i;
  StringList*                           st;
  string                                reference;
  string                                text;
  string                                bookNameCap;

  reference = InColumnValues[0];
  bookNameCap = CapitalizeBookName(reference);
  text = InColumnValues[4];
  book = atoi(InColumnValues[1]);
  chapter = atoi(InColumnValues[2]);
  verse = atoi(InColumnValues[3]);

  if ( MainBlockOutput ) {
    formatInfo = FormattingInfoListFind(MainFormatInfos, book, chapter, verse);
    text2 = NULL;
    if ( formatInfo ) {
      text2 = FormattingInfoApply(formatInfo, text);
    }
    st2 = StringMultiConcat(MainBlockOutputText,
                            text2 ? text2 : text,
                            text2 ? "" : " ",
                            NULL);
    FreeMemory(MainBlockOutputText);
    MainBlockOutputText = st2;
    if ( text2 ) {
      FreeMemory(text2);
    }
    return 0;
  }
  do {
    if ( MainDisplayReference ) {
      if ( MainBlockOutput ) {
        printf("%d:%d ", chapter, verse);
        break;
      }
      printf("%s\n", bookNameCap);
      if ( !MainVerseTextSimpleSplit && !MainVerseTextSplit ) {
        printf("  ");
      }
    }
  }
  while (false);
  FreeMemory(bookNameCap);
  st = MainProcessVerseText(text);
  for ( i = 0; i < st->stringCount ; i++ ) {
    printf("%s", st->strings[i]);
    printf("\n");
    if ( i + 1 < st->stringCount ) {
      if ( ! MainVerseTextSimpleSplit  && !MainVerseTextSplit ) {
        printf("  ");
      }
    }
  }
  if ( MainDisplayReference ) {
    printf("%s", MainBlockOutput ? " " : "\n");
  }
  StringListDestroy(st);
  return 0;
}

/*****************************************************************************!
 * Function : MainProcessVerseText
 *****************************************************************************/
StringList*
MainProcessVerseText
(string InText)
{
  char                                  ch;
  StringList*                           strings;
  char                                  versePart[1024];
  int                                   n;
  int                                   i;
  int                                   start;
  int                                   m;
  
  strings = StringListCreate();
  if ( ! MainVerseTextSplit && ! MainVerseTextSimpleSplit ) {
    StringListAppend(strings, StringCopy(InText));
    return strings;
  }

  n = strlen(InText);

  start = 0;
  for ( i = 0 ; i < n ; i++ ) {
    ch = InText[i];
    if ( ch == '.' || ch == '?' || ch == '!' ) {
      if ( InText[i+1] == '\'' || InText[i+1] == ')' || InText[i+1] == '`' ) {
        i++;
      }
      m = (i - start) + 1;
      strncpy(versePart, &(InText[start]), m);
      versePart[m] = 0x00;
      StringListAppend(strings, StringCopy(versePart));
      i++;
      while ( i < n && InText[i] == ' ' ) {
        i++;
      }
      start = i;
      continue;
    }
    if ( MainVerseTextSimpleSplit ) {
      continue;
    }
    if ( ch ==  ':' || ch == ',' || ch == ';' ) {
      if ( InText[i+1] == '\'' ) {
        i++;
      }
      if ( InText[i+1] == '`') {
        i++;
      }
      m = (i - start) + 1;
      strncpy(versePart, &(InText[start]), m);
      versePart[m] = 0x00;
      StringListAppend(strings, StringCopy(versePart));
      i++;
      while ( i < n && InText[i] == ' ' ) {
        i++;
      }
      start = i;
      continue;
    }
  }
  if ( start < n ) {
    StringListAppend(strings, StringCopy(&(InText[start])));
  }
  return strings;
}

/*****************************************************************************!
 * Function : CapitalizeBookName
 *****************************************************************************/
string
CapitalizeBookName
(string InBookname)
{
  int                                   i;
  int                                           n = strlen(InBookname);
  string                                        returnBookName;

  returnBookName = StringCopy(InBookname);
  for (i = 0; i < n; i++) {
    if ( i == 0 || isspace(returnBookName[i-1]) ) {
      returnBookName[i] = toupper(returnBookName[i]);
      continue;
    }
  }
  return returnBookName;
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
  string                                error;
  int                                   n;
  
  book = 45;  // Romans
  //!
  if ( MainVerbose ) {
    printf("Opening Database   : %s\n", MainDatabaseFilename);
  }
  
  n = sqlite3_open(MainDatabaseFilename, &MainDatabase);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "Could not open database %s : %s\n", MainDatabaseFilename, sqlite3_errstr(n));
    exit(EXIT_FAILURE);
  }

  sprintf(sqlstmt, "SELECT * FROM Verses WHERE book is %d;", book);

  (void)sqlite3_exec(MainDatabase, sqlstmt, MainWordDataBasePopulateCB, NULL, &error);
    
  //!
  if ( MainVerbose ) {
    printf("Closing Database   : %s\n", MainDatabaseFilename);
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
  char                                  ch2;
  int                                   k;
  int                                   start;
  char                                  ch;
  int                                   i;
  int                                   book;
  int                                   chapter;
  int                                   verse;
  string                                text;
  int                                   n;
  char                                  word[256];

  verse = 0;
  book = 0;
  chapter = 0;
  enum {
    Start,
    InWord,
    InSpaces
  } state = Start;
  
  for (i = 0; i < InColumnCount; i++) {
    if ( StringEqual(InColumnNames[i], "book") ) {
      book = atoi(InColumnValues[i]);
      continue;
    }
    if ( StringEqual(InColumnNames[i], "chapter") ) {
      chapter = atoi(InColumnValues[i]);
      continue;
      
    }
    if ( StringEqual(InColumnNames[i], "verse") ) {
      verse = atoi(InColumnValues[i]);
      continue;      
    }
    if ( StringEqual(InColumnNames[i], "text") ) {
      text = InColumnValues[i];
      continue;
    }
  }

  n = strlen(text);

  for (i = 0; i < n; i++) {
    ch = text[i];
    switch (state) {
      case Start : {
        if ( isalpha(ch) ) {
          start = i;
          state = InWord;
          break;
        }
        break;
      }

      case InSpaces : {
        if ( isalpha(ch) ) {
          start = i;
          state = InWord;
          break;
        }        
        break;
      }

      case InWord : {
        if ( isalpha(ch) ) {
          break;
        }
        if ( ch == '\'' ) {
          k = i + 1;
          if ( k < n ) {
            // Handle what looks like a contraction
            ch2 = text[k];
            if ( isalpha(ch2) ) {
              break;
            }
            break;
          }
        }
        m = i - start;
        strncpy(word, &(text[start]), m);
        word[m] = 0x00;
        printf("%2d %2d %2d : %s\n", book, chapter, verse, word);
        state = InSpaces;
        break;
      }
    }
  }
  return 0;
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
 * Function : MainPostProcess
 *****************************************************************************/
void
MainPostProcess
(void)
{
  char                                  ch2;
  int                                   i2;
  char                                  ch;
  int                                   start;
  int                                   end;
  int                                   len;
  int                                   n;
  int                                   i;
  string                                st;
  
  if ( ! MainBlockOutput ) {
    return;
  }

  if ( ! MainVerseTextSimpleSplit ) {
    printf("%s\n", MainBlockOutputText);
    return;
  }

  n = strlen(MainBlockOutputText);
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
    st = StringNCopy(&(MainBlockOutputText[start]), len);
    printf("%s\n", st);
    end++;
    while (MainBlockOutputText[end] && MainBlockOutputText[end] == ' ') {
      end++;
    }
    FreeMemory(st);
    start = end;
  }
}

/*****************************************************************************!
 * Function : GetBookIndexFromName
 *****************************************************************************/
int
GetBookIndexFromName
(string InBookName)
{
  int                                   n;
  if ( InBookName == NULL || InBookName[0] == 0x00 ) {
    return -1;
  }

  n = BOOK_COUNT;
  for (int i = 0; i < n; i++) {
    if ( StringEqual(InBookName, MainBookInfo[i].name) ) {
      return i + 1;
    }
  }
  return -1;
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

  MainChapter = atoi(argv[k]);
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
 * Function : ProcessFormatAdd
 *****************************************************************************/
bool
ProcessFormatAdd
()
{
  int                                   i;
  int                                   m;
  string                                error;
  char                                  sqlstatement[1024];

  for ( i = 0 ; i < MainFormatCount; i++ ) {
    sprintf(sqlstatement, SQL_STATEMENT_INSERT_FORMATTING,
            MainBookIndex, MainChapter, MainVerse[i], MainFormatType[i]);
    m  = sqlite3_exec(MainDatabase, sqlstatement, NULL, NULL, &error);
    if ( m != SQLITE_OK ) {
      fprintf(stderr, "sqlite_exec() failed\n %s\n %d : %s\n", sqlstatement, m, sqlite3_errstr(m));
      return false;
    }
  }
  return true;
}

