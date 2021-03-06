#pragma once

#include "glwidget277.h"
#include "la.h"

//This defines a class which can be rendered by our shader program.
//Make any geometry a subclass of ShaderProgram::Drawable in order to render it with the ShaderProgram class.
class Drawable
{
protected:
    int count;      // The number of indices stored in bufIdx.
    GLuint bufIdx;  // A Vertex Buffer Object that we will use to store triangle indices (GLuints)

    GLuint bufPos; // A Vertex Buffer Object that we will use to store all vertex data (floats)
    GLuint bufCol; // A Vertex Buffer Object that we will use to store all vertex data (floats)
    bool posBound; // Set to TRUE by generateData(), returned by bindData().
    bool colBound; // Set to TRUE by generateData(), returned by bindData().
    bool idxBound;  // Set to TRUE by generateIdx(), returned by bindIdx().

    GLWidget277* context; // Since Qt's OpenGL support is done through classes like QOpenGLFunctions_3_2_Core,
                          // we need to pass our OpenGL context to the Drawable in order to call GL functions
                          // from within this class.


public:
    Drawable(GLWidget277* context);

    virtual void create() = 0; // To be implemented by subclasses. Populates the VBOs of the Drawable.
    void destroy(); // Frees the VBOs of the Drawable.

    // Getter functions for various GL data
    virtual GLenum drawMode();
    int elemCount();

    // Call these functions when you want to call glGenBuffers on the buffers stored in the Drawable
    // These will properly set the values of idxBound etc. which need to be checked in ShaderProgram::draw()
    void generateIdx();
    void generatePos();
    void generateCol();

    bool bindIdx();
    bool bindPos();
    bool bindCol();
};
