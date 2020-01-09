//
//  CRC_Remender.c
//
//  Created by april on 2019/12/17.
//

#include "CRC_Remender.h"

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define BASE "1011"
#define BASELENGTH 4
#define initial_padding "000"

// 入参与 BASE 的模 2 运算，返回十进制余数
// 输入是二进制字符串，"1101100001000110"
int crc_remainder(char *input)
{
  if (!input)
  {
    return -1;
  }

  int input_length = strlen(input);
  char array[input_length + BASELENGTH];
  strcpy(array, input);
  strcat(array, initial_padding);

  // printf("%s\n", array);

  int index = 0;
  for (int i = 0; i < input_length;)
  {
    if (i == '0')
    {
      continue;
    }
    // printf("i: %d\n", i);
    index = 0;
    for (int j = 0; j < BASELENGTH && i + j < input_length + BASELENGTH - 1; j++)
    {
      char a = array[i + j];
      char b = BASE[j];
      // printf("%d %d %c %c\n", i, j, a, b);
      if (a != b)
      {
        array[i + j] = '1';
        if (index == 0) // 找出第一个 1
        {
          index = i + j;
          // printf("index %d\n", index);
        }
      }
      else
      {
        array[i + j] = '0';
      }
    }
    // printf("%s\n", array);
    if (index)
    {
      i = index;
    }
    else
    {
      i += BASELENGTH;
    }
  }
  printf("冗余结果二进制：%s\n", array);

  int n = 0;
  //取最后 3 位
  unsigned long res_length = strlen(array) - 1;
  // printf("------res_length %d-------\n", res_length);
  for (int i = res_length; i > res_length - 3; i--)
  {
    // printf("------2 ^ (%d) %f-------\n", res_length - i, pow(2, res_length - i));
    int number = array[i] == '0' ? 0 : 1;
    // printf("------i: %d, number: %d-------\n", i, number);
    n += (int)(pow(2, res_length - i)) * number;
  }

  printf("冗余结果十进制：%d\n", n);

  return n;
}

// 输入 10 进制 int 型数据，返回 2 进制字符串
// 10 进制数字前不能有 0，会被识别成 8 进制
char *bin_string(int original_num)
{
  // 转二进制太麻烦了。。
  // printf("original_num: %d\n", original_num);
  char *a = malloc(sizeof(char) * 32);

  if (original_num == 0)
  {
    strcpy(a, "0");
    printf("10进制：%d 二进制：%s\n", original_num, a);
    return a;
  }

  int index = 0;
  int number = original_num;

  while (number > 0)
  {
    sprintf(a + index, "%d", number % 2);
    number = number / 2;
    index++;
  }
  a[index] = '\0';
  // printf("--%d--\n", index);
  index--;
  // 逆序
  for (int i = 0; i <= index / 2; i++)
  {
    char temp = a[i];
    a[i] = a[index - i];
    a[index - i] = temp;
  }

  printf("10进制：%d 二进制：%s\n", original_num, a);
  return a;
}

int check_crc(int original_number, int remender)
{
  printf("----------CRC 检查---------\n");
  char *original_data = bin_string(original_number);
  char *remender_data = bin_string(remender);
  printf("原始数据二进制：%s\n", original_data);
  printf("校验位二进制：%s\n", remender_data);

  for (int i = strlen(remender_data); i < BASELENGTH - 1; i++) // 不足 3 位补0
  {
    strcat(original_data, "0");
  }

  strcat(original_data, remender_data);

  printf("校验数据二进制：%s\n", original_data);
  int a = crc_remainder(original_data);

  if (original_data)
  {
    free(original_data);
    original_data = NULL;
  }
  if (remender_data)
  {
    free(remender_data);
    remender_data = NULL;
  }

  printf("----------CRC 检查---------\n");
  if (a == 0)
  {
    return 0;
  }
  return -1;
}

int crc_remainder_number(int original_num)
{
  char *original_data = bin_string(original_num);
  if (!original_data)
  {
    return -1;
  }

  int res = crc_remainder(original_data);
  return res;
}
