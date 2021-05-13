#ifndef mcp_h
#define mcp_h

#include <PID_v1.h>

class mcp {
    public:
    //estados do MCP
       // #define mcpParado 0
       // #define mcpFuncionando 1
   
    //construtor
        mcp(bool, double, double, double, double, double, double);

        void partirMCP();
        void pararMCP();
        void demandaRotacao(double);
        void setSetPoint(double);
        void setRealimentacao(double);
        void setKp(double);
        void setKi(double);
        void setKd(double);
        bool getStatusMCP();
        unsigned int getRotacaoMCP();
        double getPosAtuador();
        double getSetPoint();
        double getRealimentacao();
        
        double processaPID(double, double);

    private:
        bool myStatusMCP=0;
        double myRotacao=0;
        // Variáveis PID
        double mySetpoint, myRealimentacao, myPosAtuador, myKp, myKi, myKd;        
        PID *myPID;
        // PID myPID;

};

#endif