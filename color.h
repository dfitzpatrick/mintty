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

#define COL_GET_RED(color)              (((color) >> 16) & 0xFF)
#define COL_GET_GREEN(color)            (((color) >> 8) & 0xFF)
#define COL_GET_BLUE(color)             ((color) & 0xFF)
uint col_make_from_rgb(uint red, uint green, uint blue);
void col_set_palette_entry(uint palette_index, uint colour);
uint col_get_palette_entry(uint palette_index);


typedef uint colour;
enum { DEFAULT_COLOUR = UINT_MAX };
static inline colour make_colour(uchar r, uchar g, uchar b) { return r | g << 8 | b << 16; }
bool parse_colour(string, colour *);
static inline uchar red(colour c) { return c; }
static inline uchar green(colour c) { return c >> 8; }
static inline uchar blue(colour c) { return c >> 16; }


#endif

