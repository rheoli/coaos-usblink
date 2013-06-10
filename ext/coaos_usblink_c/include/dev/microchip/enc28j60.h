/* Copyright 2011; All Rights Reserved
 * Please see http://www.coactionos.com/license.html for
 * licensing information.
 */

/*! \addtogroup ENC28J60 ENC28J60 SPI to Ethernet Device
 * @{
 * \ingroup MICROCHIP
 *
 * \details This is a SPI to MAC ethernet adapter.  This driver is not implemented in this version.
 *
 */

#ifndef DEV_ENC28J60_H_
#define DEV_ENC28J60_H_


#include <stdint.h>
#include "device.h"
#include "hwdl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \details This is the enc28j60 attributes data structure.
 *
 */
typedef struct {
	uint8_t mac_addr[8] /*! \brief the MAC address */;
	bool full_duplex /*! \brief Full duplex mode setting */;
} enc28j60_attr_t;

#define ENC28J60_IOC_CHAR 'e'

/*! \brief This request starts a new packet (to be transmitted).
 * Subsequent calls to enc28j60_write() will store data in
 * the new packet.  The I_ENC28J60_SEND_TX_PKT request will
 * send the packet.  The ctl argument is NULL.
 */
#define I_ENC28J60_INITTXPKT _IOCTL(ENC28J60_IOC_CHAR, 0)
#define I_ENC28J60_INIT_TX_PKT I_ENC28J60_INITTXPKT

/*! \brief This request transmits the current packet in the transmit buffer.
 * It returns 0 if the packet was successfully transmitted.
 */
#define I_ENC28J60_SENDTXPKT _IOCTL(ENC28J60_IOC_CHAR, 1)
#define I_ENC28J60_SEND_TX_PKT I_ENC28J60_SENDTXPKT

/*! \brief This request checks to see if there is a packet currently
 * being transmitted.  It returns true if a packet is currently being
 * transmitted and false otherwise (less than zero for an error).
 */
#define I_ENC28J60_TXPKTBUSY _IOCTL(ENC28J60_IOC_CHAR, 2)
#define I_ENC28J60_TX_PKT_BUSY I_ENC28J60_TXPKTBUSY

/*! \brief This request checks to see if a new packet is ready to
 * be read from the device.  It returns the number of bytes available
 * in the packet or less than zero for an error.  The ctl argument
 * points to a memory destination for the pointer to the next packet.
 */
#define I_ENC28J60_RXPKTRDY _IOCTL(ENC28J60_IOC_CHAR, 3)
#define I_ENC28J60_RX_PKT_RDY I_ENC28J60_RXPKTRDY

/*! \brief This request finalizes the reception of a packet.  The ctl
 * value is a pointer to the next packet address in the read buffer.  This
 * value is obtained when a packet is ready using the I_ENC28J60_RXPKTRDY request.
 */
#define I_ENC28J60_RXPKTCOMPLETE _IOCTL(ENC28J60_IOC_CHAR, 4)
#define I_ENC28J60_RX_PKT_COMPLETE I_ENC28J60_RXPKTCOMPLETE

/*! \brief This function sets the ENC28J60 attributes.
 * The third argument is a pointer to a const enc28j60_attr_t structure.
 *
 */
#define I_ENC28J60_SETATTR _IOCTLW(ENC28J60_IOC_CHAR, 5, const enc28j60_attr_t)

/*! \brief This function gets the ENC28J60 attributes.
 * The third argument is a pointer to a enc28j60_attr_t structure.
 *
 */
#define I_ENC28J60_GETATTR _IOCTLR(ENC28J60_IOC_CHAR, 6, enc28j60_attr_t)

#define I_ENC28J60_TOTAL 7


#ifdef __cplusplus
}
#endif

#endif /* DEV_ENC28J60_H_ */

/*! @} */
