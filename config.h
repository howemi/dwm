/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 2;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

/* These colors can be ridden by the xrdb patch */
static char normbgcolor[]           = "#000000";
static char normbordercolor[]       = "#000000";
static char normfgcolor[]           = "#000000";
static char selfgcolor[]            = "#000000";
static char selbordercolor[]        = "#000000";
static char selbgcolor[]            = "#000000";
/* Any colors can be set in Xresources if you change */
/* xrdb (dwm.c) to load them into the correct variables */

/* solarized colors http://ethanschoonover.com/solarized */
/* static const char s_base03[]        = "#002b36"; */ // Border
/* static const char s_base02[]        = "#073642"; */ // Menu
/* static const char s_base01[]        = "#586e75"; */
static const char s_base03[]        = "#fc7f80"; // salmon
static const char s_base02[]        = "#f58f90"; // darker salmon
static const char s_base01[]        = "#ab4141"; // darkerer salmon
static const char s_base00[]        = "#008585"; // darker teal
static const char s_base0[]         = "#005e5e"; // teal
static const char s_base1[]         = "#93a1a1"; // gray
static const char s_base2[]         = "#eee8d5"; // cream
static const char s_base3[]         = "#e9c46a"; // yellow
static const char s_basebl[]        = "#111111"; // black
static const char s_baselg[]        = "#444444"; // light gray
static const char s_basewh[]        = "#dddddd"; // white
static const char s_basesg[]        = "#00ff7f"; // spring green
static const char s_basely[]        = "#f5ffaa"; // light yellow

static char *colors[][4] = {
       /*               fg           bg           border   */
       /*  text      bar     border */
       { s_basely, s_basebl, s_basebl }, // Normal
       { s_basesg, s_basebl, s_basebl}, // Selected

       { s_base02, s_base0, s_base02 }, // Normal
       { s_base3, s_base00, s_base02}, // Selected

       { s_base0, s_base03, s_base2 }, // Normal
       { s_base0, s_base02, s_base2 }, // Selected

       { normfgcolor, normbgcolor, normbordercolor }, /* SchemeNorm orig */
       { selfgcolor,  selbgcolor,  selbordercolor  }, /* SchemeSel orig */
       /* [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor }, */
       /* [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  }, */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           0,         0,        -1 },
	{ "St",       NULL,       NULL,       0,            0,           1,         1,        -1 },
	{ NULL,		  "spterm",	  NULL,		SPTAG(0),		1,			 1,         0,        -1 },
	{ NULL,		  "spfm",	  NULL,		SPTAG(1),		1,			 1,         0,        -1 },
	{ NULL,       NULL,   "Event Tester", 0,            0,           0,         1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
};


#include <X11/XF86keysym.h>


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,     spawn,          {.v = dmenucmd } },
	{ MODKEY,             		    XK_backslash, spawn,          {.v = termcmd } },
	/* { MODKEY|ShiftMask,   		    XK_backslash, togglescratch,  {.v = scratchpadcmd } }, */
	{ MODKEY|ShiftMask,    			XK_backslash,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_apostrophe,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,             		    XK_w,	   spawn,          SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,    		    XK_w,	   spawn,          SHCMD("st -e sudo nmtui") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,    		            XK_r,	   spawn,          SHCMD("st -e ranger") },
	{ MODKEY,    		            XK_g,	   spawn,          SHCMD("gimp") },
	{ MODKEY,    		            XK_u,	   spawn,          SHCMD("spotify") },
	{ MODKEY,    		            XK_c,	   spawn,          SHCMD("slack") },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,             		    XK_s,      schemeCycle,    {0} },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY,             		    XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY,                 XK_bracketright, spawn,	   SHCMD("setaudio") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,             		    XK_Escape, spawn,	   SHCMD("slock & xset dpms force off") },


	/* { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } }, */


	/* { MODKEY,                       XK_F1,     mpdchange,      {.i = -1} }, */
	/* { MODKEY,                       XK_F2,     mpdchange,      {.i = +1} }, */
	/* { MODKEY,                       XK_Escape, mpdcontrol,     {0} }, */
	{ 0, XF86XK_AudioMute,      	spawn,	   SHCMD("amixer -q sset Master toggle") },
	{ 0, XF86XK_AudioLowerVolume,  	spawn,	   SHCMD("amixer -q sset Master 5%-") },
	{ 0, XF86XK_AudioRaiseVolume,  	spawn,	   SHCMD("amixer -q sset Master 5%+") },
	{ 0, XF86XK_MonBrightnessUp,  	spawn,	   SHCMD("sudo brightnessctl -d 'intel_backlight' set 5%+") },
	{ 0, XF86XK_MonBrightnessDown, 	spawn,	   SHCMD("sudo brightnessctl -d 'intel_backlight' set 5%-") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
