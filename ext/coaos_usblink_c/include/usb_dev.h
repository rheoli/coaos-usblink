/* Copyright 2011; All Rights Reserved
 * Please see http://www.coactionos.com/license.html for
 * licensing information.
 */

/*! \addtogroup USB_DEV USB Device
 *
 *
 * @{
 * \ingroup CAOSLIB
 *
 */

#ifndef USB_DEV_H_
#define USB_DEV_H_

#include "config.h"

#include "hwpl.h"
#include "usb_dev_defs.h"
#include "usb_dev_typedefs.h"
#include "usb_dev_std.h"
#include "hwpl/pio.h"
#include "dev/usb.h"

#define USB_DEV_PORT 0
#define USB_DEV_ALT_SETTING_SIZE 4
extern pio_t usb_dev_connect;

int usb_dev_init(int usb_fd, const void * dev_desc, const void * cfg_desc, const void * string_desc);

static inline void usb_dev_assert_connect(void) HWPL_ALWAYS_INLINE;
/*! \details This function asserts the USB connect.  It
 * is used to pull the D+ line high.
 */
void usb_dev_assert_connect(void){
	hwpl_pio_setmask(usb_dev_connect.port, (void*)(1<<usb_dev_connect.pin) );
}


static inline void usb_dev_deassert_connect(void) HWPL_ALWAYS_INLINE;
/*! \details This function deasserts the USB connect.  It
 * is used to pull the D+ line low.
 */
void usb_dev_deassert_connect(void){
	hwpl_pio_clrmask(usb_dev_connect.port, (void*)(1<<usb_dev_connect.pin) );
}


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

void usb_feature_event(void);
void usb_configure_event(void);
void usb_interface_event(void);
void usb_dev_std_setup_stage(void);


#endif /* USB_DEVICE_H_ */

/*! @} */
