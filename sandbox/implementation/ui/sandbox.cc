/// @file sandbox.h
/// @brief SandBox UI class implementation
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

#include "sandbox/implementation/ui/sandbox.h"

#include <map>

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <externals/imgui/imgui.h>
#include <externals/imgui/imgui_internal.h>

#include "sandbox/implementation/ui/nodegraph.h"
#include "sandbox/implementation/ui/nodegraph_helper.h"

namespace sandbox {
namespace imgui {

///////////////////////////////////////////////////////////////////////////////
// Based on alpqr implementation: https://github.com/alpqr/imgui-qtquick
// node graph from: https://github.com/rokups/ImNodes.git
///////////////////////////////////////////////////////////////////////////////

/// A structure defining a connection between two slots of two nodes.
struct Connection {
  /// `id` that was passed to BeginNode() of input node.
  void *input_node = nullptr;
  /// Descriptor of input slot.
  const char *input_slot = nullptr;
  /// `id` that was passed to BeginNode() of output node.
  void *output_node = nullptr;
  /// Descriptor of output slot.
  const char *output_slot = nullptr;

  bool operator==(const Connection &other) const {
    return input_node == other.input_node && input_slot == other.input_slot &&
           output_node == other.output_node && output_slot == other.output_slot;
  }

  bool operator!=(const Connection &other) const { return !operator==(other); }
};

enum NodeSlotTypes {
  NodeSlotPosition = 1, // ID can not be 0
  NodeSlotRotation,
  NodeSlotMatrix,
};

/// A structure holding node state.
struct MyNode {
  /// Title which will be displayed at the center-top of the node.
  const char *title = nullptr;
  /// Flag indicating that node is selected by the user.
  bool selected = false;
  /// Node position on the canvas.
  ImVec2 pos{};
  /// List of node connections.
  std::vector<Connection> connections{};
  /// A list of input slots current node has.
  std::vector<node_helpers::SlotInfo> input_slots{};
  /// A list of output slots current node has.
  std::vector<node_helpers::SlotInfo> output_slots{};

  explicit MyNode(const char *title,
                  const std::vector<node_helpers::SlotInfo> &&input_slots,
                  const std::vector<node_helpers::SlotInfo> &&output_slots) {
    this->title = title;
    this->input_slots = input_slots;
    this->output_slots = output_slots;
  }

  ~MyNode() { std::printf("delete MyNode\n"); }

  /// Deletes connection from this node.
  void DeleteConnection(const Connection &connection) {
    for (auto it = connections.begin(); it != connections.end(); ++it) {
      if (connection == *it) {
        connections.erase(it);
        break;
      }
    }
  }
};

std::map<std::string, std::unique_ptr<MyNode> (*)(void)> available_nodes{
    {"Compose",
     []() {
       auto outPtr = std::make_unique<MyNode>(
           MyNode("Compose",
                  {
                      {"Position", NodeSlotPosition},
                      {"Rotation", NodeSlotRotation} // Input slots
                  },
                  {
                      {"Matrix", NodeSlotMatrix} // Output slots
                  }));
       return outPtr;
     }},
    {"Decompose",
     []() {
       auto outPtr = std::make_unique<MyNode>(
           MyNode("Decompose",
                  {
                      {"Matrix", NodeSlotMatrix} // Input slots
                  },
                  {
                      {"Position", NodeSlotPosition},
                      {"Rotation", NodeSlotRotation} // Output slots
                  }));
       return outPtr;
     }},
};

Sandbox::Sandbox()
    : dummy_class_instance_(new sandbox::dummygroup::DummyClass()), nodes_(),
      // Canvas must be created after ImGui initializes, because constructor
      // accesses ImGui style to configure default colors.
      canvas_(new nodegraph::CanvasState()) {}

Sandbox::~Sandbox() {}

void Sandbox::frame() {
  const ImGuiStyle &style = ImGui::GetStyle();
  if (ImGui::Begin("ImNodes", nullptr,
                   ImGuiWindowFlags_NoScrollbar |
                       ImGuiWindowFlags_NoScrollWithMouse)) {
    // We probably need to keep some state, like positions of nodes/slots for
    // rendering connections.
    nodegraph::BeginCanvas(canvas_.get());
    for (auto it = nodes_.begin(); it != nodes_.end();) {
      MyNode * node = it->get();

      // Start rendering node
      if (node_helpers::BeginNode(node, node->title, &node->pos,
                                  &node->selected)) {
        // Render input nodes first (order is important)
        node_helpers::InputSlots(node->input_slots.data(),
                                 node->input_slots.size());

        // Custom node content may go here
        ImGui::Text("Content of %s", node->title);

        // Render output nodes first (order is important)
        node_helpers::OutputSlots(node->output_slots.data(),
                                  node->output_slots.size());

        // Store new connections when they are created
        Connection new_connection;
        if (nodegraph::GetNewConnection(
                &new_connection.input_node, &new_connection.input_slot,
                &new_connection.output_node, &new_connection.output_slot)) {
          ((MyNode *)new_connection.input_node)
              ->connections.push_back(new_connection);
          ((MyNode *)new_connection.output_node)
              ->connections.push_back(new_connection);
        }

        // Render output connections of this node
        for (const Connection &connection : node->connections) {
          // Node contains all it's connections (both from output and to input
          // slots). This means that multiple nodes will have same connection.
          // We render only output connections and ensure that each connection
          // will be rendered once.
          if (connection.output_node != node)
            continue;

          if (!nodegraph::Connection(
                  connection.input_node, connection.input_slot,
                  connection.output_node, connection.output_slot)) {
            // Remove deleted connections
            ((MyNode *)connection.input_node)->DeleteConnection(connection);
            ((MyNode *)connection.output_node)->DeleteConnection(connection);
          }
        }
      }
      // Node rendering is done. This call will render node background based on
      // size of content inside node.
      node_helpers::EndNode();

      if (node->selected && ImGui::IsKeyPressedMap(ImGuiKey_Delete)) {
        // Deletion order is critical: first we delete connections to us
        for (auto &connection : node->connections) {
          if (connection.output_node == node) {
            ((MyNode *)connection.input_node)->DeleteConnection(connection);
          } else {
            ((MyNode *)connection.output_node)->DeleteConnection(connection);
          }
        }
        // Then we delete our own connections, so we don't corrupt the list
        node->connections.clear();

        it = nodes_.erase(it);
      } else
        ++it;
    }

    const ImGuiIO &io = ImGui::GetIO();
    if (ImGui::IsMouseReleased(1) && ImGui::IsWindowHovered() &&
        !ImGui::IsMouseDragging(1)) {
      ImGui::FocusWindow(ImGui::GetCurrentWindow());
      ImGui::OpenPopup("NodesContextMenu");
    }

    if (ImGui::BeginPopup("NodesContextMenu")) {
      for (const auto &desc : available_nodes) {
        if (ImGui::MenuItem(desc.first.c_str())) {
          std::unique_ptr<MyNode> node = desc.second();
          nodes_.push_back(std::move(node));
          nodegraph::AutoPositionNode(nodes_.back().get());
        }
      }
      ImGui::Separator();
      if (ImGui::MenuItem("Reset Zoom"))
        canvas_->zoom = 1;

      if (ImGui::IsAnyMouseDown() && !ImGui::IsWindowHovered())
        ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }

    nodegraph::EndCanvas();
  }
  ImGui::End();
}

} // namespace imgui
} // namespace sandbox
