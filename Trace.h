/*****************************************************************************
 * FILE NAME    : Trace.h
 * DATE         : August 17 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _trace_h_
#define _trace_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TRACE_FUNCTION_INT(n)                                           \
  printf("%10s %50s::%30s:%05d : "                                      \
          "%30s %d\n",                                                  \
         "INT",                                                         \
         __FILE__, __FUNCTION__, __LINE__,                              \
         #n, (int)n);                                                   \
  
#define TRACE_FUNCTION_QSTRING(n)                                       \
  printf("%10s %50s::%30s:%05d : "                                      \
         "%30s %s\n",                                                   \
         "QSTRING",                                                     \
         __FILE__, __FUNCTION__, __LINE__,                              \
         #n, n.toStdString().c_str());                                  \

#define TRACE_FUNCTION_QSIZE(n)                                         \
  printf("%10s %50s::%30s:%05d : "                                      \
         "%30s width = %d  "                                            \
         "height = %d\n",                                               \
         "QSTRING",                                                     \
         __FILE__, __FUNCTION__, __LINE__,                              \
         #n, n.width(),                                                 \
         n.height());                                                   \

#define TRACE_FUNCTION_QPOINT(n)                                        \
  printf("%10s %50s::%30s:%05d : "                                      \
         "%30s x = %d  "                                                \
         "y = %d\n",                                                    \
         "QSTRING",                                                     \
         __FILE__, __FUNCTION__, __LINE__,                              \
         #n, n.x(),                                                     \
         n.y());                                                        \

#define TRACE_FUNCTION_LOCATION()                                       \
  printf("%10s %50s::%30s:%05d\n",                                      \
         "LOCATION",                                                    \
         __FILE__, __FUNCTION__, __LINE__);                             \
 
#define TRACE_FUNCTION_START()                                          \
  printf("%10s %50s::%30s:%05d\n",                                      \
         "START",                                                       \
         __FILE__, __FUNCTION__, __LINE__);                             \
 
#define TRACE_FUNCTION_END()                                            \
  printf("%10s %50s::%30s:%05d\n",                                      \
         "END",                                                         \
         __FILE__, __FUNCTION__, __LINE__);                             \
 
/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _trace_h_*/
