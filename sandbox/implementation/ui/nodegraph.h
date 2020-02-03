/// @file nodegraph.h
/// @brief SandBox ImGui nodegraph header
/// @author gm
/// @copyright gm 2019
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

#ifndef SANDBOX_SRC_IMPLEMENTATION_NODEGRAPH_H
#define SANDBOX_SRC_IMPLEMENTATION_NODEGRAPH_H

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <externals/imgui/imgui.h>
#include <externals/imgui/imgui_internal.h>

namespace sandbox {
namespace imgui {
namespace nodegraph {

// Borrowed from https://github.com/rokups/ImNodes.git

enum StyleColor {
  ColCanvasLines,
  ColNodeBg,
  ColNodeActiveBg,
  ColNodeBorder,
  ColConnection,
  ColConnectionActive,
  ColSelectBg,
  ColSelectBorder,
  ColMax
};

struct _CanvasStateImpl;

struct CanvasState {
  /// Current zoom of canvas.
  float zoom = 1.0;
  /// Current scroll offset of canvas.
  ImVec2 offset{};
  /// Colors used to style elements of this canvas.
  ImColor colors[StyleColor::ColMax];
  /// Style parameters
  struct {
    /// Thickness of curves that connect slots together.
    float curve_thickness = 5.f;
    /// Indent connection into slot widget a little. Useful when slot content
    /// covers connection end with some kind of icon (like a circle) and then no
    /// seam between icon and connection end is visible.
    float connection_indent = 1.f;
  } style{};
  /// Implementation detail.
  _CanvasStateImpl *_impl = nullptr;

  CanvasState() noexcept;
  ~CanvasState();
};

/// Create a node graph canvas in current window.
void BeginCanvas(CanvasState *canvas);
/// Terminate a node graph canvas that was created by calling BeginCanvas().
void EndCanvas();
/// Begin rendering of node in a graph. Render node content when returns `true`.
bool BeginNode(void *node_id, ImVec2 *pos, bool *selected);
/// Terminates current node. Should be called regardless of BeginNode() returns
/// value.
void EndNode();
/// Specified node will be positioned at the mouse cursor on next frame. Call
/// when new node is created.
void AutoPositionNode(void *node_id);
/// Returns `true` when new connection is made. Connection information is
/// returned into `connection` parameter. Must be called at id scope created by
/// BeginNode().
bool GetNewConnection(void **input_node, const char **input_slot_title,
                      void **output_node, const char **output_slot_title);
/// Get information of connection that is being made and has only one end
/// connected. Returns true when pending connection exists, false otherwise.
bool GetPendingConnection(void **node_id, const char **slot_title,
                          int *slot_kind);
/// Render a connection. Returns `true` when connection is present, `false` if
/// it is deleted.
bool Connection(void *input_node, const char *input_slot, void *output_node,
                const char *output_slot);
/// Returns active canvas state when called between BeginCanvas() and
/// EndCanvas(). Returns nullptr otherwise. This function is not thread-safe.
CanvasState *GetCurrentCanvas();
/// Convert kind id to input type.
inline int InputSlotKind(int kind) { return kind > 0 ? -kind : kind; }
/// Convert kind id to output type.
inline int OutputSlotKind(int kind) { return kind < 0 ? -kind : kind; }
/// Returns `true` if `kind` is from input slot.
inline bool IsInputSlotKind(int kind) { return kind < 0; }
/// Returns `true` if `kind` is from output slot.
inline bool IsOutputSlotKind(int kind) { return kind > 0; }
/// Begins slot region. Kind is unique value indicating slot type. Negative
/// values mean input slots, positive - output slots.
bool BeginSlot(const char *title, int kind);
/// Begins slot region. Kind is unique value whose sign is ignored.
inline bool BeginInputSlot(const char *title, int kind) {
  return BeginSlot(title, InputSlotKind(kind));
}
/// Begins slot region. Kind is unique value whose sign is ignored.
inline bool BeginOutputSlot(const char *title, int kind) {
  return BeginSlot(title, OutputSlotKind(kind));
}
/// Rends rendering of slot. Call only if Begin*Slot() returned `true`.
void EndSlot();
/// Returns `true` if curve connected to current slot is hovered. Call between
/// `Begin*Slot()` and `EndSlot()`. In-progress connection is considered hovered
/// as well.
bool IsSlotCurveHovered();
/// Returns `true` when new slot is being created and current slot can be
/// connected. Call between `Begin*Slot()` and `EndSlot()`.
bool IsConnectingCompatibleSlot();

} // namespace nodegraph
} // namespace imgui
} // namespace sandbox

#endif // SANDBOX_SRC_IMPLEMENTATION_NODEGRAPH_H
