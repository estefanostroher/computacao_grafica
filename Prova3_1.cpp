#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <climits>
#include <GL/glut.h>
#include "Prova3.h"
using namespace std;

int i = 0; // Variável global.
float minz = 500.0;

GLfloat a[] = {0.5, 0.0, 0.5, 00};
GLfloat b[] = {1.0, 1.0, 0.0, 00};

/* --> Construtor da classe <--*/
Objeto::Objeto(int x, int y, int z)
{
    posX = x;
    posY = y;
    posZ = z;
    radius = 2.0;
    numFaces = 0;
    numVertices = 0;
}
/* --------------------------- */

/* --> Destrutor da classe <-- */
Objeto::~Objeto() {}
/* --------------------------- */

/* --> Métodos da classe <-- */
void Objeto::carregarObjeto(string nome)
{
    float fx, fy, fz, a1, a2, a3;
    char letra;

    numVertices = 0;
    numFaces = 0;

    ifstream file;
    file.open(nome, ios::in);

    if (!file)
    {
        cout << "\nErro ao ler o arquivo!" << endl;
        return;
    }

    for (int i = 0; i < 0; i++)
        file.ignore(INT_MAX, '\n');

    while (!file.eof())
    {
        file >> letra;
        if (letra == 'v')
        {
            file >> fx;
            file >> fy;
            file >> fz;
            cx.push_back(fx);
            cy.push_back(fy);
            cz.push_back(fz);
            if (fz < minz)
                minz = fz;
            numVertices++;
        }

        if (letra == 'f')
        {
            file >> a1;
            file >> a2;
            file >> a3;
            v1.push_back(a1 - 1);
            v2.push_back(a2 - 1);
            v3.push_back(a3 - 1);
            faces.push_back(face(a1 - 1, a2 - 1, a3 - 1));
            numFaces++;
        }
    }

    for (i = 0; i < numFaces; i++)
    {
        double Px = cx[faces[i].I2] - cx[faces[i].I1];
        double Py = cy[faces[i].I2] - cy[faces[i].I1];
        double Pz = cz[faces[i].I2] - cz[faces[i].I1];

        double Qx = cx[faces[i].I3] - cx[faces[i].I2];
        double Qy = cy[faces[i].I3] - cy[faces[i].I2];
        double Qz = cz[faces[i].I3] - cz[faces[i].I2];

        double Ci = Py * Qz - Pz * Qy;
        double Cj = Px * Qz - Pz * Qx;
        double Ck = Px * Qy - Py * Qx;

        double modulo = sqrt(Ci * Ci + Cj * Cj + Ck * Ck);

        Ni.push_back(Ci / modulo);
        Nj.push_back(Cj / modulo);
        Nk.push_back(Ck / modulo);
    }
    file.close();
}

void Objeto::desenharObjeto(int textIndex, float escala)
{
    int hsamples = 30, vsamples = 30;
    GLfloat l = 0.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, b);
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(1.0, 1.0, 1.0, 1.0);

    GLfloat TexCoordX, TexCoordY;

    for (i = 0; i < numFaces; i++)
    {
        if (i % 2 == 1)
        {
            TexCoordX = GLfloat((i / 2) % hsamples) / (float)hsamples;
            TexCoordY = (GLfloat)l;

            glBegin(GL_POLYGON);
            glNormal3f(Ni[i], Nj[i], Nk[i]);
            glTexCoord2f(TexCoordX, TexCoordY + 1.0 / (float)vsamples);
            glVertex3f(escala * cx[faces[i].I1], escala * cy[faces[i].I1], escala * cz[faces[i].I1]);
            glTexCoord2f(TexCoordX + 1.0 / (float)hsamples, TexCoordY + (1.0 / (float)vsamples));
            glVertex3f(escala * cx[faces[i].I2], escala * cy[faces[i].I2], escala * cz[faces[i].I2]);
            glTexCoord2f(TexCoordX, TexCoordY);
            glVertex3f(escala * cx[faces[i].I3], escala * cy[faces[i].I3], escala * cz[faces[i].I3]);
            glEnd();
        }
        else
        {
            glBegin(GL_POLYGON);
            glNormal3f(Ni[i], Nj[i], Nk[i]);

            glTexCoord2f(TexCoordX + 1.0 / (float)hsamples, TexCoordY + 1.0 / (float)vsamples);
            glVertex3f(escala * cx[faces[i].I1], escala * cy[faces[i].I1], escala * cz[faces[i].I1]);

            glTexCoord2f(TexCoordX + 1.0 / (float)hsamples, TexCoordY);
            glVertex3f(escala * cx[faces[i].I2], escala * cy[faces[i].I2], escala * cz[faces[i].I2]);

            glTexCoord2f(TexCoordX, TexCoordY);
            glVertex3f(escala * cx[faces[i].I3], escala * cy[faces[i].I3], escala * cz[faces[i].I3]);
            glEnd();
        }
        if (i > 0 && (i % (2 * vsamples)) == 0)
            l += 1.0 / (float)vsamples;
    }
}

/* ---------------------------------------------- */
