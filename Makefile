flatbuffer-test:
# ON RASPBERRY
#	gcc -I ~/flatcc/include/ -I ./communications-protocol/src/c_h/ -I ./inc src/main.c src/teleop_udp_server.c src/teleop_flatbuf_server.c ~/flatcc/lib/libflatccrt.a -o flatbuffer-test
# ON MAC
	gcc -Werror=pedantic -I ~/gitrepo-getugo/flatcc/include/ -I ./communications-protocol/src/c_h/ -I ./inc src/main.c src/teleop_udp_server.c src/teleop_flatbuf_server.c ~/gitrepo-getugo/flatcc/lib/libflatccrt.a -o flatbuffer-test
