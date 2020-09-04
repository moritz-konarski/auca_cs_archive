#!/bin/bash

cd "./build"
latexmk ../summary.tex -pdf
cd ..
mv "./build/summary.pdf" "./_summary.pdf"
