#!/bin/bash

mkdir -p /usr/share/mintty/themes
chmod ugo+r /usr/share/mintty/themes
cp ./themes/* /usr/share/mintty/themes
cp mintty.exe /bin/mymintty.exe
chmod ugo+rx /bin/mymintty.exe

