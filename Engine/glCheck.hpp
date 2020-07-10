/*
 * Author		:Jeesoo Kim
 * File			:glCheck.hpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Header file for glCheck
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
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