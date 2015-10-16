/*
 * Copyright (c) 2013-2015, Christian Ferrari <tiian@users.sourceforge.net>
 * All rights reserved.
 *
 * This file is part of FLoM.
 *
 * FLoM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * FLoM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FLoM.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <config.h>



#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif



#include "flom_config.h"
#include "flom_errors.h"
#include "flom_debug_features.h"
#include "flom_trace.h"



/* set module trace flag */
#ifdef FLOM_TRACE_MODULE
# undef FLOM_TRACE_MODULE
#endif /* FLOM_TRACE_MODULE */
#define FLOM_TRACE_MODULE   FLOM_TRACE_MOD_DEBUG_FEATURES



const char *FLOM_DEBUG_FEATURES_IPV6_MULTICAST_SERVER = _DEBUG_FEATURES_IPV6_MULTICAST_SERVER;
const char *FLOM_DEBUG_FEATURES_IPV6_MULTICAST_CLIENT = _DEBUG_FEATURES_IPV6_MULTICAST_CLIENT;



int flom_debug_features(const char *name)
{
    enum Exception { INVALID_OPTION
                     , NONE } excp;
    int ret_cod = FLOM_RC_INTERNAL_ERROR;
    
    FLOM_TRACE(("flom_debug_features\n"));
    TRY {
        FLOM_TRACE(("flom_debug_features: name='%s'\n", name));

        if (0 == strcasecmp(name, FLOM_DEBUG_FEATURES_IPV6_MULTICAST_SERVER))
            ret_cod = flom_debug_features_ipv6_multicast_server();
        else if (0 == strcasecmp(name,
                                 FLOM_DEBUG_FEATURES_IPV6_MULTICAST_CLIENT))
            ret_cod = flom_debug_features_ipv6_multicast_client();
        else {
            FLOM_TRACE(("flom_debug_features: debug feature '%s' "
                        "is not available\n", name));
            THROW(INVALID_OPTION);
        }
                    
        THROW(NONE);
    } CATCH {
        switch (excp) {
            case NONE:
                break;
            case INVALID_OPTION:
                ret_cod = FLOM_RC_INVALID_OPTION;
                break;
            default:
                ret_cod = FLOM_RC_INTERNAL_ERROR;
        } /* switch (excp) */
    } /* TRY-CATCH */
    FLOM_TRACE(("flom_debug_features/excp=%d/"
                "ret_cod=%d/errno=%d\n", excp, ret_cod, errno));
    return ret_cod;
}



int flom_debug_features_ipv6_multicast_server(void)
{
    enum Exception { NONE } excp;
    int ret_cod = FLOM_RC_INTERNAL_ERROR;
    
    FLOM_TRACE(("flom_debug_features_ipv6_multicast_server\n"));
    TRY {
        char port[10];
        struct addrinfo hints;

        /* prepare port for getaddrinfo(...) */
        snprintf(port, sizeof(port), "%u",
                 flom_config_get_multicast_port(NULL));
        FLOM_TRACE(("flom_debug_features_ipv6_multicast_server: "
                    "multicast address='%s', multicast port=%s\n",
                    STRORNULL(flom_config_get_multicast_address(NULL)),
                    port));

        /* prepare hints for getaddrinfo(...) */
        memset(&hints, 0, sizeof(hints));
        hints.ai_flags = AI_CANONNAME;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;

        /* @@@ going on with code from flom_listen_udp... */
        
        THROW(NONE);
    } CATCH {
        switch (excp) {
            case NONE:
                ret_cod = FLOM_RC_OK;
                break;
            default:
                ret_cod = FLOM_RC_INTERNAL_ERROR;
        } /* switch (excp) */
    } /* TRY-CATCH */
    FLOM_TRACE(("flom_debug_features_ipv6_multicast_server/excp=%d/"
                "ret_cod=%d/errno=%d\n", excp, ret_cod, errno));
    return ret_cod;
}



int flom_debug_features_ipv6_multicast_client(void)
{
    enum Exception { NONE } excp;
    int ret_cod = FLOM_RC_INTERNAL_ERROR;
    
    FLOM_TRACE(("flom_debug_features_ipv6_multicast_client\n"));
    TRY {
        
        THROW(NONE);
    } CATCH {
        switch (excp) {
            case NONE:
                ret_cod = FLOM_RC_OK;
                break;
            default:
                ret_cod = FLOM_RC_INTERNAL_ERROR;
        } /* switch (excp) */
    } /* TRY-CATCH */
    FLOM_TRACE(("flom_debug_features_ipv6_multicast_client/excp=%d/"
                "ret_cod=%d/errno=%d\n", excp, ret_cod, errno));
    return ret_cod;
}

