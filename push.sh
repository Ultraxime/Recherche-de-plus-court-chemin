#!/bin/bash

case $1 in
	pull)
	  git  pull git@github.com:Ultraxime/Tipe-SDL.git
	;;

	*)
	  git add *.c *.h *.md
	  git commit .
	  git push git@github.com:Ultraxime/Tipe-SDL.git master
	;;

esac
exit 1

