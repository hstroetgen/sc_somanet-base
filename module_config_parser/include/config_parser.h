/*
 * config_parser.h
 *
 * Read / write device configuration from / to CSV file via SPIFFS
 *
 * Dmytro Dotsenko <ddotsenko@synapticon.com>
 *
 * 2017 Synapticon GmbH
 */

#pragma once

#include <stdint.h>
#include <co_interface.h>

/**
 * \brief Max length of one line in config file
 */
#define MAX_INPUT_LINE    255

/**
 * \brief Max length of one token in config file
 */
#define MAX_TOKEN_SIZE    15

/**
 * \brief Max nodes count in OD
 */
#define MAX_NODES_COUNT 3

/**
 * \brief Max parameters count in OD
 */
#define MAX_PARAMS_COUNT 160

/**
 * \brief Structure describing a individual parameter
 */
typedef struct {
  uint16_t index;      ///< Index of the associated object in the object dictionary
  uint8_t  subindex;   ///< Subindex of this object
  uint32_t value;      ///< Value of the container
} Param_t;

typedef struct {
  size_t node_count;       ///< Number of nodes in the config parameters file, this value needs to be checked against the real number of nodes on the bus
  size_t param_count;      ///< Number of configuration parameters, aka non commented lines in the config file
  Param_t parameter[MAX_PARAMS_COUNT][MAX_NODES_COUNT];  ///< array of node_count x param_count of configuration parameters, for every node is a list of SdoParam_t objects.
} ConfigParameter_t;

/**
 * \brief To convert uint32 value to float
 */
union parser_sdo_value {
   uint32_t i;
   float f;
};

/**
 * \brief Function to read configuration file and parse the content
 *
 * \i_spiffs          Client interface for SPIFFS service
 * \param path        Filename with full path of the file to process
 * \param parameter   Pointer to a \c ConfigParameter_t object
 * \return            0 if no error
 */
int read_config(char path[], ConfigParameter_t *parameter, client SPIFFSInterface i_spiffs, client interface i_co_communication i_canopen);

/**
 * \brief Function to generate data from OD to configuration file in csv (text) format
 *
 * \i_spiffs       Client interface for SPIFFS service
 * \param path     Filename with full path of the file to process
 * \param params   Pointer to a \c ConfigParameter_t object
 * \return         0 if no error
 */
int write_config(char path[], ConfigParameter_t *parameter, client SPIFFSInterface i_spiffs, client interface i_co_communication i_canopen);

