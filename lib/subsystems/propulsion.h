#include "../equipments/mcp.h"
#include "../configuration/config.h"
#include "../signal/signal.h"
//#include "../signal/signals_list.h"

#include <vector>

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
