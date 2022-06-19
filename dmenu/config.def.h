/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static int centered = 0;                    /* -c option; centers dmenu on screen */
static int min_width = 700;                    /* minimum width when centered */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {"Jetbrains Mono Nerd Font:size=11"};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */

static const char col_black[]     = "#2e3440";
static const char col_gray[]      = "#4c566a";
static const char col_gray3[]     = "#546e7a";
static const char col_white[]	    = "#d8dee9";
static const char col_blue[]	    = "#5E81AC";
static const char col_green[]	    = "#149b81";
static const char col_gray5[]	    = "#151515";
static const char col_cyan[]      = "#81a1c1";
static const char *colors[SchemeLast][2] = {
            	/*     fg         bg       */
	[SchemeNorm] = { col_white, col_black },
	[SchemeSel] = { col_cyan, col_black },
	[SchemeOut] = { col_black, col_cyan }
};
/* -l and -g options; controls number of lines and columns in grid if > 0 */
static unsigned int lines      = 8;
static unsigned int columns    = 2;

/* -h option; minimum height of a menu line */
static unsigned int lineheight = 32;
static unsigned int min_lineheight = 32;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/* Size of the window border */
static const unsigned int border_width = 2;
