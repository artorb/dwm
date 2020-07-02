/* See LICENSE file for copyright and license details. */
// Selmon - selected monitor
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 12;       /* snap pixel */ 
static const unsigned int gappih    = 7;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 7;       /* vert inner gap between windows */
static const unsigned int gappoh    = 7;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 7;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 2;        /* 0 means bottom bar */
static const int user_bh            = 25;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "scientifica:Medium:size=14"};
//static const char *fonts[]          = { "Cozette:size=10"};
//static const char *fonts[]          = { "Iosevka Nerd Font:size=13", "Ubuntu Mono:size=12"};
static const char dmenufont[]       = "Iosevka Nerd Font:Bold:size=13";
static const char col_gray1[]       = "#24182e";
static const char col_gray2[]       = "#3c223b";
static const char col_gray3[]       = "#f7c1d4";
static const char col_gray4[]       = "#7a8fd9";
static const char col_cyan[]        = "#2a1526";
static const char art_color1[]      = "#696ea9";
static const char art_color2[]      = "#858585";
static const char art_color3[]      = "#c1d4f7";
static const unsigned int baralpha = 60;
//static const unsigned int baralpha = 0xd0;
//static const unsigned int borderalpha = OPAQUE;
static const unsigned int borderalpha = 90;


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_cyan, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_cyan  },
    [SchemeHid]  = { col_cyan,  col_cyan, col_cyan  },
	[SchemeStatus]  = { art_color2, col_cyan,  "#9bc29e"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray3, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { art_color3, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_cyan,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const unsigned int alphas[][3]      = {
   /*               fg      bg        border     */
   [SchemeNorm] = { 150, baralpha, borderalpha },
   [SchemeSel]  = { 150, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "","" };

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
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
   	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define Win Mod4Mask
#define L_Alt Mod1Mask
#define R_Alt Mod5Mask /*alt -ISO Level3 Shift*/
#define R_Ctr Mod3Mask


#define TAGKEYS(KEY,TAG) \
	{ Win,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ R_Ctr,                  KEY,      view,           {.ui = 1 << TAG} }, \
	{ Win|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Win|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ Win|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browscmd[]  = { "chromium", NULL };

static Key keys[] = {
    /*art_cfg*/
    ///////////////////////////////////////////////////////////////////////////////////
	/* modifier                     key        function        argument */

    { R_Ctr,             XK_F7,      spawn,      SHCMD("brightnessctl set 5%-") },
    { R_Ctr,             XK_F8,      spawn,      SHCMD("brightnessctl set 5%+") },
    { R_Ctr,             XK_F10,     spawn,      SHCMD("scrot") },
    { R_Ctr,             XK_F5,      spawn,      SHCMD("mpc toggle") },
    { R_Ctr,             XK_F6,      spawn,      SHCMD("mpc next") },
    { R_Ctr,             XK_F4,      spawn,      SHCMD("mpc prev") },
    { R_Ctr,             XK_F1,      spawn,      SHCMD("toggle_mute_mpc") },
    { R_Ctr,             XK_F2,      spawn,      SHCMD("mpc volume -3") },
    { R_Ctr,             XK_F3,      spawn,      SHCMD("mpc volume +3") }, 
    { R_Ctr,             XK_d,       shiftview,      {.i = +1} }, 
    { R_Ctr,             XK_a,       shiftview,      {.i = -1} }, 
//{ Win,               XK_n,       spawn,      SHCMD("amixer -t; kill -44 $(pidof dwmblocks)") },
    { Win,               XK_n,      spawn,      SHCMD("alacritty -e ncmpcpp") },
    { Win,               XK_w,      spawn,          {.v = browscmd} },
    { Win,               XK_r,      spawn,          SHCMD("rofi -show run -theme sidebar -matching fuzzy")},
	{ L_Alt,             XK_f,      fullscreen,      {0} },
    { L_Alt,             XK_o,      setlayout,      {.v = &layouts[3]} },
    { L_Alt,             XK_u,      setlayout,      {.v = &layouts[4]} },
    
    //////////////////////////////////////////////////////////////////////////////////
    /*def*/
	/* modifier                     key        function        argument */
    { R_Ctr,                     XK_h,      hidefocused,    {0} },
    { R_Ctr,                     XK_j,      unhideall,      {0} },
	{ Win,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ Win|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ Win,                       XK_b,      togglebar,      {0} },
	{ Win,                       XK_j,      focusstack,     {.i = +1 } },
	{ Win,                       XK_k,      focusstack,     {.i = -1 } },
	{ Win,                       XK_i,      incnmaster,     {.i = +1 } },
	{ Win,                       XK_d,      incnmaster,     {.i = -1 } },
	{ Win,                       XK_h,      setmfact,       {.f = -0.05} },
	{ Win,                       XK_l,      setmfact,       {.f = +0.05} },
	{ Win|R_Ctr,                 XK_h,      incrgaps,       {.i = +1 } },
	{ Win|R_Ctr,                 XK_l,      incrgaps,       {.i = -1 } },
	{ Win|R_Ctr|ShiftMask,       XK_h,      incrogaps,      {.i = +1 } },
	{ Win|R_Ctr|ShiftMask,       XK_l,      incrogaps,      {.i = -1 } },
	{ Win|R_Ctr|ControlMask,     XK_h,      incrigaps,      {.i = +1 } },
	{ Win|R_Ctr|ControlMask,     XK_l,      incrigaps,      {.i = -1 } },
	{ Win|R_Ctr,                 XK_0,      togglegaps,     {0} },
	{ Win|R_Ctr|ShiftMask,       XK_0,      defaultgaps,    {0} },
	{ Win,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ Win,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ Win|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ Win|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ Win|R_Ctr,                 XK_y,      incrohgaps,     {.i = +1 } },
	{ Win|R_Ctr,                 XK_o,      incrohgaps,     {.i = -1 } },
	{ Win|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ Win|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ Win,                       XK_Return, zoom,           {0} },
	{ Win,                       XK_Tab,    view,           {0} },
	{ Win|ShiftMask,             XK_c,      killclient,     {0} },
	{ Win,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ Win,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ Win,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ Win|ControlMask,	      	XK_comma,  cyclelayout,    {.i = -1 } },
	{ Win|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ Win,                       XK_space,  setlayout,      {0} },
	{ Win|ShiftMask,             XK_space,  togglefloating, {0} },
	{ Win,                       XK_s,      togglesticky,   {0} },
	{ Win,                       XK_0,      view,           {.ui = ~0 } },
	{ Win|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ Win,                       XK_comma,  focusmon,       {.i = -1 } },
	{ Win,                       XK_period, focusmon,       {.i = +1 } },
	{ Win|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ Win|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ Win|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button3,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         Win,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         Win,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         Win,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            Win,         Button1,        tag,            {0} },
	{ ClkTagBar,            Win,         Button3,        toggletag,      {0} },
};

