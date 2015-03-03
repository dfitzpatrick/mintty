#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "color.h"

// The palette stores pure RGB colors.
uint palette[COL_PALETTE_SIZE];

uint
col_make_from_rgb(uint red, uint green, uint blue)
{
    uint color = ((red & 0xFF) << 16) | ((green & 0xFF) << 8) | (blue & 0xFF);
    return color;
}

void
col_set_palette_entry(uint palette_index, uint colour)
{
    palette[palette_index] = colour;
}

uint
col_get_palette_entry(uint palette_index)
{
    return palette[palette_index];
}

uint
col_parse(const char* str)
{
    return 0;
}

/*
 * Convert the internal color code (either index or RGB, see color.h) into RGB.
 * This is a direct port of vte_terminal_get_rgb_from_index().
 */
uint
col_get_rgb_from_index(uint index)
{
    bool dim = false;
    if (!(index & COL_RGB_COLOR) && (index & COL_DIM_COLOR)) {
        index &= ~COL_DIM_COLOR;
        dim = true;
    }

     if (index >= COL_LEGACY_COLORS_OFFSET && index < COL_LEGACY_COLORS_OFFSET + COL_LEGACY_FULL_COLOR_SET_SIZE)
         index -= COL_LEGACY_COLORS_OFFSET;

     uint color;
     if (index < COL_PALETTE_SIZE) {
         color = col_get_palette_entry(index);
         if (dim) {
             // magic formula taken from xterm
             uint dimRed = COL_GET_RED(color) * 2 / 3;
             uint dimGreen = COL_GET_GREEN(color) * 2 / 3;
             uint dimBlue = COL_GET_BLUE(color) * 2 / 3;
             color = col_make_from_rgb(dimRed, dimGreen, dimBlue);
         }
     }
     else if (index & COL_RGB_COLOR) {
         uint red = COL_GET_RED(index) * 257;
         uint green = COL_GET_GREEN(index) * 257;
         uint blue = COL_GET_BLUE(index) * 257;
         color = col_make_from_rgb(red, green, blue);
     }
     else {
         assert(false);
//         g_assert_not_reached();
     }


    return 0;
}


int
main()
{
    // Test forming/extracting color triples from uints.
    uint red = 255, green = 64, blue = 32;
    uint c1 = col_make_from_rgb(red, green, blue);
    printf("c1 = %x\n", c1);
    uint red2 = COL_GET_RED(c1);
    uint green2 = COL_GET_GREEN(c1);
    uint blue2 = COL_GET_BLUE(c1); 
    printf("red = %x, red2 = %x\n", red, red2);
    printf("green = %x, green2 = %x\n", green, green2);
    printf("blue = %x, blue2 = %x\n", blue, blue2);
    assert(red == red2);
    assert(green == green2);
    assert(blue == blue2);

    // Test setting and getting palette entries;
    int pindex;
    for (pindex = 0; pindex < COL_PALETTE_SIZE; pindex++)
    {
        uint pc = col_make_from_rgb(pindex, pindex, pindex);
        col_set_palette_entry(pindex, pc);
        uint pc2 = col_get_palette_entry(pindex);
        assert(pc == pc2);
    }
    printf("Palette set/get checks completed ok.\n");

    printf("COL_PALETTE_SIZE = %d\n", COL_PALETTE_SIZE);
    printf("\n");
    return 0;
}

