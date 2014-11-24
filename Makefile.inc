
ifndef doxygen_path
  doxygen_path := `pwd`'/doxygen'
endif

ifndef build
  display = sdl2
  build = debug
endif

ifeq ($(display), windows)
  libs = -lopengl32 -lgdi32
  display = -DDISPLAY_WIN32
else
  libs = -lGL -lSDL2
  osdefs = -DDISPLAY_SDL2
endif

ifeq ($(build),release)
  CC = g++ -O3 -DBUILD_RELEASE $(osdefs)
else
  CC = g++ -g -DBUILD_DEBUG $(osdefs)
endif

.PHONY: clean doxygen