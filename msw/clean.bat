@rem ############################################################################
@rem #
@rem #	Script pour le nettoyage de la compilationsous windows.
@rem #
@rem # - author 	:	Maleyrie Antoine : antoine.maleyrie@gmail.com
@rem # - version	:	0.1
@rem # - date 		:	29/12/2012
@rem #
@rem ############################################################################

@echo clean ...
mingw32-make.exe -f Makefile clean
@pause
