#ifndef _SHELL_H_
#define _SHELL_H_

#define IMG_WIDTH  368
#define IMG_HEIGHT 425

void dialogue_get_filename(int idx);
void pstat(void);
int ls(void);
void cat(unsigned short *file_name);
void edit(unsigned short *file_name);
void view(unsigned short *img_name, unsigned int width, unsigned int height);
void shell(void);

#endif
