flatbuffer-test:
# ON RASPBERRY
#	gcc -I ~/flatcc/include/  main.c ~/flatcc/lib/libflatccrt.a -o flatbuffer-test
# ON MAC
	gcc -I ~/gitrepo-getugo/flatcc/include/ -I ./communications-protocol/src/c_h/ -I ./inc src/main.c src/teleop-udp-server.c src/teleop-flatbuf-api.c ~/gitrepo-getugo/flatcc/lib/libflatccrt.a -o flatbuffer-test
