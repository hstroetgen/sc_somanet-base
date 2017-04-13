#pragma once

#include <xs1.h>

/**
 * @brief Type for COM boards enumeration
 *
 * There are 12 possible communication (COM) modules that can be identified.
 * The configuration is done in hardware and read via a dedicated COM-detect port
 */
typedef enum {
    COM_DETECT_IS_NONE,         /* very short delay */
    COM_DETECT_IS_RESERVED0,
    COM_DETECT_IS_ETHERCAT,
    COM_DETECT_IS_RESERVED2,
    COM_DETECT_IS_RESERVED3,
    COM_DETECT_IS_RESERVED4,
    COM_DETECT_IS_RESERVED5,
    COM_DETECT_IS_RESERVED6,
    COM_DETECT_IS_RESERVED7,
    COM_DETECT_IS_RESERVED8,
    COM_DETECT_IS_RESERVED9,
    COM_DETECT_IS_RESERVED10,
    COM_DETECT_IS_RESERVED11,
    COM_DETECT_IS_UNKNOWN       /* delay beyond detection limit */
} com_module_type_t;

/**
 * @brief COM module detection method
 *
 * @param p COM-detect port
 * @return com_module_type_t - detected board enumeration
 */
com_module_type_t com_detect(port p);
