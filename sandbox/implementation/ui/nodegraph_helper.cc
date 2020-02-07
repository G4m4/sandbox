/// @file nodegraph_helper.cc
/// @brief SandBox ImGui nodegraph helper implementation
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

#include "sandbox/implementation/ui/nodegraph_helper.h"

#include "sandbox/implementation/ui/nodegraph.h"

namespace sandbox {
namespace imgui {

namespace nodegraph {
extern CanvasState *gCanvas;
}
using nodegraph::gCanvas;

namespace node_helpers {

bool BeginNode(void *node_id, const char *title, ImVec2 *pos, bool *selected) {
  bool result = nodegraph::BeginNode(node_id, pos, selected);

  auto *storage = ImGui::GetStateStorage();
  float node_width = storage->GetFloat(ImGui::GetID("node-width"));
  if (node_width > 0) {
    // Center node title
    ImVec2 title_size = ImGui::CalcTextSize(title);
    if (node_width > title_size.x)
      ImGui::SetCursorPosX(ImGui::GetCursorPosX() + node_width / 2.f -
                           title_size.x / 2.f);
  }

  // Render node title
  ImGui::TextUnformatted(title);

  ImGui::BeginGroup();
  return result;
}

void EndNode() {
  // Store node width which is needed for centering title.
  auto *storage = ImGui::GetStateStorage();
  ImGui::EndGroup();
  storage->SetFloat(ImGui::GetID("node-width"), ImGui::GetItemRectSize().x);
  nodegraph::EndNode();
}

bool Slot(const char *title, int kind) {
  auto *storage = ImGui::GetStateStorage();
  const auto &style = ImGui::GetStyle();
  const float CIRCLE_RADIUS = 5.f * gCanvas->zoom;
  ImVec2 title_size = ImGui::CalcTextSize(title);
  // Pull entire slot a little bit out of the edge so that curves connect into
  // int without visible seams
  float item_offset_x = style.ItemSpacing.x * gCanvas->zoom;
  if (!nodegraph::IsOutputSlotKind(kind))
    item_offset_x = -item_offset_x;
  ImGui::SetCursorScreenPos(ImGui::GetCursorScreenPos() +
                            ImVec2{item_offset_x, 0});

  if (nodegraph::BeginSlot(title, kind)) {
    auto *draw_lists = ImGui::GetWindowDrawList();

    // Slot appearance can be altered depending on curve hovering state.
    bool is_active =
        nodegraph::IsSlotCurveHovered() || (nodegraph::
                                                IsConnectingCompatibleSlot() /*&& !IsAlreadyConnectedWithPendingConnection(title, kind)*/);

    ImColor color = gCanvas->colors[is_active ? nodegraph::ColConnectionActive
                                              : nodegraph::ColConnection];

    ImGui::PushStyleColor(ImGuiCol_Text, color.Value);

    if (nodegraph::IsOutputSlotKind(kind)) {
      // Align output slots to the right edge of the node.
      ImGuiID max_width_id = ImGui::GetID("output-max-title-width");
      float output_max_title_width =
          ImMax(storage->GetFloat(max_width_id, title_size.x), title_size.x);
      storage->SetFloat(max_width_id, output_max_title_width);
      float offset =
          (output_max_title_width + style.ItemSpacing.x) - title_size.x;
      ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);

      ImGui::TextUnformatted(title);
      ImGui::SameLine();
    }

    ImRect circle_rect{ImGui::GetCursorScreenPos(),
                       ImGui::GetCursorScreenPos() +
                           ImVec2{CIRCLE_RADIUS * 2, CIRCLE_RADIUS * 2}};
    // Vertical-align circle in the middle of the line.
    float circle_offset_y = title_size.y / 2.f - CIRCLE_RADIUS;
    circle_rect.Min.y += circle_offset_y;
    circle_rect.Max.y += circle_offset_y;
    draw_lists->AddCircleFilled(circle_rect.GetCenter(), CIRCLE_RADIUS, color);

    ImGui::ItemSize(circle_rect.GetSize());
    ImGui::ItemAdd(circle_rect, ImGui::GetID(title));

    if (nodegraph::IsInputSlotKind(kind)) {
      ImGui::SameLine();
      ImGui::TextUnformatted(title);
    }

    ImGui::PopStyleColor();
    nodegraph::EndSlot();

    // A dirty trick to place output slot circle on the border.
    ImGui::GetCurrentWindow()->DC.CursorMaxPos.x -= item_offset_x;
    return true;
  }
  return false;
}

void InputSlots(const SlotInfo *slots, std::size_t snum) {
  const auto &style = ImGui::GetStyle();

  // Render input slots
  ImGui::BeginGroup();
  {
    for (std::size_t i = 0; i < snum; i++)
      node_helpers::Slot(slots[i].title,
                         nodegraph::InputSlotKind(slots[i].kind));
  }
  ImGui::EndGroup();

  // Move cursor to the next column
  ImGui::SetCursorScreenPos({ImGui::GetItemRectMax().x + style.ItemSpacing.x,
                             ImGui::GetItemRectMin().y});

  // Begin region for node content
  ImGui::BeginGroup();
}

void OutputSlots(const SlotInfo *slots, std::size_t snum) {
  const auto &style = ImGui::GetStyle();

  // End region of node content
  ImGui::EndGroup();

  // Render output slots in the next column
  ImGui::SetCursorScreenPos({ImGui::GetItemRectMax().x + style.ItemSpacing.x,
                             ImGui::GetItemRectMin().y});
  ImGui::BeginGroup();
  {
    for (std::size_t i = 0; i < snum; i++)
      node_helpers::Slot(slots[i].title,
                         nodegraph::OutputSlotKind(slots[i].kind));
  }
  ImGui::EndGroup();
}

} // namespace node_helpers
} // namespace imgui
} // namespace sandbox
