#!/bin/sh
./make_pot.sh

msgmerge -s -U po/es.po po/freegemas.pot
msgmerge -s -U po/en.po po/freegemas.pot
