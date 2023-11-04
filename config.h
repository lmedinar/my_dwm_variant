/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int gappx     = 10;                 /* gaps between windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab			= showtab_auto;        /* Default tab bar show mode */
static const int toptab				= True;               /* False means bottom tab bar */

/* static const char *fonts[]          = { "monospace:size=10" }; */
/* static const char dmenufont[]       = "monospace:size=10"; */
static const char *fonts[]          = {
  "HackGen Console:size=9",
  "Twitter Color Emoji:size=9",
  "unicons:size=7"
};
static const char dmenufont[]       = "HackGen Console:size=9";
//static const char col_gray1[]       = "#222222";
//static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
//static const char *colors[][3]      = {
	/*               fg         bg         border   */
//	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
//};
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance  title  tags mask  iscentered   isfloating  isfreesize  monitor */
  { "Gimp",     NULL,       NULL,       0,         1,           0,          0,      -1 },
  { "Tor Browser", NULL,    NULL,       0,         1,           1,          0,      -1 },
  { "feh",      NULL,       NULL,       0,         1,           1,          0,      -1 },
  { "mpv",      NULL,       NULL,       0,         1,           1,          1,      -1 },
  { "mpv",       NULL, "cara_mpv",   0,         0,           1,          1,      -1 },
  { "mpv",  "cara_mpv",  NULL,       0,         0,           1,          1,      -1 },
  { "Godot",    NULL,       NULL,       0,         1,           0,          1,      -1 },
  { NULL,   "Godot_Engine", NULL,       0,         1,           1,          1,      -1 },
  { "vokoscreenNG", NULL,   "Area",     0,         1,           1,          0,      -1 },
  /* { "obs",      NULL,       NULL,       1 << 7,    1,           0,          0,      -1 }, */
  { "krita",    NULL,   "Krita - Editar texto",    1,   0,      0,          1,      -1 },
  { "Citra",    NULL,       NULL,       0,         1,           1,          1,      -1 },
  /* { "Godot", "Godot_ProjectList", NULL, 0,      1,              0,           -1 }, */
  /* { "Godot", "Godot_Editor", NULL,      0,         1,           0,           -1 }, */
  { "URxvt",    NULL,  "scratchpad",     0,         1,           1,          0,      -1 },
  { "URxvt",    NULL,  "help_search",    0,         1,           1,          0,      -1 },
  { "URxvt",    NULL,  "pal_search",     0,         1,           1,          0,      -1 },
  { "URxvt",    NULL,  "mpv_link.sh",    0,         1,           1,          0,      -1 },
  { "zoom",     NULL,       "zoom",      0,         1,           1,          1,      -1 },
  { "matplotlilb", NULL,    NULL,        0,         1,           1,          1,      -1 },    
  { NULL,     NULL,       "Figure 1",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 2",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 3",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 4",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 5",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 6",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 7",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 8",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 9",    0,        1,           1,          1,      -1 },
  { NULL,     NULL,       "Figure 10",   0,        1,           1,          1,      -1 },
  { "avatar2.py",     NULL,      NULL,   0,        0,           1,          1,      -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 0;    /* 1 means respect decoration hints */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
  	{ "[ ]≡",      tile },    /* first entry is default */
   	{ "[ ]H",     dwindle },
 	{ "[↺]H",      spiral },
	{ "[▪□]",      NULL },    /* no layout function means floating behavior */
	{ "[¨¨]",      monocle },
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
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL }; */
static const char *dmenucmd[] = { "rofi", "-show", "combi", NULL };
static const char *upvol[]   = { "bash", "/home/staineko/scripts/dwm_vol_up.sh",    NULL };
static const char *downvol[] = { "bash", "/home/staineko/scripts/dwm_vol_down.sh",  NULL };
static const char *mutevol[] = { "bash", "/home/staineko/scripts/dwm_vol_mute.sh",  NULL };
static const char *mutemic[] = { "/usr/bin/pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle",  NULL };
static const char *lockscreen[] = { "bash", "/home/staineko/scripts/lock.sh", NULL};
static const char *scr_cap1[] = { "bash", "/home/staineko/scripts/captura.sh", NULL};
static const char *scr_cap2[] = { "bash", "/home/staineko/scripts/capturafull.sh", NULL};
static const char *scr_cap3[] = { "bash", "/home/staineko/scripts/capturafloat.sh", NULL};
static const char *scr_capT[] = { "bash", "/home/staineko/scripts/capturatexto.sh", NULL};
static const char *montador[] = { "bash", "/home/staineko/scripts/mounter.sh", NULL};
static const char *cambiar_fondo[] = { "bash", "/home/staineko/scripts/pickwal.sh", NULL};
static const char *camera_start[] = { "bash", "/home/staineko/scripts/camera.sh", NULL};
static const char *scr_flame[] = { "flameshot", "gui", NULL};
static const char *filemanagergui[] = { "thunar", NULL};
static const char *cmus_play[] = { "cmus-remote", "-u", NULL};
static const char *cmus_next[] = { "cmus-remote", "-n", NULL};
static const char *cmus_prev[] = { "cmus-remote", "-r", NULL};
static const char *subir_brillo[] = { "xbacklight", "-inc", "5", NULL};
static const char *bajar_brillo[] = { "xbacklight", "-dec", "5", NULL};
static const char *rangerscript[] = { "urxvt", "-e", "/home/staineko/scripts/iniciar_ranger.sh", NULL};
static const char *code_helper[] = { "urxvt", "-geometry", "158x42",  "-e", "/home/staineko/scripts/help_search", "-name", "scratchpad", NULL};
static const char *word_helper[] = { "urxvt", "-geometry", "158x42",  "-e", "/home/staineko/scripts/pal_search", "-name", "scratchpad", NULL};
static const char *cmus_start[] = { "urxvt", "-e", "cmus", NULL};
static const char *nmtui_start[] = { "urxvt", "-e", "nmtui", NULL};
static const char *emacs_start[] = { "emacsclient", "-nc", NULL};
static const char *emacs_term[] = { "urxvt", "-e", "emacsclient", "-t", NULL};
static const char *calcurse_term[] = { "urxvt", "-e", "/home/staineko/scripts/iniciar_calcurse.sh", NULL};
static const char *color_picker[] = { "bash", "/home/staineko/scripts/color_picker.sh", NULL};
static const char *browser_start[] = { "qutebrowser", NULL};
static const char *firefox_start[] = { "firefox", NULL};
static const char *rofimoji_mat[] = { "rofimoji", "-a", "clipboard", "-f", "math", "mathematical_operators", "mathematical_alphanumeric_symbols", NULL};
static const char *rofimoji_emo[] = { "rofimoji", "-a", "clipboard", "-f", "emojis", "emoticons", NULL};
static const char *rofimoji_jap[] = { "rofimoji", "-a", "clipboard", "-f", "hiragana", "katakana", NULL};
static const char *roficalc[] = { "rofi", "-show", "calc", "-modi", "calc", "-no-show-match", "-no-sort", NULL};
static const char *scratch_term[] = { "urxvt", "-name", "scratchpad", "-geometry", "116x25", NULL};
static const char *sudo_dmenucmd[] = { "bash", "/home/staineko/scripts/sudorofiinit.sh", NULL };
static const char *termcmd[]  = { "urxvt", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = sudo_dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_o,      spawn,          {.v = scratch_term } }, 
        { MODKEY,                       XK_g,      spawn,          {.v = roficalc } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_w,      tabmode,        {-1} },
	/* { MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, */
	/* { MODKEY,                       XK_k,      focusstack,     {.i = -1 } }, */
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
        { MODKEY|ShiftMask,             XK_Down,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_plus,   incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
	/* { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, */
	/* { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, */
        { MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
 	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[2]} },
        { MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_braceleft,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_braceright,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_braceleft,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_braceright,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,       setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_plus,        setgaps,        {.i = +5 } },
	/* { MODKEY|ShiftMask,             XK_period,      setgaps,        {.i = 10  } }, */
	{ MODKEY,                       XK_k,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_i,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_l,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_j,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_k,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_i,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_l,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_j,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_i,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_k,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_j,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_l,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_i,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_k,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_j,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,  moveresizeedge, {.v = "R"} },
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
    { 0,                       XF86XK_AudioMicMute, spawn, {.v = mutemic   } },
    { 0,                       XF86XK_ScreenSaver, spawn, {.v = lockscreen   } },
    { 0,                       XF86XK_MonBrightnessUp,  spawn, {.v = subir_brillo   } },
    { 0,                       XF86XK_MonBrightnessDown,  spawn, {.v = bajar_brillo   } },
    { 0,                       XF86XK_AudioPlay,  spawn, {.v = cmus_play   } },
    { 0,                       XF86XK_AudioNext,  spawn, {.v = cmus_next   } },
    { 0,                       XF86XK_AudioPrev,  spawn, {.v = cmus_prev   } },
    { 0,                            XK_Print,      spawn,           {.v = scr_cap1 } },
    { ShiftMask,                    XK_Print,      spawn,           {.v = scr_cap2 } },
    { ControlMask,                  XK_Print,      spawn,           {.v = scr_cap3 } },
    { MODKEY|ShiftMask,             XK_t,          spawn,           {.v = scr_capT } },
    { ControlMask|ShiftMask,        XK_Print,      spawn,           {.v = scr_flame } },
    { MODKEY|ShiftMask,             XK_n,          spawn,           {.v = filemanagergui } },
    { MODKEY,                       XK_n,          spawn,           {.v = rangerscript } },
    { MODKEY,                       XK_p,          spawn,           {.v = cmus_start } },
    { MODKEY,                       XK_z,          spawn,           {.v = emacs_start } },
    { MODKEY|ShiftMask,             XK_z,          spawn,           {.v = emacs_term } },
    { MODKEY|ShiftMask,             XK_h,          spawn,           {.v = code_helper } },
    { MODKEY|ShiftMask,             XK_p,          spawn,           {.v = word_helper } },
    { MODKEY|ShiftMask,             XK_y,          spawn,           {.v = rofimoji_mat } },        
    { MODKEY,                       XK_y,          spawn,           {.v = rofimoji_emo } },
    { MODKEY,                       XK_h,          spawn,           {.v = rofimoji_jap } },
    { MODKEY,                       XK_u,          spawn,           {.v = browser_start } },
    { MODKEY|ShiftMask,             XK_u,          spawn,           {.v = firefox_start } },
    { MODKEY|ShiftMask,             XK_w,          spawn,           {.v = nmtui_start } },
    { MODKEY|ShiftMask,             XK_x,          spawn,           {.v = lockscreen } },
    { MODKEY|ShiftMask,             XK_m,          spawn,           {.v = montador } },
    { MODKEY|ShiftMask,             XK_r,          spawn,           {.v = cambiar_fondo } },
    { MODKEY|ShiftMask,             XK_v,          spawn,           {.v = camera_start } },
    { MODKEY,                       XK_c,          spawn,           {.v = color_picker } },
    { MODKEY|ShiftMask,             XK_c,          spawn,           {.v = calcurse_term } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	/* { ClkWinTitle,          0,              Button2,        zoom,           {0} }, // Eliminamos el título */
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

