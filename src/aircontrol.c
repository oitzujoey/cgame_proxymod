#include "aircontrol.h"

#include "cg_cvar.h"
#include "cg_draw.h"
#include "cg_local.h"
#include "cg_utils.h"
#include "help.h"

static vmCvar_t aircontrol;
static vmCvar_t aircontrol_yh;
static vmCvar_t aircontrol_rgbas;

static cvarTable_t aircontrol_cvars[] = {
  { &aircontrol, "mdd_aircontrol", "0", CVAR_ARCHIVE_ND },
  { &aircontrol_yh, "mdd_aircontrol_yh", "188 8", CVAR_ARCHIVE_ND },
  { &aircontrol_rgbas, "mdd_aircontrol_rgbas", "1 1 1 1 / 1 .5 0 1", CVAR_ARCHIVE_ND },
};

static help_t aircontrol_help[] = {
  { aircontrol_cvars + 0,
    BINARY_LITERAL,
    {
      "mdd_aircontrol (0 | 1)",
    }
  },
  {
    aircontrol_cvars + 1,
    Y | H,
    {
      "mdd_aircontrol_yh X X",
    },
  },
  {
    aircontrol_cvars + 2,
    RGBAS,
    {
      "mdd_aircontrol_rgbas X X X X / X X X X / X X X X / X X X X",
    },
  }
};

typedef struct
{
  vec2_t yh;
  vec4_t rgba;
  playerState_t pm_ps;
  qhandle_t cpmMaxTurnIndicator;

} aircontrol_t;

static aircontrol_t s;

void init_aircontrol(void)
{
  init_cvars(aircontrol_cvars, ARRAY_LEN(aircontrol_cvars));
  init_help(aircontrol_help, ARRAY_LEN(aircontrol_help));

  s.cpmMaxTurnIndicator = trap_R_RegisterShader("cpmMaxTurnIndicator");
}

void update_aircontrol(void)
{
  update_cvars(aircontrol_cvars, ARRAY_LEN(aircontrol_cvars));
  aircontrol.integer = cvar_getInteger("mdd_aircontrol");
}

void draw_aircontrol(void)
{
  if (!aircontrol.integer) return;

  ParseVec(aircontrol_yh.string, s.yh, 2);

  s.pm_ps = *getPs();

  float yaw = DEG2RAD(s.pm_ps.viewangles[YAW]);

  if (aircontrol.integer && (s.pm_ps.velocity[0] != 0 || s.pm_ps.velocity[1] != 0))
  {
    ParseVec4(aircontrol_rgbas.string, &s.rgba, 2);
    vec4_t* color = &s.rgba;
    if (s.pm_ps.velocity[0] == 0 || s.pm_ps.velocity[1] == 0)
    {
      color = &s.rgba;
    }

    float v_dir = atan2f(s.pm_ps.velocity[1], s.pm_ps.velocity[0]);

    float const y = s.yh[0] + s.yh[1];
    float const w = s.yh[1];
    float const h = s.yh[1];

    CG_DrawCharYaw(v_dir, yaw + DEG2RAD(51.66), y - h, w, h, '|', *color);
    CG_DrawCharYaw(v_dir, yaw - DEG2RAD(51.66), y - h, w, h, '|', *color);
  }
}
