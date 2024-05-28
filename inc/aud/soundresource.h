#pragma once
#include <variant>
#include <optional>
#include "wavtool.h"

using SoundRes = std::optional<std::variant<WavTool::RiffWAV>>;     // will get exteded
                                                                    // with other formats
