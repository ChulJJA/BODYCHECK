/*
   Rudy Castan
   Graphics Library
   CS230

   Use this to automatically error check an OpenGL Calls.
   ie
        glCheck(glClearColor(0,0,0,1));
        int GetVertexAttributeLocation(...)
        {
            int location = glCheck(glGetAttribLocation(handleToShader, vertex_field_name));
            return location;
        }
 */
#pragma once

void glCheckError(const char* file, unsigned int line, const char* expression);
void glClearErrors();


// Note that this macro calls glClearErrors, does expression, semicolon, and then calls glCheckError,
// so you shouldn't use this macro under an if statement without { } and
// you shouldn't use it in a return statement.
#ifdef _DEBUG
#define glCheck(expr)                                                                                                  \
    glClearErrors();                                                                                                   \
    (expr);                                                                                                            \
    glCheckError(__FILE__, __LINE__, #expr)
#else
#define glCheck(expr) (expr)
#endif