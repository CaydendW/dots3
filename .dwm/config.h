/* See LICENSE file fo copyright and license details. */

/* Constants */
#define TERMINAL "kitty"

/* appearance */
static unsigned int borderpx = 2; /* border pixel of windows */
static unsigned int snap = 3;     /* snap pixel */
static unsigned int gappih = 35;  /* horiz inner gap between windows */
static unsigned int gappiv = 35;  /* vert inner gap between windows */
static unsigned int gappoh = 35;  /* horiz outer gap between windows and screen edge */
static unsigned int gappov = 35;  /* vert outer gap between windows and screen edge */
static int swallowfloating = 0;   /* 1 means swallow floating windows by default */
static int smartgaps = 0;         /* 1 means no outer gap when there is only one window */
static int showbar = 0;           /* 0 means no bar */
static int topbar = 1;            /* 0 means bottom bar */
static char *fonts[] = {"Source Code Pro:size=10"};
static char normbgcolor[] = "#161925";
static char normbordercolor[] = "#7CB7FF";
static char normfgcolor[] = "#dedede";
static char selfgcolor[] = "#dedede";
static char selbordercolor[] = "#71F79F";
static char selbgcolor[] = "#161925";

static char *colors[][3] = {
    /*            fg         bg         border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

typedef struct
{
   const char *name;
   const void *cmd;
} Sp;

const char *spcmd1[] = {"Shutup"}; // can't get rid of this
static Sp scratchpads[] = {
    /* name        cmd  */
    {"spterm", spcmd1},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
*	WM_CLASS(STRING) = instance, class
*	WM_NAME(STRING) = title
*/
    /* class   instance     title      	 tags mask   isfloating   isterminal  noswallow  monitor */
    {"leave me alone", NULL, NULL, 1 << 8, 0, 0, 0, -1},
};

/* layout(s) */
static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 1; /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1      /* nrowgrid layout: force two clients to always split vertically */

#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol    arrange function */
    {"[]=", tile},   /* Default: Master on left, slaves on right */
    {"TTT", bstack}, /* Master on top, slaves on bottom */

    {"[@]", spiral},   /* Fibonacci spiral */
    {"[\\]", dwindle}, /* Decreasing in size right and leftward */

    {"|M|", centeredmaster},         /* Master in middle, slaves on sides */
    {"|<M>|", centeredfloatingmaster}, /* Master in middle, slaves on sides but master floats*/

    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

/* Key Definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY, TAG)                                                        \
   {MODKEY | ShiftMask, KEY, view, {.ui = 1 << TAG}}, /*Move view to workspace*/ \
       {MODKEY, KEY, tag, {.ui = 1 << TAG}},          /*Move window to workspace*/

#define STACKKEYS(MOD, ACTION) \ 
{MOD, XK_j, ACTION##stack,{.i = INC(+1)}},    \
{MOD, XK_k, ACTION##stack, {.i = INC(-1)}},      \  

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                         \
   {                                                       \
      .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
   }

/* commands */
static const char *termcmd[] = {TERMINAL, NULL};

/*
* Xresources preferences to load at startup
*/
ResourcePref resources[] = {
    {"color0", STRING, &normbordercolor},
    {"color8", STRING, &selbordercolor},
    {"color0", STRING, &normbgcolor},
    {"color4", STRING, &normfgcolor},
    {"color0", STRING, &selfgcolor},
    {"color4", STRING, &selbgcolor},
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
    {"gappih", INTEGER, &gappih},
    {"gappiv", INTEGER, &gappiv},
    {"gappoh", INTEGER, &gappoh},
    {"gappov", INTEGER, &gappov},
    {"swallowfloating", INTEGER, &swallowfloating},
    {"smartgaps", INTEGER, &smartgaps},
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
    /* The Basics */
    {MODKEY, XK_q, killclient, {0}},                                                                                         // Kill focussed window
    {MODKEY, XK_Return, spawn, {.v = termcmd}},                                                                              // Open Terminal
    {MODKEY, XK_d, spawn, SHCMD("rofi -modi drun,window -theme sweet -icon-theme \"Numix Circle\" -show-icons -show drun")}, // Launch rofi
    {MODKEY | ShiftMask, XK_e, quit, {0}},                                                                                   // Exit dwm

    /* Workspace stuff */
    TAGKEYS(XK_1, 0)                   // Move / Focus workspace 1
    TAGKEYS(XK_2, 1)                   // Move / Focus workspace 2
    TAGKEYS(XK_3, 2)                   // Move / Focus workspace 3
    TAGKEYS(XK_4, 3)                   // Move / Focus workspace 4
    TAGKEYS(XK_5, 4)                   // Move / Focus workspace 6
    TAGKEYS(XK_6, 5)                   // Move / Focus workspace 7
    TAGKEYS(XK_7, 6)                   // Move / Focus workspace 8
    TAGKEYS(XK_8, 7)                   // Move / Focus workspace 9
    TAGKEYS(XK_9, 8)                   // Move / Focus workspace 10
    {MODKEY, XK_g, togglesticky, {0}}, // Make window sticky (Persist on all workspaces)

    /* Scratchpad */
    {MODKEY, XK_minus, scratchpad_show, {0}},             // Cycle scratchpad
    {MODKEY | ShiftMask, XK_minus, scratchpad_hide, {0}}, // Send to scratchpad
    {MODKEY, XK_equal, scratchpad_remove, {0}},           // Remove from scratchpad
    {MODKEY, XK_0, view, {.ui = ~0}},                     // View scratchpad workspace

    /* Moving of tiled windows */
    STACKKEYS(MODKEY, push) // Move focused window

    /* Chaning focus of tiled windows */
    STACKKEYS(MODKEY | ShiftMask, focus) // Change focus

    /* Layouts */
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},             // Tile
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[1]}}, // Bstack
    {MODKEY, XK_s, setlayout, {.v = &layouts[2]}},             // Spiral
    {MODKEY | ShiftMask, XK_s, setlayout, {.v = &layouts[3]}}, // Dwindle
    {MODKEY, XK_r, setlayout, {.v = &layouts[4]}},             // Centered master
    {MODKEY | ShiftMask, XK_r, setlayout, {.v = &layouts[5]}}, // Centered floating master
    {MODKEY, XK_f, togglefullscr, {0}},                        // Fullscreen

    /* Gaps */
    {MODKEY, XK_a, togglegaps, {0}},              // Toggle gaps
    {MODKEY, XK_x, incrgaps, {.i = +3}},          // Increase gaps
    {MODKEY, XK_z, incrgaps, {.i = -3}},          // Decrease gaps
    {MODKEY | ShiftMask, XK_a, defaultgaps, {0}}, // Reset gaps

    /* Borders */
    {MODKEY, XK_c, toggleborder, {0}},                  // Toggle borderping
    {MODKEY | ShiftMask, XK_x, setborderpx, {.i = +1}}, // Increase border
    {MODKEY | ShiftMask, XK_z, setborderpx, {.i = -1}}, // Decrease border
    {MODKEY | ShiftMask, XK_c, setborderpx, {.i = 0}},  // Reset border (to 3)

    /* Resize of tiled windows */
    {MODKEY | ControlMask, XK_j, setmfact, {.f = +0.01}}, // Make master area bigger
    {MODKEY | ControlMask, XK_k, setmfact, {.f = -0.01}},  // Make master area smaller

    /* Reset master area size */
    {MODKEY | ControlMask | ShiftMask, XK_j, setmfact, {.f = 1.55}}, // Reset master area size
    {MODKEY | ControlMask | ShiftMask, XK_k, setmfact, {.f = 1.55}},    // Reset master area size

    /* Controll of master pane(s) */
    {MODKEY, XK_space, zoom, {0}},                // Send window to master
    {MODKEY, XK_w, incnmaster, {.i = +1}},        // Add possible master window
    {MODKEY, XK_e, incnmaster, {.i = -1}},        // Remove possible master window
    {MODKEY | ShiftMask, XK_w, resetmaster, {0}}, // Set amount of masters to default

    /* Misc */
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}}, // Toggle floating window
    {MODKEY, XK_b, togglebar, {0}},                      // Toggle bar
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
#ifndef __OpenBSD__
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button1, sigdwmblocks, {.i = 1}},
    {ClkStatusText, 0, Button2, sigdwmblocks, {.i = 2}},
    {ClkStatusText, 0, Button3, sigdwmblocks, {.i = 3}},
    {ClkStatusText, 0, Button4, sigdwmblocks, {.i = 4}},
    {ClkStatusText, 0, Button5, sigdwmblocks, {.i = 5}},
    {ClkStatusText, ShiftMask, Button1, sigdwmblocks, {.i = 6}},
#endif
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, defaultgaps, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button4, incrgaps, {.i = +1}},
    {ClkClientWin, MODKEY, Button5, incrgaps, {.i = -1}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkTagBar, 0, Button4, shiftview, {.i = -1}},
    {ClkTagBar, 0, Button5, shiftview, {.i = 1}},
    {ClkRootWin, 0, Button2, togglebar, {0}},
};
