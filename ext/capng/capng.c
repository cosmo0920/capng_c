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

#include <capng.h>

struct CapNG {};

static void capng_free(void* capng);

static const rb_data_type_t rb_capng_type = {
  "capng/capng",
  {
    0,
    capng_free,
    0,
  },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY
};

static void
capng_free(void* ptr)
{
  xfree(ptr);
}

static VALUE
rb_capng_alloc(VALUE klass)
{
  VALUE obj;
  struct CapNG* capng;
  obj = TypedData_Make_Struct(
    klass, struct CapNG, &rb_capng_type, capng);
  return obj;
}

static VALUE
rb_capng_initialize(VALUE self)
{
  return Qnil;
}

static VALUE
rb_capng_clear(VALUE self, VALUE rb_action_set)
{
  Check_Type(rb_action_set, T_FIXNUM);

  capng_clear(NUM2INT(rb_action_set));

  return Qnil;
}

static VALUE
rb_capng_fill(VALUE self, VALUE rb_action_set)
{
  Check_Type(rb_action_set, T_FIXNUM);

  capng_fill(NUM2INT(rb_action_set));

  return Qnil;
}

static VALUE
rb_capng_setpid(VALUE self, VALUE rb_pid)
{
  Check_Type(rb_pid, T_FIXNUM);

  capng_setpid(NUM2INT(rb_pid));

  return Qnil;
}

static VALUE
rb_capng_get_caps_process(VALUE self)
{
  int result = 0;
  result = capng_get_caps_process();

  if (result == 0)
    return Qtrue;
  else
    return Qfalse;
}

static VALUE
rb_capng_update(VALUE self, VALUE rb_action_set, VALUE rb_type, VALUE rb_capability)
{
  int result = 0;

  Check_Type(rb_action_set, T_FIXNUM);
  Check_Type(rb_type, T_FIXNUM);
  Check_Type(rb_capability, T_FIXNUM);

  result = capng_update(NUM2UINT(rb_action_set), NUM2INT(rb_type), NUM2UINT(rb_capability));

  if (result == 0)
    return Qtrue;
  else
    return Qfalse;
}

static VALUE
rb_capng_apply(VALUE self, VALUE rb_action_set)
{
  int result = 0;

  Check_Type(rb_action_set, T_FIXNUM);

  result = capng_apply(NUM2INT(rb_action_set));

  if (result == 0)
    return Qtrue;
  else
    return Qfalse;
}

static VALUE
rb_capng_lock(VALUE self)
{
  int result = 0;

  result = capng_lock();

  if (result == 0)
    return Qtrue;
  else
    return Qfalse;
}

static VALUE
rb_capng_change_id(VALUE self, VALUE rb_uid, VALUE rb_gid, VALUE rb_flags)
{
  int result = 0;

  result = capng_change_id(NUM2INT(rb_uid), NUM2INT(rb_gid), NUM2INT(rb_flags));

  if (result == 0)
    return Qtrue;
  else
    return Qfalse;
}

static VALUE
rb_capng_have_capabilities_p(VALUE self, VALUE rb_select_enum)
{
  int result = 0;

  result = capng_have_capabilities(NUM2INT(rb_select_enum));

  return INT2NUM(result);
}

static VALUE
rb_capng_have_capability_p(VALUE self, VALUE rb_type, VALUE rb_select_enum)
{
  int result = 0;

  result = capng_have_capability(NUM2INT(rb_type), NUM2INT(rb_select_enum));

  if (result == 1)
    return Qtrue;
  else
    return Qfalse;
}

static VALUE
rb_capng_get_caps_file(VALUE self, VALUE rb_file)
{
  int result = 0, fd = 0;
  rb_io_t *fptr = NULL;

  Check_Type(rb_file, T_FILE);

  if (NIL_P(rb_file)) {
    return Qfalse;
  }
  fptr = RFILE(rb_file)->fptr;
  fd = fptr->fd;
  result = capng_get_caps_fd(fd);

  if (result == 0)
    return Qtrue;
  else
    return Qfalse;
}

static VALUE
rb_capng_apply_caps_file(VALUE self, VALUE rb_file)
{
  int result = 0, fd = 0;
  rb_io_t *fptr = NULL;

  Check_Type(rb_file, T_FILE);

  if (NIL_P(rb_file)) {
    return Qfalse;
  }

  fptr = RFILE(rb_file)->fptr;
  fd = fptr->fd;
  result = capng_apply_caps_fd(fd);

  if (result == 0)
    return Qtrue;
  else
    return Qfalse;
}


void
Init_capng(void)
{
  rb_cCapNG = rb_define_class("CapNG", rb_cObject);

  rb_define_alloc_func(rb_cCapNG, rb_capng_alloc);

  rb_define_method(rb_cCapNG, "initialize", rb_capng_initialize, 0);
  rb_define_method(rb_cCapNG, "clear", rb_capng_clear, 1);
  rb_define_method(rb_cCapNG, "fill", rb_capng_fill, 1);
  rb_define_method(rb_cCapNG, "setpid", rb_capng_setpid, 1);
  rb_define_method(rb_cCapNG, "caps_process", rb_capng_get_caps_process, 0);
  rb_define_method(rb_cCapNG, "get_caps_process", rb_capng_get_caps_process, 0);
  rb_define_method(rb_cCapNG, "update", rb_capng_update, 3);
  rb_define_method(rb_cCapNG, "apply", rb_capng_apply, 1);
  rb_define_method(rb_cCapNG, "lock", rb_capng_lock, 0);
  rb_define_method(rb_cCapNG, "change_id", rb_capng_change_id, 3);
  rb_define_method(rb_cCapNG, "have_capabilities?", rb_capng_have_capabilities_p, 1);
  rb_define_method(rb_cCapNG, "have_capability?", rb_capng_have_capability_p, 2);
  rb_define_method(rb_cCapNG, "get_caps_file", rb_capng_get_caps_file, 1);
  rb_define_method(rb_cCapNG, "caps_file", rb_capng_get_caps_file, 1);
  rb_define_method(rb_cCapNG, "apply_caps_file", rb_capng_apply_caps_file, 1);

  Init_capng_enum(rb_cCapNG);
  Init_capng_capability(rb_cCapNG);
  Init_capng_print(rb_cCapNG);
  Init_capng_state(rb_cCapNG);
}
