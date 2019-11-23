#include "xgetopt.h"
#include "ihex.h"
#include <stdio.h>
#include <stdlib.h>

static int
process_rom(unsigned address, unsigned count, unsigned char *data)
{
	// TODO: implement this
	(void)address;
	(void)count;
	(void)data;
	return 0;
}

static void
load_rom(const char *filename)
{
	if (ihex_load(filename, process_rom)) {
		fprintf(stderr, "%s:could not load\n", filename);
		exit(1);
	}
}

static void
process_args(int argc, char *argv[])
{
	int c, errflg = 0;
	const char *progname;

	/* get the program name as the basename of the argv[0] */
	progname = argv[0];
	while (*progname)
		progname++;
	while (--progname > argv[0] && progname[-1] != '/')
		;

	while ((c = xgetopt(argc, argv, "h")) != -1) {
		switch(c) {
		case 'h':
			errflg = 1;
			break;
		case ':':
		case '?':
			errflg = 1;
			break;
		default:
			fprintf(stderr, "%s: option is unimplemented -- %c\n", progname, xoptopt);
			errflg = 1;
		}
	}

	if (errflg) {
		fprintf(stderr, "usage: %s [-h] [files...]\n", progname);
		exit(1);
	}

	/* if no arguments, load a single default ROM */
	if (xoptind == argc) {
		load_rom("sys.hex");
		return;
	}

	/* load each ROM file in the order they appear on the command line */
	for ( ; xoptind < argc; xoptind++) {
		char *s = argv[xoptind];
		printf("Loading %s ...\n", s);
		load_rom(s);
	}
}

int
main(int argc, char *argv[])
{
	process_args(argc, argv);

	/// run something ///

	return 0;
}
