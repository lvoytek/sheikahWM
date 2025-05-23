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

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <miral/display_configuration.h>
#include <miral/minimal_window_manager.h>

namespace sheikah {
class WindowManagerObserver {
public:
  WindowManagerObserver() = default;
  void add_window_opened_callback(std::function<void()> const &callback);
  void add_window_closed_callback(std::function<void()> const &callback);

private:
  friend class WindowManager;

  void process_window_opened_callbacks() const;
  void process_window_closed_callbacks() const;

  std::vector<std::function<void()>> window_opened_callbacks;
  std::vector<std::function<void()>> window_closed_callbacks;
};

class WindowManager : public miral::MinimalWindowManager {
public:
  using MinimalWindowManager::MinimalWindowManager;
  WindowManager(miral::WindowManagerTools const &tools,
                WindowManagerObserver &window_manager_observer,
                miral::DisplayConfiguration const &display_config);

  void handle_layout(
      miral::WindowSpecification &spec,
      miral::Application const &application_info,
      miral::WindowInfo &info);

  auto place_new_window(miral::ApplicationInfo const &app_info, miral::WindowSpecification const &request)
    -> miral::WindowSpecification override;

private:
  WindowManagerObserver const &window_manager_observer;
  miral::DisplayConfiguration display_config;
};
}
#endif //WINDOWMANAGER_H