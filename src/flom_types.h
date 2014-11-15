/*
 * Copyright (c) 2013-2014, Christian Ferrari <tiian@users.sourceforge.net>
 * All rights reserved.
 *
 * This file is part of FLoM.
 *
 * FLoM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 2.1 as
 * published by the Free Software Foundation.
 *
 * FLoM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FLoM.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FLOM_TYPES_H
# define FLOM_TYPES_H



/**
 * Lock mode that can be asked for a resource
 */
typedef enum flom_lock_mode_e {
    /**
     * Null lock mode
     */
    FLOM_LOCK_MODE_NL,
    /**
     * Concurrent read lock mode
     */
    FLOM_LOCK_MODE_CR,
    /**
     * Concurrent write lock mode
     */
    FLOM_LOCK_MODE_CW,
    /**
     * Protected read / shared lock mode
     */
    FLOM_LOCK_MODE_PR,
    /**
     * Protected write / update lock mode
     */
    FLOM_LOCK_MODE_PW,
    /**
     * Exclusive lock mode
     */
    FLOM_LOCK_MODE_EX,
    /**
     * Number of lock modes
     */
    FLOM_LOCK_MODE_N,
    /**
     * Special value used to encode an invalid value
     */
    FLOM_LOCK_MODE_INVALID
} flom_lock_mode_t;



#endif /* FLOM_HANDLE_H */