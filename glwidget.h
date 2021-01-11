#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class GLWidget: public QOpenGLWidget
{
public:
    explicit GLWidget(QWidget *parent = nullptr);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QOpenGLFunctions *glFunctions;
    QOpenGLShaderProgram *program;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;
    QMatrix4x4 m_projection, m_view;
};

#endif // GLWIDGET_H
