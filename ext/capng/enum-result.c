/* capng_c */
/* Copyright 2020- Hiroshi Hatake*/
/* */
/* Licensed under the Apache License, Version 2.0 (the "License"); */
/* you may not use this file except in compliance with the License. */
/* You may obtain a copy of the License at */
/*     http://www.apache.org/licenses/LICENSE-2.0 */
/* Unless required by applicable law or agreed to in writing, software */
/* distributed under the License is distributed on an "AS IS" BASIS, */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/* See the License for the specific language governing permissions and */
/* limitations under the License. */

/* clang-format off */
/*
 * Document-module: CapNG::Result
 *
 * Define FAIL, NONE, PARTAIL, and FULL constants.
 */
/* clang-format on */

#include <capng.h>

void
Init_capng_enum_result(VALUE rb_cCapNG)
{
  VALUE rb_mResult = rb_define_module_under(rb_cCapNG, "Result");

  // capng_result_t enum constants
  /* Fail to retrieve result */
  rb_define_const(rb_mResult, "FAIL", LONG2NUM(CAPNG_FAIL));
  /* Retrieve no result */
  rb_define_const(rb_mResult, "NONE", LONG2NUM(CAPNG_NONE));
  /* Retrieve partial result. Some capabilities are set up. */
  rb_define_const(rb_mResult, "PARTIAL", LONG2NUM(CAPNG_PARTIAL));
  /* Retrieve partial result. Full capabilities are set up. */
  rb_define_const(rb_mResult, "FULL", LONG2NUM(CAPNG_FULL));
}
