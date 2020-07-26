#ifndef _SHELL_H_
#define _SHELL_H_

#include <efi.h>
#include <efilib.h>
#include "graphics.h"
#include "gui.h"
#include "file.h"

#define MAX_COMMAND_LEN  256
#define FILE_BUFFER_SIZE 4096

void shell();
void rect();
void pstat();
void ls();
void cat(CHAR16 *filename);

#endif
