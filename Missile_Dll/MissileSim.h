// MissileSim.h
#ifndef MISSILE_SIM_H
#define MISSILE_SIM_H

#ifdef _WIN32
#ifndef MISSILE_SIM_EXPORTS
#define MISSILE_SIM_API __declspec(dllexport)
#else
#define MISSILE_SIM_API __declspec(dllimport)
#endif
#else
#define MISSILE_SIM_API __attribute__((visibility("default")))
#endif
//建议采用命名空间，避免变量名污染，XXX可换成具体代号名称
namespace XXX_MissileSim {  

	//——————————————导弹初始化函数的输入结构体———————————————//
    struct InitParams {
		unsigned id;                        //导弹ID
        double time;						//仿真时间
		double Lm0, Bm0, Hm0;				//导弹初始经纬高
		double Vx_n0, Vy_n0, Vz_n0;			//导弹初始北天东速度

        //.....根据具体情况增加其他变量
    };
	//——————————————导弹更新函数的输入结构体———————————————//
	
    struct UpdateParams {
		double step;						//步长
        double time;						//仿真时间
		double Lt, Bt, Ht;					//目标实时经纬高
		double Vtx_n0, Vty_n0, Vtz_n0;		//目标实时北天东速度

		//.....根据具体情况增加其他变量
    };
	//——————————————导弹内部数据输出结构体———————————————//
    struct OutputParams {
		unsigned id;                        //导弹ID
        double time;						//仿真时间
        double LLA[3];						//导弹经纬高位置
        double Vn[3];						//导弹北天东速度
		bool flag_ko;						//摧毁标志位

		//.....根据具体情况增加其他变量
    };
	//=================================================================================================//
#ifdef __cplusplus
    extern "C" { //C风格导出，保证兼容多平台
#endif
		 
        MISSILE_SIM_API void* CreateMissile();											 //【导出函数】-创建导弹对象
		MISSILE_SIM_API void* CopyMissile(void* sourcemissile);							 //【导出函数】-复制构造函数
		MISSILE_SIM_API void AssignMissile(void* targetmissile, void* sourcemissile );	 //【导出函数】-拷贝赋值函数
        MISSILE_SIM_API void InitializeMissile(void* missile, const InitParams* params); //【导出函数】-初始化导弹参数
        MISSILE_SIM_API void UpdateMissile(void* missile, const UpdateParams* params);   //【导出函数】-更新导弹状态
        MISSILE_SIM_API void DestroyMissile(void* missile);								 //【导出函数】-销毁导弹实体
		MISSILE_SIM_API void GetMissileState(void* missile, OutputParams* output);       //【导出函数】-获取导弹参数

#ifdef __cplusplus
    }
#endif

}

#endif // MISSILE_SIM_H


