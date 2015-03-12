#include <stdlib.h>

#include "freetype.h"
#include "../dbg.h"

// --- //

/* A representation of FreeType Glyph data */
ftchar_t* cogfCreate(GLchar c, GLint id, GLint sx, GLint sy, GLint bx, GLint by, GLint a) {
        ftchar_t* data = malloc(sizeof(ftchar_t));
        check_mem(data);

        data->c = c;
        data->textureID = id;
        data->sizeX = sx;
        data->sizeY = sy;
        data->bearingX = bx;
        data->bearingY = by;
        data->advance = a;

        return data;
 error:
        return NULL;
}

/* A list of all ASCII chars and their Glyph data */
ftchar_t** cogfAllAscii(FT_Face f) {
        GLubyte c;
        GLuint i;
        GLuint texture;
        ftchar_t* curr;
        ftchar_t** all;

        all = malloc(sizeof(long) * 128);
        check_mem(all);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);

        for(c = 0, i = 0; c < 128; c++, i++) {
                check(!FT_Load_Char(f,c,FT_LOAD_RENDER),
                      "Failed to load glyph for: %c", c);

                glGenTextures(1,&texture);
                glBindTexture(GL_TEXTURE_2D,texture);
                glTexImage2D(GL_TEXTURE_2D,0,GL_RED,
                             f->glyph->bitmap.width,
                             f->glyph->bitmap.rows,
                             0,GL_RED,GL_UNSIGNED_BYTE,
                             f->glyph->bitmap.buffer);

                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

                curr = cogfCreate(c,
                                  texture,
                                  f->glyph->bitmap.width,
                                  f->glyph->bitmap.rows,
                                  f->glyph->bitmap_left,
                                  f->glyph->bitmap_top,
                                  f->glyph->advance.x
                                  );

                all[i] = curr;
        }

        return all;
 error:
        return NULL;
}
