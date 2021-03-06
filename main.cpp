#include "lineDrawer.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);

	// image.set(52, 41, red);
	line(0, 0, 100, 50, image, red);
	line2(0, 0, 30, 100, image, red);
	line(0, 0, 50, 100, image, red);
	line(0, 0, 25, 100, image, red);
	line(0, 0, 100, 0, image, red);
	line3(0, 0, 100, 90, image, TGAColor(100, 200, 200, 255));
	line4(0, 0, 70, 100, image, TGAColor(255, 255, 0, 255));
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

