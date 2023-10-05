/**
 * \file skeleton.c
 * \brief Basic parsing options skeleton.
 * \author Pierre L. <pierre1.leroy@orange.com>
 * \version 0.1
 * \date 10 septembre 2016
 *
 * Basic parsing options skeleton exemple c file.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<getopt.h>


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
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}


/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* to_free pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void free_if_needed(void* to_free)
{
  if (to_free != NULL) free(to_free);  
}


/**
 *
 * \see man 3 strndup
 * \see man 3 perror
 * \return
 */
char* dup_optarg_str()
{
  char* str = NULL;

  if (optarg != NULL)
  {
    str = strndup(optarg, MAX_PATH_LENGTH);
    
    // Checking if ERRNO is set
    if (str == NULL) 
      perror(strerror(errno));
  }

  return str;
}


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



/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  /**
   * Binary variables
   * (could be defined in a structure)
   */
  char* bin_command = argv[1];
  short int is_verbose_mode = 0;
  char* bin_input_param = NULL;
  char* bin_output_param = NULL;

  // Parsing options
  int opt = -1;
  int opt_idx = -1;

  while ((opt = getopt_long(argc, argv, binary_optstr, binary_opts, &opt_idx)) != -1)
  {
    switch (opt)
    {
      case 'i':
        //input param
        if (optarg)
        {
          bin_input_param = dup_optarg_str();         
        }
        break;
      case 'o':
        //output param
        if (optarg)
        {
          bin_output_param = dup_optarg_str();
        }
        break;
      case 'v':
        //verbose mode
        is_verbose_mode = 1;
        break;
      case 'h':
        print_usage(argv[0]);

        free_if_needed(bin_input_param);
        free_if_needed(bin_output_param);
        free_if_needed(bin_command);
 
        exit(EXIT_SUCCESS);
      
      default :
        break;
    }
  } 

  /**
   * Checking binary requirements
   * (could defined in a separate function)
   */
  if (bin_input_param == NULL || bin_output_param == NULL)
  {
    dprintf(STDERR, "Bad usage! See HELP [--help|-h]\n");

    // Freeing allocated data
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    free_if_needed(bin_command);
    // Exiting with a failure ERROR CODE (== 1)
    exit(EXIT_FAILURE);
  }

  printf("** COMMAND **\n%s\n", bin_command);

  // Printing params
  dprintf(1, "** PARAMS **\n%-8s: %s\n%-8s: %s\n%-8s: %d\n", 
          "input",   bin_input_param, 
          "output",  bin_output_param, 
          "verbose", is_verbose_mode);


  // Switch case on command
  int result = 0;
  if(strcmp(bin_command, "copy") == 0)
  {
    printf("Copy\n");
    result = copy_file(bin_input_param, bin_output_param);
  }
  else if(strcmp(bin_command, "reverse") == 0)
  {
    printf("reverse\n");
  }
  else if(strcmp(bin_command, "ls") == 0)
  {
    printf("ls\n");
  }
  else
  {
    printf("Unknown command\n");
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    free_if_needed(bin_command);
    exit(EXIT_FAILURE);
  }

  if(result != 0)
  {
    printf("Error while executing command\n");
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    free_if_needed(bin_command);
    exit(EXIT_FAILURE);
  }

  // Freeing allocated data
  free_if_needed(bin_input_param);
  free_if_needed(bin_output_param);
  free_if_needed(bin_command);

  return EXIT_SUCCESS;
}

/**
 * The copy_file function copies the content of a file to another.
 * \param bin_input_param: the path of the input file to copy
 * \param bin_output_param: the path of the output file
*/
int copy_file(char* bin_input_param, char* bin_output_param)
{

}
