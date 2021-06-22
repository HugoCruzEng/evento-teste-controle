#include "../equipments/mcp.h"

class Propulsion
{
private:
    Mcp_ctrl* mcp_be;

    void control_mcp(Mcp_ctrl* mcp);

public:
    Propulsion();
    ~Propulsion();

    void control_propulsion();
};
