/// @file imguiitem.h
/// @brief SandBox ImGui item header
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

#ifndef SANDBOX_SRC_IMPLEMENTATION_IMGUIITEM_H
#define SANDBOX_SRC_IMPLEMENTATION_IMGUIITEM_H

#include <QQuickItem>
#include <QImage>
#include <QSGRenderNode>

struct ImGuiContext;
class QOpenGLTexture;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
class ImGuiInputEventFilter;

class ImGuiRenderer : public QSGRenderNode {
public:
  ImGuiRenderer();
  ~ImGuiRenderer();

  void render(const RenderState *state) override;
  void releaseResources() override;
  StateFlags changedStates() const override;
  RenderingFlags flags() const override;
  QRectF rect() const override;

  struct FrameDesc {
    QVector<QImage> textures;
    struct Cmd {
      uint elemCount;
      const void *indexOffset;
      QPointF scissorPixelBottomLeft;
      QSizeF scissorPixelSize;
      uint textureIndex;
    };
    struct CmdListEntry {
      QByteArray vbuf;
      QByteArray ibuf;
      QVector<Cmd> cmds;
    };
    QVector<CmdListEntry> cmdList;
  };

private:
  QPointF m_scenePixelPosBottomLeft;
  QSizeF m_itemPixelSize;
  QSizeF m_itemSize;
  float m_dpr;
  FrameDesc m_frameDesc;
  QVector<QOpenGLTexture *> m_textures;
  QOpenGLShaderProgram *m_program = nullptr;
  int m_mvpLoc;
  int m_texLoc;
  int m_opacityLoc;
  QOpenGLVertexArrayObject *m_vao = nullptr;
  QOpenGLBuffer *m_vbo = nullptr;
  QOpenGLBuffer *m_ibo = nullptr;

  friend class ImGuiItem;
};

class ImGuiItem : public QQuickItem {
  Q_OBJECT

public:
  ImGuiItem(QQuickItem *parent = nullptr);
  ~ImGuiItem();

signals:
  void frame();

private:
  QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
  void itemChange(ItemChange, const ItemChangeData &) override;
  void updatePolish() override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
#if QT_CONFIG(wheelevent)
  void wheelEvent(QWheelEvent *event) override;
#endif
  void hoverMoveEvent(QHoverEvent *event) override;
  void touchEvent(QTouchEvent *event) override;

  void initialize();
  void cleanup();

  void setInputEventSource(QObject *src);
  void updateInput();

  QQuickWindow *m_w = nullptr;
  qreal m_dpr;
  QMetaObject::Connection m_c;
  ImGuiContext *m_imGuiContext = nullptr;
  ImGuiRenderer::FrameDesc m_frameDesc;
  bool m_inputInitialized = false;
  ImGuiInputEventFilter *m_inputEventFilter = nullptr;
  QObject *m_inputEventSource = nullptr;
  QObject m_dummy;
};

#endif // SANDBOX_SRC_IMPLEMENTATION_IMGUIITEM_H
