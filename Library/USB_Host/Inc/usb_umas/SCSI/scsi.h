/*
 *  scsi.h Copyright (C) 1992 Drew Eckhardt
 *         Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale
 *  generic SCSI package header file by
 *      Initial versions: Drew Eckhardt
 *      Subsequent revisions: Eric Youngdale
 *
 *  <drew@colorado.edu>
 *
 *       Modified by Eric Youngdale eric@andante.org to
 *       add scatter-gather, multiple outstanding request, and other
 *       enhancements.
 */

#ifndef _SCSI_H_
#define _SCSI_H_


/// @cond HIDDEN_SYMBOLS

/*
 * Some of the public constants are being moved to this file.
 * We include it here so that what came from where is transparent.
 */

/*
 *      SCSI opcodes
 */

#define TEST_UNIT_READY       0x00
#define REZERO_UNIT           0x01
#define REQUEST_SENSE         0x03
#define FORMAT_UNIT           0x04
#define READ_BLOCK_LIMITS     0x05
#define REASSIGN_BLOCKS       0x07
#define READ_6                0x08
#define WRITE_6               0x0a
#define SEEK_6                0x0b
#define READ_REVERSE          0x0f
#define WRITE_FILEMARKS       0x10
#define SPACE                 0x11
#define INQUIRY               0x12
#define RECOVER_BUFFERED_DATA 0x14
#define MODE_SELECT           0x15
#define RESERVE               0x16
#define RELEASE               0x17
#define COPY                  0x18
#define ERASE                 0x19
#define MODE_SENSE            0x1a
#define START_STOP            0x1b
#define RECEIVE_DIAGNOSTIC    0x1c
#define SEND_DIAGNOSTIC       0x1d
#define ALLOW_MEDIUM_REMOVAL  0x1e

#define SET_WINDOW            0x24
#define READ_CAPACITY         0x25
#define READ_10               0x28
#define WRITE_10              0x2a
#define SEEK_10               0x2b
#define WRITE_VERIFY          0x2e
#define VERIFY                0x2f
#define SEARCH_HIGH           0x30
#define SEARCH_EQUAL          0x31
#define SEARCH_LOW            0x32
#define SET_LIMITS            0x33
#define PRE_FETCH             0x34
#define READ_POSITION         0x34
#define SYNCHRONIZE_CACHE     0x35
#define LOCK_UNLOCK_CACHE     0x36
#define READ_DEFECT_DATA      0x37
#define MEDIUM_SCAN           0x38
#define COMPARE               0x39
#define COPY_VERIFY           0x3a
#define WRITE_BUFFER          0x3b
#define READ_BUFFER           0x3c
#define UPDATE_BLOCK          0x3d
#define READ_LONG             0x3e
#define WRITE_LONG            0x3f
#define CHANGE_DEFINITION     0x40
#define WRITE_SAME            0x41
#define READ_TOC              0x43
#define LOG_SELECT            0x4c
#define LOG_SENSE             0x4d
#define MODE_SELECT_10        0x55
#define RESERVE_10            0x56
#define RELEASE_10            0x57
#define MODE_SENSE_10         0x5a
#define PERSISTENT_RESERVE_IN 0x5e
#define PERSISTENT_RESERVE_OUT 0x5f
#define MOVE_MEDIUM           0xa5
#define READ_12               0xa8
#define WRITE_12              0xaa
#define WRITE_VERIFY_12       0xae
#define SEARCH_HIGH_12        0xb0
#define SEARCH_EQUAL_12       0xb1
#define SEARCH_LOW_12         0xb2
#define READ_ELEMENT_STATUS   0xb8
#define SEND_VOLUME_TAG       0xb6
#define WRITE_LONG_2          0xea

/*
 *  Status codes
 */

#define GOOD                 0x00
#define CHECK_CONDITION      0x01
#define CONDITION_GOOD       0x02
#define BUSY                 0x04
#define INTERMEDIATE_GOOD    0x08
#define INTERMEDIATE_C_GOOD  0x0a
#define RESERVATION_CONFLICT 0x0c
#define COMMAND_TERMINATED   0x11
#define QUEUE_FULL           0x14

#define STATUS_MASK          0x3e

/*
 *  SENSE KEYS
 */

#define NO_SENSE            0x00
#define RECOVERED_ERROR     0x01
#define NOT_READY           0x02
#define MEDIUM_ERROR        0x03
#define HARDWARE_ERROR      0x04
#define ILLEGAL_REQUEST     0x05
#define UNIT_ATTENTION      0x06
#define DATA_PROTECT        0x07
#define BLANK_CHECK         0x08
#define COPY_ABORTED        0x0a
#define ABORTED_COMMAND     0x0b
#define VOLUME_OVERFLOW     0x0d
#define MISCOMPARE          0x0e


/*
 *  DEVICE TYPES
 */

#define TYPE_DISK           0x00
#define TYPE_TAPE           0x01
#define TYPE_PROCESSOR      0x03    /* HP scanners use this */
#define TYPE_WORM           0x04    /* Treated as ROM by our system */
#define TYPE_ROM            0x05
#define TYPE_SCANNER        0x06
#define TYPE_MOD            0x07    /* Magneto-optical disk - 
                     * - treated as TYPE_DISK */
#define TYPE_MEDIUM_CHANGER 0x08
#define TYPE_COMM           0x09    /* Communications device */
#define TYPE_ENCLOSURE      0x0d    /* Enclosure Services Device */
#define TYPE_NO_LUN         0x7f

/*
 * standard mode-select header prepended to all mode-select commands
 *
 * moved here from cdrom.h -- kraxel
 */

struct ccs_modesel_head {
    uint8_t   _r1;                       /* reserved */
    uint8_t   medium;                    /* device-specific medium type */
    uint8_t   _r2;                       /* reserved */
    uint8_t   block_desc_length;         /* block descriptor length */
    uint8_t   density;                   /* device-specific density code */
    uint8_t   number_blocks_hi;          /* number of blocks in this block desc */
    uint8_t   number_blocks_med;
    uint8_t   number_blocks_lo;
    uint8_t   _r3;
    uint8_t   block_length_hi;           /* block length for blocks in this desc */
    uint8_t   block_length_med;
    uint8_t   block_length_lo;
};



/*
 *  MESSAGE CODES
 */
#define COMMAND_COMPLETE    0x00
#define EXTENDED_MESSAGE    0x01
#define     EXTENDED_MODIFY_DATA_POINTER    0x00
#define     EXTENDED_SDTR                   0x01
#define     EXTENDED_EXTENDED_IDENTIFY      0x02    /* SCSI-I only */
#define     EXTENDED_WDTR                   0x03
#define SAVE_POINTERS       0x02
#define RESTORE_POINTERS    0x03
#define DISCONNECT          0x04
#define INITIATOR_ERROR     0x05
#define ABORT               0x06
#define MESSAGE_REJECT      0x07
#define NOP                 0x08
#define MSG_PARITY_ERROR    0x09
#define LINKED_CMD_COMPLETE 0x0a
#define LINKED_FLG_CMD_COMPLETE 0x0b
#define BUS_DEVICE_RESET    0x0c

#define INITIATE_RECOVERY   0x0f            /* SCSI-II only */
#define RELEASE_RECOVERY    0x10            /* SCSI-II only */

#define SIMPLE_QUEUE_TAG    0x20
#define HEAD_OF_QUEUE_TAG   0x21
#define ORDERED_QUEUE_TAG   0x22

/*
 * Here are some scsi specific ioctl commands which are sometimes useful.
 */
/* These are a few other constants  only used by scsi  devices */

#define SCSI_IOCTL_GET_IDLUN         0x5382

/* Used to turn on and off tagged queuing for scsi devices */

#define SCSI_IOCTL_TAGGED_ENABLE     0x5383
#define SCSI_IOCTL_TAGGED_DISABLE    0x5384

/* Used to obtain the host number of a device. */
#define SCSI_IOCTL_PROBE_HOST        0x5385

/* Used to get the bus number for a device */
#define SCSI_IOCTL_GET_BUS_NUMBER    0x5386


/* copied from scatterlist.h, and remove scatterlist.h */
typedef struct scatterlist {
    char    *address;                  /* Location data is to be transferred to */
    char    *alt_address;              /* Location of actual if address is a
                                        * dma indirect buffer.  NULL otherwise */
    uint32_t  length;
} SCATTER_LIST_T;

#define ISA_DMA_THRESHOLD (0x00ffffff)


/*
 * These are the values that the SCpnt->sc_data_direction and
 * SRpnt->sr_data_direction can take.  These need to be set
 * The SCSI_DATA_UNKNOWN value is essentially the default.
 * In the event that the command creator didn't bother to
 * set a value, you will see SCSI_DATA_UNKNOWN.
 */
#define SCSI_DATA_UNKNOWN       0
#define SCSI_DATA_WRITE         1
#define SCSI_DATA_READ          2
#define SCSI_DATA_NONE          3

/*
 * Some defs, in case these are not defined elsewhere.
 */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


#ifdef DEBUG
#define SCSI_TIMEOUT (5*HZ)
#else
#define SCSI_TIMEOUT (2*HZ)
#endif



/*
 *  Use these to separate status msg and our bytes
 *
 *  These are set by:
 *
 *      status byte = set from target device
 *      msg_byte    = return status from host adapter itself.
 *      host_byte   = set by low-level driver to indicate status.
 *      driver_byte = set by mid-level.
 */
#define status_byte(result) (((result) >> 1) & 0x1f)
#define msg_byte(result)    (((result) >> 8) & 0xff)
#define host_byte(result)   (((result) >> 16) & 0xff)
#define driver_byte(result) (((result) >> 24) & 0xff)
#define suggestion(result)  (driver_byte(result) & SUGGEST_MASK)

#define sense_class(sense)  (((sense) >> 4) & 0x7)
#define sense_error(sense)  ((sense) & 0xf)
#define sense_valid(sense)  ((sense) & 0x80);

#define NEEDS_RETRY     0x2001
#define SUCCESS         0x2002
#define FAILED          0x2003
#define QUEUED          0x2004
#define SOFT_ERROR      0x2005
#define ADD_TO_MLQUEUE  0x2006

/*
 * These are the values that scsi_cmd->state can take.
 */
#define SCSI_STATE_TIMEOUT         0x1000
#define SCSI_STATE_FINISHED        0x1001
#define SCSI_STATE_FAILED          0x1002
#define SCSI_STATE_QUEUED          0x1003
#define SCSI_STATE_UNUSED          0x1006
#define SCSI_STATE_DISCONNECTING   0x1008
#define SCSI_STATE_INITIALIZING    0x1009
#define SCSI_STATE_BHQUEUE         0x100a
#define SCSI_STATE_MLQUEUE         0x100b

/*
 * These are the values that the owner field can take.
 * They are used as an indication of who the command belongs to.
 */
#define SCSI_OWNER_HIGHLEVEL       0x100
#define SCSI_OWNER_MIDLEVEL        0x101
#define SCSI_OWNER_LOWLEVEL        0x102
#define SCSI_OWNER_ERROR_HANDLER   0x103
#define SCSI_OWNER_BH_HANDLER      0x104
#define SCSI_OWNER_NOBODY          0x105

#define COMMAND_SIZE(opcode) scsi_command_size[((opcode) >> 5) & 7]

#define IDENTIFY_BASE       0x80
#define IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |\
                     ((can_disconnect) ?  0x40 : 0) |\
                     ((lun) & 0x07))



/*
 * These are the macros that are actually used throughout the code to
 * log events.  If logging isn't enabled, they are no-ops and will be
 * completely absent from the user's code.
 *
 * The 'set' versions of the macros are really intended to only be called
 * from the /proc filesystem, and in production kernels this will be about
 * all that is ever used.  It could be useful in a debugging environment to
 * bump the logging level when certain strange events are detected, however.
 */
#define SCSI_LOG_ERROR_RECOVERY(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_ERROR_SHIFT, SCSI_LOG_ERROR_BITS, LEVEL,CMD);
#define SCSI_LOG_TIMEOUT(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_TIMEOUT_SHIFT, SCSI_LOG_TIMEOUT_BITS, LEVEL,CMD);
#define SCSI_LOG_SCAN_BUS(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_SCAN_SHIFT, SCSI_LOG_SCAN_BITS, LEVEL,CMD);
#define SCSI_LOG_MLQUEUE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_MLQUEUE_SHIFT, SCSI_LOG_MLQUEUE_BITS, LEVEL,CMD);
#define SCSI_LOG_MLCOMPLETE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_MLCOMPLETE_SHIFT, SCSI_LOG_MLCOMPLETE_BITS, LEVEL,CMD);
#define SCSI_LOG_LLQUEUE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_LLQUEUE_SHIFT, SCSI_LOG_LLQUEUE_BITS, LEVEL,CMD);
#define SCSI_LOG_LLCOMPLETE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_LLCOMPLETE_SHIFT, SCSI_LOG_LLCOMPLETE_BITS, LEVEL,CMD);
#define SCSI_LOG_HLQUEUE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_HLQUEUE_SHIFT, SCSI_LOG_HLQUEUE_BITS, LEVEL,CMD);
#define SCSI_LOG_HLCOMPLETE(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_HLCOMPLETE_SHIFT, SCSI_LOG_HLCOMPLETE_BITS, LEVEL,CMD);
#define SCSI_LOG_IOCTL(LEVEL,CMD)  \
        SCSI_CHECK_LOGGING(SCSI_LOG_IOCTL_SHIFT, SCSI_LOG_IOCTL_BITS, LEVEL,CMD);


#define SCSI_SET_ERROR_RECOVERY_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_ERROR_SHIFT, SCSI_LOG_ERROR_BITS, LEVEL);
#define SCSI_SET_TIMEOUT_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_TIMEOUT_SHIFT, SCSI_LOG_TIMEOUT_BITS, LEVEL);
#define SCSI_SET_SCAN_BUS_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_SCAN_SHIFT, SCSI_LOG_SCAN_BITS, LEVEL);
#define SCSI_SET_MLQUEUE_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_MLQUEUE_SHIFT, SCSI_LOG_MLQUEUE_BITS, LEVEL);
#define SCSI_SET_MLCOMPLETE_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_MLCOMPLETE_SHIFT, SCSI_LOG_MLCOMPLETE_BITS, LEVEL);
#define SCSI_SET_LLQUEUE_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_LLQUEUE_SHIFT, SCSI_LOG_LLQUEUE_BITS, LEVEL);
#define SCSI_SET_LLCOMPLETE_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_LLCOMPLETE_SHIFT, SCSI_LOG_LLCOMPLETE_BITS, LEVEL);
#define SCSI_SET_HLQUEUE_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_HLQUEUE_SHIFT, SCSI_LOG_HLQUEUE_BITS, LEVEL);
#define SCSI_SET_HLCOMPLETE_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_HLCOMPLETE_SHIFT, SCSI_LOG_HLCOMPLETE_BITS, LEVEL);
#define SCSI_SET_IOCTL_LOGGING(LEVEL)  \
        SCSI_SET_LOGGING(SCSI_LOG_IOCTL_SHIFT, SCSI_LOG_IOCTL_BITS, LEVEL);

/*
 *  the return of the status word will be in the following format :
 *  The low byte is the status returned by the SCSI command,
 *  with vendor specific bits masked.
 *
 *  The next byte is the message which followed the SCSI status.
 *  This allows a stos to be used, since the Intel is a little
 *  endian machine.
 *
 *  The final byte is a host return code, which is one of the following.
 *
 *  IE
 *  lsb     msb
 *  status  msg host code
 *
 *  Our errors returned by OUR driver, NOT SCSI message.  Or'd with
 *  SCSI message passed back to driver <IF any>.
 */


#define DID_OK          0x00    /* NO error                                */
#define DID_NO_CONNECT  0x01    /* Couldn't connect before timeout period  */
#define DID_BUS_BUSY    0x02    /* BUS stayed busy through time out period */
#define DID_TIME_OUT    0x03    /* TIMED OUT for other reason              */
#define DID_BAD_TARGET  0x04    /* BAD target.                             */
#define DID_ABORT       0x05    /* Told to abort for some other reason     */
#define DID_PARITY      0x06    /* Parity error                            */
#define DID_ERROR       0x07    /* Internal error                          */
#define DID_RESET       0x08    /* Reset by somebody.                      */
#define DID_BAD_INTR    0x09    /* Got an interrupt we weren't expecting.  */
#define DID_PASSTHROUGH 0x0a    /* Force command past mid-layer            */
#define DID_SOFT_ERROR  0x0b    /* The low level driver just wish a retry  */
#define DRIVER_OK       0x00    /* Driver status                           */

/*
 *  These indicate the error that occurred, and what is available.
 */
#define DRIVER_BUSY         0x01
#define DRIVER_SOFT         0x02
#define DRIVER_MEDIA        0x03
#define DRIVER_ERROR        0x04

#define DRIVER_INVALID      0x05
#define DRIVER_TIMEOUT      0x06
#define DRIVER_HARD         0x07
#define DRIVER_SENSE        0x08

#define SUGGEST_RETRY       0x10
#define SUGGEST_ABORT       0x20
#define SUGGEST_REMAP       0x30
#define SUGGEST_DIE         0x40
#define SUGGEST_SENSE       0x80
#define SUGGEST_IS_OK       0xff

#define DRIVER_MASK         0x0f
#define SUGGEST_MASK        0xf0

#define MAX_COMMAND_SIZE    12
#define SCSI_SENSE_BUFFERSIZE   64

/*
 *  SCSI command sets
 */

#define SCSI_UNKNOWN    0
#define SCSI_1          1
#define SCSI_1_CCS      2
#define SCSI_2          3
#define SCSI_3          4

/*
 *  Every SCSI command starts with a one byte OP-code.
 *  The next byte's high three bits are the LUN of the
 *  device.  Any multi-byte quantities are stored high byte
 *  first, and may have a 5 bit MSB in the same byte
 *  as the LUN.
 */

/*
 *  As the scsi do command functions are intelligent, and may need to
 *  redo a command, we need to keep track of the last command
 *  executed on each one.
 */
#define WAS_RESET         0x01
#define WAS_TIMEDOUT      0x02
#define WAS_SENSE         0x04
#define IS_RESETTING      0x08
#define IS_ABORTING       0x10
#define ASKED_FOR_SENSE   0x20
#define SYNC_RESET        0x40

/*
 * Add some typedefs so that we can prototyope a bunch of the functions.
 */
struct scsi_cmnd;
struct scsi_request;
struct umas_data;

#define SCSI_CMND_MAGIC    0xE25C23A5
#define SCSI_REQ_MAGIC     0x75F6D354


#define RQ_INACTIVE             (-1)
#define RQ_ACTIVE               1
#define RQ_SCSI_BUSY            0xffff
#define RQ_SCSI_DONE            0xfffe
#define RQ_SCSI_DISCONNECTING   0xffe0

/*
 * Ok, this is an expanded form so that we can use the same
 * request for paging requests when that is implemented. In
 * paging, 'bh' is NULL, and the semaphore is used to wait
 * for read/write completion.
 */
struct request {
    int     cmd;                /* READ or WRITE */
    int     errors;
    uint32_t  start_time;
    uint32_t  sector;
    uint32_t  nr_sectors;
    uint32_t  hard_sector, hard_nr_sectors;
    uint32_t  nr_segments;
    uint32_t  nr_hw_segments;
    uint32_t  current_nr_sectors;
    void    *special;
    char    *buffer;
    struct buffer_head  *bh;
    struct buffer_head  *bhtail;
};



/*
 * The SCSI_CMD_T structure is used by scsi.c internally, and for communication
 * with low level drivers that support multiple outstanding commands.
 */
typedef struct scsi_pointer {
    char *ptr;              /* data pointer */
    int this_residual;      /* left in this buffer */
    struct scatterlist *buffer;     /* which buffer */
    int buffers_residual;   /* how many buffers left */

    volatile int Status;
    volatile int Message;
    volatile int have_data_in;
    volatile int sent_command;
    volatile int phase;
} Scsi_Pointer;

/*
 * This is essentially a slimmed down version of SCSI_CMD_T.  The point of
 * having this is that requests that are injected into the queue as result
 * of things like ioctls and character devices shouldn't be using a
 * SCSI_CMD_T until such a time that the command is actually at the head
 * of the queue and being sent to the driver.
 */
typedef struct scsi_request {
    int     sr_magic;
    int     sr_result;                 /* Status code from lower level driver */
    /*
     * obtained by REQUEST SENSE when CHECK CONDITION is received on original
     * command (auto-sense)
     */
    uint8_t   sr_sense_buffer[SCSI_SENSE_BUFFERSIZE];
    struct scsi_cmnd  *sr_command;
    struct request  sr_request;        /* A copy of the command we are working on */
    uint32_t  sr_bufflen;                /* Size of data buffer */
    void    *sr_buffer;                /* Data buffer */
    int     sr_allowed;
    uint8_t   sr_data_direction;
    uint8_t   sr_cmd_len;
    uint8_t   sr_cmnd[MAX_COMMAND_SIZE];
    uint16_t  sr_use_sg;                 /* Number of pieces of scatter-gather */
    uint16_t  sr_sglist_len;             /* size of malloc'd scatter-gather list */
} Scsi_Request;

/*
 * FIXME(eric) - one of the great regrets that I have is that I failed to define
 * these structure elements as something like sc_foo instead of foo.  This would
 * make it so much easier to grep through sources and so forth.  I propose that
 * all new elements that get added to these structures follow this convention.
 * As time goes on and as people have the stomach for it, it should be possible to
 * go back and retrofit at least some of the elements here with with the prefix.
 */
typedef struct scsi_cmnd {
    struct umas_data  *umas;
    Scsi_Request  *sc_request;
    struct scsi_cmnd  *reset_chain;

    /*
     * A SCSI Command is assigned a nonzero serial_number when internal_cmnd
     * passes it to the driver's queue command function.  The serial_number
     * is cleared when scsi_done is entered indicating that the command has
     * been completed.  If a timeout occurs, the serial number at the moment
     * of timeout is copied into serial_number_at_timeout.  By subsequently
     * comparing the serial_number and serial_number_at_timeout fields
     * during abort or reset processing, we can detect whether the command
     * has already completed.  This also detects cases where the command has
     * completed and the SCSI Command structure has already being reused
     * for another command, so that we can avoid incorrectly aborting or
     * resetting the new command.
     */
    uint32_t  serial_number;

    uint32_t  target;
    uint32_t  lun;
    uint32_t  channel;
    uint8_t   cmd_len;
    uint8_t   old_cmd_len;
    uint8_t   sc_data_direction;
    uint8_t   sc_old_data_direction;

    /* These elements define the operation we are about to perform */
    uint8_t   cmnd[MAX_COMMAND_SIZE];
    uint32_t  request_bufflen;       /* Actual request size */

    void    *request_buff;       /* Actual requested buffer */

    /* These elements define the operation we ultimately want to perform */
    uint8_t   data_cmnd[MAX_COMMAND_SIZE];
    uint16_t  old_use_sg;            /* We save  use_sg here when requesting sense info */
    uint16_t  use_sg;                /* Number of pieces of scatter-gather */
    uint16_t  sglist_len;            /* size of malloc'd scatter-gather list */
    uint32_t  bufflen;               /* Size of data buffer */
    void    *buffer;               /* Data buffer */

    uint32_t  transfersize;          /* How much we are guaranteed to transfer
                                    * with each SCSI transfer (ie, between
                                    * disconnect reconnects.
                                    * Probably == sector size */

    struct request request;        /* A copy of the command we are working on */

    uint8_t   sense_buffer[SCSI_SENSE_BUFFERSIZE];
    /* obtained by REQUEST SENSE when CHECK
     * CONDITION is received on original
     * command (auto-sense) */
    int     result;                /* Status code from lower level driver */
} SCSI_CMD_T;

/*
 *  Flag bit for the internal_timeout array
 */
#define NORMAL_TIMEOUT 0

/*
 * Definitions and prototypes used for scsi mid-level queue.
 */
#define SCSI_MLQUEUE_HOST_BUSY       0x1055
#define SCSI_MLQUEUE_DEVICE_BUSY     0x1056

/* old style reset request from external source (private to sg.c and
 * scsi_error.c, supplied by scsi_obsolete.c)
 * */
#define SCSI_TRY_RESET_DEVICE   1
#define SCSI_TRY_RESET_BUS      2
#define SCSI_TRY_RESET_HOST     3

#endif  /* _SCSI_H_ */

/*
 * Overrides for Emacs so that we follow Linus's tabbing style.
 * Emacs will notice this stuff at the end of the file and automatically
 * adjust the settings for this buffer only.  This must remain at the end
 * of the file.
 * ---------------------------------------------------------------------------
 * Local variables:
 * c-indent-level: 4
 * c-brace-imaginary-offset: 0
 * c-brace-offset: -4
 * c-argdecl-indent: 4
 * c-label-offset: -4
 * c-continued-statement-offset: 4
 * c-continued-brace-offset: 0
 * indent-tabs-mode: nil
 * tab-width: 8
 * End:
 */

/// @endcond HIDDEN_SYMBOLS
