/*****************************************************************************
 * FILE NAME    : trace_winnet.h
 * DATE         : December 09 2021
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/
#ifndef _trace_winnet_h_
#define _trace_winnet_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/
#define TRACE_NET_ADDRESS                      "192.168.100.3"
#define TRACE_NET_PORT                         8080

#define TRACE_OUTPUT_BUFFER_SIZE                2048
#define TRACE_FUNCTION_NAME_LENGTH              60

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
extern int
TraceIndent;

extern char
TraceOutputBuffer[TRACE_OUTPUT_BUFFER_SIZE +1];

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void
TraceSocketClose
(int InSocket);

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TRACE_FUNCTION_INIT()                                                                       \
    int                                 sockfd;                                                     \
    WSADATA                             MainWinsockData;                                            \
    struct sockaddr_in                  servaddr;                                                   \
    WSAStartup(MAKEWORD(2, 2), &MainWinsockData);                                                   \
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);                                                        \
    memset(&servaddr, 0, sizeof(servaddr));                                                         \
    servaddr.sin_family = AF_INET;                                                                  \
    servaddr.sin_port = htons(TRACE_NET_PORT);                                                      \
    servaddr.sin_addr.s_addr = inet_addr(TRACE_NET_ADDRESS);                                        \

#define TRACE_FUNCTION_SEND()                                                                       \
    sendto(sockfd, (const char *)TraceOutputBuffer, strlen(TraceOutputBuffer),                      \
           0, (const struct sockaddr *) &servaddr,                                                  \
           sizeof(servaddr));                                                                       \

#define TRACE_FUNCTION_FINISH()                                                                     \
    TraceSocketClose(sockfd);                                                                       \
    WSACleanup();                                                                                   \
  
#define TRACE_FUNCTION_START()                                                                      \
  {                                                                                                 \
    TRACE_FUNCTION_INIT()                                                                           \
    TraceIndent++;                                                                                  \
    sprintf(TraceOutputBuffer, "%02d:ENTER:%s:%s:%04d \n",                                          \
            TraceIndent, __FILE__, __FUNCTION__, __LINE__);                                         \
    TRACE_FUNCTION_SEND()                                                                           \
    TRACE_FUNCTION_FINISH()                                                                         \
  }                                                                                                 \
 
//!
#define TRACE_FUNCTION_END()                                                                        \
  {                                                                                                 \
    TRACE_FUNCTION_INIT()                                                                           \
    sprintf(TraceOutputBuffer, "%02d:EXIT:%s:%s:%04d \n",                                           \
            TraceIndent, __FILE__, __FUNCTION__, __LINE__);                                         \
    TRACE_FUNCTION_SEND()                                                                           \
    TraceIndent--;                                                                                  \
    TRACE_FUNCTION_FINISH()                                                                         \
  }                                                                                                 \

//!
#define TRACE_FUNCTION_LOCATION()                                                                   \
  {                                                                                                 \
    TRACE_FUNCTION_INIT()                                                                           \
    sprintf(TraceOutputBuffer, "%02d:LOCATION:%s:%s:%04d \n",                                       \
            TraceIndent, __FILE__, __FUNCTION__, __LINE__);                                         \
    TRACE_FUNCTION_SEND()                                                                           \
    TRACE_FUNCTION_FINISH()                                                                         \
  }                                                                                                 \

//!
#define TRACE_FUNCTION_BOOL(n)                                                                      \
  {                                                                                                 \
    TRACE_FUNCTION_INIT()                                                                           \
    sprintf(TraceOutputBuffer, "%02d:BOOL:%s:%s:%04d:%s = %s \n",                                   \
            TraceIndent, __FILE__, __FUNCTION__, __LINE__, #n, n ? "TRUE" : "FALSE");               \
    TRACE_FUNCTION_SEND()                                                                           \
    TRACE_FUNCTION_FINISH()                                                                         \
  }                                                                                                 \

//!
#define TRACE_FUNCTION_INT(n)                                                                       \
  {                                                                                                 \
    TRACE_FUNCTION_INIT()                                                                           \
    sprintf(TraceOutputBuffer, "%02d:INT:%s:%s:%04d:%s = %d \n",                                    \
            TraceIndent, __FILE__, __FUNCTION__, __LINE__, #n, n);                                  \
    TRACE_FUNCTION_SEND()                                                                           \
    TRACE_FUNCTION_FINISH()                                                                         \
  }

//!
#define TRACE_FUNCTION_HEX(n)                                                                       \
  {                                                                                                 \
    TRACE_FUNCTION_INIT()                                                                           \
    sprintf(TraceOutputBuffer, "%02d:INT:%s:%s:%04d:%s = 0x%08X \n",                                \
            TraceIndent, __FILE__, __FUNCTION__, __LINE__, #n, (int)n);                             \
    TRACE_FUNCTION_SEND()                                                                           \
    TRACE_FUNCTION_FINISH()                                                                         \
  }

//!
#define TRACE_FUNCTION_STRING(n)                                                                    \
  {                                                                                                 \
    TRACE_FUNCTION_INIT()                                                                           \
    sprintf(TraceOutputBuffer, "%02d:STRING:%s:%s:%04d:%s = \"%s\" \n",                             \
            TraceIndent, __FILE__, __FUNCTION__, __LINE__, #n, n);                                  \
    TRACE_FUNCTION_SEND()                                                                           \
    TRACE_FUNCTION_FINISH()                                                                         \
  }                                                                                                 \

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _trace_winnet_h_*/
