#include <stdatomic.h>
unsigned char *uart = (unsigned char *)0x10000000;
unsigned char *uart_lsr = (unsigned char *)0x10000005;

int strcmp(const char *s1, const char *s2)
{
  while (*s1 && (*s1 == *s2))
  {
    s1++;
    s2++;
  }
  return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void print(const char *str)
{
  while (*str != '\0')
  {

    while ((*uart_lsr & 0x20) == 0)
    {
      // polling
    }

    *uart = *str;
    str++;
  }
}

char getc(void)
{
  while ((*uart_lsr & 0x01) == 0)
  {
  }
  return *uart;
}
void kmain(void)
{
  const char *str = "welcome to faisal's operating system\n\r";
  print(str);
  char input_buffer[64];
  int index = 0;
  while (1)
  {
    char c = getc();

    // remove letter from screen
    if (c == '\b' || c == 127)
    {
      if (index > 0)
      {
        index--;
        print("\b \b");
      }
      continue;
    }

    // enter

    if (c == '\r')
    {
      print("\r\n");
      input_buffer[index] = '\0';

      if (strcmp(input_buffer, "help") == 0)
      {
        print("system commands: help, clear\r\n");
      }
      else if (strcmp(input_buffer, "clear") == 0)
      {
        print("\x1B[2J\x1B[H");
        index = 0;
        continue;
      }
      else
      {
        print("command not found: ");
        print(input_buffer);
        print("\r\n");
      }
      // print("you typed: ");
      // print(input_buffer);

      index = 0;
      continue;
    }

    if (index < 63)
    {
      input_buffer[index] = c;
      index++;
      char echo_str[2] = {c, '\0'};
      print(echo_str);
    }
  }
}

// void putchar(char c) {
//   *uart = c;
//   return;
// }
//
// void print(const char *str) {
//   while (*str != '\0') {
//     putchar(*str);
//     str++;
//   }
//   return;
// }
//
// void kmain(void) {
//   print("Hello world!\r\n");
//   while (1) {
//     // Read input from the UART
//     putchar(*uart);
//   }
//   return;
// }
