/* See LICENSE file for copyright and license details. */

/* appearance */
#define NUMCOLORS	11	// need at least 3
static const char colors[NUMCOLORS][ColLast][8] = {
	// border   background  forground
	{ "#2e3436", "#000000", "#2e3436" },	// 0 = normal
	{ "#d3d7cf", "#000000", "#ffffff" },	// 1 = selected
	{ "#d3d7cf", "#a31604", "#000000" },	// 2 = urgent/warning
	{ "#000000", "#000000", "#555753" },	// black
	{ "#000000", "#000000", "#c60001" },	// red
	{ "#000000", "#000000", "#27a343" },	// green
	{ "#000000", "#000000", "#d5a30e" },	// yellow
	{ "#000000", "#000000", "#0f75bd" },	// blue
	{ "#000000", "#000000", "#893c8c" },	// magenta
	{ "#000000", "#000000", "#12bccb" },	// cyan
	{ "#000000", "#000000", "#d3d7cf" },	// white
};
static const char font[]                    = "Source Code Pro Icon-10";
static const unsigned int borderpx          = 1;        /* border pixel of windows */
static const unsigned int snap              = 16;       /* snap pixel */
static const unsigned int systrayspacing    = 2;        /* systray spacing */
static const Bool showsystray               = True;     /* False means no systray */
static const Bool showbar                   = True;     /* False means no bar */
static const Bool topbar                    = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,     "scratchpad", 0,            True,        -1 },
	{ "Vlc",      NULL,       NULL,       0,            True,        -1 },
	{ "mpv",      NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", colors[1][ColBG], "-nf", colors[1][ColFG], "-sb", colors[8][ColBG], "-sf", colors[8][ColFG], NULL }; //, "-m", dmenumon
static const char *passcmd[] = { "passmenu", "--type", "-fn", font, "-nb", colors[1][ColBG], "-nf", colors[1][ColFG], "-sb", colors[4][ColBG], "-sf", colors[4][ColFG], NULL }; //, "-m", dmenumon
static const char *termcmd[]  = { "termite", "-e", "fish", NULL };
static const char *scratchcmd[] = { "termite", "-e", "fish", "-t", "scratchpad", "--geometry", "605x122-20+30" ,NULL };
static const char *notecmd[] = { "termite", "-e", "/home/cornu/bin/note.sh", "-t", "scratchpad", "--geometry", "605x122-20+30" ,NULL };
static const char *filecmd[]  = { "termite", "-e", "ranger", NULL };
static const char *webcmd[]  = { "chromium", NULL, NULL, NULL, "Chromium" };
static const char *mediacmd[]  = { "vlc", NULL, NULL, NULL, "Vlc" };
static const char *prtncmd[]  = { "/home/cornu/bin/scrot.sh", NULL };
static const char *wificmd[]  = { "/home/cornu/bin/wifi.sh", NULL };
static const char *volupcmd[]  = { "/home/cornu/bin/volume.sh", "up", NULL };
static const char *voldowncmd[]  = { "/home/cornu/bin/volume.sh", "down", NULL };
static const char *volmutecmd[]  = { "/home/cornu/bin/volume.sh", "mute", NULL };

static Key keys[] = {
	/* modifier                     key             function        argument */
	{ MODKEY,                       XK_x,           spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_p,           spawn,          {.v = passcmd } },
	{ MODKEY|ShiftMask,             XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,           spawn,          {.v = scratchcmd } },
	{ MODKEY,                       XK_n,           spawn,          {.v = notecmd } },
	{ MODKEY,                       XK_r,           spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_w,           runorraise,     {.v = webcmd } },
	{ MODKEY,                       XK_v,           runorraise,     {.v = mediacmd } },
	{ 0,                            XK_Print,       spawn,          {.v = prtncmd } },
	{ 0,                            XK_XF86Battery, spawn,          {.v = wificmd } },
	{ 0,                            0x1008ff13,     spawn,          {.v = volupcmd } },
	{ 0,                            0x1008ff12,     spawn,          {.v = volmutecmd } },
	{ 0,                            0x1008ff11,     spawn,          {.v = voldowncmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
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
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

