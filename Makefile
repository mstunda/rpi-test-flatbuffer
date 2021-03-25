flatbuffer-test:
# ON RASPBERRY
#	gcc -I ~/flatcc/include/ -I ./communications-protocol/src/c_h/ -I ./inc src/main.c src/teleop_udp_server_api.c src/teleop_flatbuf_server_api.c ~/flatcc/lib/libflatccrt.a -o flatbuffer-test
# ON MAC
	gcc -I ~/gitrepo-getugo/flatcc/include/ -I ./communications-protocol/src/c_h/ -I ./inc src/main.c src/teleop_udp_server_api.c src/teleop_flatbuf_server_api.c ~/gitrepo-getugo/flatcc/lib/libflatccrt.a -o flatbuffer-test
