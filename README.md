This is a fork of mintty from https://code.google.com/p/mintty/

The configuration file syntax has been extended to support themes (it is still
a work-in-progress as there is no installer yet).

Themes
======
Flat UI is from https://github.com/geekjuice/flat-ui-mintty/blob/master/flat-minttyrc
Gnome is from https://github.com/rhlee/mintty-gnome-colors/blob/master/.minttyrc
Rosipov is from http://www.rosipov.com/blog/mintty-color-scheme-cygwin/
Xoria is from https://gist.github.com/pasela/3422835
Zenburn is from http://www.billzajac.com/wordpress/articles/2010/12/28/windows-is-nicer-with-mintty/

The others are based on my fork of Base16 builder at https://github.com/PhilipDaniels/base16-builder
I have tweaked it a bit to include FG/BG and cursor colours. I also used this
to create the Solarized Dark and Light themes, though based on Ethan Schooner's
Solarized, of course: http://ethanschoonover.com/solarized

A Caveat
========
Of course setting the terminal colours is great, but for maximum effect
you will want to configure your 'dircolors'. For solarized, I used the
one here https://github.com/seebi/dircolors-solarized

TrueColor / Multiple Font Support
=================================
term.h
  appears to contain a lot of important defns relating to colour, such as the
  main colour indexes and the ATTR_* shifts and masks.
term.c
  term_paint() - IMPORTANT. This is the top-level routine that figures out
                 where colours, attributes etc. change and then calls
                 win_text() to do the output. Not sure how colours in a run
                 are determined though.
  term_write()
termout.c
  do_sgr() - sets bold etc.
  do_colour_osc() - prints color from palette?
  line 1174 and on - palette stuff
    line 1216 contains a call to win_set_colour()
  term_write() - I think this calls when you send the escape sequence using
                 echo -ne "\033]11;#123123\007";
wintext.c
  win_init_fonts() - creates fonts here 
  win_text() - IMPORTANT. Here is where it sets the foreground and background
               colour. attr is where the colors are held, 2nd to last param. 
  win_set_colour() - ???
  win_reset_colours() - ???
winmain.c
  win_reconfig() - a top level routine that appears to reset colours and fonts
