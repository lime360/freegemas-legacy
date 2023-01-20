#!/bin/sh

echo "* Generating es.mo..."
mkdir -p lang/es/LC_MESSAGES
msgfmt -c -v -o lang/es/LC_MESSAGES/freegemas.mo po/es.po

echo "* Generating en.mo..."
mkdir -p lang/en/LC_MESSAGES
msgfmt -c -v -o lang/en/LC_MESSAGES/freegemas.mo po/en.po
