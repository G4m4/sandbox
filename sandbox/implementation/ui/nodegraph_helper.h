/// @file nodegraph_helper.h
/// @brief SandBox ImGui nodegraph helper header
/// @author gm
/// @copyright gm 2020
///
/// This file is part of SandBox
///
/// SandBox is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// SandBox is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with SandBox.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SANDBOX_SRC_IMPLEMENTATION_NODEGRAPH_HELPER_H
#define SANDBOX_SRC_IMPLEMENTATION_NODEGRAPH_HELPER_H

#include <cstddef>

struct ImVec2;

namespace sandbox {
namespace imgui {

// Borrowed from https://github.com/rokups/ImNodes.git

/// This namespace includes functions for easily creating nodes. They implement
/// a somewhat nice node layout. If you need a quick solution - use easy nodes.
/// If you want to customize node look - use lower level node functions
namespace node_helpers {

struct SlotInfo {
  /// Slot title, will be displayed on the node.
  const char *title;
  /// Slot kind, will be used for matching connections to slots of same kind.
  int kind;
};

/// Begin rendering of node in a graph. Render node content when returns `true`.
bool BeginNode(void *node_id, const char *title, ImVec2 *pos, bool *selected);
/// Terminates current node. Should be called regardless of BeginNode() returns
/// value.
void EndNode();
/// Renders input slot region. Kind is unique value whose sign is ignored.
/// This function must always be called after BeginNode() and before
/// OutputSlots(). When no input slots are rendered call InputSlots(nullptr, 0);
void InputSlots(const SlotInfo *slots, std::size_t snum);
/// Renders output slot region. Kind is unique value whose sign is ignored. This
/// function must always be called after InputSlots() and function call is
/// required (not optional). This function must always be called after
/// InputSlots() and before EndNode(). When no input slots are rendered call
/// OutputSlots(nullptr, 0);
void OutputSlots(const SlotInfo *slots, std::size_t snum);

} // namespace node_helpers

} // namespace imgui
} // namespace sandbox

#endif // SANDBOX_SRC_IMPLEMENTATION_NODEGRAPH_HELPER_H
