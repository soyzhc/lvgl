/**
 * @file lv_draw_img.h
 *
 */

#ifndef LV_DRAW_IMG_H
#define LV_DRAW_IMG_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_draw.h"

/*********************
 *      DEFINES
 *********************/

/*If image pixels contains alpha we need to know how much byte is a pixel*/
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
# define LV_IMG_PX_SIZE_ALPHA_BYTE   2
#elif LV_COLOR_DEPTH == 16
# define LV_IMG_PX_SIZE_ALPHA_BYTE   3
#elif LV_COLOR_DEPTH == 24
# define LV_IMG_PX_SIZE_ALPHA_BYTE   4
#endif

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
	LV_BLIT_MODE_OVER = 0,		/*Just copy src to dest*/
	LV_BLIT_MODE_ADD,			/*Add src to dest*/
	LV_BLIT_MODE_MULT,			/*Multiply src by dest*/
	LV_BLIT_MODE_CHROMA_KEY,	/*Copy only not LV_COLOR_TRANSP pixels to of src to dest*/
	LV_BLIT_MODE_ALPHA,			/*Copy ssrc to dest but use the alpha channel in every pixel*/
	LV_BLIT_MODE_MASK,			/*Copy src only to those dest pixels where dest is not LV_COLOR_TRANSP*/
	LV_BLIT_MODE_STENCIL,		/*Copy src only to those dest pixels where the act. `lv_stencil_test()` function gives true*/
}lv_blit_mode_t;

typedef enum {
	LV_COLOR_FORMAT_INDEXED_1BIT,		/*Can have 2 different colors in a palette */
	LV_COLOR_FORMAT_INDEXED_2BIT,		/*Can have 4 different colors in a palette*/
	LV_COLOR_FORMAT_INDEXED_4BIT,		/*Can have 16 different colors in a palette*/
	LV_COLOR_FORMAT_INDEXED_8BIT,		/*Can have 256 different colors in a palette*/

	LV_COLOR_FORMAT_ALPHA_1BIT, 		/*Can have one color and it can be drawn or not*/
	LV_COLOR_FORMAT_ALPHA_2BIT, 		/*Can have one color but 4 different alpha value*/
	LV_COLOR_FORMAT_ALPHA_4BIT, 		/*Can have one color but 16 different alpha value*/
	LV_COLOR_FORMAT_ALPHA_8BIT, 		/*Can have one color but 256 different alpha value*/

	LV_COLOR_FORMAT_ALPHA_INDEXED_2BIT,	/*Can have 2 colors which will be drawn or not*/
	LV_COLOR_FORMAT_ALPHA_INDEXED_4BIT,	/*Can have 4 colors with 4 alpha values*/
	LV_COLOR_FORMAT_ALPHA_INDEXED_8BIT,	/*Can have 16 colors with 16 alpha values*/
	LV_COLOR_FORMAT_ALPHA_INDEXED_16BIT,/*Can have 256 colors with 256 alpha values*/

	LV_COLOR_FORMAT_TRUE_COLOR,			/*Color format and depth should match with LV_COLOR settings (most typical!)*/
	LV_COLOR_FORMAT_TRUE_COLOR_ALPHA,	/*Same as `LV_COLOR_FORMAT_TRUE_COLOR` but every pixel has an alpha value*/
}lv_color_format_t;

/* Image header it is compatible with
 * the result image converter utility*/
typedef struct
{
    union{
        struct {
            uint32_t chroma_keyed:1;    /*1: The image contains transparent pixels with LV_COLOR_TRANSP color*/
            uint32_t alpha_byte  :1;    /*Every pixel is extended with a 8 bit alpha channel*/
            uint32_t format      :6;    /*See: lv_img_px_format*/
            uint32_t w:12;              /*Width of the image map*/
            uint32_t h:12;              /*Height of the image map*/
        }header;

        lv_color_format_t color_format;


        uint8_t src_type;
    };

    union {
        const uint8_t * pixel_map;  /*For internal images (c arrays) pointer to the pixels array*/
        uint8_t first_pixel;        /*For external images (binary) the first byte of the pixels (just for convenient)*/
    };
}lv_img_t;

typedef enum {
    LV_IMG_FORMAT_UNKOWN = 0,
    LV_IMG_FORMAT_INTERNAL_RAW,       /*'lv_img_t' variable compiled with the code*/
    LV_IMG_FORMAT_FILE_RAW_RGB332,    /*8 bit*/
    LV_IMG_FORMAT_FILE_RAW_RGB565,    /*16 bit*/
    LV_IMG_FORMAT_FILE_RAW_RGB888,    /*24 bit (stored on 32 bit)*/
}lv_img_format_t;


typedef enum {
    LV_IMG_SRC_VARIABLE,
    LV_IMG_SRC_FILE,
    LV_IMG_SRC_SYMBOL,
    LV_IMG_SRC_UNKNOWN,
}lv_img_src_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

#if USE_LV_IMG

/**
 * Draw an image
 * @param coords the coordinates of the image
 * @param mask the image will be drawn only in this area
 * @param src pointer to a lv_color_t array which contains the pixels of the image
 * @param style style of the image
 * @param opa_scale scale down all opacities by the factor
 */
void lv_draw_img(const lv_area_t * coords, const lv_area_t * mask,
				 const void * src, const lv_style_t * style, lv_opa_t opa_scale);

#endif

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TEMPL_H*/
