#!/bin/bash
mkdir build > /dev/null 2>&1
gcc -o build/wd2ntlm src/main.c src/lib/wd2ntlm.c
chmod +x build/wd2ntlm