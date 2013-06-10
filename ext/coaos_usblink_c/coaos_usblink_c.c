#include <ruby.h>

/* our new native method; it just returns
 * the string "bonjour!" */
static VALUE usblink_bonjour(VALUE self) {
  return rb_str_new2("bonjour!");
}

/* ruby calls this to load the extension */
void Init_coaos_usblink_c(void) {
  /* assume we haven't yet defined Hola */
  VALUE klass = rb_define_class("CoAOSUSBLink",
      rb_cObject);

  /* the hola_bonjour function can be called
   * from ruby as "Hola.bonjour" */
  rb_define_singleton_method(klass,
      "bonjour", usblink_bonjour, 0);
	  
  //rb_define_method(cTest, "add", t_add, 1);
	  
}
