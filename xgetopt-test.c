/* xgetopt-test.c : tests for xgetopt.c - public domain */
#include "xgetopt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	int c;
	int bflg = 0, aflg = 0, errflg = 0;
	const char *ifile = NULL;
	const char *ofile = NULL;
	const char *progname;

	while ((c = xgetopt(argc, argv, ":abf:o:")) != -1) {
		switch(c) {
		case 'a':
			if (bflg)
				errflg++;
			else
				aflg++;
			break;
		case 'b':
			if (aflg)
				errflg++;
			else
				bflg++;
			break;
		case 'f':
			ifile = xoptarg;
			break;
		case 'o':
			ofile = xoptarg;
			break;
		case ':':		/* -f or -o without operand */
			fprintf(stderr, "Option -%c requires an operand\n", xoptopt);
			errflg++;
			break;
		case '?':
			fprintf(stderr, "Unrecognized option: '-%c'\n", xoptopt);
			errflg++;
		}
	}

	/* get the program name as the basename of the argv[0] */
	progname = argv[0];
	while (*progname)
		progname++;
	while (--progname > argv[0] && progname[-1] != '/')
		;

	if (errflg) {
		fprintf(stderr, "usage: %s [-ab] [-f ifile] [-o ofile] [files...]\n", progname);
		exit(2);
	}

	if (ifile)
		printf("ifile=%s\n", ifile);
	if (ofile)
		printf("ofile=%s\n", ofile);

	for ( ; xoptind < argc; xoptind++) {
		char *f = argv[xoptind];
		printf("%s : ", f);
		if (access(f, R_OK)) {
			printf("missing\n");
		} else {
			printf("exists\n");
		}
	}

	return 0;
}
