#include <iostream>
#include "engine/universe/universe.h"
#include "engine/helpers/proxygl.h"

int main(int argc, char *argv[])
{
    using engine::universe::Universe;
	int cnt_cubes, mode_grid;
	char *p;
	long conv;

	/* cnt_cubes can be override with optional parameter */
	if (argc >= 2) {
		conv = strtol(argv[1], &p, 10);
		if (errno != 0 || *p != '\0' || conv > INT_MAX) {
			printf("Bad cubes count parameter\n");
			exit(1);
		}

		cnt_cubes = (int)conv;
		if (cnt_cubes > 256)
			cnt_cubes = 256;
	}

	/* The third parameter disable textures */
	if (argc == 3)
		mode_grid = 1;

    cnt_cubes = 1;

	/* Init world */
    engine::helpers::proxygl::initGL();
    std::unique_ptr<Universe> engine_universe{new Universe()};
    engine::helpers::proxygl::settingsGL(engine_universe.get());
}
