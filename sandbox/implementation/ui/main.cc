/// @file implementation/ui/main.cc
/// @brief Implementation UI main entry point
/// @author gm
/// @copyright gm 2019
///
/// This file is part of Sandbox
///
/// Sandbox is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Sandbox is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with sandbox.  If not, see <http://www.gnu.org/licenses/>.

#include "sandbox/implementation/ui/imguiitem.h"
#include "sandbox/implementation/ui/sandbox.h"

#include <QGuiApplication>
#include <QQuickView>

int main(int argc, char *argv[]) {
  QGuiApplication a(argc, argv);
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  qputenv("QSG_INFO", "1");

  qmlRegisterType<ImGuiItem>("ImGui", 1, 0, "ImGui");

  QQuickView viewer;
  viewer.setSource(QUrl("qrc:/main.qml"));

  Sandbox gui;
  ImGuiItem *imguiItem = viewer.rootObject()->findChild<ImGuiItem *>("imgui");
  QObject::connect(imguiItem, &ImGuiItem::frame, imguiItem, [&gui] {
    gui.frame();
  });

  viewer.setTitle(QStringLiteral("ImGui Sandbox"));
  viewer.setResizeMode(QQuickView::SizeRootObjectToView);
  viewer.resize(1280, 720);
  viewer.show();

  return a.exec();
}
