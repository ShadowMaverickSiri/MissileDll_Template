// main.cpp
#include "..\Missile_Dll\MissileSim.h"
#include <vector>
#include <iostream>
#include <windows.h>  // 用于设置控制台编码
#ifdef _DEBUG
#pragma comment(lib,"../bin/Missile_Dll_d.lib")
#else
#pragma comment(lib,"../bin/Missile_Dll.lib")
#endif // _DEBUG


using namespace XXX_MissileSim;  //不涉及多弹种时可以使用
void SingleSim();
void MultiSim();

int main() {
	// 设置控制台为UTF-8编码（解决中文乱码问题）
	SetConsoleOutputCP(CP_UTF8);

	SingleSim();
	//MultiSim();
	return 0;
}

void SingleSim()
{
	// 在函数内部创建导弹对象（避免全局变量初始化顺序问题）
	void* singleMissile1 = CreateMissile();
	void* singleMissile2 = CopyMissile(singleMissile1);  // 测试拷贝构造
	void* singleMissile3 = CreateMissile();

	// 测试赋值函数
	AssignMissile(singleMissile3, singleMissile1);

	XXX_MissileSim::InitParams initParams = { 1,0,100,30,10.e3,400,0,0};
	XXX_MissileSim::InitializeMissile(singleMissile1, &initParams);

	XXX_MissileSim::UpdateParams updateParams = { 0.1,0.0,100,40,10e3,-300,0,0 };

	XXX_MissileSim::OutputParams outParams = {};

	std::cout << u8"=== 单弹仿真开始 ===\n";

	while (true)
	{
		XXX_MissileSim::UpdateMissile(singleMissile1, &updateParams);
		XXX_MissileSim::GetMissileState(singleMissile1, &outParams);

		std::cout << u8"导弹编号:" << outParams.id
			<< u8" 仿真时间:" << outParams.time
			<< u8" 导弹高度:" << outParams.LLA[2]
			<< std::endl;

		if (outParams.time > 10)
		{
			std::cout << u8"仿真结束" << std::endl;
			break;
		}
	}

	// 摧毁所有对象（包括singleMissile2，避免内存泄漏）
	XXX_MissileSim::DestroyMissile(singleMissile1);
	XXX_MissileSim::DestroyMissile(singleMissile2);
	XXX_MissileSim::DestroyMissile(singleMissile3);
}

void MultiSim()
{
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

			XXX_MissileSim::OutputParams outParams;
			XXX_MissileSim::GetMissileState(missiles[i], &outParams);
			std::cout << "导弹 " << i + 1
				<< " - 位置: " << outParams.LLA[0] << " " << outParams.LLA[1] << " " << outParams.LLA[2] << " "
				<< ", 速度: " << outParams.Vn[0] << " " << outParams.Vn[1] << " " << outParams.Vn[2] << " "
				<< "\n";
		}
	}

	for (auto* m : missiles) {
		XXX_MissileSim::DestroyMissile(m);
	}
	
}
