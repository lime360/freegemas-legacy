#!/bin/sh
VERSION=0.4
echo "* Initial pot file..."
xgettext --package-name freegemas --package-version $VERSION --default-domain freegemas --output po/freegemas.pot --from-code=utf-8 --copyright-holder="José Tomás Tocino García <theom3ga@gmail.com>" --msgid-bugs-address="theom3ga@gmail.com" -s -k_ -C ./src/*.cpp
