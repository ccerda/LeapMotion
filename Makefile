OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY := ../LeapSDK/lib/x64/libLeap.so -Wl,-rpath,../LeapSDK/lib/x64
  else
    LEAP_LIBRARY := ../LeapSDK/lib/x86/libLeap.so -Wl,-rpath,../LeapSDK/lib/x86
  endif
else
  # OS X
  LEAP_LIBRARY := ../LeapSDK/lib/libLeap.dylib
endif

main: main.cpp
	$(CXX) -Wall -g -I ../LeapSDK/include main.cpp -o main $(LEAP_LIBRARY)
ifeq ($(OS), Darwin)
	install_name_tool -change @loader_path/libLeap.dylib ../lib/libLeap.dylib Sample
endif

clean:
	rm -rf Sample Sample.dSYM
