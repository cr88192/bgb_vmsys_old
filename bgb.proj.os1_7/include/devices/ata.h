#ifndef __ATA_H__
#define __ATA_H__

#define ATA_LG_SECTSIZE 9       /* ATA sector bits */
#define ATA_SECTSIZE (1<<9)     /* ATA sector size */

#define ATAPI_LG_SECTSIZE 11    /* ATAPI sector bits */
#define ATAPI_SECTSIZE (1<<11)  /* ATAPI sector size */

#define ATA_CMD_NOP		0x00	/* do nothing */
#define ATA_CMD_RESET	0x04	/* reset */
#define ATA_CMD_RD      0x20    /* ATA/ATAPI: read a sector */
#define ATA_CMD_WR      0x30    /* ATA: write a sector */
#define ATA_CMD_PKT     0xA0    /* ATAPI: send a command packet */
#define ATA_CMD_PID     0xA1    /* ATAPI: id self */
#define ATA_CMD_RDMUL   0xC4    /* read group of sectors */
#define ATA_CMD_WRMUL   0xC5    /* write group of sectors */
#define ATA_CMD_ID      0xEC    /* ATA: identify self */

#define ATA_REG_DATA    0       /* R/W: data register */
#define ATA_REG_FEAT    1       /* W: features */
#define ATA_REG_ERR     1       /* R: error code */
#define ATA_REG_CNT     2       /* sector count */
#define ATA_REG_REASON  2       /* ATAPI: reason for irq */
#define ATA_REG_SECT    3       /* sector, LBA bits 0-7 */
#define ATA_REG_LOCYL   4       /* low byte of cylinder, LBA 8-15 */
#define ATA_REG_LOCNT   4       /* ATAPI: low byte of count */
#define ATA_REG_HICYL   5       /* high byte of cylinder, LBA 16-23 */
#define ATA_REG_HICNT   5       /* ATAPI: high byte of count */
#define ATA_REG_DRVHD   6       /* head and drive, LBA 24-27(need bit 6) */
#define ATA_REG_CMD     7       /* W: command register */
#define ATA_REG_STAT    7       /* R: status register */

#define ATA_STAT_ERR	1
#define ATA_STAT_INDEX	2
#define ATA_STAT_ECC	4
#define ATA_STAT_DRQ	8
#define ATA_STAT_SEEK	16
#define ATA_STAT_WRERR	32
#define ATA_STAT_READY	64
#define ATA_STAT_BUSY	128

#define ATA_ERR_MARK	1
#define ATA_ERR_TRK0	2
#define ATA_ERR_ABRT	4
#define ATA_ERR_ID		16
#define ATA_ERR_ECC		64
#define	ATA_ERR_BBD		128

#endif
