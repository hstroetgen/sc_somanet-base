/*
 * config_parser.xc
 *
 * Read / write device configuration from / to CSV file via SPIFFS
 *
 * Dmytro Dotsenko <ddotsenko@synapticon.com>
 *
 * 2017 Synapticon GmbH
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <safestring.h>
#include <syscall.h>
#include <xccompat.h>
#include <flash_service.h>
#include <spiffs_service.h>
#include <canod_datatypes.h>
#include <config_parser.h>
#include <print.h>



struct _token_t {
  size_t count;
  char token[MAX_NODES_COUNT][MAX_TOKEN_SIZE];
};



static size_t get_token_count(char *buf, size_t bufsize)
{
  size_t separator = 0;
  char *c = buf;

  for (size_t i = 0; i < bufsize && *c != '\0'; i++, c++) {
    if (*c == ',') {
      separator++;
    }
  }

  return (separator + 1);
}



static int tokenize_inbuf(char *buf, size_t bufsize, struct _token_t *token)
{
  char sep = ',';
  int tok_pos, last_tok_pos = 0;

  size_t tokenitem = 0;
  token->count = get_token_count(buf, bufsize);

  if (token->count > MAX_NODES_COUNT) return -1;

  while ((tok_pos = safestrchr(buf + last_tok_pos, sep)) > 0) {
    strncpy((token->token[tokenitem]), buf + last_tok_pos, tok_pos);
    token->token[tokenitem][tok_pos] = '\0';
    last_tok_pos += tok_pos + 1;
    tokenitem++;
    if (tokenitem > MAX_NODES_COUNT) return -1;
  }

  strncpy((token->token[tokenitem]), buf + last_tok_pos, sizeof(buf + last_tok_pos));
  token->token[tokenitem][sizeof(buf + last_tok_pos)] = '\0';
  return 0;
}


static uint32_t parse_token(char *token_str, uint8_t type)
{
    unsafe {
        char * unsafe str_end[1];

        union parser_sdo_value value;

        value.i = (uint32_t)strtol(token_str, str_end, 0);

        if (*(str_end[0]) == '.' && isdigit(*(str_end[0]+1))) {
            // we found a dot, parse as float value
            sscanf(token_str, "%f", &(value.f));
            if (!type) { //object is int type, convert value
                value.i = (uint32_t)value.f;
            }
        } else {
            if (type) { //object is float type, convert value
                value.f = (float)value.i;
            }
        }


        return value.i;
    }
}

static void parse_token_for_node(struct _token_t *tokens, Param_t *param,
                                 size_t node, client interface i_co_communication i_canopen)
{
  param->index    = (uint16_t) parse_token(tokens->token[0], 0);
  param->subindex = (uint8_t)  parse_token(tokens->token[1], 0);

  struct _sdoinfo_entry_description od_entry;
  {od_entry, void} = i_canopen.od_get_entry_description(param->index, param->subindex);
  if (od_entry.dataType == DEFTYPE_REAL32) {
      param->value    = (uint32_t) parse_token(tokens->token[2 + node], 1);
  } else {
      param->value    = (uint32_t) parse_token(tokens->token[2 + node], 0);
  }
}


#pragma stackfunction  50
int read_config(char path[], ConfigParameter_t *parameter, client SPIFFSInterface i_spiffs, client interface i_co_communication i_canopen)
{

  int retval = 0;
  if (parameter == NULL) {
    return -1;
  }

  int cfd = i_spiffs.open_file(path, strlen(path), SPIFFS_RDONLY);
  if (cfd < 0) {
    return -1;
  }

  struct _token_t t;
  int param_count = 0;

  char inbuf[MAX_INPUT_LINE];
  size_t inbuf_length = 0;
  char c[1];

  /* read file and tokenize */

  while ((retval = i_spiffs.read(cfd, c, 1)) > 0) {
    if (c[0] == '#') {
      while (c[0] != '\n') {
         retval = i_spiffs.read(cfd, c, 1);
         if (retval < 0)
         {
             i_spiffs.close_file(cfd);
             return retval;
         }
      }
    }

    if (c[0] == '\n') {
      if (inbuf_length > 1) {
        inbuf[inbuf_length++] = '\0';
        if (tokenize_inbuf(inbuf, inbuf_length, &t) != 0) return -1;
        for (size_t node = 0; node < t.count - 2; node++) {
            parse_token_for_node(&t, &parameter->parameter[param_count][node], node, i_canopen);
        }

        param_count++;
      }

      inbuf_length = 0;
      continue;
    }

    if (c[0] == ' ' ||
        c[0] == '\t') {
      continue;
    }

    inbuf[inbuf_length] = (char)c[0];
    inbuf_length++;
  }

  if ((retval < 0)&&(retval != SPIFFS_EOF))
  {
      i_spiffs.close_file(cfd);
      return retval;
  }

  retval = i_spiffs.close_file(cfd);
  if ( retval < 0) {
    return retval;
  }

  parameter->param_count = param_count;
  parameter->node_count  = t.count - 2;
  if (parameter->node_count == 0 || parameter->param_count == 0) {
    retval = 0;
  }

  return retval;
}




int write_config(char path[], ConfigParameter_t *parameter, client SPIFFSInterface i_spiffs, client interface i_co_communication i_canopen)
{

  int retval = 0;
  if (parameter == NULL) {
    return -1;
  }

  char line_buf[255];
  int cfd = i_spiffs.open_file(path, strlen(path), (SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR));
  if (cfd < 0) {
    return -1;
  }


   for (size_t param = 0; param < parameter->param_count; param++) {
          uint16_t index = parameter->parameter[param][0].index;
          uint8_t subindex = parameter->parameter[param][0].subindex;

          safememset(line_buf, 0, sizeof(line_buf));
          sprintf(line_buf, "0x%x,  %3d", index, subindex);

          for (size_t node = 0; node < parameter->node_count; node++) {
              union parser_sdo_value value;
              value.i = parameter->parameter[param][node].value;

              struct _sdoinfo_entry_description od_entry;
              {od_entry, void} = i_canopen.od_get_entry_description(index, subindex);

              if (od_entry.dataType == DEFTYPE_REAL32) {
                  sprintf(line_buf + strlen(line_buf), ", %f", value.f);
              } else {
                  sprintf(line_buf + strlen(line_buf), ", %12d", value.i);
              }
          }
          line_buf[strlen(line_buf)]='\n';

          retval = i_spiffs.write(cfd, line_buf, strlen(line_buf));
          if (retval < 0)
          {
              i_spiffs.close_file(cfd);
              return retval;
          }

  }

  retval = i_spiffs.close_file(cfd);
  if ( retval < 0) {
    return retval;
  }


  return retval;
}

