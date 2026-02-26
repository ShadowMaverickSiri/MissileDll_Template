#ifndef MISSILE_CORE_H
#define MISSILE_CORE_H
#include "MissileSim.h"  



namespace MissileSimInternal {//最好加上命名空间
	
	//导弹内部实现类
    class MissileCore {
    public:
        MissileCore();
        ~MissileCore();

		MissileCore(const MissileCore& aSrc);	//复制构造函数
		//MissileCore& operator = (const MissileCore &aSrc)=delete; //禁止拷贝赋值（特殊情况下使用）

		MissileCore& operator = (const MissileCore& aSrc) ; //拷贝赋值函数

		//初始化函数
        void initialize(const XXX_MissileSim::InitParams &initial); 

		//步进更新函数
        void update(const XXX_MissileSim::UpdateParams &update);

		//导弹内部数据获取
        void getState(XXX_MissileSim::OutputParams &out )const;

		static size_t count;		//记录这个类被使用了多少次 （注意，是静态变量）

    private:
		class SubModels; //定义导弹子模块管理类，前向引用用声明
		SubModels* mp;   //通过对象指针统一管理子模块类 （具体实现在cpp文件中，避免头文件暴露）
		 
		//可在此处定义一些通用的内部参数，建议在调试阶段使用
		unsigned id;   //导弹id
		double time;   //仿真时间
		double Time_system;  //系统时间
		double Lm, Bm, Hm;   //导弹经度（°）、纬度（°）、高度（m）
		double Vx_n, Vy_n, Vz_n; //导弹当地北天东速度（m/s）
		
    };

} // namespace MissileSimInternal



#endif // MISSILE_CORE_H
