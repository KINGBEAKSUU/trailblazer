#pragma once

#include "system/hardware/base.h"
#include "common/util.h"
#include "common/params.h"

#if QCOM2
#include "system/hardware/tici/hardware.h"
#define Hardware HardwareTici
#else
#include "system/hardware/pc/hardware.h"
#define Hardware HardwarePC
#endif

namespace Path {
inline std::string log_root() {
  if (const char *env = getenv("LOG_ROOT")) {
    return env;
  }
  if (std::atoi(Params().get("dp_atl").c_str()) > 0 || Params().getBool("dp_jetson") || Params().getBool("dp_api_custom")) {
    return "/data/media/0/fakedata";
  } else {
    return Hardware::PC() ? util::getenv("HOME") + "/.comma/media/0/realdata" : "/data/media/0/realdata";
  }
}
inline std::string params() {
  return Hardware::PC() ? util::getenv("HOME") + "/.comma/params" : "/data/params";
}
inline std::string rsa_file() {
  return Hardware::PC() ? util::getenv("HOME") + "/.comma/persist/comma/id_rsa" : "/persist/comma/id_rsa";
}
}  // namespace Path
