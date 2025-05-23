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

#include <miral/application_info.h>

#include "WindowManager.h"

using namespace sheikah;

void apply_fullscreen(miral::WindowSpecification &spec) {
  spec.state() = mir_window_state_fullscreen;
  spec.size() = mir::optional_value<miral::Size>{};
  spec.top_left() = mir::optional_value<miral::Point>{};
}

void WindowManagerObserver::add_window_opened_callback(std::function<void()> const &callback) {
  window_opened_callbacks.push_back(callback);
}

void WindowManagerObserver::add_window_closed_callback(std::function<void()> const &callback) {
  window_closed_callbacks.push_back(callback);
}


void WindowManagerObserver::process_window_opened_callbacks() const {
  for (auto const &callback : window_opened_callbacks) {
    callback();
  }
}

void WindowManagerObserver::process_window_closed_callbacks() const {
  for (auto const &callback : window_closed_callbacks) {
    callback();
  }
}

WindowManager::WindowManager(
    miral::WindowManagerTools const &tools,
    WindowManagerObserver &window_manager_observer,
    miral::DisplayConfiguration const &display_config)
  : MinimalWindowManager{tools},
    window_manager_observer{window_manager_observer},
    display_config{display_config} {
}

void WindowManager::handle_layout(
    miral::WindowSpecification &specification,
    miral::Application const &application,
    miral::WindowInfo &window_info) {
  apply_fullscreen(specification);
}

auto WindowManager::place_new_window(miral::ApplicationInfo const &app_info, miral::WindowSpecification const &request)
  -> miral::WindowSpecification {
  miral::WindowSpecification specification = MinimalWindowManager::place_new_window(app_info, request);
  miral::WindowInfo window_info{};
  handle_layout(specification, app_info.application(), window_info);

  return specification;
}