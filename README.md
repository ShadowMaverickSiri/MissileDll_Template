# 导弹仿真动态库模板 V1.0

一个用于导弹系统仿真的 C++ 动态链接库（DLL）框架模板，提供模块化、可扩展的导弹仿真解决方案。

## 项目简介

本项目采用 Visual Studio C++ 开发，提供了一个完整的导弹仿真动态库框架。通过 DLL 封装和 C 风格接口，支持单弹及多弹仿真场景，适用于导弹系统建模、武器系统测试与评估等应用。

### 主要特性

- **双层架构设计**：C 风格 DLL 接口 + C++ 实现层，确保跨语言兼容性
- **Pimpl 模式**：隐藏内部实现细节，提供编译防火墙
- **模块化设计**：制导、气动、控制等功能模块分离，便于扩展
- **多弹仿真支持**：支持同时仿真多枚独立导弹实例
- **内存安全管理**：DLL 内部统一管理对象生命周期

## 项目结构

```
导弹动态库模板V1.0/
├── Missile_Dll.sln           # Visual Studio 解决方案文件
├── Missile_Dll/              # DLL 项目目录
│   ├── MissileSim.h          # DLL 公共接口头文件
│   ├── MissileSim.cpp        # DLL 接口实现
│   ├── MissileCore.h         # 导弹核心类头文件
│   └── MissileCore.cpp       # 导弹核心类实现
└── main/                     # 测试程序项目目录
    └── 源.cpp                # 测试程序源代码
```

## 编译环境

- **IDE**: Visual Studio 2019 或更高版本
- **平台工具集**: v142
- **Windows SDK**: 10.0
- **支持平台**: Win32 / x64

## 快速开始

### 1. 编译项目

在 Visual Studio 中打开 `Missile_Dll.sln`，选择所需配置（Debug/Release），然后生成解决方案。

编译后将生成以下文件：
- `Missile_Dll.dll` - 动态链接库
- `Missile_Dll.lib` - 导入库
- `DLL_TEST.exe` - 测试可执行文件

### 2. 使用 DLL

在你的项目中包含 `MissileSim.h` 头文件，并链接 `Missile_Dll.lib`：

```cpp
#include "MissileSim.h"

// 创建导弹实例
void* missile = XXX_MissileSim::CreateMissile();

// 初始化参数
XXX_MissileSim::InitParams initParams = {0};
initParams.initialPosition[0] = 100.0;  // X 位置
initParams.initialPosition[1] = 0.0;    // Y 位置
initParams.initialPosition[2] = 1000.0; // Z 位置
XXX_MissileSim::InitializeMissile(missile, &initParams);

// 仿真循环
XXX_MissileSim::UpdateParams updateParams = {0};
updateParams.dt = 0.01;  // 时间步长
updateParams.targetPosition[0] = 5000.0;  // 目标位置
XXX_MissileSim::UpdateMissile(missile, &updateParams);

// 获取状态
XXX_MissileSim::OutputParams state;
XXX_MissileSim::GetMissileState(missile, &state);

// 销毁导弹实例
XXX_MissileSim::DestroyMissile(missile);
```

### 3. 多弹仿真示例

```cpp
#include <vector>
#include "MissileSim.h"

int main() {
    const int missileCount = 3;
    std::vector<void*> missiles;

    // 创建多枚导弹
    for (int i = 0; i < missileCount; i++) {
        missiles.push_back(XXX_MissileSim::CreateMissile());
    }

    // 分别初始化
    for (auto* missile : missiles) {
        XXX_MissileSim::InitializeMissile(missile, &initParams);
    }

    // 批量更新
    for (int step = 0; step < 1000; step++) {
        for (auto* missile : missiles) {
            XXX_MissileSim::UpdateMissile(missile, &updateParams);
        }
    }

    // 销毁所有导弹
    for (auto* missile : missiles) {
        XXX_MissileSim::DestroyMissile(missile);
    }

    return 0;
}
```

## API 接口说明

### 导出函数

| 函数 | 说明 |
|------|------|
| `CreateMissile()` | 创建导弹实例，返回句柄 |
| `InitializeMissile(void*, InitParams*)` | 初始化导弹参数 |
| `UpdateMissile(void*, UpdateParams*)` | 更新导弹状态 |
| `GetMissileState(void*, OutputParams*)` | 获取导弹当前状态 |
| `DestroyMissile(void*)` | 销毁导弹实例 |

### 数据结构

#### InitParams - 初始化参数
```cpp
struct InitParams {
    double initialPosition[3];  // 初始位置 [x, y, z]
    double initialVelocity[3];  // 初始速度 [vx, vy, vz]
    double initialAttitude[3];  // 初始姿态
    // ... 其他初始化参数
};
```

#### UpdateParams - 更新参数
```cpp
struct UpdateParams {
    double dt;                  // 时间步长
    double targetPosition[3];   // 目标位置
    double targetVelocity[3];   // 目标速度
    // ... 其他更新参数
};
```

#### OutputParams - 输出参数
```cpp
struct OutputParams {
    double currentPosition[3];  // 当前位置
    double currentVelocity[3];  // 当前速度
    double currentAttitude[3];  // 当前姿态
    // ... 其他状态参数
};
```

## 架构设计

```
┌─────────────────────────────────────────────────────┐
│                   用户应用程序                         │
└─────────────────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────┐
│              DLL 接口层 (MissileSim.h/cpp)           │
│         extern "C" 风格导出函数 + void* 句柄          │
└─────────────────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────┐
│              核心实现层 (MissileCore)                 │
│                                                      │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐          │
│  │  Guide   │  │   Aero   │  │ Control  │          │
│  │  制导模块 │  │  气动模块 │  │  控制模块 │          │
│  └──────────┘  └──────────┘  └──────────┘          │
└─────────────────────────────────────────────────────┘
```

### 子模块说明

| 模块 | 功能 | 待实现方法 |
|------|------|-----------|
| **Guide** | 制导模块 | `computeGuidance()` - 制导指令计算 |
| **Aero** | 气动模块 | `computeAerodynamics()` - 气动力/力矩计算 |
| **Control** | 控制模块 | `computeControl()` - 控制律实现 |

## 扩展开发

### 添加新的子模块

1. 在 `MissileCore.cpp` 的 `SubModels` 类中添加新模块类
2. 在构造函数中初始化模块
3. 在 `MissileCore::update()` 中调用模块方法

示例：
```cpp
// 在 SubModels 类中添加
class Navigation {
public:
    void computeNavigation() {
        // 实现导航算法
    }
};

Navigation* nav;

// 在构造函数中
nav = new Navigation();

// 在 update 中使用
nav->computeNavigation();
```

## 注意事项

1. **内存管理**：导弹实例必须通过 `DestroyMissile()` 销毁，避免内存泄漏
2. **空指针检查**：所有导出函数内部已实现空指针检查
3. **线程安全**：当前实现非线程安全，多线程使用需自行加锁
4. **命名空间**：所有接口位于 `XXX_MissileSim` 命名空间中

## 待完善功能

- [ ] 完善 `CopyMissile()` 和 `AssignMissile()` 函数实现
- [ ] 补充各子模块的具体算法实现
- [ ] 添加更多仿真参数配置项
- [ ] 增加日志输出功能
- [ ] 支持仿真数据导出

## 许可证

本项目仅供学习和研究使用。

## 版本历史

- **V1.0** - 初始版本
  - 框架搭建
  - 基础 DLL 接口实现
  - 单弹/多弹仿真示例
