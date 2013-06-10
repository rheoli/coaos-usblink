/* Copyright 2011; All Rights Reserved
 * Please see http://www.coactionos.com/license.html for
 * licensing information.
 */

/*! \addtogroup EEPROM EEPROM (EE)
 *
 * @{
 *
 * \ingroup PERIPHIO
 *
 * \details The EEPROM module has functions to access the on chip EEPROM.
 *
 *
 */

/*! \file
 * \brief EEPROM Header file
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief EEPROM Attribute Data Structure
 * \details This structure defines how the control structure
 * for opening or reconfiguring the EEPROM port.
 */
typedef struct HWPL_PACK {
	uint32_t reserved;
} eeprom_attr_t;

int eeprom_open(const device_cfg_t * cfg);
int eeprom_read(const device_cfg_t * cfg, void * buf, int size);
int eeprom_write(const device_cfg_t * cfg, const void * buf, int size);
int eeprom_ioctl(const device_cfg_t * cfg, int request, void * ctl);
int eeprom_close(const device_cfg_t * cfg);


#ifdef __cplusplus
}
#endif

#endif // EEPROM_HEADER

/*! @} */
