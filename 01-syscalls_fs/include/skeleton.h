#ifndef SKELETON_H
#define SKELETON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <dirent.h>

#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096


#define USAGE_SYNTAX "[COMMAND] [OPTIONS] -i INPUT -o OUTPUT"
#define USAGE_PARAMS "COMMANDS:\n\
  copy : copy a file to another\n\
  reverse : reverse a file text\n\
  ls : \n\
  \n\
OPTIONS:\n\
  -i, --input  INPUT_FILE  : input file\n\
  -o, --output OUTPUT_FILE : output file\n\
***\n\
  -v, --verbose : enable *verbose* mode\n\
  -h, --help    : display this help\n\
"

/**
 * Binary options declaration
 * (must end with {0,0,0,0})
 *
 * \see man 3 getopt_long or getopt
 * \see struct option definition
 */
static struct option binary_opts[] = 
{
  { "help",    no_argument,       0, 'h' },
  { "verbose", no_argument,       0, 'v' },
  { "input",   required_argument, 0, 'i' },
  { "output",  required_argument, 0, 'o' },
  { 0,         0,                 0,  0  } 
};

/**
 * Binary options string
 * (linked to optionn declaration)
 *
 * \see man 3 getopt_long or getopt
 */ 
const char* binary_optstr = "hvi:o:";

void print_usage(char* bin_name);
void print_info(const char* message, ...);
void free_if_needed(void* to_free);
char* dup_optarg_str();
int copy_file(char* bin_input_param, char* bin_output_param);
int reverse_file(char* bin_input_param);
int ls_command(char* bin_input_param);

#endif /* SKELETON_H */