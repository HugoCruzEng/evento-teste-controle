#ifndef mcp_h
#define mcp_h

#include <PID_v1.h>
#include "../signal/signal.h"

class mcp {
    public:
    //estados do MCP
       // #define mcpParado 0
       // #define mcpFuncionando 1
   
    //construtor
        mcp(bool, double, double, double, double, double, double);

        void partirMCP();
        void pararMCP();
        void demandaRotacao(unsigned short int);
        void setSetPoint(unsigned short int);
        void setRealimentacao(unsigned short int);
        void setKp(unsigned short int);
        void setKi(unsigned short int);
        void setKd(unsigned short int);
        bool getStatusMCP();
        unsigned short int getRotacaoMCP();
        unsigned short int getPosAtuador();
        unsigned short int getSetPoint();
        unsigned short int getRealimentacao();
        
        double processaPID(unsigned short int, unsigned short int);

    private:
        bool myStatusMCP;
        unsigned short myRotacao;
        // Variáveis PID
        double mySetpoint, myRealimentacao, myPosAtuador;
        double myKp, myKi, myKd;        
        PID *myPID;
        //PID myPID;

};
#endif