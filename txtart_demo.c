
#include "txtart.c"


//=============================================================================
int main (int argc, char** argv)
{

  if (txtart_load_font()) return 1;
  if (argc == 1)
  {
    printf("use: %s \"text to display\" [compression] [\"separator\"]\n\n", argv[0]);
    printf("examples:\n%s \"abcde ABCDE\"\n", argv[0]);
    printf("%s\n", txtart_get_str("abcde ABCDE", 0, "", 0));
    printf("%s \"abcde ABCDE\" 1 \n", argv[0]);
    printf("%s\n", txtart_get_str("abcde ABCDE", 1, "", 0));
    printf("%s \"abcde ABCDE\" -1 \n", argv[0]);
    printf("%s\n", txtart_get_str("abcde ABCDE", -1, "", 0));
    printf("%s \"abcde ABCDE\" 0 \"  \"\n", argv[0]);
    printf("%s\n", txtart_get_str("abcde ABCDE", 0, "  ", 2));
    printf("%s \"abcde ABCDE\" -2 \n", argv[0]);
    printf("%s\n", txtart_get_str("abcde ABCDE", -2, "", 0));

    return 1;
  }

  const char *str = "TEST";
  int  compress = 0;
  const char *separator = "";

  if (argc > 1) str = argv[1];
  if (argc > 2) compress = atoi(argv[2]);
  if (argc > 3) separator = argv[3];

  printf("%s\n", txtart_get_str(str, compress, separator, strlen(separator)));

  return 0;
}
