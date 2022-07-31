/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 9;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 9;       /* vert inner gap between windows */
static const unsigned int gappoh    = 9;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 9;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 1;
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 0;        /* vertical padding for statusbar */
static const int vertpad            = 9;       /* vertical padding of bar */
static const int sidepad            = 9;       /* horizontal padding of bar */
static const int user_bh            = 32;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { 
        "jetbrains mono nerd font :size=11"
        };
static const char col_black[]       = "#282C34";
static const char col_gray[]        = "#3E4452";
static const char col_white[]	      = "#ABB2BF";
static const char col_green[]	      = "#98C379";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_gray },
	[SchemeSel]  = { col_green, col_black, col_green },
};

/* tagging */
//static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
//static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL }
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *browsercmd[]  = { "firefox", NULL }; /* Web Browser here */
static const char *filemncmd[]  = {"pcmanfm", NULL  }; /* File Manager here */
static const char *termcmd[]  = { "st", NULL }; /* Terminal ofc */
static const char *dmenucmd[]  = { "dmenu_run", "-c", "-p", "Commands  ", NULL }; /* Terminal ofc */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static Key keys[] = {
	/* modifier                     key        function        argument */

  /* Apps shortcuts */
	{ MODKEY|ShiftMask,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                                 XK_p,      spawn,          SHCMD("j4-dmenu-desktop --dmenu='dmenu -c -p Apps '")},
	{ MODKEY|ShiftMask,                       XK_n,      spawn,          SHCMD("networkmanager_dmenu -c -p Networkﯱ ")},
	{ MODKEY,                                 XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		          XK_b,	     spawn,	     {.v = browsercmd } },
	{ MODKEY|ShiftMask,		          XK_r,	     spawn,	     SHCMD("st -e lf")},
  { MODKEY|ControlMask,		          XK_b,	     spawn,	     SHCMD("tabbed -c surf -e")},
	{ MODKEY|ShiftMask,		          XK_Return, spawn,	     {.v = filemncmd } },

  /* Volume */
  {0,              XF86XK_AudioMute,         spawn,          SHCMD("pamixer -t")},
  {0,              XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pamixer -i 5")},
  {0,              XF86XK_AudioLowerVolume,  spawn,          SHCMD("pamixer -d 5")},
  {0,              XF86XK_AudioPlay,         spawn,          SHCMD("mpc toggle")},
  {0,              XF86XK_AudioStop,         spawn,          SHCMD("mpc stop")},
  {0,              XF86XK_AudioPrev,         spawn,          SHCMD("mpc prev")},
  {0,              XF86XK_AudioNext,         spawn,          SHCMD("mpc next")},
  {0,              XF86XK_MonBrightnessDown, spawn,          SHCMD("light -U 5")},
  {0,              XF86XK_MonBrightnessUp,   spawn,          SHCMD("light -A 5")},

  /* Screenshot */
  {MODKEY|ControlMask,                XK_u,       spawn,
        SHCMD("maim | xclip -selection clipboard -t image/png")},
  {MODKEY|ShiftMask,                            XK_u,       spawn,
        SHCMD("maim --select | xclip -selection clipboard -t image/png")},

  /* Vanity gap */
/*	
  { MODKEY|Mod2Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod2Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|ControlMask,           XK_l,      incrigaps,      {.i = -1 } },
*/
	{ MODKEY|ControlMask,           XK_0,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_comma,  defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },

  /* Default Functions */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	//{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,             XK_q,      quit,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

