//
//  RA_Types.h
//  RASketch
//
//  Created by Rinat Abdrashitov on 2014-09-26.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#ifndef RASketch_RA_Types_h
#define RASketch_RA_Types_h

#if (defined(__APPLE__) && (defined(__GNUC__) ||\
defined(__xlC__) || defined(__xlc__))) || defined(__MACOS__)
#  if (defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__IPHONE_OS_VERSION_MIN_REQUIRED))
#    define RA_OS_IPHONE
#  else
#    define RA_OS_DARWIN
#    define RA_OS_MAC
#  endif
#elif (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define RA_OS_WIN32
#elif (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  define RA_OS_WIN32
#elif defined(__linux__) || defined(__linux)
#  define RA_OS_LINUX
#else
#  define RA_OS_OTHER
#endif


#endif
