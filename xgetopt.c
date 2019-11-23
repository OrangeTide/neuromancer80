/* xgetopt.c : portable command-line argument processing - public domain */
#include "xgetopt.h"
#include <stdio.h>
#include <string.h>

const char *xoptarg = 0;
int xopterr = 1, xoptind = 0, xoptopt = 0;

int
xgetopt(int argc, char * const argv[], const char *optstring)
{
	static const char *cur = "", *progname;
	const char *ip;

	/* guess at our program name using basename of argv[0] */
	if (!xoptind) {
		if (!argc) {
			progname = "";
		} else {
			progname = strrchr(argv[0], '/');
			if (!progname)
				progname = argv[0];
			else
				progname++;
		}
	}

	/* disable stderr output if optstring starts with ':' */
	if (*optstring == ':') {
		xopterr = 0;
		optstring++;
	}

	/* done processing flag series on current argument? */
	if (!*cur) {
		xoptind++;

		if (xoptind >= argc) {
			cur = "";
			return -1; /* done processing - end of arguments */
		}

		/* start a flag series at the new optind */
		cur = argv[xoptind];
		if (*cur != '-') {
			cur = "";
			return -1; /* done processing - no more flag series */
		}
		/* end flags if argument is exactly "--" */
		if (cur[1] == '-' && cur[2] == 0) {
			xoptind++;
			cur = "";
			return -1; /* done processing - no more flag series */
		}
		cur++;
	}

	/* current flag */
	xoptopt = (int)(unsigned char)*cur++;

	/* locate flag in the optstring */
	ip = strchr(optstring, xoptopt);
	if (!ip) {
		if (xopterr)
			fprintf(stderr, "%s: illegal option -- %c\n", progname, xoptopt);
		return '?'; /* error: unknown flag */
	}

	/* does this optstring have arguments? */
	if (ip[1] == ':') {
		if (*cur) {
			/* use remaining portion of current argv as xoptarg */
			xoptarg = cur;
			cur = ""; /* at next entry, go to next xoptind */
		} else {
			/* use next argv as the xoptarg */
			xoptind++;
			if (xoptind >= argc) {
				if (xopterr)
					fprintf(stderr, "%s: option requires an argument -- %c\n", progname, xoptopt);
				return ':'; /* error: missing argument */
			}
			xoptarg = argv[xoptind];
			cur = ""; /* at next entry, go to next xoptind */
		}
	}

	return xoptopt;
}
