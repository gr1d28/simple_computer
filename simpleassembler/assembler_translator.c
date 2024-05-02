#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
translate (char c)
{
  c = tolower (c);
  switch (c)
    {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'a':
      return 10;
    case 'b':
      return 11;
    case 'c':
      return 12;
    case 'd':
      return 13;
    case 'e':
      return 14;
    case 'f':
      return 15;
    }
  return -1;
}

void
send_error (char *str, int str_num, int col)
{
  printf ("%s\n", str);
  for (int i = 0; i < col; i++)
    printf (" ");
  printf ("^\n");
  printf ("Синтаксическая ошибка в строке %d, столбце %d\n", str_num, col);
}

int
check_address (char *address, int size)
{
  int i;
  for (i = 0; i < size; i++)
    {
      if (address[i] < 48 || address[i] > 57)
        return -1;
    }
  if (size < 3)
    address[size] = '\0';
  int addr = atoi (address);
  if (addr < 0 || addr >= 128)
    return -1;
  return addr;
}

int
check_command (char *command, int size)
{
  for (int i = 0; i < size; i++)
    command[i] = toupper (command[i]);
  char nop[4] = { 'N', 'O', 'P', '\0' };
  char cpuinfo[8] = { 'C', 'P', 'U', 'I', 'N', 'F', 'O', '\0' };
  char read[5] = { 'R', 'E', 'A', 'D', '\0' };
  char write[6] = { 'W', 'R', 'I', 'T', 'E', '\0' };
  char load[5] = { 'L', 'O', 'A', 'D', '\0' };
  char store[6] = { 'S', 'T', 'O', 'R', 'E', '\0' };
  char add[4] = { 'A', 'D', 'D', '\0' };
  char sub[4] = { 'S', 'U', 'B', '\0' };
  char divide[7] = { 'D', 'I', 'V', 'I', 'D', 'E', '\0' };
  char mul[4] = { 'M', 'U', 'L', '\0' };
  char jump[5] = { 'J', 'U', 'M', 'P', '\0' };
  char jneg[5] = { 'J', 'N', 'E', 'G', '\0' };
  char jz[3] = { 'J', 'Z', '\0' };
  char halt[5] = { 'H', 'A', 'L', 'T', '\0' };
  char jns[4] = { 'J', 'N', 'S', '\0' };
  char shr[4] = { 'S', 'H', 'R', '\0' };
  char assign[2] = { '=', '\0' };
  char *ex_ch[17];
  int com[17]
      = { 0, 1, 10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43, 55, 60, 2 };
  ex_ch[0] = nop;
  ex_ch[1] = cpuinfo;
  ex_ch[2] = read;
  ex_ch[3] = write;
  ex_ch[4] = load;
  ex_ch[5] = store;
  ex_ch[6] = add;
  ex_ch[7] = sub;
  ex_ch[8] = divide;
  ex_ch[9] = mul;
  ex_ch[10] = jump;
  ex_ch[11] = jneg;
  ex_ch[12] = jz;
  ex_ch[13] = halt;
  ex_ch[14] = jns;
  ex_ch[15] = shr;
  ex_ch[16] = assign;
  if (size < 7)
    command[size] = '\0';
  for (int i = 0; i < 17; i++)
    {
      if (strncmp (ex_ch[i], command, size) == 0)
        return com[i];
    }
  return -1;
}

int
check_operand (char *operand, int size)
{
  if (size <= 3)
    return check_address (operand, size);

  if (size != 5)
    return -1;

  int ans = 0, i = 1, shift = 11, tmp = 0;
  if (operand[0] == '-')
    ans = 0x4000;
  for (int j = 0; j < 4; j++)
    {
      tmp = translate (operand[i]);
      if (j % 2 == 0)
        {
          if (tmp > 0x7 || tmp < 0)
            return -1;
          ans = ans | (tmp << shift);
          shift -= 4;
        }
      else
        {
          if (tmp > 0xf || tmp < 0)
            return -1;
          ans = ans | (tmp << shift);
          shift -= 3;
        }
      i++;
    }
  return ans;
}

int
check_format (char *str, int *a, int *b, int *c)
{
  char ch = ' ';
  char address[3] = { ' ', ' ', ' ' };
  char command[7] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
  char operand[5] = { ' ', ' ', ' ', ' ', ' ' };
  int i = 0, add = 0, com = 0, oper = 0;
  int enda = 0, endc = 0, endo = 0;
  int check_comment = 0;
  int address_ans, command_ans, operand_ans;
  address_ans = command_ans = operand_ans = -1;

  while (ch != '\n' && ch != EOF) //проверка синтаксиса строки
    {
      ch = str[i];
      if (ch == ' ' || ch == '\t')
        {
          i++;
          continue;
        }

      if (ch == ';')
        check_comment = 1;

      if (enda == 0)
        {
          address[add] = ch;
          if (str[i + 1] == ' ' || str[i + 1] == '\t')
            enda = 1;
          else if (add == 2)
            return i + 1;
          add++;
        }
      else if (endc == 0)
        {
          command[com] = ch;
          if (str[i + 1] == ' ' || str[i + 1] == '\t')
            endc = 1;
          else if (com == 6)
            return i + 1;
          com++;
        }
      else if (endo == 0)
        {
          operand[oper] = ch;
          if (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == ';'
              || str[i + 1] == '\n')
            {
              if (str[i + 1] == '\n')
                ch = str[i + 1];
              endo = 1;
            }
          else if (oper == 4)
            return i + 1;
          oper++;
        }
      else
        {
          if (ch != ' ' && ch != '\t' && check_comment == 0)
            return i + 1;
        }
      i++;
    }

  address_ans = check_address (address, add);
  command_ans = check_command (command, com);
  operand_ans = check_operand (operand, oper);
  if (address_ans == -1)
    printf ("Ошибка в значении адреса\n");
  if (command_ans == -1)
    printf ("Неверная команда\n");
  if (operand_ans == -1)
    printf ("Ошибка в значении операнда\n");
  if (address_ans == -1 || command_ans == -1 || operand_ans == -1)
    return -1;
  *a = address_ans;
  *b = command_ans;
  *c = operand_ans;
  return 0;
}

int
main (int argc, char *argv[])
{
  if (argc != 2 && argc != 4)
    {
      printf (
          "Пример: \"./translator <file_name.sa> -o <res_file_name.o>\"\n");
      return 0;
    }
  FILE *fp = NULL, *fout = NULL;
  char str[90];
  int check = 1, address = -1, command = -1, operand = -1, it = 0;
  int ram[128];
  if ((fp = fopen (argv[1], "rb")) == NULL)
    {
      printf ("Файл %s не найден\n", argv[1]);
      return 0;
    }
  if (argc == 2)
    {
      if ((fout = fopen ("out.o", "wb")) == NULL)
        {
          printf (
              "Не удалось создать файл с именем по умолчанию (\"out.o\")\n");
          return 0;
        }
    }
  else
    {
      if ((fout = fopen (argv[3], "wb")) == NULL)
        {
          printf ("Не удалось создать файл с именем %s\n", argv[3]);
          return 0;
        }
    }
  for (int i = 0; i < 128; i++)
    ram[i] = 0;

  while (fgets (str, 90, fp) != NULL)
    {
      check = check_format (str, &address, &command, &operand);
      if (check != 0)
        {
          if (check > 0)
            send_error (str, it, check);
          else
            printf ("Строка номер %d\n", it + 1);
          fclose (fp);
          fclose (fout);
          return 0;
        }
      if (command == 2)
        ram[address] = operand;
      else
        {
          command = command << 7;
          ram[address] = ram[address] | command;
          ram[address] = ram[address] | operand;
        }
      it++;
    }
  if (fwrite (ram, sizeof (int), 128, fout) != 128)
    {
      fclose (fp);
      fclose (fout);
      return -1;
    }

  fclose (fp);
  fclose (fout);
  return 0;
}