/*****************************************************************************
 * FILE NAME    : SQLStatement.cpp
 * DATE         : September 20 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SQLStatement.h"

#define SQL_STATEMENT_INSERT_FORMATTING         \
  "INSERT INTO Formatting VALUES(%d, %d, %d, %d, '%s', %d);\n"

#define SQL_STATEMENT_DELETE_FORMATTING         \
  "DELETE FROM Formatting where book is %d "    \
  "and chapter is %d "                          \
  "and verse is %d "                            \
  "and word is %d "                             \
  "and type is %d;"

/*****************************************************************************!
 * Function : SQLStatement
 *****************************************************************************/
SQLStatement::SQLStatement
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~SQLStatement
 *****************************************************************************/
SQLStatement::~SQLStatement
()
{
}

/*****************************************************************************!
 * Function : GetFormattingInsert
 *****************************************************************************/
QString
SQLStatement::GetFormattingInsert(void)
{
  return QString(SQL_STATEMENT_INSERT_FORMATTING);
}

/*****************************************************************************!
 * Function : GetFormattingDelete
 *****************************************************************************/
QString
SQLStatement::GetFormattingDelete(void)
{
  return QString(SQL_STATEMENT_DELETE_FORMATTING);
}
