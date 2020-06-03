//
// Created by amanda on 03/06/2020.
//

#ifndef CAL_PROJ_MASTER_FILEUTILS_H
#define CAL_PROJ_MASTER_FILEUTILS_H

#include <Autoridade_Publica.h>

//Classe para leitura de ficheiros
class FileUtils {
protected:
    Autoridade_Publica autoridadePublica;


public:
    FileUtils();

    void read_agente( Autoridade_Publica autoridadePublica);
    void read_denuncias( Autoridade_Publica autoridadePublica);
    void read_brigada( Autoridade_Publica autoridadePublica);
};


#endif //CAL_PROJ_MASTER_FILEUTILS_H
