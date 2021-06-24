
#include "../equipments/mcp.h"
#include "../signal/signals_list.h"

class Propulsion
{
private:
    Mcp_ctrl* mcp_be;

    void control_mcp(Mcp_ctrl* mcp);

public:
    Propulsion();
    ~Propulsion();

    char* control_propulsion();
};
