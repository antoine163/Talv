@rem ############################################################################
@rem #
@rem #	Script pour le nettoyage de la compilationsous windows.
@rem #
@rem # - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
@rem # - version	:	0.2
@rem # - date 		:	29/12/2012
@rem #
@rem ############################################################################

@echo clean ...
cd ..
mingw32-make.exe OS_NAME=msw clean
@pause
