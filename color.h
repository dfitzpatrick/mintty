#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

/*
 * Every single character will have a "fg-colour" and a "bg-colour" field.
 * Currently these are stored in the termchar.attr field which is used everywhere...
 * but see ATTR_FGSHIFT, ATTR_FGMASK (defined in term.h) for usage relating to colours.
 *
 * In the trucolor design it will be one of these augmented colour things,
 * see below for their encoding. When used in Windows, you will first need to
 * call the function "col_get_rgb_from_index" which converts one of these
 * compound colours into an RGB colour.
 *
 * Compound colour is a nice name. RGB colour?
 * We don't currently have a way of creating a compound colour from an RGB colour,
 * i.e. offsetting them. Just shift by 1?
 */

/*
 * Colors are encoded in 25 bits as follows:
 *
 * 0 .. 255 (256 slots):
 *   Colors set by SGR 256-color extension (38/48;5;index).
 *   These are direct indices into the color palette.
 *
 * 256 .. COL_PALETTE_SIZE - 1 (261) (6 slots):
 *   Special values, such as default colors.
 *   These are direct indices into the color palette.
 *
 * COL_LEGACY_COLORS_OFFSET (512) .. COL_LEGACY_COLORS_OFFSET + COL_LEGACY_FULL_COLOR_SET_SIZE - 1 (527) (16 slots):
 *   Colors set by legacy escapes (30..37/40..47, 90..97/100..107).
 *   These are translated to 0 .. 15 before looking up in the palette, taking bold into account.
 *
 * COL_DIM_COLORS (2^10) .. (??? 528 slots ???):
 *   Dimmed version of the above, for foreground colors.
 *   Cell attributes can't have these colors.
 *
 * COL_RGB_COLOR (2^24) .. COL_RGB_COLOR + 16Mi - 1 (2^25 - 1) (16 million slots):
 *   Colors set by SGR truecolor extension (38/48;2;red;green;blue)
 *   These are direct RGB values.
 */
#define COL_PALETTE_SIZE                262
#define COL_LEGACY_COLORS_OFFSET        512
#define COL_LEGACY_COLOR_SET_SIZE       8
#define COL_LEGACY_FULL_COLOR_SET_SIZE  16
#define COL_COLOR_PLAIN_OFFSET          0
#define COL_COLOR_BRIGHT_OFFSET         8
#define COL_DIM_COLOR                   (1 << 10)
#define COL_RGB_COLOR                   (1 << 24)

inline uint8_t
col_get_red(int colour)
{
    return (colour >> 16) & 0xFF;
}

inline uint8_t
col_get_green(int colour)
{
    return (colour >> 8) & 0xFF;
}

inline uint8_t
col_get_blue(int colour)
{
    return colour & 0xFF;
}

inline void
col_set_red(int *colour, uint8_t red)
{
    *colour = (*colour & ~0xFF0000) | ((red << 16) & 0xFF0000);
}

inline void
col_set_green(int *colour, uint8_t green)
{
    *colour = (*colour & ~0xFF00) | ((green << 8) & 0xFF00);
}

inline void
col_set_blue(int *colour, uint8_t blue)
{
    *colour = (*colour & ~0xFF) | (blue & 0xFF);
}

inline int
col_from_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    return red << 16 | green << 8 | blue;
}

inline int
col_make_dim(int colour)
{
    uint8_t dim_red = col_get_red(colour) * 2 / 3;
    uint8_t dim_green = col_get_green(colour) * 2 / 3;
    uint8_t dim_blue = col_get_blue(colour) * 2 / 3;
    colour = col_from_rgb(dim_red, dim_green, dim_blue);
    return colour;
}

void col_set_palette_entry(uint palette_index, int colour);
int col_get_palette_entry(uint palette_index);
 


#endif

