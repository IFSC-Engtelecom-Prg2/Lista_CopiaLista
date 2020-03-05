//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>
#include <list>
#include "questao.h"
#include "gtest/gtest.h"

using namespace std;

class TesteQuestao: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }
    void gen_lista(list<double> & q) {
        int n;

        n = 2 + (rand() % 10);
        while (n-- > 0) {
            double x = (rand() % 100) + (rand() % 1000)*1e-3;
            q.push_back(x);
        }
    }

    void concatena(list<double> & q, list<double> & q1) {
        for (auto & x: q) q1.push_back(x);
    }
};

TEST_F(TesteQuestao, Vazia)
{
    list<string> orig, nova;

    try {
        copia_lista(orig, nova);
        if (nova.size() > 0) {
            FAIL() << "após copiar lista vazia, nova lista ficou com " << nova.size() << " dados, mas deveria ter 0";
            return;
        }
    } catch (...) {
        FAIL() << "exceção inesperada ao copiar lista";
    }
}

TEST_F(TesteQuestao, Anexar)
{
    list<string> orig, nova;

    nova.push_back("um");
    nova.push_back("dois");
    nova.push_back("tres");
    nova.push_back("quatro");
    list<string> aux = nova;

    orig.push_back("peniche");
    orig.push_back("matadeiro");
    orig.push_back("tourinho");
    try {
        copia_lista(orig, nova);
        if (nova.size() < aux.size()) {
            FAIL() << "estranho: após cópia, comprimento da nova lista ficou menor que antes";
            return;
        }
        auto it1 = nova.begin();
        auto it2 = aux.begin();
        for (; it2 != aux.end(); it1++, it2++) {
                if (*it1 != *it2) {
                    FAIL() << "após cópia dados que existiam na lista nova foram modificados";
                    return;
                }
        }
    } catch (...) {
        FAIL() << "exceção inesperada ao copiar lista";
    }
}

TEST_F(TesteQuestao, Copiar) {
    list<string> orig, nova;

    nova.push_back("um");
    nova.push_back("dois");
    nova.push_back("tres");
    nova.push_back("quatro");
    list<string> aux = nova;

    orig.push_back("peniche");
    orig.push_back("matadeiro");
    orig.push_back("tourinho");
    try {
        copia_lista(orig, nova);
        if (nova.size() != aux.size() + orig.size()) {
            FAIL() << "após cópia lista nova tem size " << nova.size() << ", mas o esperado é "+to_string(aux.size() + orig.size())+", porque lista original tem size "+to_string(orig.size())+" e antes da cópia lista nova tinha size " << nova.size();
            return;
        }
        auto it1 = nova.rbegin();
        auto it2 = orig.rbegin();
        for (; it2 != orig.rend(); it1++, it2++) {
            if (*it1 != *it2) {
                FAIL() << "dados copiados para a lista nova não estão na mesma sequência que estavam na lista original";
                return;
            }
        }
    } catch (...) {
        FAIL() << "exceção inesperada ao copiar lista";
    }
}

TEST_F(TesteQuestao, Preserva)
{
    list<string> orig, nova;

    nova.push_back("um");
    nova.push_back("dois");
    nova.push_back("tres");
    nova.push_back("quatro");

    orig.push_back("peniche");
    orig.push_back("matadeiro");
    orig.push_back("tourinho");
    list<string> aux = orig;
    try {
        copia_lista(orig, nova);
        if (orig.size() != aux.size()) {
            FAIL() << "após cópia lista original tem size " << orig.size() << ", mas o esperado é "<< (aux.size() + orig.size()) << ", porque lista original tem size "+to_string(orig.size())+" mas não deveria ter se modificado .. antes tinha " << aux.size();
            return;
        }
        auto it1 = aux.begin();
        auto it2 = orig.begin();
        for (; it2 != orig.end(); it1++, it2++) {
            if (*it1 != *it2) {
                FAIL() << "após cópia lista original foi modificada ... ao menos um de seus dados foi alterado";
                return;
            }
        }
    } catch (...) {
        FAIL() << "exceção inesperada ao copiar lista";
    }
}

