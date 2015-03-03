#ifndef COLOR_H
#define COLOR_H

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
#define COL_PALETTE_SIZE                16
#define COL_LEGACY_COLORS_OFFSET        512
#define COL_LEGACY_COLOR_SET_SIZE       8
#define COL_LEGACY_FULL_COLOR_SET_SIZE  16
#define COL_COLOR_PLAIN_OFFSET          0
#define COL_COLOR_BRIGHT_OFFSET         8
#define COL_DIM_COLOR                   (1 << 10)
#define COL_RGB_COLOR                   (1 << 24)

// Signed so that -1 can indicate "no colour".
typedef unsigned char uchar;
typedef int colour;

static inline uchar col_get_red(colour c) { return (c >> 16) & 0xFF; }
static inline uchar col_get_green(colour c) { return (c >> 8) & 0xFF; }
static inline uchar col_get_blue(colour c) { return c & 0xFF; }

static inline void col_set_red(colour *c, uchar red) { *c = (*c & ~0xFF0000) | (red & 0xFF0000); }
static inline void col_set_green(colour *c, uchar green) { *c = (*c & ~0xFF00) | (green & 0xFF00); }
static inline void col_set_blue(colour *c, uchar blue) { *c = (*c & ~0xFF) | (blue & 0xFF); }

static inline colour col_from_rgb(uchar red, uchar green, uchar blue) { return red << 16 | green << 8 | blue; }
static inline colour col_make_dim(colour c)
{
    colour dimRed = ((colour)col_get_red(c)) * 2 / 3;
    colour uchar dimGreen = ((colour)col_get_green(c)) * 2 / 3;
    colour uchar dimBlue = ((colour)col_get_blue(c)) * 2 / 3;
    return col_from_rgb(dimRed, dimGreen, dimBlue);
}

void col_set_palette_entry(uint palette_index, uint colour);
uint col_get_palette_entry(uint palette_index);


#endif

