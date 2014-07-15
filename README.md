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

