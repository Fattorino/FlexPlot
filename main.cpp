#include <imgui.h>
#include <implot.h>

#include "includes/ToroImGuiHandle/ToroImGuiHandle.h"
#include "FlexPlot.h"

void menuBar()
{

}

int main()
{
    if (!IGH.init("Flex Plot", 1300, 800))
        return 1;
    ImPlot::CreateContext();

    ImGui::GetIO().IniFilename = nullptr;

    IGH.pushLayer<FlexPlot>();

    IGH.menuBar(menuBar);
    IGH.setActiveWin(0);

    bool done = false;
    while (!done)
    {
        IGH.loop(&done);
    }

    ImPlot::DestroyContext();
    IGH.end();

    return 0;
}
