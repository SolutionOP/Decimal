#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define TRUE 0
#define FALSE 1
#define SIGN 0x80000000

typedef enum {
  s21_NORMAL_VALUE = 0,
  s21_INFINITY = 1,
  s21_NEGATIVE_INFINITY = 2,
  s21_NAN = 3,
  s21_ADDCODE = 4
} value_type_t;

typedef struct {
  int bits[4];
  value_type_t value_type;
} s21_decimal;

typedef union {
  int ui;
  float fl;
} floatbits;

s21_decimal s21_add(s21_decimal, s21_decimal);
s21_decimal s21_sub(s21_decimal, s21_decimal);
s21_decimal s21_mul(s21_decimal, s21_decimal);
s21_decimal s21_div(s21_decimal, s21_decimal);
s21_decimal s21_mod(s21_decimal, s21_decimal);
s21_decimal s21_floor(s21_decimal);
s21_decimal s21_round(s21_decimal);
s21_decimal s21_truncate(s21_decimal);
s21_decimal s21_negate(s21_decimal);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// support function

int get_bit(const s21_decimal decVar, int bit);
int get_sign(const s21_decimal *varPtr);
int get_scale(const s21_decimal *varPtr);
int scale_equalize(s21_decimal *number_1, s21_decimal *number_2);
int last_bit(s21_decimal number);
void bits_copy(s21_decimal src, s21_decimal *dest);
void convert_to_addcode(s21_decimal *number_1);
void set_scale(s21_decimal *varPtr, int scale);
void offset_left(s21_decimal *varPtr, int value_offset);
void init_struct(s21_decimal *varPtr);
void set_bit(s21_decimal *varPtr, int bit, int value);
void set_sign(s21_decimal *varPtr, int sign);
void clear_bits(s21_decimal *varPtr);
s21_decimal bit_addition(s21_decimal *less, s21_decimal *more);
s21_decimal div_only_bits(s21_decimal a, s21_decimal b, s21_decimal *buf);
s21_decimal check_for_mul(s21_decimal number_1, s21_decimal number_2);
s21_decimal check_for_add(s21_decimal number_1, s21_decimal number_2);

#define SUCESS 0
#define CONVERTING_ERROR 1

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int getFloatExp(float *src);
int getFloatSign(float *src);
int s21_is_even(s21_decimal dec1);
int is_NAN(s21_decimal *dec1, s21_decimal *dec2);
int zero_check(s21_decimal dec1, s21_decimal dec2);
int is_inf(s21_decimal *dec1, s21_decimal *dec2);
int is_neg_inf(s21_decimal *dec1, s21_decimal *dec2);
int is_negative(s21_decimal *dec1, s21_decimal *dec2);
void check_scale(s21_decimal *dec1, s21_decimal *dec2);

#endif  // SRC_S21_DECIMAL_H_
