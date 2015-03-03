#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "color.h"

// The palette stores pure RGB colors.
int palette[COL_PALETTE_SIZE];

void
col_set_palette_entry(uint palette_index, int colour)
{
    palette[palette_index] = colour;
}

int
col_get_palette_entry(uint palette_index)
{
    return palette[palette_index];
}

int
col_parse(const char* str)
{
    return 0;
}

/*
 * Convert the internal color code (either index or RGB, see color.h) into RGB.
 * This is a direct port of vte_terminal_get_rgb_from_index().
colour
col_get_rgb_from_index(uint index)
{
    bool dim = false;
    if (!(index & COL_RGB_COLOR) && (index & COL_DIM_COLOR)) {
        index &= ~COL_DIM_COLOR;
        dim = true;
    }

     if (index >= COL_LEGACY_COLORS_OFFSET && index < COL_LEGACY_COLORS_OFFSET + COL_LEGACY_FULL_COLOR_SET_SIZE)
         index -= COL_LEGACY_COLORS_OFFSET;

     colour c;
     if (index < COL_PALETTE_SIZE) {
         c = col_get_palette_entry(index);
         if (dim) {
             // magic formula taken from xterm
             colour dimRed = col_get_red(c) * 2 / 3;
             colour dimGreen = col_get_green(c) * 2 / 3;
             colour dimBlue = col_get_blue(c) * 2 / 3;
             c = col_from_rgb(dimRed, dimGreen, dimBlue);
         }
     }
     else if (index & COL_RGB_COLOR) {
         colour red = col_get_red(index) * 257;
         colour green = col_get_green(index) * 257;
         colour blue = col_get_blue(index) * 257;
         c = col_from_rgb(red, green, blue);
     }
     else {
         assert(false);
//         g_assert_not_reached();
     }


    return 0;
}
*/

int
main()
{
    // Test forming/extracting color triples from uints.
    uint8_t red1 = 0x40, green1 = 0x30, blue1 = 0x20;
    int c1 = col_from_rgb(red1, green1, blue1);
    printf("c1 = 0x%x\n", c1);

    uint8_t red2 = col_get_red(c1);
    uint8_t green2 = col_get_green(c1);
    uint8_t blue2 = col_get_blue(c1); 
    printf("red1 = 0x%x, red2 = 0x%x\n", red1, red2);
    printf("green1 = 0x%x, green2 = 0x%x\n", green1, green2);
    printf("blue1 = 0x%x, blue2 = 0x%x\n", blue1, blue2);
    assert(red1 == red2);
    assert(green1 == green2);
    assert(blue1 == blue2);


    // Test the individual colour set functions.
    col_set_red(&c1, 0x55);
    uint8_t red3 = col_get_red(c1);
    assert(red3 == 0x55);

    col_set_green(&c1, 0x17);
    uint8_t green3 = col_get_green(c1);
    assert(green3 == 0x17);

    col_set_blue(&c1, 0x65);
    uint8_t blue3 = col_get_blue(c1);
    assert(blue3 == 0x65);

    assert(col_get_red(c1) == 0x55);
    assert(col_get_green(c1) == 0x17);
    assert(col_get_blue(c1) == 0x65);


    // Test make_dim.
    int c2 = col_from_rgb(255, 150, 0);
    int c3 = col_make_dim(c2);
    assert(col_get_red(c3) == 170);
    assert(col_get_green(c3) == 100);
    assert(col_get_blue(c3) == 0);


    // Test setting and getting palette entries;
    int pindex;
    for (pindex = 0; pindex < COL_PALETTE_SIZE; pindex++)
    {
        int pc1 = col_from_rgb(pindex, pindex, pindex);
        col_set_palette_entry(pindex, pc1);
        int pc2 = col_get_palette_entry(pindex);
        assert(pc1 == pc2);
    }
    printf("Palette set/get checks completed ok.\n");


    //printf("COL_PALETTE_SIZE = %d\n", COL_PALETTE_SIZE);
    

    return 0;
}

