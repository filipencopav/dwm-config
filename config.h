/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 12;       /* gaps between windows */
static const unsigned int snap      = 4;        /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[] = {
	"Terminus:pixelsize=14:antialias=false:hinting=false",
};
static const char norm_bg[]     = "#282828";
static const char sel_bg[]      = "#32302F";
static const char norm_border[] = "#282828";

static const char norm_fg[]     = "#BDAE83";
static const char sel_border[]  = "#D79921";
static const char sel_fg[]      = "#EBDBB2";

static const char *colors[][3]   = {
    /*               fg         bg         border   */
    [SchemeNorm] = { norm_fg,   norm_bg,   norm_border },
    [SchemeSel]  = { sel_fg,    sel_bg,    sel_border },
};

/* tagging */
static const char *tags[] = {
    "\u2022",
    "\u2022",
    "\u2022",
    "\u2022",
    "\u2022",
    "\u2022",
    "\u2022",
    "\u2022",
    "\u2022",
};

static const Rule rules[] = {
    /* xprop(1):
     *      WM_CLASS(STRING) = instance, class
     *      WM_NAME(STRING) = title
     */
    /* class                instance        title                   tags mask       isfloating      monitor */
    { "Chromium",           NULL,           NULL,                   1 << 3,         0,              -1 },
    { "ripcord",            NULL,           NULL,                   1 << 7,         0,              -1 },
    { "ripcord",            NULL,           "Emoji",                0,              1,              -1 },
    { "ripcord",            NULL,           "Ripcord Voice Chat",   0,              1,              -1 },
    { "UnityHub",           NULL,           NULL,                   1 << 5,         1,              -1 },
    { "Unity",              NULL,           NULL,                   1 << 5,         0,              -1 },
    { "Lingot",             NULL,           NULL,                   0,              1,              -1 },
    { "TelegramDesktop",    NULL,           NULL,                   1 << 7,         0,              -1 },
};

/* layout(s) */
static const float mfact     = 0.35; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol   arrange function */
    { "[]",     monocle }, /* first entry is default */
    { "##",     tile },
    { "<X>",    NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)                                                \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *mpdcmd[] = { "mpc", "toggle", NULL };
static const char *passmenucmd[] = { "passmenu", NULL };
static const char *screenshotcmd[] = { "screenshot", NULL };
static const char *maimcmd[] = { "screenshot", "-a", NULL };
static const char *winscrotcmd[] = { "screenshot", "-f", NULL };
static const char *emacs_client_cmd[] = { "emacsclient", "-n", "-c", NULL };
static const char *lowervolumecmd[] = { "amixer", "sset", "Master", "2%-", NULL };
static const char *raisevolumecmd[] = { "amixer", "sset", "Master", "2%+", NULL };

void nop(const Arg* arg) { return; }

static Key keys[] = {
    /* modifier                     key        function        argument */
    { Mod1Mask,                     XK_Caps_Lock,
                                               nop,            {0} },
    { MODKEY,                       XK_bracketleft,
                                               spawn,          {.v = lowervolumecmd } },
    { MODKEY,                       XK_bracketright,
                                               spawn,          {.v = raisevolumecmd } },
    { MODKEY,                       XK_p,      spawn,          {.v = passmenucmd } },
    { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { 0,                            XK_Print,  spawn,          {.v = screenshotcmd} },
    { ShiftMask,                    XK_Print,  spawn,          {.v = maimcmd} },
    { Mod1Mask,                     XK_Print,  spawn,          {.v = winscrotcmd} },
    { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = emacs_client_cmd} },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_s,      zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  spawn,          {.v = mpdcmd } },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

/* vim: set noexpandtab tw=4 sw=4: */
