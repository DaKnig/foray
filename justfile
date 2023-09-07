build:
	ninja -C build -v

run: build
	./build/foray > image.ppm
	xdg-open image.ppm

debug: build
	gdb build/foray

reconfigure:
	meson setup --reconfigure build

configure:
	meson setup build
