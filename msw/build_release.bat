@rem ############################################################################
@rem #
@rem #	Script pour la compilation en release sous windows.
@rem #
@rem # - author 	:	Antoine Maleyrie : antoine.maleyrie@gmail.com
@rem # - version	:	0.2
@rem # - date 		:	27/12/2012
@rem #
@rem ############################################################################

@echo build in release ...
cd ..
mingw32-make.exe OS_NAME=msw release
@pause
