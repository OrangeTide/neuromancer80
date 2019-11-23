/* xgetopt.h : portable command-line argument processing - public domain */
#ifndef XGETOPT_H_
#define XGETOPT_H_
int xgetopt(int argc, char * const argv[], const char *optstring);
extern const char *xoptarg;
extern int xopterr, xoptind, xoptopt;
#endif
