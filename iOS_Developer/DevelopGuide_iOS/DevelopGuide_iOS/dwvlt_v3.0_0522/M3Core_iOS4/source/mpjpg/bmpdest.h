#ifndef _BITMAP_DEST_H_
#define _BITMAP_DEST_H_

typedef struct {
    struct djpeg_dest_struct pub; /* public fields */
    Boolean is_os2; /* saves the OS2 format request flag */
    JDIMENSION data_width; /* JSAMPLEs per row */
    JDIMENSION row_width; /* physical width of one row in the BMP file */
    int pad_bytes; /* number of padding bytes needed per row */
    JDIMENSION cur_output_row; /* next row# to write to virtual array */
} bmp_dest_struct;
typedef bmp_dest_struct *bmp_dest_ptr;

#endif

//CHANGE LOG
//97.10.03 - matsu - modified(V3)
