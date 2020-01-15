// (C) 2020 jacekms
// This code is licensed under Apache 2.0 license (see LICENSE for details)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=============================================================================
typedef struct
{
  int w, h;
  char data[5][12];
} Mark;

//=============================================================================
Mark marks[256];

//=============================================================================
int txtart_load_font(const char* file_dir)
{
  char sline[255];
  int h = 5;

  FILE *f = fopen(file_dir, "rt");
  if (!f) {printf("ERROR open font.txt\n"); return 1;}

  static const int first_char = '!';
  static const int last_char  = '~';
  for (int ch=first_char; ch<=last_char; ++ch)
  {
    int max_len = 0;
    for (int i=0; i<h; ++i)
    {
      fgets(sline, 255, f);

      int str_len = strlen(sline);
      if (sline[str_len-1] == '\n') { sline[str_len-1] = '\0'; }

      strcpy(marks[ch].data[i], sline);
      str_len = strlen(sline);
      if (str_len > max_len) max_len = str_len;
      marks[ch].w = max_len;
    }
  }

  for (int i=0; i<h; ++i)
  {
    strcpy(sline, "     ");
    char ch = ' ';
    strcpy(marks[ch].data[i], sline);
    marks[ch].w = 5;
  }

  for (int ch=first_char; ch<=last_char; ++ch)
  {
    for (int i=0; i<h; ++i)
    {
      int str_len = strlen(marks[ch].data[i]);
      for (int sp=0; sp<marks[ch].w - str_len; ++sp) strcat(marks[ch].data[i], " ");
    }
  }
  return 0;
}

//=============================================================================
char *txtart_get_str(const char *str, int compress, const char *separator, int sep_len)
{
  static char buf[1024] = {0};
  memset(buf, 0x00, 1024);
  char bu[5][1024/5] = {0};
  int last_char = strlen(str)-1;
  int start = 0;

  int k = 0;

  for (int i=0; i<=last_char; ++i) //iterate string to convert
  {
    for (int r=0; r<5; ++r)
    {
      int c=0;
      for (; marks[str[i]].data[r][c] != 0; ++c)
      {

        if (compress < 0)
        {
          if (bu[r][c+start] == 0 || bu[r][c+start] == ' ') {
            bu[r][c+start] = marks[str[i]].data[r][c];
          }
        } else
        {
          if (marks[str[i]].data[r][c] == ' ')
          {
            if (bu[r][c+start] == 0) bu[r][c+start] = ' ';
          }
          else
          {
            bu[r][c+start] = marks[str[i]].data[r][c];
          }
        }
      }

      if (separator != NULL) { //separator
        for (int i=0; i<sep_len; ++i)
          bu[r][c+i +start] = separator[i];
      }
    }
    start += (marks[str[i]].w-abs(compress));
    if (separator != NULL) { start += sep_len; } //separator
  }

  for (int r=0; r<5; ++r)
  {
    strcat(buf, bu[r]);
    strcat(buf, "\n");
  }

  return buf;
}

