#ifndef MISSILE_CORE_H
#define MISSILE_CORE_H
#include "MissileSim.h"  
#include <iostream>


namespace MissileSimInternal {//最好加上命名空间
	
	//导弹内部实现类
    class MissileCore {
    public:
        MissileCore();
        ~MissileCore();

		MissileCore(const MissileCore& aSrc);				//复制构造函数
		//MissileCore& operator = (const MissileCore &aSrc)=delete; //禁止拷贝赋值

		MissileCore& operator = (const MissileCore& aSrc) ;
		//初始化函数
        void initialize(const XXX_MissileSim::InitParams &initial); 
		//步进更新函数
        void update(const XXX_MissileSim::UpdateParams &update);
		//导弹内部数据获取
        void getState(XXX_MissileSim::OutputParams &out )const;


		static size_t count;		//记录这个类被使用了多少次
    private:
		class SubModels; //定义导弹子模块管理类，前向引用用声明
		SubModels* mp;   //通过对象指针统一管理子模块类 （具体实现在cpp文件中，避免头文件暴露）
		 
		//可在此处定义一些内部的参数，也可不定义
		double id;//导弹id
		double Time_system;  //系统时间
		

    };

} // namespace MissileSimInternal



#endif // MISSILE_CORE_H
