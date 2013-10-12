/*
 * Copyright (c) 2009-2012, Christian Ferrari <tiian@users.sourceforge.net>
 * All rights reserved.
 *
 * This file is part of FLOM.
 *
 * FLOM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * FLOM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FLOM.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <config.h>



#ifdef HAVE_STDARG_H
# include <stdarg.h>
#endif
#ifdef HAVE_STDIO_H
# include <stdio.h>
#endif
#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_GLIB_H
# include <glib.h>
#endif



#include "flom_trace.h"



int flom_trace_initialized = FALSE;

unsigned long flom_trace_mask = 0;

FILE *trace_file = NULL;


/**
 * This mutex is used to avoid contention (bad output) on trace file
 */
GStaticMutex flom_trace_mutex = G_STATIC_MUTEX_INIT;



/**
 * Initialize the library when the library is loaded.
 */
void flom_trace_init(const char *filename)
{
    /* initialize thread system if necessary */
    if (!g_thread_supported ()) g_thread_init(NULL);

    /* lock the mutex */
    g_static_mutex_lock(&flom_trace_mutex);
    if (!flom_trace_initialized) {
        /* retrieve environemnt variable */
        if (getenv(FLOM_TRACE_MASK_ENV_VAR) != NULL)
            flom_trace_mask = strtoul(
                getenv(FLOM_TRACE_MASK_ENV_VAR), NULL, 0);
        else
            flom_trace_mask = 0x0;
        if (NULL == (trace_file = fopen(filename, "w")))
            trace_file = stderr;
        flom_trace_initialized = TRUE;
    }
    /* remove the lock from mutex */
    g_static_mutex_unlock(&flom_trace_mutex);
}



void flom_trace(const char *fmt, ...)
{
    va_list args;
    struct tm broken_time;
    struct timeval tv;
    
    va_start(args, fmt);
#ifdef HAVE_VFPRINTF
    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &broken_time);

    /* lock the mutex */
    g_static_mutex_lock(&flom_trace_mutex);
    /* default header */
    fprintf(trace_file,
            "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%6.6d [" PID_T_FORMAT
            "/%p] ",
            broken_time.tm_year + 1900, broken_time.tm_mon + 1,
            broken_time.tm_mday, broken_time.tm_hour,
            broken_time.tm_min, broken_time.tm_sec, (int)tv.tv_usec,
            getpid(), g_thread_self());
    /* custom message */
    vfprintf(trace_file, fmt, args);
    /* remove the lock from mutex */
    g_static_mutex_unlock(&flom_trace_mutex);
#else
# error "vfprintf is necessary for flom_trace function!"
#endif
    va_end(args);
}



void flom_trace_hex_data(const char *prefix, const byte_t *data,
                         size_t size, FILE *out_stream)
{
    size_t i;
    struct tm broken_time;
    struct timeval tv;
    
#ifdef HAVE_VFPRINTF
    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &broken_time);

    /* lock the mutex */
    g_static_mutex_lock(&flom_trace_mutex);
    /* default header */
    fprintf(out_stream,
            "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%6.6d [" PID_T_FORMAT
            "/%p] %s",
            broken_time.tm_year + 1900, broken_time.tm_mon + 1,
            broken_time.tm_mday, broken_time.tm_hour,
            broken_time.tm_min, broken_time.tm_sec, (int)tv.tv_usec,
            getpid(), g_thread_self(), prefix);
    /* dump data */
    for (i = 0; i < size; ++i) {
        fprintf(out_stream, "%02x ", (data[i] & 0xff));
    } /* for (i = 0; i < size; ++i) */
    /* close trace record */
    fprintf(out_stream, "\n");
    /* remove the lock from mutex */
    g_static_mutex_unlock(&flom_trace_mutex);
#else
# error "vfprintf is necessary for flom_trace_hex_data function!"
#endif
}



void flom_trace_text_data(const char *prefix, const byte_t *data,
                          size_t size, FILE *out_stream)
{
    size_t i;
    struct tm broken_time;
    struct timeval tv;
    
#ifdef HAVE_VFPRINTF
    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &broken_time);

    /* lock the mutex */
    g_static_mutex_lock(&flom_trace_mutex);
    /* default header */
    fprintf(out_stream,
            "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%6.6d ["
            PID_T_FORMAT "/%p] %s",
            broken_time.tm_year + 1900, broken_time.tm_mon + 1,
            broken_time.tm_mday, broken_time.tm_hour,
            broken_time.tm_min, broken_time.tm_sec, (int)tv.tv_usec,
            getpid(), g_thread_self(), prefix);
    /* dump data */
    for (i = 0; i < size; ++i) {
        if (data[i] >= (byte_t)' ' && data[i] < (byte_t)0x80)
            putc((int)(data[i] & 0xff), out_stream);
        else
            putc((int)' ', out_stream);
    } /* for (i = 0; i < size; ++i) */
    /* close trace record */
    fprintf(out_stream, "\n");
    /* remove the lock from mutex */
    g_static_mutex_unlock(&flom_trace_mutex);
#else
# error "vfprintf is necessary for flom_trace_hex_data function!"
#endif
}



