#include <vector>
#include <string>
using namespace std;

struct face{
    int I1, I2, I3;

    face(int a1, int a2, int a3){
        I1 = a1;
        I2 = a2;
        I3 = a3;
    }
};

class Objeto{
    private:
        /* --> Atributos privados da classe <-- */
        vector<float> v1;
        vector<float> v2;
        vector<float> v3;
        vector<float> cx;
        vector<float> cy;
        vector<float> cz;
        vector<float> Ni;
        vector<float> Nj;
        vector<float> Nk;
        vector<face> faces;
        int numFaces, numVertices;
        /* ------------------------------------ */
    public:
        /* --> Atributos públicos da classe <-- */
        float posX, posY, posZ, radius;
        /* ------------------------------------ */

        /* --> Construtor e destrutor da classe <-- */
        Objeto(int x, int y, int z);
        ~Objeto();
        /* ---------------------------------------- */

        /* --> Métodos da classe <-- */
        void carregarObjeto(string nome);
        void desenharObjeto(int textIndex, float escala);
        /* ------------------------- */
};
