#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
// #include <string>
#include <stdlib.h>
#define MASK1 0x7
#define MASK2 0xF
using namespace std;

int check_command (int str_num, string str, int *command, int *finish);

char
to_x (int value)
{
  char ans = '\0';
  switch (value)
    {
    case 0:
      ans = '0';
      break;
    case 1:
      ans = '1';
      break;
    case 2:
      ans = '2';
      break;
    case 3:
      ans = '3';
      break;
    case 4:
      ans = '4';
      break;
    case 5:
      ans = '5';
      break;
    case 6:
      ans = '6';
      break;
    case 7:
      ans = '7';
      break;
    case 8:
      ans = '8';
      break;
    case 9:
      ans = '9';
      break;
    case 10:
      ans = 'A';
      break;
    case 11:
      ans = 'B';
      break;
    case 12:
      ans = 'C';
      break;
    case 13:
      ans = 'D';
      break;
    case 14:
      ans = 'E';
      break;
    case 15:
      ans = 'F';
      break;
    }
  return ans;
}

int
count_str_in_file (ifstream *fp)
{
  int count = 0;
  string str;
  if (fp->is_open () == 0)
    return -1;
  while (getline (*fp, str))
    count++;
  return count;
}

string
translate (int n)
{
  string ans = "";
  ans.clear ();
  int shift = 11;
  if (n >= 0x8000)
    return "";
  if (n < 0)
    {
      ans = '-';
      n *= -1;
    }
  else
    ans = '+';
  for (int j = 0; j < 4; j++)
    {
      if (j % 2 == 0)
        {
          ans = ans + to_x ((n >> shift) & MASK1);
          shift -= 4;
        }
      else
        {
          ans = ans + to_x ((n >> shift) & MASK2);
          shift -= 3;
        }
    }
  return ans;
}

int
check_command (int str_num, string str, int *command, int *finish)
{
  string check;
  string commands[7]
      = { "REM", "INPUT", "OUTPUT", "GOTO", "IF", "LET", "END" };
  int i = 0, start = 0, res_num = 0;
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  start = i;
  for (; i <= 4; i++)
    {
      if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\0')
        break;
    }
  if (i == 5)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Недопустимый номер строки" << endl;
      return -1;
    }
  check = str.substr (start, i);
  res_num = atoi (check.c_str ());
  if (res_num != str_num)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Недопустимый номер строки" << endl;
      return -1;
    }
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  start = i;
  for (int j = 0; j < 6; j++)
    {
      if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\0')
        break;
      i++;
    }
  if (i - start == 0)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Команда не обнаружена" << endl;
      return -1;
    }
  check = str.substr (start, i - start);
  for (int j = 0; j < 7; j++)
    {
      if (check == commands[j])
        {
          *command = j;
          *finish = i;
          return 0;
        }
    }
  cout << "Ошибка в строке " << str_num / 10 << endl;
  cout << "Неверная команда" << endl;
  return -1;
}

int
end_func (ofstream *fout, map<int, int> *address_str, int str_num,
          int *this_address)
{
  string address;
  address = to_string ((*this_address));
  (*address_str)[str_num] = (*this_address);
  *this_address = (*this_address) + 1;
  (*fout) << address << "  "
          << "HALT"
          << "  "
          << "00" << endl;
  return 0;
}

int
input (ofstream *fout, map<char, int> *variable_list,
       map<int, int> *address_str, string str, int str_num, int start,
       int *this_address, int *variable_count)
{
  string address, command, operand;
  command = "READ";
  address = to_string ((*this_address));
  (*address_str)[str_num] = (*this_address);
  *this_address = (*this_address) + 1;
  int i = start;
  char name = '\0';
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  if ((name = str[i]) == '\0')
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Не задано имя переменной" << endl;
      return -1;
    }
  if (name < 65 || name > 90)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Неверное имя переменной" << endl;
      return -1;
    }
  i++;
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  if (str[i] != '\0' && str[i] != '\n')
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Недопустимый аргумент после имени переменной" << endl;
      return -1;
    }
  if (!variable_list->count (name))
    {
      if ((*variable_count) <= (*this_address))
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Недостаточно оперативной памяти для записи программы"
               << endl;
          return -1;
        }
      (*variable_list)[name] = *variable_count;
      *variable_count = *variable_count - 1;
    }
  operand = to_string ((*variable_list)[name]);
  (*fout) << address << "  " << command << "  " << operand << endl;
  return 0;
}

int
output (ofstream *fout, map<char, int> *variable_list,
        map<int, int> *address_str, string str, int str_num, int start,
        int *this_address, int *variable_count)
{
  string address, command, operand;
  command = "WRITE";
  address = to_string ((*this_address));
  (*address_str)[str_num] = (*this_address);
  *this_address = (*this_address) + 1;
  int i = start;
  char name = '\0';
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  if ((name = str[i]) == '\0')
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Не задано имя переменной" << endl;
      return -1;
    }
  if (name < 65 || name > 90)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Неверное имя переменной" << endl;
      return -1;
    }
  i++;
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  if (str[i] != '\0' && str[i] != '\n')
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Недопустимый аргумент после имени переменной" << endl;
      return -1;
    }
  if (!variable_list->count (name))
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Необъявленная переменна" << name << endl;
      return -1;
    }
  // if(!variable_list->count(name))
  // {
  //   if((*variable_count) <= (*this_address))
  //   {
  //     cout << "Ошибка в строке " << str_num / 10 << endl;
  //     cout << "Недостаточно оперативной памяти для записи программы" <<
  //     endl; return -1;
  //   }
  //   (*variable_list)[name] = *variable_count;
  //   *variable_count = *variable_count - 1;
  // }
  operand = to_string ((*variable_list)[name]);
  (*fout) << address << "  " << command << "  " << operand << endl;
  return 0;
}

int
goto_func (ofstream *fout, map<int, int> *address_str, stack<int> *addr_stack,
           string str, int str_num, int count_str, int start,
           int *this_address)
{
  string address, command, operand;
  int num = 0;
  address = to_string ((*this_address));
  (*address_str)[str_num] = (*this_address);
  command = "JUMP";
  *this_address = (*this_address) + 1;
  int i = start;
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  start = i;
  while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
    i++;
  if (start == i)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Недопустимый номер строки для перехода" << endl;
      return -1;
    }
  operand = str.substr (start, i - start);
  num = atoi (operand.c_str ());
  if ((num % 10) != 0 || num <= 0 || (num > count_str * 10) || num == str_num)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Недопустимый номер строки для перехода" << endl;
      return -1;
    }
  addr_stack->push (num);
  addr_stack->push ((*this_address) - 1);
  (*fout) << address << "  " << command << "  " << endl;
  return 0;
}

int
check_notation (string str, int start)
{
  int i = start;
  int last_op = 0; // 1 - знак, 2 - операнд
  while (str[i] == ' ')
    i++;
  if (str[i] == '+' || str[i] == '*' || str[i] == '/')
    return 2;
  while (str[i] != '\0')
    {
      while (str[i] == ' ')
        i++;
      if (str[i] == '(')
        return 1;
      if ((str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '-'))
        {
          if (last_op == 1)
            return 2;
          last_op = 1;
          i++;
        }
      else
        {
          if (last_op == 2)
            return 2;
          last_op = 2;
          while (str[i] != ' ' && str[i] != '\0')
            i++;
        }
    }
  return 1;
}

int
check_next_value (map<char, int> *variable_list, string str, int *var,
                  char *revar, int *start)
{
  int i = *start, count = 0;
  string sub = "";
  if (str[i] == 'A')
    {
      *var = 3;
      *start = (*start) + 1;
      return 0;
    }
  else if (str[i] >= 65 && str[i] <= 90)
    {
      if (variable_list->count (str[i]))
        {
          *var = 1;
          *start = (*start) + 1;
          *revar = str[i];
          return 0;
        }
      return -1;
    }
  else
    {
      while (str[i] >= 48 && str[i] <= 57)
        {
          sub = sub + str[i];
          count++;
          i++;
        }
      if (count == 0)
        return -1;
      *var = 2;
      *start = (*start) + count;
      return atoi (sub.c_str ());
    }
  return -1;
}

int
polish_notation (ofstream *fout, map<char, int> *variable_list, string str,
                 int str_num, int start, int *this_address,
                 int *variable_count)
{
  int i = start, beginning = 0;
  int left = 0, right = 0, lvalue = 0, rvalue = 0, acc = 0,
      res_addr = (*variable_count), temp = 0;
  char varl = '\0', varr = '\0', oper = '\0';
  string address = "", command = "", operand = "", sub1 = "", sub2 = "";
  stack<int> varib;
  str = str.substr (i, str.length () - i);
  i = 0;
  while (1)
    {
      while (str[i] == ' ')
        i++;
      beginning = i;
      if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
          oper = str[i];
          i++;
        }
      else
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Нарушен синтаксис команды LET" << endl;
          return -1;
        }
      while (str[i] == ' ')
        i++;
      if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        continue;
      if ((lvalue = check_next_value (variable_list, str, &left, &varl, &i))
          == -1)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Нарушен синтаксис команды LET" << endl;
          return -1;
        }
      while (str[i] == ' ')
        i++;
      if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        continue;
      if ((rvalue = check_next_value (variable_list, str, &right, &varr, &i))
          == -1)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Нарушен синтаксис команды LET" << endl;
          return -1;
        }

      if (((right == 3 && (oper == '-' || oper == '/'))
           || (left != 3 && right != 3) || (left == 3 && right == 3))
          && acc == 1)
        {
          address = to_string ((*this_address));
          *this_address = (*this_address) + 1;
          command = "  STORE  ";
          if (((*variable_count) + 1) < res_addr)
            operand = to_string (res_addr);
          else
            {
              operand = to_string ((*variable_count));
              *variable_count = (*variable_count) - 1;
            }
          (*fout) << address << command << operand << endl;
          varib.push (res_addr);
          res_addr--;
          acc = 0;
        }
      if (left == 3 && right == 3)
        {
          temp = varib.top ();
          varib.pop ();
          address = to_string ((*this_address));
          *this_address = (*this_address) + 1;
          command = "  LOAD  ";
          operand = to_string (varib.top ());
          varib.pop ();
          (*fout) << address << command << operand << endl;
          operand = to_string (temp);
          res_addr = res_addr + 2;
        }

      if (left != 3)
        {
          if (left == 2) //константа
            {
              address = to_string ((*variable_count));
              *variable_count = (*variable_count) - 1;
              command = " = ";
              operand = translate (lvalue);
              (*fout) << address << command << operand << endl;
              operand = to_string ((*variable_count) + 1);
            }
          else if (left == 1)
            operand = to_string ((*variable_list)[varl]);
          if (acc == 0)
            {
              address = to_string ((*this_address));
              *this_address = (*this_address) + 1;
              command = "  LOAD  ";
              (*fout) << address << command << operand << endl;
            }
        }
      if (right != 3)
        {
          if (right == 2) //константа
            {
              address = to_string ((*variable_count));
              *variable_count = (*variable_count) - 1;
              command = " = ";
              operand = translate (rvalue);
              (*fout) << address << command << operand << endl;
              operand = to_string ((*variable_count) + 1);
            }
          else if (right == 1)
            operand = to_string ((*variable_list)[varr]);
        }
      else if (right == 3 && left != 3 && (oper == '-' || oper == '/'))
        {
          operand = to_string (varib.top ());
          varib.pop ();
          res_addr++;
        }
      left = 0;
      varl = '\0';
      right = 0;
      varr = '\0';
      if (oper == '+')
        command = "  ADD  ";
      else if (oper == '-')
        command = "  SUB  ";
      else if (oper == '*')
        command = "  MUL  ";
      else
        command = "  DIVIDE  ";
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      (*fout) << address << command << operand << endl;
      acc = 1;
      sub1 = str.substr (0, beginning);
      sub2 = str.substr (i, str.length () - i);
      char ch1 = '\0', ch2 = '\0';
      int j = 0;
      while (sub1[j] == ' ')
        j++;
      ch1 = sub1[j];
      j = 0;
      while (sub2[j] == ' ')
        j++;
      ch2 = sub2[j];
      if (ch1 == '\0' && ch2 == '\0')
        break;
      str = sub1 + 'A' + sub2;
      i = 0;
    }
  if (acc == 0 || !varib.empty ())
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Нарушен синтаксис команды LET" << endl;
      return -1;
    }
  return 0;
}
int
definition_coefficient (string str, int start)
{
  int i = start, bracket = 0, max_bracket = 0, k = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '(')
        {
          bracket++;
          if (max_bracket < bracket)
            {
              max_bracket = bracket;
              k = 2 * max_bracket;
            }
        }
      if (str[i] == ')')
        bracket--;
      if (str[i] == '*' || str[i] == '/')
        {
          if (k == max_bracket * 2 && max_bracket == bracket)
            k++;
        }
      i++;
    }
  if (bracket != 0)
    return -1;
  return k;
}
int
min_coefficient (string str, int start, int max_k)
{
  int i = start, bracket = 0, k = max_k, min_k = max_k;
  while (str[i] != '\0')
    {
      if (str[i] == '+' || str[i] == '-')
        k = bracket * 2;
      if (str[i] == '*' || str[i] == '/')
        k = bracket * 2 + 1;
      if (str[i] == '(')
        bracket++;
      if (str[i] == ')')
        bracket--;
      if (k < min_k)
        min_k = k;
      i++;
    }
  if (k == -1)
    return -1;
  return min_k;
}
int
recursive_counting (ofstream *fout, map<char, int> *variable_list, string str,
                    int str_num, int start, int *this_address,
                    int *variable_count, int level, int min_level,
                    queue<int> *constants_save)
{
  //Обнаружить константу или переменную, обнаружить операнд, обнаружить
  //следующую переменную либо константу. Если k == level и обнаружены две
  //переменные, либо одна переменная в аккумуляторе, а другая обнаружена, то
  //сделать действие
  int i = start, loper = 0, roper = 0, k = 0, last_k = 0, next_k = 0,
      rconst = 0, lconst = 0, acc = 0, bracket = 0, var = 1, sign = 0,
      write = 0, t = 0, this_constants = 0,
      answer_constants = 0; // use_answer_constants = 0;   //oper == 0 - не
                            // найден, oper == 1 - переменная, oper == 2 -
                            // константа    acc == 1 - результат в аккумуляторе
  char lname = '\0', rname = '\0', op = '\0';
  string address = "", command = "", operand = "";
  queue<int> this_constants_save;
  while (str[i] != '\0')
    {
      while (str[i] == ' ')
        i++;
      if (str[i] == '(')
        {
          bracket++;
          i++;
          continue;
        }
      if (str[i] == ')')
        {
          bracket--;
          i++;
          continue;
        }

      if (str[i] >= 65 && str[i] <= 90 && var && loper == 0) //левое значение
        {
          loper = 1;
          lname = str[i];
          if (!variable_list->count (lname))
            {
              cout << "Ошибка в строке " << str_num / 10 << endl;
              cout << "Необъявленная переменная " << lname << endl;
              return -1;
            }
          i++;
          var = 0;
          sign = 1;
          continue;
        }
      else if ((str[i] == '-' || (str[i] >= 48 && str[i] <= 57)) && var
               && loper == 0)
        {
          int s = 0, st = 0;
          string sub = "";
          if (str[i] == '-')
            {
              s = 1;
              i++;
            }
          st = i;
          while (str[i] >= 48 && str[i] <= 57)
            {
              sub = sub + str[i];
              i++;
            }
          if (st == i)
            {
              cout << "Ошибка в строке " << str_num / 10 << endl;
              cout << "Не найдено значение константы" << endl;
              return -1;
            }
          loper = 2;
          lconst = atoi (sub.c_str ());
          if (s)
            lconst *= -1;
          var = 0;
          sign = 1;
          continue;
        }
      else if (var && loper == 0)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Нарушен синтаксис команды LET, ожидались значение или "
                  "переменная"
               << endl;
          return -1;
        }
      if (sign)
        {
          if (str[i] != '-' && str[i] != '+' && str[i] != '*' && str[i] != '/')
            {
              cout << "Ошибка в строке " << str_num / 10 << endl;
              cout << "Нарушен синтаксис команды LET, ожидался операнд"
                   << endl;
              return -1;
            }
          else
            {
              if (str[i] == '+' || str[i] == '-')
                {
                  // last_op = op;
                  last_k = k;
                  k = bracket * 2;
                  op = str[i];
                }
              else
                {
                  // last_op = op;
                  last_k = k;
                  k = bracket * 2 + 1;
                  op = str[i];
                }
              i++;
              sign = 0;
              var = 1;
              continue;
            }
        }
      if (k == level)
        write = 1;
      else
        {
          if (acc && level != min_level)
            {
              address = to_string ((*this_address));
              *this_address = (*this_address) + 1;
              command = "STORE";
              if (this_constants
                  > answer_constants) //есть место для сохранения резултата
                {
                  this_constants_save.push ((*variable_count) + this_constants
                                            - answer_constants);
                  operand = to_string ((*variable_count) + this_constants
                                       - answer_constants);
                }
              else
                {
                  this_constants_save.push ((*variable_count));
                  operand = to_string ((*variable_count));
                  *variable_count = (*variable_count) - 1;
                  this_constants++;
                }
              answer_constants++;
              (*fout) << address << "  " << command << "  " << operand << endl;
              acc = 0;
            }
          if (last_k > level
              && k < level) //копирование результатов прошлых уровней, если они
                            //не использовались текущим
            {
              this_constants_save.push (constants_save->front ());
              constants_save->pop ();
            }
          write = 0;
        }
      if (str[i] >= 65 && str[i] <= 90 && var && loper) //правое значение
        {
          roper = 1;
          rname = str[i];
          if (!variable_list->count (rname))
            {
              cout << "Ошибка в строке " << str_num / 10 << endl;
              cout << "Необъявленная переменная " << rname << endl;
              return -1;
            }
          i++;
          var = 0;
          sign = 1;
          if (write == 0) //Если k != level, то переписываем roper в loper
            {
              if (loper == 1)
                {
                  lname = rname;
                  roper = 0;
                  rname = '\0';
                }
              else
                {
                  lconst = 0;
                  loper = 1;
                  lname = rname;
                  roper = 0;
                  rname = '\0';
                }
              continue;
            }
        }
      else if ((str[i] == '-' || (str[i] >= 48 && str[i] <= 57)) && var
               && loper)
        {
          int s = 0, st = 0;
          string sub = "";
          if (str[i] == '-')
            {
              s = 1;
              i++;
            }
          st = i;
          while (str[i] >= 48 && str[i] <= 57)
            {
              sub = sub + str[i];
              i++;
            }
          if (st == i)
            {
              cout << "Ошибка в строке " << str_num / 10 << endl;
              cout << "Не найдено значение константы" << endl;
              return -1;
            }
          roper = 2;
          rconst = atoi (sub.c_str ());
          if (s)
            rconst *= -1;
          var = 0;
          sign = 1;
          if (write == 0) //Если k != level, то переписываем roper в loper
            {
              if (loper == 1)
                {
                  loper = 2;
                  lname = '\0';
                  lconst = rconst;
                  roper = 0;
                  rconst = 0;
                }
              else
                {
                  lconst = rconst;
                  roper = 0;
                  rconst = 0;
                }
              continue;
            }
        }
      else if (var && loper)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Нарушен синтаксис команды LET, ожидались значение или "
                  "переменная"
               << endl;
          return -1;
        }

      next_k = k;
      t = i;
      while (str[t] != '(' && str[t] != ')' && str[t] != '+' && str[t] != '-'
             && str[t] != '*' && str[t] != '/' && str[t] != '\0')
        t++;
      if (str[t] == '(')
        next_k = (bracket + 1) * 2;
      if (str[t] == ')')
        next_k = (bracket - 1) * 2;
      if (str[t] == '+' || str[t] == '-')
        next_k = bracket * 2;
      if (str[t] == '*' || str[t] == '/')
        next_k = bracket * 2 + 1;
      if (str[i] == '\0')
        next_k = 0;

      if ((k == last_k && k == next_k) || (k == last_k && k > next_k)
          || (k > last_k && k == next_k) || (k > last_k && k > next_k))
        {
          if (acc == 0) //аккумулятор пуст
            {
              if (loper == 2) // loper - константа
                {
                  address = to_string ((*variable_count));
                  *variable_count = (*variable_count) - 1;
                  this_constants++;
                  command = "=";
                  operand = translate (lconst);
                  (*fout) << address << "  " << command << "  " << operand
                          << endl;
                  operand = to_string ((*variable_count) + 1);
                }
              else // loper - переменная
                operand = to_string ((*variable_list)[lname]);
              address = to_string ((*this_address));
              *this_address = (*this_address) + 1;
              command = "LOAD";
              (*fout) << address << "  " << command << "  " << operand << endl;
              acc = 1;
            }
          if (roper == 2) // roper - константа
            {
              address = to_string ((*variable_count));
              *variable_count = (*variable_count) - 1;
              this_constants++;
              command = "=";
              operand = translate (rconst);
              (*fout) << address << "  " << command << "  " << operand << endl;
              operand = to_string ((*variable_count) + 1);
            }
          else
            operand = to_string ((*variable_list)[rname]);
          if (op == '+')
            command = "ADD";
          else if (op == '-')
            command = "SUB";
          else if (op == '*')
            command = "MUL";
          else if (op == '/')
            command = "DIVIDE";
          address = to_string ((*this_address));
          *this_address = (*this_address) + 1;
          (*fout) << address << "  " << command << "  " << operand << endl;
          // load loper, вычисление с roper
        }
      else if ((k < last_k && k == next_k) || (k < last_k && k > next_k))
        {
          if (acc == 0)
            {
              address = to_string ((*this_address));
              *this_address = (*this_address) + 1;
              command = "LOAD";
              operand = to_string (
                  constants_save
                      ->front ()); //используем ответ предыдущего уровня
              constants_save->pop ();
              (*fout) << address << "  " << command << "  " << operand << endl;
              acc = 1;
            }
          if (roper == 2) // roper - константа
            {
              address = to_string ((*variable_count));
              *variable_count = (*variable_count) - 1;
              this_constants++;
              command = "=";
              operand = translate (rconst);
              (*fout) << address << "  " << command << "  " << operand << endl;
              operand = to_string ((*variable_count) + 1);
            }
          else
            operand = to_string ((*variable_list)[rname]);
          address = to_string ((*this_address));
          *this_address = (*this_address) + 1;
          if (op == '+')
            command = "ADD";
          else if (op == '-')
            command = "SUB";
          else if (op == '*')
            command = "MUL";
          else if (op == '/')
            command = "DIVIDE";
          (*fout) << address << "  " << command << "  " << operand << endl;
          // load ansl, вычисление с roper
        }
      else if (k < last_k && k < next_k)
        {
          if (acc == 0)
            {
              address = to_string ((*this_address));
              *this_address = (*this_address) + 1;
              command = "LOAD";
              operand = to_string (constants_save->front ());
              constants_save->pop ();
              (*fout) << address << "  " << command << "  " << operand << endl;
              acc = 1;
            }
          if (op == '+')
            command = "ADD";
          else if (op == '-')
            command = "SUB";
          else if (op == '*')
            command = "MUL";
          else if (op == '/')
            command = "DIVIDE";
          address = to_string ((*this_address));
          *this_address = (*this_address) + 1;
          operand = to_string (constants_save->front ());
          constants_save->pop ();
          (*fout) << address << "  " << command << "  " << operand << endl;
          // load ansl, вычисление с ansr
        }
      else if ((k == last_k && k < next_k) || (k > last_k && k < next_k))
        {
          if (acc == 0)
            {
              if (loper == 2)
                {
                  address = to_string ((*variable_count));
                  *variable_count = (*variable_count) - 1;
                  this_constants++;
                  command = "=";
                  operand = translate (lconst);
                  (*fout) << address << "  " << command << "  " << operand
                          << endl;
                  operand = to_string ((*variable_count) + 1);
                }
              else
                operand = to_string ((*variable_list)[lname]);
              address = to_string ((*this_address));
              *this_address = (*this_address) + 1;
              command = "LOAD";
              (*fout) << address << "  " << command << "  " << operand << endl;
              acc = 1;
            }
          if (op == '+')
            command = "ADD";
          else if (op == '-')
            command = "SUB";
          else if (op == '*')
            command = "MUL";
          else if (op == '/')
            command = "DIVIDE";
          address = to_string ((*this_address));
          *this_address = (*this_address) + 1;
          operand = to_string (constants_save->front ());
          constants_save->pop ();
          (*fout) << address << "  " << command << "  " << operand << endl;
          // load loper, вычисление с ansr
        }
    }
  while (!constants_save->empty ())
    {
      this_constants_save.push (constants_save->front ());
      constants_save->pop ();
    }
  if (acc && level != min_level) //выгрузка ответа из аккумулятора
    {
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      command = "STORE";
      if (this_constants
          > answer_constants) //есть место для сохранения результата
        {
          this_constants_save.push ((*variable_count) + this_constants
                                    - answer_constants);
          operand = to_string ((*variable_count) + this_constants
                               - answer_constants);
        }
      else
        {
          this_constants_save.push ((*variable_count));
          operand = to_string ((*variable_count));
          *variable_count = (*variable_count) - 1;
          this_constants++;
        }
      answer_constants++;
      (*fout) << address << "  " << command << "  " << operand << endl;
      acc = 0;
    }
  int check = -1;
  if (level == min_level)
    {
      check = this_constants_save.front ();
      this_constants_save.pop ();
      if (acc == 0)
        {
          if (loper == 0)
            {
              cout << "Ошибка в строке " << str_num / 10 << endl;
              cout << "Нарушен синтаксис команды LET, ожидались значение или "
                      "переменная"
                   << endl;
              return -1;
            }
          if (loper == 1)
            operand = to_string ((*variable_list)[lname]);
          else
            {
              address = to_string ((*variable_count));
              *variable_count = (*variable_count) - 1;
              command = "=";
              operand = translate (lconst);
              (*fout) << address << "  " << command << "  " << operand << endl;
              operand = to_string ((*variable_count) + 1);
            }
          address = to_string ((*this_address));
          *this_address = (*this_address) + 1;
          command = "LOAD";
          (*fout) << address << "  " << command << "  " << operand << endl;
        }
      return check;
    }
  check = recursive_counting (fout, variable_list, str, str_num, start,
                              this_address, variable_count, level - 1,
                              min_level, &this_constants_save);
  return check;
}

int
let_func (ofstream *fout, map<char, int> *variable_list,
          map<int, int> *address_str, string str, int str_num, int start,
          int *this_address, int *variable_count)
{
  int i = start, max_coefficient = 0, min_coeff = 0, ans = -1;
  char name = '\0';
  queue<int> p;
  (*address_str)[str_num] = (*this_address);
  while (str[i] == ' ')
    i++;
  if (str[i] < 65 || str[i] > 90)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Недопустимое имя переменной" << endl;
      return -1;
    }
  name = str[i];
  i++;
  if (!variable_list->count (name))
    {
      if ((*variable_count) <= (*this_address))
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Недостаточно оперативной памяти для записи программы"
               << endl;
          return -1;
        }
      (*variable_list)[name] = *variable_count;
      *variable_count = *variable_count - 1;
    }
  while (str[i] == ' ')
    i++;
  if (str[i] != '=')
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Нарушен синтаксис команды LET (\"=\")" << endl;
      return -1;
    }
  i++;
  if (check_notation (str, i) == 1) //арифметика
    {
      max_coefficient = definition_coefficient (str, i);
      if (max_coefficient == -1)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Нарушен синтаксис команды LET" << endl;
          return -1;
        }
      min_coeff = min_coefficient (str, i, max_coefficient);
      if (min_coeff == -1)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Нарушен синтаксис команды LET" << endl;
          return -1;
        }
      if ((ans = recursive_counting (fout, variable_list, str, str_num, i,
                                     this_address, variable_count,
                                     max_coefficient, min_coeff, &p))
          == -1)
        return -1;
    }
  else //польская нотация
    {
      if (polish_notation (fout, variable_list, str, str_num, i, this_address,
                           variable_count)
          == -1)
        return -1;
    }
  (*fout) << to_string ((*this_address)) << "  STORE  "
          << to_string ((*variable_list)[name]) << endl;
  *this_address = (*this_address) + 1;
  return 0;
}

int
if_func (ofstream *fout, map<char, int> *variable_list,
         map<int, int> *address_str, stack<int> *addr_stack, string str,
         int str_num, int count_str, int start, int *this_address,
         int *variable_count)
{
  ifstream rf;
  ofstream wf;
  string address = "", command = "", operand = "";
  string sub1 = "", sub2 = "";
  char namel = '\0', namer = '\0';
  int i = 0, variablel = 0, variabler = 0, left = -1, right = -1,
      start_address;
  start_address = (*this_address);
  i = start;
  while (str[i] == ' ')
    i++;
  if (str[i] >= 65 && str[i] <= 90)
    {
      variablel = 1;
      if ((left = (*variable_list)[str[i]]) == 0)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Необъявленная переменная" << endl;
          return -1;
        }
      namel = str[i];
      i++;
    }
  else
    {
      int s = i;
      if (str[i] == '-')
        {
          sub1 = sub1 + str[i];
          i++;
        }
      while (str[i] >= 48 && str[i] <= 57)
        {
          sub1 = sub1 + str[i];
          i++;
        }
      if (s == i)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Не обнаружен левый операнд" << endl;
          return -1;
        }
      left = atoi (sub1.c_str ());
      sub1.clear ();
    }
  while (str[i] == ' ')
    i++;
  for (int j = 0; j < 2; j++)
    {
      if (str[i] != '<' && str[i] != '>' && str[i] != '=' && str[i] != '!')
        break;
      sub2 = sub2 + str[i];
      i++;
    }
  while (str[i] == ' ')
    i++;
  if (str[i] >= 65 && str[i] <= 90)
    {
      variabler = 1;
      if ((right = (*variable_list)[str[i]]) == 0)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Необъявленная переменная" << endl;
          return -1;
        }
      namer = str[i];
      i++;
    }
  else
    {
      int s = i;
      if (str[i] == '-')
        {
          sub1 = sub1 + str[i];
          i++;
        }
      while (str[i] >= 48 && str[i] <= 57)
        {
          sub1 = sub1 + str[i];
          i++;
        }
      if (s == i)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Не обнаружен правый операнд" << endl;
          return -1;
        }
      right = atoi (sub1.c_str ());
      sub1.clear ();
    }
  if (variablel == 0
      && variabler == 0) //Если условие не выполняется, то пропускаем строку с
                         // IF и следующую команду
    {
      int com = 0, fin = 0;
      if (sub2 == ">" && !(left > right))
        return 0;
      if (sub2 == ">=" && !(left >= right))
        return 0;
      if (sub2 == "<" && !(left < right))
        return 0;
      if (sub2 == "<=" && !(left <= right))
        return 0;
      if (sub2 == "==" && !(left == right))
        return 0;
      if (sub2 == "!=" && !(left != right))
        return 0;
      sub1 = to_string (str_num) + "  " + str.substr (i, str.length () - i);
      if (check_command (str_num, sub1, &com, &fin) == -1)
        return -1;
      if (com == 0 || com == 4)
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Недоустимая команда после IF" << endl;
          return -1;
        }
      switch (com)
        {
        case 1:
          if (input (fout, variable_list, address_str, str, str_num, fin,
                     this_address, variable_count)
              == 0)
            return 0;
          return -1;
        case 2:
          if (output (fout, variable_list, address_str, str, str_num, fin,
                      this_address, variable_count)
              == 0)
            return 0;
          return -1;
        case 3:
          if (goto_func (fout, address_str, addr_stack, str, str_num,
                         count_str, fin, this_address)
              == 0)
            return 0;
          return -1;
        case 5:
          if (let_func (fout, variable_list, address_str, str, str_num, fin,
                        this_address, variable_count)
              == 0)
            return 0;
          return -1;
        case 6:
          end_func (fout, address_str, str_num, this_address);
          return 0;
        }
    }
  if (variablel == 0)
    {
      address = to_string ((*variable_count));
      *variable_count = (*variable_count) - 1;
      command = "=";
      if ((operand = translate (left)).empty ())
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Недопустимое значение константы" << endl;
          return -1;
        }
      (*fout) << address << "  " << command << "  " << operand << endl;
      address.clear ();
      operand.clear ();
    }
  if (variabler == 0)
    {
      address = to_string ((*variable_count));
      *variable_count = (*variable_count) - 1;
      command = "=";
      if ((operand = translate (right)).empty ())
        {
          cout << "Ошибка в строке " << str_num / 10 << endl;
          cout << "Недопустимое значение константы" << endl;
          return -1;
        }
      (*fout) << address << "  " << command << "  " << operand << endl;
      address.clear ();
      operand.clear ();
    }
  int com = 0, fin = 0, k = 0;
  sub1 = to_string (str_num) + "  " + str.substr (i, str.length () - i);
  if (check_command (str_num, sub1, &com, &fin) == -1)
    return -1;
  if (com == 0 || com == 4)
    {
      cout << "Ошибка в строке " << str_num / 10 << endl;
      cout << "Недоустимая команда после IF" << endl;
      return -1;
    }
  if (sub2 == ">" || sub2 == ">=")
    {
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      command = "LOAD";
      if (variablel == 0)
        operand = to_string ((*variable_count) + 1);
      else
        operand = to_string ((*variable_list)[namel]);
      (*fout) << address << "  " << command << "  " << operand << endl;
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      command = "SUB";
      if (variabler == 0)
        operand = to_string ((*variable_count) + 1);
      else
        operand = to_string ((*variable_list)[namer]);
      (*fout) << address << "  " << command << "  " << operand << endl;
      command = "JNEG";
      if (sub2 == ">")
        k = 2;
      else
        k = 1;
    }
  if (sub2 == "<" || sub2 == "<=")
    {
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      command = "LOAD";
      if (variabler == 0)
        operand = to_string ((*variable_count) + 1);
      else
        operand = to_string ((*variable_list)[namer]);
      (*fout) << address << "  " << command << "  " << operand << endl;
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      command = "SUB";
      if (variablel == 0)
        operand = to_string ((*variable_count) + 1);
      else
        operand = to_string ((*variable_list)[namel]);
      (*fout) << address << "  " << command << "  " << operand << endl;
      command = "JNEG";
      if (sub2 == "<")
        k = 2;
      else
        k = 1;
    }
  if (sub2 == "==" || sub2 == "!=")
    {
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      command = "LOAD";
      if (variablel == 0)
        operand = to_string ((*variable_count) + 1);
      else
        operand = to_string ((*variable_list)[namel]);
      (*fout) << address << "  " << command << "  " << operand << endl;
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      command = "SUB";
      if (variabler == 0)
        operand = to_string ((*variable_count) + 1);
      else
        operand = to_string ((*variable_list)[namer]);
      (*fout) << address << "  " << command << "  " << operand << endl;
      if (sub2 == "==")
        {
          command = "JNEG";
          k = 2;
        }
      else
        {
          k = 1;
          command = "JZ";
        }
    }

  if (com != 5) // ">,<,==" - 2 jump; ">=,<=,!=" - 1 jump
    {
      address = to_string ((*this_address));
      *this_address = (*this_address) + 1;
      operand = to_string ((*this_address) + k);
      (*fout) << address << "  " << command << "  " << operand << endl;
      k--;
      if (k)
        {
          if (sub2 == "==")
            command = "JNS";
          else
            command = "JZ";
          address = to_string ((*this_address));
          *this_address = (*this_address) + 1;
          operand = to_string ((*this_address) + k);
          (*fout) << address << "  " << command << "  " << operand << endl;
        }
      switch (com)
        {
        case 1:
          if (input (fout, variable_list, address_str, sub1, str_num, fin,
                     this_address, variable_count)
              != 0)
            return -1;
          break;
        case 2:
          if (output (fout, variable_list, address_str, sub1, str_num, fin,
                      this_address, variable_count)
              != 0)
            return -1;
          break;
        case 3:
          if (goto_func (fout, address_str, addr_stack, sub1, str_num,
                         count_str, fin, this_address)
              != 0)
            return -1;
          break;
        case 6:
          end_func (fout, address_str, str_num, this_address);
          break;
        }
      (*address_str)[str_num] = start_address;
    }
  else //создаем файл с именем temp.sa, куда записываем все команды LET, затем
       //устанавливаем переходы и переписываем команды из файла
    {
      wf.open ("temp.sa");
      int begining = (*this_address);
      *this_address = (*this_address) + k;
      if (let_func (&wf, variable_list, address_str, sub1, str_num, fin,
                    this_address, variable_count)
          == -1)
        {
          wf.close ();
          remove ("temp.sa");
          return -1;
        }
      wf.close ();
      (*address_str)[str_num] = start_address;
      address = to_string (begining);
      begining++;
      operand = to_string ((*this_address));
      (*fout) << address << "  " << command << "  " << operand << endl;
      k--;
      if (k)
        {
          if (sub2 == "==")
            command = "JNS";
          else
            command = "JZ";
          address = to_string (begining);
          operand = to_string ((*this_address));
          (*fout) << address << "  " << command << "  " << operand << endl;
        }
      rf.open ("temp.sa");
      while (getline (rf, sub1))
        (*fout) << sub1;
      rf.close ();
      remove ("temp.sa");
      return 0;
    }
  return 0;
}

int
translate_command (ofstream *fout, map<char, int> *variable_list,
                   map<int, int> *address_str, stack<int> *addr_stack,
                   string str, int str_num, int count_str, int command_code,
                   int start, int *this_address, int *variable_count)
{
  if (command_code == 0)
    return 0;

  switch (command_code)
    {
    case 1:
      if (input (fout, variable_list, address_str, str, str_num, start,
                 this_address, variable_count)
          == 0)
        return 0;
      return -1;
    case 2:
      if (output (fout, variable_list, address_str, str, str_num, start,
                  this_address, variable_count)
          == 0)
        return 0;
      return -1;
    case 3:
      if (goto_func (fout, address_str, addr_stack, str, str_num, count_str,
                     start, this_address)
          == 0)
        return 0;
      return -1;
    case 4:
      if (if_func (fout, variable_list, address_str, addr_stack, str, str_num,
                   count_str, start, this_address, variable_count)
          == 0)
        return 0;
      return -1;
    case 5:
      if (let_func (fout, variable_list, address_str, str, str_num, start,
                    this_address, variable_count)
          == 0)
        return 0;
      return -1;
    case 6:
      end_func (fout, address_str, str_num, this_address);
      return 0;
    }
  return 0;
}

int
main (int argc, char *argv[])
{
  if (argc != 2 && argc != 4)
    {
      cout << "Пример: \"./translator <file_name.bs> -s <res_file_name.sa>\""
           << endl;
      return 0;
    }
  // FILE *fp = NULL, *fout = NULL;
  ifstream fp;
  ofstream fout;
  // char str[90];
  string str, outfilename, sub;
  int str_num = 10, finish = -1, command_code = -1, variable_count = 127,
      this_address = 0, count_str = -1, size = 0, end = 0;
  map<char, int> variable_list;
  map<int, int> address_str;
  stack<int> addr_stack;
  fp.open (argv[1]);
  if (fp.is_open () == 0)
    {
      cout << "Файл " << argv[1] << " не найден" << endl;
      return 0;
    }
  if (argc == 2)
    {
      fout.open ("out.sa");
      outfilename = "out.sa";
      if (fout.is_open () == 0)
        {
          cout << "Не удалось создать файл с именем по умолчанию (\"out.sa\")"
               << endl;
          fp.close ();
          return 0;
        }
    }
  else
    {
      fout.open (argv[3]);
      outfilename = argv[3];
      if (fout.is_open () == 0)
        {
          cout << "Не удалось создать файл с именем " << argv[3] << endl;
          fp.close ();
          return 0;
        }
    }

  count_str = count_str_in_file (&fp);
  fp.close ();
  fp.open (argv[1]);

  while (getline (fp, str))
    {
      if (check_command (str_num, str, &command_code, &finish) == -1)
        {
          fp.close ();
          fout.close ();
          remove (outfilename.c_str ());
          return 0;
        }
      if (translate_command (&fout, &variable_list, &address_str, &addr_stack,
                             str, str_num, count_str, command_code, finish,
                             &this_address, &variable_count)
          == -1)
        {
          fp.close ();
          fout.close ();
          remove (outfilename.c_str ());
          return 0;
        }
      if (variable_count <= this_address)
        {
          cout
              << "Недостаточно размера оперативной памяти для записи программы"
              << endl;
          fp.close ();
          fout.close ();
          remove (outfilename.c_str ());
          return 0;
        }
      if (command_code == 6)
        end = 1;
      //проверка строки, получение команды и точки остановки чтения строки
      //передача в функцию для интерпритации в ассемблер последовательности
      //команд (итерация номера ячейки, декремент номера ячейки для переменных
      //(начиная с 127), поиск адреса переменной в map) и запись в файл fout
      str_num = str_num + 10;
    }
  if (end == 0)
    {
      cout << "Отсутствует признак выхода из программы (END)" << endl;
      fp.close ();
      fout.close ();
      remove (outfilename.c_str ());
      return 0;
    }
  if (addr_stack.empty ())
    {
      fp.close ();
      fout.close ();
      return 0;
    }
  //установка джампов go to
  size = addr_stack.size ();
  int mas[size];
  for (int i = size - 1; i >= 0;
       i--) //Перезаписываем стэк с номерами строк и адресами джампов в массив
    {
      mas[i] = addr_stack.top ();
      addr_stack.pop ();
    }
  fp.close ();
  fout.close ();
  fp.open (outfilename.c_str ());
  fout.open ("stack.sa");
  while (getline (fp, str))
    fout << str << endl;
  fp.close ();
  fout.close ();
  remove (outfilename.c_str ());
  fp.open ("stack.sa");
  fout.open (outfilename.c_str ());
  for (int i = 0; i < size; i += 2)
    {
      while (getline (fp, str))
        {
          int t = 0;
          sub.clear ();
          while (str[t] >= 48 && str[t] <= 57)
            {
              sub = sub + str[t];
              t++;
            }
          if (atoi (sub.c_str ())
              == mas[i + 1]) //Если найден jump, то переписываем адрес нужной
                             //команды, иначе переписываем всю строку в
                             //конечный файл
            {
              fout << mas[i + 1] << "  JUMP  "
                   << to_string (address_str[mas[i]]) << endl;
              break;
            }
          else
            fout << str << endl;
        }
    }
  while (getline (fp, str))
    fout << str << endl;
  remove ("stack.sa");
  fp.close ();
  fout.close ();
  return 0;
}