// main.cpp
#include "..\Missile_Dll\MissileSim.h"
#include <vector>
#include <iostream>

//#pragma comment(lib, "Missile_Dll.lib") //可以手动配置lib，也可以用该代码配置

using namespace XXX_MissileSim;  //不涉及多弹种时可以使用
int main() {
    std::cout << L"单弹仿真:\n";
    void* singleMissile = XXX_MissileSim::CreateMissile();

    XXX_MissileSim::InitParams initParams = { 100.0 };
    XXX_MissileSim::InitializeMissile(singleMissile, &initParams);

    XXX_MissileSim::UpdateParams updateParams = { 0.1 };
    XXX_MissileSim::UpdateMissile(singleMissile, &updateParams);

    XXX_MissileSim::OutputParams state;
    XXX_MissileSim::GetMissileState(singleMissile, &state);
    std::cout << "单弹 - 时间: " << state.time
        << ", 速度: " << state.flag_ko << "\n";

    while (true)
    {
        XXX_MissileSim::UpdateMissile(singleMissile, &updateParams);
        XXX_MissileSim::GetMissileState(singleMissile, &state);
        if (state.time>10)
        {
            std::cout << "仿真结束" << std::endl;
        }
    }


    XXX_MissileSim::DestroyMissile(singleMissile);

    std::cout << "\n 多弹仿真: \n";
    const int numMissiles = 3;
    std::vector<void*> missiles;
    missiles.reserve(numMissiles);

    for (int i = 0; i < numMissiles; ++i) {
        void* m = XXX_MissileSim::CreateMissile();
        missiles.push_back(m);
    }

    for (int i = 0; i < numMissiles; ++i) {
        XXX_MissileSim::InitParams ip = { 100.0 + i * 20.0 };
        XXX_MissileSim::InitializeMissile(missiles[i], &ip);
    }

    const int simulationSteps = 5;
    for (int step = 0; step < simulationSteps; ++step) {
        std::cout << "\n仿真步进 " << step + 1 << ":\n";
        for (int i = 0; i < numMissiles; ++i) {
            XXX_MissileSim::UpdateParams up = { 0.1 };
            XXX_MissileSim::UpdateMissile(missiles[i], &up);

            XXX_MissileSim::OutputParams state;
            XXX_MissileSim::GetMissileState(missiles[i], &state);
            std::cout << "导弹 " << i + 1
                << " - 位置: " << state.position
                << ", 速度: " << state.velocity << "\n";
        }
    }

    for (void* m : missiles) {
        XXX_MissileSim::DestroyMissile(m);
    }

    return 0;
}
