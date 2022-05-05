#include "EditorGrid.h"
#define gred 0.1f
#define ggreen 0.1f
#define gblue 0.1f
#define gopacity 0.2f

void drawGrid(int xSize, int ySize, int zSize, float edgeLength, int startX, int startY, int startZ) {

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    GLfloat halfSideLength = edgeLength * 0.5f;
    int x = 0, y = 0, z = 0;

    //draw horizontal lines across x axis
    for (int x = 0; x < xSize; x++) {
        for (int y = -1; y < ySize; y++) {
            for (int z = -1; z < zSize; z++) {
                GLfloat vertices[] =
                {
                    x - halfSideLength + startX, y + halfSideLength + startY, z + halfSideLength + startZ,
                    x + halfSideLength + startX, y + halfSideLength + startY, z + halfSideLength + startZ,

                };
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glColor4f(gred, ggreen, gblue, gopacity);
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vertices);

                glDrawArrays(GL_LINES, 0, 2);
                glDisableClientState(GL_VERTEX_ARRAY);
            }
        }
    }

    //draw vertical lines
    for (int x = -1; x < xSize; x++) {
        for (int y = 0; y < ySize; y++) {
            for (int z = -1; z < zSize; z++) {
                GLfloat vertices[] =
                {
                    x + halfSideLength + startX, y - halfSideLength + startY, z + halfSideLength + startZ,
                    x + halfSideLength + startX, y + halfSideLength + startY, z + halfSideLength + startZ,


                };
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glColor4f(gred, ggreen, gblue, gopacity);
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vertices);

                glDrawArrays(GL_LINES, 0, 2);
                glDisableClientState(GL_VERTEX_ARRAY);
            }
        }
    }

    //draw horizontal lines across z axis
    for (int x = -1; x < xSize; x++) {
        for (int y = -1; y < ySize; y++) {
            for (int z = 0; z < zSize; z++) {
                GLfloat vertices[] =
                {
                    x + halfSideLength + startX, y + halfSideLength + startY, z - halfSideLength + startZ,
                    x + halfSideLength + startX, y + halfSideLength + startY, z + halfSideLength + startZ,
                };
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glColor4f(gred, ggreen, gblue, gopacity);
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vertices);

                glDrawArrays(GL_LINES, 0, 2);
                glDisableClientState(GL_VERTEX_ARRAY);
            }
        }
    }
}
