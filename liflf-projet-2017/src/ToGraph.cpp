#include <iostream>
#include <fstream>
#include "ToGraph.h"


using namespace std;

bool ToGraph(sAutoNDE& at, std::string path)
{
    ofstream resultFile(path, ios::out | ios::trunc);

    if (resultFile)
    {
        etatset_t::iterator itr1, itr2;

        resultFile << "digraph finite_state_machine {" << endl;
        resultFile << "rankdir=LR;" << endl;
        resultFile << "size=\"10,10\"" << endl << endl;

        resultFile << "node [shape = doublecircle];";
        for(itr1 = at.finaux.begin(); itr1!= at.finaux.end(); ++itr1)
        {
            resultFile << *itr1 << " ";
        }
        resultFile << ";" << endl;
        resultFile << "node [shape = point ]; q;" << endl << "node [shape = circle];" << endl << endl;

        resultFile << "q -> 0;" << endl;
        for(size_t i = 0 ; i < at.trans.size() ; ++i ){
            for(size_t c = 0 ; c < at.trans[i].size() ; ++c ){
                for(itr2 = at.trans[i][c].begin() ; itr2 != at.trans[i][c].end() ; ++itr2 ){
                    resultFile << i << " -> " << *itr2 << " [label = \"" << (char)(c + ASCII_A) << "\"];" << endl;
                }
            }
        }
        resultFile << endl;

        for(size_t i = 0 ; i < at.epsilon.size() ; ++i ){
            for( itr1 = at.epsilon[i].begin() ; itr1 != at.epsilon[i].end() ; ++itr1 ){
                resultFile << i << " -> " << *itr1 << " [label = \"ε\"];" << endl;
            }
        }

        resultFile << endl << "}" << endl;

        resultFile.close();
        return true;
    }
    else
    {
        cerr << "Erreur lors de l'ouverture du fichier" << endl;
        return false;
    }

}

//******************************************************************************
