@rem ############################################################################
@rem #
@rem #	Script pour lancer le programme.
@rem #
@rem # - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
@rem # - version	:	0.2
@rem # - date 		:	27/12/2012
@rem #
@rem ############################################################################

@echo run ...
cd ..
mingw32-make.exe OS_NAME=msw run
@pause
