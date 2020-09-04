#!/bin/bash

pandoc *.md -o notes_computer_architecture.pdf -V papersize=a4 -V linkcolor=blue -V geometry:margin=1in -V numbersections=true --toc --toc-depth=5 -V fontsize=12pt

#pandoc 00*.md -o summary.pdf -V papersize=a4 -V linkcolor=blue -V geometry:margin=1in -V numbersections=true --toc --toc-depth=5 -V fontsize=12pt
