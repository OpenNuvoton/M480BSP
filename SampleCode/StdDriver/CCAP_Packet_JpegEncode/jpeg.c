#include <stdio.h>
#include <string.h>
#include "jpeglib.h"
#include "NuMicro.h"

//
// Encodes a 256 Greyscale image to JPEG directly to a memory buffer
// libJEPG will malloc() the buffer so the caller must free() it when
// they are finished with it.
//
// image    - the input greyscale image, 1 byte is 1 pixel.
// width    - the width of the input image
// height   - the height of the input image
// quality  - target JPEG 'quality' factor (max 100)
// comment  - optional JPEG NULL-termoinated comment, pass NULL for no comment.
// jpegSize - output, the number of bytes in the output JPEG buffer
// jpegBuf  - output, a pointer to the output JPEG buffer, must call free() when finished with it.
//
void encode_jpeg_to_memory(unsigned char* image, int width, int height, int quality,
    const char* comment, unsigned long* jpegSize, unsigned char** jpegBuf) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];
    int row_stride;

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_compress(&cinfo);
    cinfo.image_width = width;
    cinfo.image_height = height;

    // Input is greyscale, 1 byte per pixel
    cinfo.input_components = 1;
    cinfo.in_color_space = JCS_GRAYSCALE;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, (boolean)TRUE);

    //
    //
    // Tell libJpeg to encode to memory, this is the bit that's different!
    // Lib will alloc buffer.
    //
    jpeg_mem_dest(&cinfo, jpegBuf, jpegSize);

    jpeg_start_compress(&cinfo, (boolean)TRUE);

    // Add comment section if any..
    if (comment) {
        jpeg_write_marker(&cinfo, JPEG_COM, (const JOCTET*)comment, strlen(comment));
    }

    // 1 BPP
    row_stride = width;

    // Encode
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &image[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
}

void JpegEncode(unsigned char* image, unsigned char* jBuf,unsigned long *jSize,int width,int height) {

    // Encode image
    encode_jpeg_to_memory(image, width, height, 85, "Nuvoton!", jSize, &jBuf);

    printf("Jpeg image range: 0x%08x to 0x%08x, JPEG size (bytes): %ld",
            (unsigned int)jBuf,
            (unsigned int)jBuf+(unsigned int)*jSize,
             *jSize);
}
