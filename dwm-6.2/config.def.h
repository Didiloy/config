/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
#include <X11/XF86keysym.h>
/* appearance */
static const char font[]            = "-*-*-medium-*-*-*-10-*-*-*-*-*-*-*";
// static const char normbordercolor[] = "#ababab";
// static const char normbgcolor[]     = "#292929";
// static const char normfgcolor[]     = "#ff6b6b";
// static const char selbordercolor[]  = "#ababab";
// static const char selbgcolor[]      = "#292929";
// static const char selfgcolor[]      = "#ff6b6b";
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps size between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
//================================================
//Je bind les touches de volume et de luminosité.
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
// static const char *brightness_up[]  =   { "cwm-brightness", "up", NULL };
static const char *brightness_up[]  =   { "brightnessctl", "--min-val=2", "-q", "set", "3%-", NULL };
// static const char *brightness_down[]  = { "cwm-brightness", "down", NULL };
static const char *brightness_down[]  =   { "brightnessctl", "-q", "set", "3%+", NULL };
//================================================
//background color
static const char col_gray1[]       = "#222222";
//inactive window border color
static const char col_gray2[]       = "#444444";
//font color
static const char col_gray3[]       = "#bbbbbb";

//current tag and and current window font color
static const char col_gray4[]       = "#eeeeee";

//top bar seconde color and active window border color
static const char col_left[]       = "#2e3440";	
//J'ajoute une couleur pour le coté gauche de la bar

static const char col_right[]       ="#3b4252";
// "#3bb994";"#F17F42";
//J'ajoute une couleur pour le coté droit de la bar

static const char col_middle[]        = "#434c5e";
//#684cdf

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_middle, "#fa8caa"  }, //Couleur de la bordure des fenetre
	[SchemeStatus]  = { col_gray4, col_right,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_left,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_left,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_middle,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* tile normal. Master a gauche et slave a droite*/
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle }, /*toute les fenetre les une sur les autres (plein écran)*/
	{ "TTT",      bstack }, /* Tile vertical. Master en haut et slave en bas*/
	{ "===",      bstackhoriz },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_middle, "-sf", col_gray4, NULL };
// static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = {"kitty", "-e", "fish", NULL};




static Key keys[] = {
	/* modifier                     key        function        argument */
    { 0,                            XF86XK_MonBrightnessUp,   spawn, SHCMD("brightnessctl --min-val=2 set 3%+")},
    { 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl --min-val=2 set 3%-")},
    // { MODKEY,                       XK_a,      spawn,         SHCMD("brightnessctl --min-val=2 set 3%-")},
    // { MODKEY,                       XK_z,      spawn,         SHCMD("brightnessctl --min-val=2 set 3%+")},
    // { MODKEY,                       XK_z,      spawn,         {.v = brightness_down   } },
    // { MODKEY,                       XK_a,      spawn,         {.v = brightness_up   } },
    { MODKEY,			            XK_n,	   spawn,          SHCMD("redshift -O 3000K") },
    { MODKEY|ShiftMask,	            XK_n,	   spawn,          SHCMD("redshift -l 47.21:-1.55 -o 6500K -P") },
    // { MODKEY,			            XK_d,	   spawn,          SHCMD("rofi -show drun -theme onedark") },
    // { MODKEY,			            XK_d,	   spawn,          SHCMD("dmenu_run") },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("bash $HOME/.config/dmenu/dmconfig")},
    { MODKEY|ShiftMask,	            XK_p,	   spawn,          SHCMD("reboot") },
    { MODKEY|ShiftMask,	            XK_o,	   spawn,          SHCMD("shutdown -h now") },
	{ MODKEY,                      XK_Return, spawn,           {.v = termcmd } },         
    { MODKEY|ShiftMask,	            XK_u,	   spawn,          SHCMD("qutebrowser") },
    { MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[3]} },
	// { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	// { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_m,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,       {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_m,         tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,       setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_l,       setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_j,       setgaps,        {.i = 0  } },
	TAGKEYS(                        0x26,                      0)
	TAGKEYS(                        0xe9,                      1)
	TAGKEYS(                        0x22,                      2)
	TAGKEYS(                        0x27,                      3)
	TAGKEYS(                        0x28,                      4)
	TAGKEYS(                        0x2d,                      5)
	TAGKEYS(                        0xe8,                      6)
	TAGKEYS(                        0x5f,                      7)
	TAGKEYS(                        0xe7,                      8)
	TAGKEYS(                        XK_KP_End,                      0)
	TAGKEYS(                        XK_KP_Down,                     1)
	TAGKEYS(                        XK_KP_Next,                     2)
	TAGKEYS(                        XK_KP_Left,                     3)
	TAGKEYS(                        XK_KP_Begin,                    4)
	TAGKEYS(                        XK_KP_Right,                    5)
	TAGKEYS(                        XK_KP_Home,                     6)
	TAGKEYS(                        XK_KP_Up,                       7)
	TAGKEYS(                        XK_KP_Prior,                    8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    //Touches de volume======================================================
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioMute, spawn,        {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
    //======================================================================
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
