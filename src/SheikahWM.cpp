/*
 * sheikahWM
 * Copyright (C) 2025  Lena Voytek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <miral/runner.h>
#include <miral/set_window_management_policy.h>

#include "WindowManager.h"

using namespace miral;

int main(int argc, char const *argv[]) {
  MirRunner runner{argc, argv};
  sheikah::WindowManagerObserver window_manager_observer{};
  DisplayConfiguration display_config{runner};

  return runner.run_with({
      display_config,
      set_window_management_policy<sheikah::WindowManager>(window_manager_observer, display_config)
  });
}