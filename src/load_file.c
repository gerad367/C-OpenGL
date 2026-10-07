#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

char* load_file(const char* filename) {
  struct stat file_stat;
  char *pos, *buff;
  int bytes_read;

  int file = open(filename, O_RDONLY);
  if (file < 0) goto load_error;

  int status = fstat(file, &file_stat);
  if (status != 0) goto load_error;

  buff = malloc(file_stat.st_size + 1);
  if (buff == 0) goto load_error;
  pos = buff;

  int remaining = file_stat.st_size;
  int block_size = file_stat.st_blksize;

  while (remaining > block_size) {
    bytes_read = read(file, pos, block_size);
    if (bytes_read != block_size) goto load_error;
    pos += block_size;
    remaining -= block_size;
  }

  if (remaining) {
    bytes_read = read(file, pos, remaining);
    if (bytes_read != remaining) goto load_error;
  }

  *(pos+remaining) = '\0';

  close(file);
  return buff;

load_error:
  fprintf(stderr, "Error loading the file in memory\n");
  return NULL;
}
