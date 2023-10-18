/**
 * \file skeleton.c
 * \brief Basic parsing options skeleton.
 * \author Pierre L. <pierre1.leroy@orange.com>
 * \version 0.1
 * \date 10 septembre 2016
 *
 * Basic parsing options skeleton exemple c file.
 */

#include "skeleton.h"

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
 * Print method to display information in the console in blue color
 * \param message the message to display
 * \param ... list of args
 * \return void
*/
void print_info(const char* message, ...)
{
  va_list args;
  va_start(args, message);
  printf("\033[1;34m");
  vprintf(message, args);
  printf("\033[0m");
  va_end(args);  
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
    // Exiting with a failure ERROR CODE (== 1)
    exit(EXIT_FAILURE);
  }

  // Printing params
  dprintf(1, "** PARAMS **\n%-8s: %s\n%-8s: %s\n%-8s: %d\n", 
          "input",   bin_input_param, 
          "output",  bin_output_param, 
          "verbose", is_verbose_mode);

  printf("** COMMAND **\nmethod  : %s\n", bin_command);

  int result = 0;
  if(strcmp(bin_command, "copy") == 0)
  {
    result = copy_file(bin_input_param, bin_output_param);
  }
  else if(strcmp(bin_command, "reverse") == 0)
  {
    result = reverse_file(bin_input_param);
  }
  else if(strcmp(bin_command, "ls") == 0)
  {
    result = ls_command(bin_input_param);
  }
  else
  {
    printf("Unknown command\n");
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    exit(EXIT_FAILURE);
  }

  if(result != 0)
  {
    printf("Error while executing command\n");
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    exit(EXIT_FAILURE);
  }

  // Freeing allocated data
  free_if_needed(bin_input_param);
  free_if_needed(bin_output_param);

  return EXIT_SUCCESS;
}

/**
 * The copy_file function copies the content of a file to another.
 * \param bin_input_param: the path of the input file to copy
 * \param bin_output_param: the path of the output file
 * \return 0 if it exit successfully
 * 
 * ./bin/skeleton copy -i <input> -o <output>
*/
int copy_file(char* bin_input_param, char* bin_output_param)
{
  int f1_src = open(bin_input_param, O_RDONLY);
  if (f1_src == -1) {
      perror("Erreur lors de l'ouverture du fichier source");
      return errno;
  }

  /**
  * Memo for me : 
  * O_CREAT : créer le fichier s'il n'existe pas
  * O_WRONLY : ouvrir le fichier en écriture
  * O_TRUNC : vider le fichier s'il existe déjà
  * 0755 : les droits sont en octal
  */
  int f2_dest = open(bin_output_param, O_CREAT | O_WRONLY | O_TRUNC, 0755);
  if (f2_dest == -1) {
      perror("Erreur lors de la création du fichier de destination");
      close(f1_src);
      return errno;
  }

  char* buffer = malloc(sizeof(char)*4096); // 1 octet = un caractère ASCII = 1 byte = 8 bits
  ssize_t bytes_read;
  ssize_t bytes_written;

  /**
   *  ssize_t read(int fd, void *buf, size_t count);
   * fd : file descriptor
   * buf : buffer dans lequel on va stocker les données lues
   * count : nombre d'octets à lire = je dis de lire 1024 octetst à chaque fois
   * \return le nombre de données réellement lues grâce au buffer
   */

  /**
   *  ssize_t write(int fd, const void *buf, size_t count);
   * fd : file descriptor
   * buf : buffer dans lequel on va stocker les données à écrire
   * count : nombre d'octets à écrire = je dis de écrire 1024 octets à chaque fois
   * \return le nombre de données réellement lues grâce au buffer
   */

  while ((bytes_read = read(f1_src, buffer, 4096)) > 0) {
      bytes_written = write(f2_dest, buffer, bytes_read);
      if (bytes_written != bytes_read) { 
          perror("Erreur lors de l'écriture dans le fichier de destination");
          free(buffer);
          close(f1_src);
          close(f2_dest);
          return errno;
      }
  }

  if (bytes_read == -1) {
      perror("Erreur lors de la lecture du fichier source");
      close(f1_src);
      close(f2_dest);
      free(buffer);
      return errno;
  }

  close(f1_src);
  close(f2_dest);
  free(buffer);

  print_info("Copie du fichier terminée.\n");
  print_info("Le fichier de destination se trouve ici : %s\n", bin_output_param);
  return 0;
}


/**
 * The reverse_file function reverses the content of a file.
 * \param bin_input_param: the path of the input file to reverse
 * \return 0 if it exit successfully
 * 
 * ./bin/skeleton reverse -i <input> -o <output>
*/
int reverse_file(char* bin_input_param)
{
  int input_fd = open(bin_input_param, O_RDONLY);

  if (input_fd == -1)
  {
      perror("Error opening input file");
      return -1;
  }

  /**
   * off_t lseek(int __fd, off_t __offset, int __whence)
   * __fd : file descriptor
   * __offset : décalage à partir duquel on veut se positionner
   * __whence : position à partir de laquelle on veut se positionner
   * 
   * off_t = long int
   * 
   * \return la nouvelle position du curseur
  */
  off_t file_size = lseek(input_fd, 0, SEEK_END);
  
  if (file_size == -1)
  {
      perror("Error seeking to end of file");
      close(input_fd);
      return -1;
  }

  // Parcourez le fichier à l'envers
  for (off_t pos = file_size - 1; pos >= 0; pos--)
  {
      if (lseek(input_fd, pos, SEEK_SET) == -1)
      {
          perror("Error seeking to position in file");
          close(input_fd);
          return -1;
      }

      char c;
      if (read(input_fd, &c, 1) == -1)
      {
          perror("Error reading from file");
          close(input_fd);
          return -1;
      }

      // Écriture du caractère inversé sur la sortie standard
      if (write(STDOUT, &c, 1) == -1)
      {
          perror("Error writing to STDOUT");
          close(input_fd);
          return -1;
      }
  }

  close(input_fd);
  print_info("\nReverse done\n");
  return 0;
}



/**
 * The ls_command function lists the metadata of files in a directory tree.
 * \param bin_input_param: the path of the directory to list
 * \return 0 if it exits successfully
 * 
 * ./bin/skeleton ls -i <input> -o <output>
*/
int ls_command(char* bin_input_param)
{
  DIR* dir = opendir(bin_input_param);

  if (dir == NULL)
  {
    perror("Error opening directory");
    return errno;
  }

  struct dirent* entry;
  struct stat file_stat;
  struct passwd* pw;
  struct group* gr;
  struct tm* tm_info;
  char date_str[20];

  while ((entry = readdir(dir)) != NULL)
  {
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", bin_input_param, entry->d_name);

    if (stat(file_path, &file_stat) == -1)
    {
      perror("Error getting file stats");
      continue;
    }

    // File name
    printf("%s\t", entry->d_name);

    // Permissions
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t");

    // Owner
    if ((pw = getpwuid(file_stat.st_uid)) != NULL)
    {
      printf("%s\t", pw->pw_name);
    }
    else
    {
      printf("%d\t", file_stat.st_uid);
    }

    if ((gr = getgrgid(file_stat.st_gid)) != NULL)
    {
      printf("%s\t", gr->gr_name);
    }
    else
    {
      printf("%d\t", file_stat.st_gid);
    }

    printf("%ld\t", file_stat.st_size); 

    tm_info = localtime(&file_stat.st_mtime);  // Last modification date
    strftime(date_str, sizeof(date_str), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("%s\n", date_str);
  }

  closedir(dir);
  return 0;
}