flatbuffer-test:
# ON RASPBERRY
#	gcc -I ~/flatcc/include/  main.c ~/flatcc/lib/libflatccrt.a -o flatbuffer-test
# ON MAC
	gcc -I ~/gitrepo-getugo/flatcc/include/ -I ./teleop-flatbuf/communications-protocol/src/c_h/  main.c teleop-udp-server.c teleop-flatbuf-api.c ~/gitrepo-getugo/flatcc/lib/libflatccrt.a -o flatbuffer-test
