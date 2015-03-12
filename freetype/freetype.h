#ifndef __cog_freetype_h__
#define __cog_freetype_h__

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct ftchar_t {
        GLchar c;
        GLint textureID;
        GLint sizeX;
        GLint sizeY;
        GLint bearingX;
        GLint bearingY;
        GLint advance;
} ftchar_t;

// --- //

/* A representation of FreeType Glyph data */
ftchar_t* cogfCreate(GLchar c, GLint id, GLint sx, GLint sy, GLint bx, GLint by, GLint a);

/* A list of all ASCII chars and their Glyph data */
ftchar_t** cogfAllAscii(FT_Face f);

/* Print Glyph data */
void cogfPrint(ftchar_t*);

#endif
