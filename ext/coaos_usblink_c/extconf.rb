require 'mkmf'

$CFLAGS << ' -D__link -I./include -D__macosx'

create_makefile('coaos_usblink_c/coaos_usblink_c')
