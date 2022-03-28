#include <check.h>

#include "s21_decimal.h"

START_TEST(compare_less) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);  // 1.2345 < 1.2
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);   // 1.2 < 1.2345

    dst1 = s21_negate(dst1);
    dst2 = s21_negate(dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), TRUE);   // -1.2345 < -1.2
    ck_assert_int_eq(s21_is_less(dst2, dst1), FALSE);  // -1.2 < -1.2345

    dst1 = s21_negate(dst1);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);  //  1.2345 < -1.2 fail
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);   //  -1.2 < 1.2345 fail

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);  // 0 < 0

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);  // +INFINITY < 0
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);   // 0 < +INFINITY

    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_less(dst1, dst2), TRUE);   // -INFINITY < 0
    ck_assert_int_eq(s21_is_less(dst2, dst1), FALSE);  // 0 < -INFINITY
}
END_TEST

START_TEST(compare_greater) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);   // 1.2345 > 1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE);  // 1.2 > 1.2345

    dst1 = s21_negate(dst1);
    dst2 = s21_negate(dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE);  // -1.2345 > -1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), TRUE);   // -1.2 > 1.2345

    dst1 = s21_negate(dst1);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);   //  1.2345 > -1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE);  //  -1.2 > 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE);  // 0 > 0

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);   // +INFINITY > 0
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE);  // 0 > +INFINITY

    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE);  // -INFINITY > 0
    ck_assert_int_eq(s21_is_greater(dst2, dst1), TRUE);   // 0 > -INFINITY
}
END_TEST

START_TEST(compare_less_or_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), FALSE);  // 1.2345 <= 1.2
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), TRUE);   // 1.2 <= 1.2345

    dst1 = s21_negate(dst1);
    dst2 = s21_negate(dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     TRUE);  // -1.2345 <= -1.2
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE);  // -1.2 <= 1.2345

    dst1 = s21_negate(dst1);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     FALSE);  //  1.2345 <= -1.2 // fail
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);  //  -1.2 <= 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), TRUE);  // 0 <= 0

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     FALSE);                                   // +INFINITY <= 0
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), TRUE);  // 0 <= +INFINITY

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_INFINITY;
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);  // +INFINITY <= +INFINITY

    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), TRUE);  // -INFINITY <= 0
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE);  // 0 <= -INFINITY

    s21_from_float_to_decimal(1726.73, &dst1);
    s21_from_float_to_decimal(1726.73, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     TRUE);  // 1726.73 <= 1726.73
}
END_TEST

START_TEST(compare_greater_or_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE);  // 1.2345 >= 1.2
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE);  // 1.2 >= 1.2345

    dst1 = s21_negate(dst1);
    dst2 = s21_negate(dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     FALSE);  // -1.2345 >= -1.2
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     TRUE);  // -1.2 >= 1.2345

    dst1 = s21_negate(dst1);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE);  //  1.2345 >= -1.2 // fail
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE);  //  -1.2 >= 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2), TRUE);  // 0 >= 0

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE);  // +INFINITY >= 0
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE);  // 0 >= +INFINITY

    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     FALSE);  // -INFINITY >= 0
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     TRUE);  // 0 >= -INFINITY
}
END_TEST

START_TEST(compare_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);  // 1.2345 = 1.2

    s21_from_float_to_decimal(1.2, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NEGATIVE_INFINITY;
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);  // 1.2 = 1.2

    s21_from_float_to_decimal(-234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);

    s21_from_float_to_decimal(234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_INFINITY;
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);  // +INFINITY = +INFINITY
}
END_TEST

START_TEST(compare_equal_null) {
    s21_decimal dst1, dst2;
    s21_from_int_to_decimal(0, &dst1);  // -0 == 0
    s21_from_int_to_decimal(0, &dst2);
    dst1.bits[3] = SIGN;
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);
    s21_from_int_to_decimal(0, &dst1);  // NAN == NAN
    s21_from_int_to_decimal(0, &dst2);
    dst1.value_type = s21_NAN;
    dst2.value_type = s21_NAN;
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);
}
END_TEST

START_TEST(compare_not_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), TRUE);  // 1.2345 = 1.2

    s21_from_float_to_decimal(1.2, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);  // 1.2 = 1.2

    s21_from_float_to_decimal(-234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NEGATIVE_INFINITY;
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);

    s21_from_float_to_decimal(234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);
}
END_TEST

START_TEST(s21_add_1) {
    s21_decimal src1, src2;
    int a = -1234;
    float b = 1.234;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1232.766;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_2) {
    s21_decimal src1, src2;
    int a = -1234;
    float b = -1.234;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1235.234;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_3) {
    s21_decimal src1, src2;
    int a = -46;
    float b = 0.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_int_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_add_4) {
    s21_decimal src1, src2;
    float a = -1234;
    float b = -221.234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1455.234;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_5) {
    s21_decimal src1, src2;
    int a = -1234;
    float b = -221.234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1455.234;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_6) {
    s21_decimal src1, src2;
    float a = -1.0 / 0.0;
    int b = 202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_add_7) {
    s21_decimal src1, src2;
    float a = -9403;
    float b = 0.00234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -9402.99766;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_8) {
    s21_decimal src1, src2;
    int a = -9403;
    int b = 234;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -9169;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_9) {
    s21_decimal src1, src2;
    float a = -940.3;
    float b = 0.000234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -940.299766;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_10) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = 0.000234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -0.940066;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_11) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = 2.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 1.0831;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_12) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 112.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od;
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_add_13) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = -112.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -112.9637;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_14) {
    s21_decimal src1, src2;
    float a = -0.94e03;
    float b = -112.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1052.0234;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_15) {
    s21_decimal src1, src2;
    float a = -0.94e03;
    float b = -112.0e2;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -12140;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_16) {
    s21_decimal src1, src2;
    int a = 9403;
    int b = 202;
    int res_origin = 9605;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_17) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x300000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xF;
    src1.bits[0] = 0x67E4FEEF;
    src2.bits[3] = 0x300000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFF;
    src2.bits[0] = 0x67E4FFFF;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x300000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x10E;
    result_origin.bits[0] = 0xCFC9FEEE;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_add_18) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFF;
    src1.bits[0] = 0x67E4F;
    src2.bits[3] = 0x60000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xEA;
    src2.bits[0] = 0x67E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x60000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x3E502;
    result_origin.bits[0] = 0x1963E2E7;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_add_19) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x70000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_add_20) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_add_21) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x70000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_sub_1) {
    s21_decimal src1, src2;
    int a = 9403;
    int b = 202;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = 9201;
    s21_decimal res_od = s21_sub(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_sub_2) {
    s21_decimal src1, src2;
    int a = 9403;
    float b = 202.098;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 9200.902;
    s21_decimal res_od = s21_sub(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_sub_3) {
    s21_decimal src1, src2;
    float a = -9403;
    float b = 202.098;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a - b;
    s21_decimal res_od = s21_sub(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_sub_4) {
    s21_decimal src1, src2;
    float a = 9403.0;
    float b = 202.09e8;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -20208990597;
    s21_decimal res_od = s21_sub(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_sub_5) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    float b = 202.09e8;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -20208059700;
    s21_decimal res_od = s21_sub(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_sub_6) {
    s21_decimal src1, src2;
    float a = -9403.0e2;
    int b = -202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = a - b;
    s21_decimal res_od = s21_sub(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_sub_7) {
    s21_decimal src1, src2;
    float a = -1.0 / 0.0;
    int b = 202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_sub(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_sub_8) {
    s21_decimal src1, src2;
    float a = -94;
    float b = -202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a - b;
    s21_decimal res_od = s21_sub(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_sub_9) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b00000000000000010000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000000000110011011110000;
    src2.bits[3] = 0b00000000000000110000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00000000000001000101000111010110;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b00000000000000110000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00000000001000111110001111101010;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_10) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b00000000000000110000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000001000101000111010110;
    src2.bits[3] = 0b00000000000000010000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00000000000000000000101110111100;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b10000000000000110000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00000000000000000100001110011010;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_11) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_12) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x70000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_13) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b10000000000000010000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000000000000000100110000;
    src2.bits[3] = 0b10000000000001100000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00010001001000010001101001100000;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b00000000000001100000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00001111010100010011110001100000;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_14) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x70000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_15) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00000000000000000000011111100100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    src2.bits[0] = 0b00000101100110111101101000011001;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result, result_our;
    result_our = s21_sub(src2, src1);
    result.value_type = s21_NORMAL_VALUE;
    result.bits[0] = 0b00000101100110111101001000110101;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(result.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_16) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00000000000000000000011111100100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000000000000000000000;
    src2.bits[0] = 0b00000000000000000010010010111011;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal result, result_our;
    result_our = s21_sub(src2, src1);
    result.value_type = s21_NORMAL_VALUE;
    result.bits[0] = 0b00000000000000000001110011010111;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(result.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_mul_1) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    int b = 202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = 189940600;
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_mul_2) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    float b = 9403.0e2;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 884164090000;
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_mul_3) {
    s21_decimal src1, src2;
    int a = 9403;
    int b = 202;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = 1899406;
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_mul_4) {
    s21_decimal src1, src2;
    int a = -32768;
    int b = 2;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -65536;
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_mul_5) {
    s21_decimal src1, src2;
    int a = -32768;
    int b = 32768;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -1073741824;
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_mul_6) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    int b = 0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_int_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_7) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 132;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_8) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 1.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_9) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 0.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_10) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = -1.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_11) {
    s21_decimal src1, src2;
    float a = -1.0 / 0.0;
    float b = 123;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_12) {
    s21_decimal src1, src2;
    float a = -1.0 / 0.0;
    float b = -123;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_13) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 132;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src2, src1);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_14) {
    s21_decimal src1, src2;
    float a = -1.0 / 0.0;
    float b = 123;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src2, src1);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_15) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    int b = 0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src2, src1);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_16) {
    s21_decimal src1, src2;
    float a = -1.0 / 0.0;
    float b = 0.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src2, src1);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_17) {
    s21_decimal src1, src2;
    float a = -1.0 / 0.0;
    float b = 0.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_mul_18) {
    s21_decimal src1, src2;
    float a = 0.0 / 0.0;
    float b = 0.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_mul(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(s21_mod_1) {
    s21_decimal src1, src2, res_mod;
    int a = 3;
    int b = 2;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_2) {
    s21_decimal src1, src2, res_mod;
    int a = -98765;
    int b = 1234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_3) {
    s21_decimal src1, src2, res_mod;
    int a = 30198;
    int b = 20210;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_4) {
    s21_decimal src1, src2, res_mod;
    int a = -98765;
    int b = -1234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_5) {
    s21_decimal src1, src2, res_mod;
    int a = 98765;
    int b = 127234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_6) {
    s21_decimal src1, src2, res_mod;
    int a = 342576;
    int b = 1542134;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_7) {
    s21_decimal src1, src2, res_mod;
    float a = 1.2;
    float b = 0.3;
    float res_origin = fmod(a, b);
    float res = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_float(res_mod, &res);
    ck_assert_float_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_8) {
    s21_decimal src1, src2, res_mod;
    float a = 1.2;
    int b = 3;
    float res_origin = fmod(a, b);
    float res = 0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_float(res_mod, &res);
    ck_assert_float_eq(res_origin, res);
}
END_TEST

START_TEST(s21_div_1) {
    s21_decimal src1, src2;
    float a = 9403.0e2;
    int b = 202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = 4654.950495049504950495049505;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_2) {
    s21_decimal src1, src2;
    int a = -32768;
    int b = 2;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -16384;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_3) {
    s21_decimal src1, src2;
    float a = -9403.0e2;
    float b = -2020.29;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 465.4282306005573457275935633;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_4) {
    s21_decimal src1, src2;
    float a = -9403.0e2;
    float b = 2020.29;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -465.4282306005573457275935633;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_5) {
    s21_decimal src1, src2;
    float a = -9403.0e20;
    float b = 2.28e17;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_6) {
    s21_decimal src1, src2;
    float a = -0.9;
    float b = 30.323;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_7) {
    s21_decimal src1, src2;
    float a = -0.9e3;
    float b = 30.32;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_8) {
    s21_decimal src1, src2;
    float a = -0.9e3;
    int b = 30;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_9) {
    s21_decimal src1, src2;
    float a = -0.9;
    float b = 0.000076;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = a / b;
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_div_10) {
    s21_decimal src1, src2, src3;
    src1.value_type = s21_INFINITY;
    src2.value_type = s21_INFINITY;
    src3.value_type = s21_NAN;
    s21_decimal res_od = s21_div(src1, src2);
    ck_assert_int_eq(res_od.value_type, src3.value_type);
}
END_TEST
START_TEST(s21_div_11) {
    s21_decimal src1, src2, src3;
    s21_from_int_to_decimal(10, &src1);
    s21_from_int_to_decimal(0, &src2);
    src3.value_type = s21_INFINITY;
    s21_decimal res_od = s21_div(src1, src2);

    ck_assert_int_eq(res_od.value_type, src3.value_type);
}
END_TEST
START_TEST(s21_div_12) {
    s21_decimal src1, src2;
    s21_from_int_to_decimal(-10, &src1);
    src1.value_type = s21_INFINITY;
    src2.value_type = s21_NEGATIVE_INFINITY;
    s21_decimal res_od = s21_div(src1, src2);
    ck_assert_int_eq(res_od.value_type, s21_NAN);
}
END_TEST
START_TEST(s21_div_13) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 1.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_div(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_div_15) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01110001001110010011101000100111;
    src1.bits[1] = 0b00000000000000000000000011100010;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000001010000000000000000;
    src2.bits[0] = 0b00000000000000010111101111011011;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000100000000000000000;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[0] = 0b00100000111100011100110110110001;
    result_origin.bits[1] = 0b01011000000100101111110011101001;
    result_origin.bits[2] = 0b00100000010100001110111000110111;
    result_origin.bits[3] = 0b00000000000110000000000000000000;
    s21_decimal res_od = s21_div(src1, src2);
    float a, b;
    s21_from_decimal_to_float(result_origin, &a);
    s21_from_decimal_to_float(res_od, &b);
    ck_assert_float_eq(a, b);
}
END_TEST
START_TEST(s21_div_16) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00010001100000110100010101000111;
    src1.bits[1] = 0b00000000000000101011011100110010;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000001010000000000000000;
    src2.bits[0] = 0b01111001000001000011011001001011;
    src2.bits[1] = 0b00000000000000000101010011111111;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000001010000000000000000;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[0] = 0b01000111110000001001001101101011;
    result_origin.bits[1] = 0b10111000000101111000101110100000;
    result_origin.bits[2] = 0b00011010011011010111110000110100;
    result_origin.bits[3] = 0b00000000000110110000000000000000;
    s21_decimal res_od = s21_div(src1, src2);
    float a, b;
    s21_from_decimal_to_float(result_origin, &a);
    s21_from_decimal_to_float(res_od, &b);
    ck_assert_float_eq(a, b);
}
END_TEST
START_TEST(s21_div_17) {
    s21_decimal src1, src2;
    int a = -17272;
    float b = -1.0 / 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_div(src1, src2);
    s21_decimal zero = {{0, 0, 0, 0}, s21_NORMAL_VALUE};
    ck_assert_int_eq(!!(s21_is_equal(res_od, zero) == TRUE), 1);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST
START_TEST(s21_div_18) {
    s21_decimal src1, src2, src3;
    src1.value_type = s21_INFINITY;
    src2.value_type = s21_NAN;
    src3.value_type = s21_NAN;
    s21_decimal res_od = s21_div(src1, src2);
    ck_assert_int_eq(res_od.value_type, src3.value_type);
}
END_TEST
START_TEST(s21_div_19) {
    s21_decimal src1, src2;
    float a = -115.2;
    float b = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_div(src1, src2);

    ck_assert_int_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    ck_assert_int_eq(res_od.bits[2], 0);
    ck_assert_int_eq(res_od.bits[1], 0);
    ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(s21_trun_1) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x000A0000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0x0;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x6DF37F67;
    s21_decimal res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_trun_2) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x800C0000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0x80000000;
    result.bits[2] = 0x0;
    result.bits[1] = 0x0;
    result.bits[0] = 0x1197998;
    s21_decimal res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_trun_3) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80000000;
    src1.bits[2] = 0x0;
    src1.bits[1] = 0xFFFFFFFF;
    src1.bits[0] = 0xFFFFFFFF;
    s21_decimal result;
    result.bits[3] = 0x80000000;
    result.bits[2] = 0x0;
    result.bits[1] = 0xFFFFFFFF;
    result.bits[0] = 0xFFFFFFFF;
    s21_decimal res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_trun_4) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00000000000000000000000001101101;
    src1.bits[1] = 0b00000000000011000110010101011011;
    src1.bits[2] = 0b00000000000000000011000000111001;
    src1.bits[3] = 0b00000000000011100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b10000111101111000001011000011110;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_trun_5) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b11011110101001001000000010110110;
    src1.bits[1] = 0b01011111101001011101111110100000;
    src1.bits[2] = 0b00011111111010011010111101100000;
    src1.bits[3] = 0b00000000000010010000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00110100101011011100000100111110;
    result.bits[1] = 0b10001001000100001000011110111001;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_trun_6) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80090000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFFEA34;
    src1.bits[0] = 0xFF837E4F;
    s21_decimal result = s21_truncate(src1);
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x4;
    result_origin.bits[0] = 0x4B829C70;
    ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST
START_TEST(s21_trun_7) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b11010000101000110011000001101101;
    src1.bits[1] = 0b00011111100110100110101101011000;
    src1.bits[2] = 0;
    src1.bits[3] = 0b00000000000010010000000000000000;
    s21_decimal result = s21_truncate(src1);
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b10000111101111000001011000011110;
    ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST
START_TEST(s21_trun_8) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01111000101001111011110011000110;
    src1.bits[1] = 0b10011111111111001111101010000100;
    src1.bits[2] = 0b00011111111010011010111101101101;
    src1.bits[3] = 0b00000000000111000000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_trun_9) {
    s21_decimal src1;
    float a = 1.0 / 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_decimal res_od = s21_truncate(src1);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
}
END_TEST

START_TEST(s21_round_1) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01100011000011111111111111111111;
    src1.bits[1] = 0b01101011110001110101111000101101;
    src1.bits[2] = 0b00000000000000000000000000000101;
    src1.bits[3] = 0b10000000000010100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b01010100000010111110010000000000;
    result.bits[1] = 0b00000000000000000000000000000010;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res_od = s21_round(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_2) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01010101001110101110101110110001;
    src1.bits[1] = 0b00001101101101001101101001011111;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000100100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000001;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res_od = s21_round(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_3) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10010011111100000001110001010010;
    src1.bits[1] = 0b00000000000000000000000100100000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000010100000000000000000;
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000001111100;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res_od = s21_round(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_4) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b11001101110001110111110001000000;
    src1.bits[1] = 0b00111110001001010000001001100000;
    src1.bits[2] = 0b00100000010011111100111001011110;
    src1.bits[3] = 0b10000000000001000000000000000000;
    s21_decimal result;
    result.bits[0] = 0b10100000111111100100111000000100;
    result.bits[1] = 0b00011011110011101100110011101101;
    result.bits[2] = 0b00000000000000001101001111000010;
    result.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal res_od = s21_round(src1);
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_5) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10100000111111100100111000000100;
    src1.bits[1] = 0b00011011110011101100110011101101;
    src1.bits[2] = 0b00000000000000001101001111000010;
    src1.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res_od = s21_round(src1);
    s21_decimal result;
    result.bits[0] = 0b10100000111111100100111000000100;
    result.bits[1] = 0b00011011110011101100110011101101;
    result.bits[2] = 0b00000000000000001101001111000010;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_6) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10010111011100111001111111111111;
    src1.bits[1] = 0b00111100000010000011000110001101;
    src1.bits[2] = 0b00000000000000000000000000000001;
    src1.bits[3] = 0b00000000000001110000000000000000;
    s21_decimal res_od = s21_round(src1);
    s21_decimal result;
    result.bits[3] = 0;
    result.bits[2] = 0;
    result.bits[1] = 0b00000000000000000000001000010010;
    result.bits[0] = 0b00110110101101101000110001000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_7) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10010111011100111001111111111111;
    src1.bits[1] = 0b00111100000010000011000110001101;
    src1.bits[2] = 0b00000000000000000000000000000001;
    src1.bits[3] = 0b10000000000001110000000000000000;
    s21_decimal res_od = s21_round(src1);
    s21_decimal result;
    result.bits[3] = 0b10000000000000000000000000000000;
    result.bits[2] = 0;
    result.bits[1] = 0b00000000000000000000001000010010;
    result.bits[0] = 0b00110110101101101000110001000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_8) {
    s21_decimal src1;
    float a = -1.0 / 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_decimal res_od = s21_round(src1);
    ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
}
END_TEST

START_TEST(s21_floor_1) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00001111111111111111111111111111;
    src1.bits[1] = 0b00111110001001010000001001100001;
    src1.bits[2] = 0b00100000010011111100111001011110;
    src1.bits[3] = 0b00000000000010100000000000000000;
    s21_decimal res_od = s21_floor(src1);
    s21_decimal result;
    result.bits[0] = 0b10100111011000111111111111111111;
    result.bits[1] = 0b00001101111000001011011010110011;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_2) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00001111111111111111111111111111;
    src1.bits[1] = 0b00111110001001010000001001100001;
    src1.bits[2] = 0b00100000010011111100111001011110;
    src1.bits[3] = 0b10000000000010100000000000000000;
    s21_decimal res_od = s21_floor(src1);
    s21_decimal result;
    result.bits[0] = 0b10100111011001000000000000000000;
    result.bits[1] = 0b00001101111000001011011010110011;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_3) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10111101001001111000010001010010;
    src1.bits[1] = 0b00000000000000000000000000011100;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000010010000000000000000;
    s21_decimal res_od = s21_floor(src1);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000001111100;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_4) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10010011111100000001110001010010;
    src1.bits[1] = 0b00000000000000000000000100100000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000010100000000000000000;
    s21_decimal res_od = s21_floor(src1);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000001111011;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_5) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01010101001110101110101110110001;
    src1.bits[1] = 0b00001101101101001101101001011111;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000100100000000000000000;
    s21_decimal res_od = s21_floor(src1);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000001;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_6) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b01010101001110101110101110110001;
    src1.bits[1] = 0b00001101101101001101101001011111;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000100100000000000000000;
    s21_decimal res_od = s21_floor(src1);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000000000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_float_eq(res_od.bits[0], result.bits[0]);
    ck_assert_float_eq(res_od.bits[1], result.bits[1]);
    ck_assert_float_eq(res_od.bits[2], result.bits[2]);
    ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_7) {
    s21_decimal src1;
    src1.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b10010111011100111001111111111111;
    src1.bits[1] = 0b00111100000010000011000110001101;
    src1.bits[2] = 0b00000000000000000000000000000001;
    src1.bits[3] = 0b00000000000001110000000000000000;
    s21_decimal result = s21_floor(src1);
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0b00000000000000000000001000010010;
    result_origin.bits[0] = 0b00110110101101101000110000111111;
    ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST
START_TEST(s21_floor_8) {
    s21_decimal src1;
    float a = 0.0 / 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_decimal res_od = s21_floor(src1);
    ck_assert_float_eq(res_od.value_type, s21_NAN);
}
END_TEST

START_TEST(s21_negate_1) {
    int a = 10;
    int res_a = 0;
    s21_decimal src;
    s21_from_int_to_decimal(a, &src);
    s21_decimal res = s21_negate(src);
    s21_from_decimal_to_int(res, &res_a);
    ck_assert_int_eq(-10, res_a);
}
END_TEST
START_TEST(s21_negate_2) {
    float a = 10.12345;
    float res_a = 0;
    s21_decimal src;
    s21_from_float_to_decimal(a, &src);
    s21_decimal res = s21_negate(src);
    s21_from_decimal_to_float(res, &res_a);
    ck_assert_float_eq(-10.12345, res_a);
}
END_TEST
START_TEST(s21_negate_3) {
    float a = 10.1234e5;
    float res_a = 0;
    s21_decimal src;
    s21_from_float_to_decimal(a, &src);
    s21_decimal res = s21_negate(src);
    s21_from_decimal_to_float(res, &res_a);
    ck_assert_float_eq(-10.1234e5, res_a);
}
END_TEST

START_TEST(s21_from_int_to_decimal_1) {
    s21_decimal val;

    s21_from_int_to_decimal(0, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_int_to_decimal(-128, &val);
    ck_assert_int_eq(val.bits[0], 128);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147483648);

    s21_from_int_to_decimal(127, &val);
    ck_assert_int_eq(val.bits[0], 127);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_int_to_decimal(-2147483648, &val);
    ck_assert_int_eq(val.bits[0], -2147483648);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147483648);

    s21_from_int_to_decimal(2147483647, &val);
    ck_assert_int_eq(val.bits[0], 2147483647);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_1) {
    s21_decimal val;

    s21_from_float_to_decimal(0.03, &val);
    ck_assert_int_eq(val.bits[0], 3);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 131072);

    s21_from_float_to_decimal(127.1234, &val);
    ck_assert_int_eq(val.bits[0], 1271234);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 262144);
}
END_TEST
START_TEST(s21_from_float_to_decimal_2) {
    s21_decimal val;
    s21_from_float_to_decimal(-128.023, &val);
    ck_assert_int_eq(val.bits[0], 12802299);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147155968);
}
END_TEST
START_TEST(s21_from_float_to_decimal_3) {
    s21_decimal val;
    s21_from_float_to_decimal(-2.1474836E+09, &val);
    ck_assert_int_eq(val.bits[0], -2147483648);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147483648);
}
END_TEST
START_TEST(s21_from_float_to_decimal_4) {
    s21_decimal val;
    s21_from_float_to_decimal(22.14836E+03, &val);
    ck_assert_int_eq(val.bits[0], 2214836);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 131072);
}
END_TEST
START_TEST(s21_from_float_to_decimal_5) {
    s21_decimal val;
    s21_from_float_to_decimal(1.02E+09, &val);
    ck_assert_int_eq(val.bits[0], 1020000000);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_6) {
    s21_decimal val;
    s21_from_float_to_decimal(-333.2222, &val);
    ck_assert_int_eq(val.bits[0], 3332222);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147221504);
}
END_TEST
START_TEST(s21_from_float_to_decimal_7) {
    s21_decimal val;
    float a = 1.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_8) {
    s21_decimal val;
    float a = -1.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_9) {
    s21_decimal val;
    float a = 0.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_1) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = INT_MAX;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_float_eq(number, 2147483647);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_2) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 133141;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, 133141);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_3) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 2147483647;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    set_sign(&src, 1);
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, -2147483647);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_4) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 123451234;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147483648;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, -123451234);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_5) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 18;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147483648;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, -18);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_6) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 4294967295;
    src.bits[1] = 4294967295;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, 0xFFFFFFFFFFFFFFFF);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 18122;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147680256;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, -18.122);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_2) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 1812;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147483648;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, -1812);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_3) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 0XFFFFFF;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, 16777215);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_4) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 23450987;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147745792;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, -2345.0987);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_5) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 4294967295;
    src.bits[1] = 4294967295;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
    ck_assert_int_eq(result, 0);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Suite");
    SRunner *sr = srunner_create(s1);

    TCase *tc1_1 = tcase_create("tests");
    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, compare_less);
    tcase_add_test(tc1_1, compare_greater);
    tcase_add_test(tc1_1, compare_less_or_equal);
    tcase_add_test(tc1_1, compare_greater_or_equal);
    tcase_add_test(tc1_1, compare_equal);
    tcase_add_test(tc1_1, compare_equal_null);
    tcase_add_test(tc1_1, compare_not_equal);

    tcase_add_test(tc1_1, s21_add_1);
    tcase_add_test(tc1_1, s21_add_2);
    tcase_add_test(tc1_1, s21_add_3);
    tcase_add_test(tc1_1, s21_add_4);
    tcase_add_test(tc1_1, s21_add_5);
    tcase_add_test(tc1_1, s21_add_6);
    tcase_add_test(tc1_1, s21_add_7);
    tcase_add_test(tc1_1, s21_add_8);
    tcase_add_test(tc1_1, s21_add_9);
    tcase_add_test(tc1_1, s21_add_10);
    tcase_add_test(tc1_1, s21_add_11);
    tcase_add_test(tc1_1, s21_add_12);
    tcase_add_test(tc1_1, s21_add_13);
    tcase_add_test(tc1_1, s21_add_14);
    tcase_add_test(tc1_1, s21_add_15);
    tcase_add_test(tc1_1, s21_add_16);
    tcase_add_test(tc1_1, s21_add_17);
    tcase_add_test(tc1_1, s21_add_18);
    tcase_add_test(tc1_1, s21_add_19);
    tcase_add_test(tc1_1, s21_add_20);
    tcase_add_test(tc1_1, s21_add_21);

    tcase_add_test(tc1_1, s21_sub_1);
    tcase_add_test(tc1_1, s21_sub_2);
    tcase_add_test(tc1_1, s21_sub_3);
    tcase_add_test(tc1_1, s21_sub_4);
    tcase_add_test(tc1_1, s21_sub_5);
    tcase_add_test(tc1_1, s21_sub_6);
    tcase_add_test(tc1_1, s21_sub_7);
    tcase_add_test(tc1_1, s21_sub_8);
    tcase_add_test(tc1_1, s21_sub_9);
    tcase_add_test(tc1_1, s21_sub_10);
    tcase_add_test(tc1_1, s21_sub_11);
    tcase_add_test(tc1_1, s21_sub_12);
    tcase_add_test(tc1_1, s21_sub_13);
    tcase_add_test(tc1_1, s21_sub_14);
    tcase_add_test(tc1_1, s21_sub_15);
    tcase_add_test(tc1_1, s21_sub_16);

    tcase_add_test(tc1_1, s21_mul_1);
    tcase_add_test(tc1_1, s21_mul_2);
    tcase_add_test(tc1_1, s21_mul_3);
    tcase_add_test(tc1_1, s21_mul_4);
    tcase_add_test(tc1_1, s21_mul_5);
    tcase_add_test(tc1_1, s21_mul_6);
    tcase_add_test(tc1_1, s21_mul_7);
    tcase_add_test(tc1_1, s21_mul_8);
    tcase_add_test(tc1_1, s21_mul_9);
    tcase_add_test(tc1_1, s21_mul_10);
    tcase_add_test(tc1_1, s21_mul_11);
    tcase_add_test(tc1_1, s21_mul_12);
    tcase_add_test(tc1_1, s21_mul_13);
    tcase_add_test(tc1_1, s21_mul_14);
    tcase_add_test(tc1_1, s21_mul_15);
    tcase_add_test(tc1_1, s21_mul_16);
    tcase_add_test(tc1_1, s21_mul_17);
    tcase_add_test(tc1_1, s21_mul_18);

    tcase_add_test(tc1_1, s21_mod_1);
    tcase_add_test(tc1_1, s21_mod_2);
    tcase_add_test(tc1_1, s21_mod_3);
    tcase_add_test(tc1_1, s21_mod_4);
    tcase_add_test(tc1_1, s21_mod_5);
    tcase_add_test(tc1_1, s21_mod_6);
    tcase_add_test(tc1_1, s21_mod_7);
    tcase_add_test(tc1_1, s21_mod_8);

    tcase_add_test(tc1_1, s21_div_1);
    tcase_add_test(tc1_1, s21_div_2);
    tcase_add_test(tc1_1, s21_div_3);
    tcase_add_test(tc1_1, s21_div_4);
    tcase_add_test(tc1_1, s21_div_5);
    tcase_add_test(tc1_1, s21_div_6);
    tcase_add_test(tc1_1, s21_div_7);
    tcase_add_test(tc1_1, s21_div_8);
    tcase_add_test(tc1_1, s21_div_9);
    tcase_add_test(tc1_1, s21_div_10);
    tcase_add_test(tc1_1, s21_div_11);
    tcase_add_test(tc1_1, s21_div_12);
    tcase_add_test(tc1_1, s21_div_13);
    tcase_add_test(tc1_1, s21_div_15);
    tcase_add_test(tc1_1, s21_div_16);
    tcase_add_test(tc1_1, s21_div_17);
    tcase_add_test(tc1_1, s21_div_18);
    tcase_add_test(tc1_1, s21_div_19);

    tcase_add_test(tc1_1, s21_trun_1);
    tcase_add_test(tc1_1, s21_trun_2);
    tcase_add_test(tc1_1, s21_trun_3);
    tcase_add_test(tc1_1, s21_trun_4);
    tcase_add_test(tc1_1, s21_trun_5);
    tcase_add_test(tc1_1, s21_trun_6);
    tcase_add_test(tc1_1, s21_trun_7);
    tcase_add_test(tc1_1, s21_trun_8);
    tcase_add_test(tc1_1, s21_trun_9);

    tcase_add_test(tc1_1, s21_round_1);
    tcase_add_test(tc1_1, s21_round_2);
    tcase_add_test(tc1_1, s21_round_3);
    tcase_add_test(tc1_1, s21_round_4);
    tcase_add_test(tc1_1, s21_round_5);
    tcase_add_test(tc1_1, s21_round_6);
    tcase_add_test(tc1_1, s21_round_7);
    tcase_add_test(tc1_1, s21_round_8);

    tcase_add_test(tc1_1, s21_floor_1);
    tcase_add_test(tc1_1, s21_floor_2);
    tcase_add_test(tc1_1, s21_floor_3);
    tcase_add_test(tc1_1, s21_floor_4);
    tcase_add_test(tc1_1, s21_floor_5);
    tcase_add_test(tc1_1, s21_floor_6);
    tcase_add_test(tc1_1, s21_floor_7);
    tcase_add_test(tc1_1, s21_floor_8);

    tcase_add_test(tc1_1, s21_negate_1);
    tcase_add_test(tc1_1, s21_negate_2);
    tcase_add_test(tc1_1, s21_negate_3);

    tcase_add_test(tc1_1, s21_from_int_to_decimal_1);

    tcase_add_test(tc1_1, s21_from_float_to_decimal_1);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_2);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_3);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_4);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_5);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_6);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_7);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_8);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_9);

    tcase_add_test(tc1_1, s21_from_decimal_to_int_1);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_2);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_3);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_4);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_5);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_6);

    tcase_add_test(tc1_1, s21_from_decimal_to_float_1);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_2);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_3);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_4);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_5);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);

    return 0;
}
