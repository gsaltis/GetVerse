@echo off
doskey m=make -j 4 -f Makefile.Release $T make -j 4 -f Makefile.Debug
doskey mr=make -j 4 -f Makefile.Release
doskey md=make -j 4 -f Makefile.Debug
doskey mc=make cleanall
doskey mq=qmake
doskey ge=release\GetVerse $*
doskey ged=gdb debug\GetVerse $*
title GetVerse
set GETVERSE_DATABASE=./NASB.db

doskey switch=git switch $*
doskey branch=git branch $*
doskey push=git push $*
doskey merge=git merge $*
doskey status=git status $*
doskey add=git add $*
doskey commit=git commit $*

git status | head -1 | gawk "{print $3;}"> .branch.txt
set /p P=<.branch.txt
prompt GetVerse [%p%] : 
del .branch.txt
