/* Copyright 2011; All Rights Reserved
 * Please see http://www.coactionos.com/license.html for
 * licensing information.
 */

/*! \addtogroup DMA Direct Memory Access (DMA)
 * @{
 *
 * \ingroup CORE
 *
 * \details The Direct memory access allows for direct memory transfers from memory to memory or
 * memory to/from peripherals.  Various peripheral APIs use the DMA to asynchronously read/write
 * peripheral data.  The DMA should not be used directly by the application because it
 * may conflict with peripheral IO's use of the DMA.
 *
 *
 *
 */

/*! \file
 * \brief Direct Memory Access Header File
 *
 */

#ifndef DMA_H_
#define DMA_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef dma_no_sleep_ram
/* \details This attribute can be applied to RAM so
 * that it is stored in RAM that is not shut off
 * when the processor sleeps.  This allows DMA operations
 * to continue during sleep.
 *
 * Example:
 * \code
 * dma_no_sleep_ram static char buffer[512];
 * \endcode
 */
#define dma_no_sleep_ram
#endif

typedef struct dma_lli_t{
	const void * src;
	void * dest;
	struct dma_lli_t * next;
	uint32_t ctrl;
} dma_lli_t;


/*! \details This lists the valid DMA operations.
 */
enum {
	DMA_MEM_TO_MEM /*! A memory to memory DMA operation */,
	DMA_MEM_TO_PERIPH /*! A memory to peripheral DMA operation */,
	DMA_PERIPH_TO_MEM /*! A peripheral to memory DMA operation */,
	DMA_PERIPH_TO_PERIPH /*! A peripheral to peripheral DMA operation */
};


/*! \details This function opens the DMA peripheral.
 */
void hwpl_dma_open(int port /*! The port number */,
		int mode /*! Flags which specify how the DMA is configured */);


/*! \details This function creates a new callback associated
 * with the DMA transfer.
 */
void hwpl_dma_new_callback(int port /*! The DMA port */,
		int chan /*! The DMA channel */,
		void (*cb)(char) /*! The callback to execute */);

/*! \details This function deletes a callback creating using dma_new_callback().
 */
void hwpl_dma_del_callback(int port /*! The DMA port */,
		int chan /*! The DMA channel */);

/*! \details This function creates a new DMA list (uses malloc()).
 */
dma_lli_t * _hwpl_dma_new_list(void * dest /*! The pointer to the destination memory */,
		void * src /*! A pointer to the source memory */,
		uint32_t size /*! The number of bytes in the transfer */,
		uint32_t ctrl /*! The transfer's control value */);

/*! \details This function creates a new DMA linked list where
 * the last item is linked to the first.
 * \return A pointer to the new list or NULL if unsuccessful.
 */
dma_lli_t * _hwpl_dma_new_list_loop(void * dest /*! The pointer to the destination memory */,
		void * src /*! A pointer to the source memory */,
		uint32_t size /*! The number of bytes in the transfer */,
		uint32_t ctrl /*! The transfer's control value */);

/*! \details This function frees the memory associated with the specified linked list.
 */
void hwpl_dma_del_list(dma_lli_t * list /*! A pointer to the list */);

/*! \details  This function asynchronously does a DMA transfer.
 */
char hwpl_dma_transfer_async(int port, void * dest, void * src, int ctrl, int priority, void(*cb)(int));

/*! \details This function halts the specified DMA channel.
 */
void hwpl_dma_halt(int port /*! The DMA port to halt */,
		int chan /*! The channel to halt */);

/*! \details This function closes and disables the DMA peripheral.
 */
void hwpl_dma_close(int port);


#ifdef __cplusplus
}
#endif

#endif /* DMA_H_ */

/*! @} */
