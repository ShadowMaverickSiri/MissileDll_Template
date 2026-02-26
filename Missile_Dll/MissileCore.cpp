// MissileCore.cpp
#include "MissileCore.h"
#include<vector>
#include<array>
#include <iostream>
namespace MissileSimInternal {

    // 定义你的子模块类，也可以分开写在多个文件中，注意包含顺序 ，自由实现
	//以下实现方式仅做参考，可根据个人习惯具体调整
    class Guide {
    public:
		Guide() :time(0),nx(1), ny(2) {
			std::cout << "Guide 构造完成\n"; //构造函数
		};

		void computeGuidance() {
           //根据需要具体实现
        }
		double time;
		double hm;
        double nx, ny;
		//定义其他变量
		//.....
	private:
		std::array<double, 3>n1a = { 0,0,0 };
    };

    class Aero {
    public:
        void computeAerodynamics(const Guide &guide_in ) {  //传入其他模块的引用，记得使用前向引用声明，避免报错
			//气动模块输入
			std::cout << "[Aero] 气动计算...\n";
			hm = guide_in.hm;
        }
		double Ma, hm;
		std::vector<int>aa = {0,0,0};
		//定义其他变量
		//.....
    };

    class Control {
    public:
        void computeControl() {
            std::cout << "[Control] 计算控制...\n";
        }

		double nx, ny;

	private:

		double dp[3];
    };

	//子模块管理类具体实现（不要包含指针成员变量）
	class MissileCore::SubModels {
	public:
		//定义导弹计算模块类对象
		Guide guide_;
		Aero aero_;
		Control control_;
		//自行增加定义计算模块
		//Air air_
		//....

		// 显式定义拷贝构造函数和析构函数
		SubModels() = default;
		~SubModels() = default;
		SubModels(const SubModels& other) = default;
		SubModels& operator=(const SubModels& other) = default;
	};


	MissileCore::MissileCore() : id(0), time(0.0), Time_system(0.0), Lm(0.0), Bm(0.0), Hm(0.0), Vx_n(0.0), Vy_n(0.0), Vz_n(0.0) {
		mp = new SubModels;
	}

    MissileCore::~MissileCore() {
		delete mp;

        std::cout << "MissileCore 析构完成。\n";
    }

	MissileCore::MissileCore(const MissileCore& aSrc) :id(aSrc.id),time(aSrc.time), Time_system(aSrc.Time_system)
			, Lm(aSrc.Lm) , Bm(aSrc.Bm), Hm(aSrc.Hm), Vx_n(aSrc.Vx_n), Vy_n(aSrc.Vy_n), Vz_n(aSrc.Vz_n)
	{
		mp = new SubModels(*aSrc.mp);
	}

	MissileCore& MissileCore::operator=(const MissileCore& other)
	{
		if (this == &other)
		{
			return *this;
		}
		*mp = *other.mp;
		id = other.id;
		time = other.time;
		Time_system = other.Time_system;
		Lm = other.Lm;
		Bm = other.Bm;
		Hm = other.Hm;
		Vx_n = other.Vx_n;
		Vy_n = other.Vy_n;
		Vz_n = other.Vz_n;

		//...
		//根据你定义的MissileCore类中的变量情况完成拷贝赋值函数的深拷贝

		return *this;
	};

	void MissileCore::initialize(const XXX_MissileSim::InitParams& initial) {
		id = initial.id;
		time = initial.time;
		Lm = initial.Lm0;
		Bm = initial.Bm0;
		Hm = initial.Hm0;
		Vx_n = initial.Vx_n0;
		Vy_n = initial.Vy_n0;
		Vz_n = initial.Vz_n0;

		mp->guide_.nx = 0;
		mp->guide_.ny = 0;
		mp->guide_.hm = 15000.;
    }

    void MissileCore::update(const XXX_MissileSim::UpdateParams& update) {
		time += update.step;  // 累加时间步长
		mp->aero_.hm = update.time;
		mp->aero_.computeAerodynamics(mp->guide_);
    }


    void MissileCore::getState(XXX_MissileSim::OutputParams& out) const {
		out.id = id;
		out.time = time;
		out.LLA[0] = Lm;
		out.LLA[1] = Bm;
		out.LLA[2] = Hm;
		out.Vn[0] = Vx_n;
		out.Vn[1] = Vy_n;
		out.Vn[2] = Vz_n;
		out.flag_ko = false;
    }

} // namespace MissileSimInternal
