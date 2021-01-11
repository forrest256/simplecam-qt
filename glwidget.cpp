#include "glwidget.h"
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

GLWidget::GLWidget(QWidget *parent)
{

}

void GLWidget::initializeGL()
{

    const QString vertexShader =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}";

    const QString fragmentShader =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "FragColor = vec4(1.0f, 0.9f, 0.1f, 1.0f);\n"
            "}";

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f,  0.5f, 0.0f //triangle 1
        -0.7f, -0.2f, 0.5f, 0.1f, -0.8f, 1.0f, 0.0f,  0.5f, 0.0f //triangle 2
    };


    this->glFunctions = this->context()->functions();

    program = new QOpenGLShaderProgram();
    program->create();
    bool s = program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader.toStdString().c_str());
    if(!s){
        qDebug() << program->log();
    }
    bool k = program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    if(!k){
        qDebug() << program->log();
    }
    bool j = program->link();
    if(!j){
        qDebug() << program->log();
    }

    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();
    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo->create();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->bind();
    vbo->allocate(vertices, sizeof vertices);
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glFunctions->glEnableVertexAttribArray(0);
}

void GLWidget::resizeGL(int w, int h)
{
    glFunctions->glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    glFunctions->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glFunctions->glClear(GL_COLOR_BUFFER_BIT);

    vao->bind();
    program->bind();
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 6);
    vao->release();

    update();
}
