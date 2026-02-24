// MissileCore.cpp
#include "MissileCore.h"
#include<vector>
#include<array>
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
        double nx, ny;
		//定义其他变量
		//.....
	private:
		std::array<double, 3>n1a = { 0,0,0 };
    };

    class Aero {
    public:
        void computeAerodynamics() {
			//根据需要具体实现
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
		//自行定义计算模块
		//SubModels& operator= (SubModels& other) {

		//};

	};


	MissileCore::MissileCore() {
		mp = new SubModels;
	}

    MissileCore::~MissileCore() {
		delete mp;

        std::cout << "MissileCore 析构完成。\n";
    }

	MissileCore::MissileCore(const MissileCore& aSrc) :id(aSrc.id), Time_system(aSrc.Time_system)
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
		Time_system = other.Time_system;
		return *this;
	};

	void MissileCore::initialize(const XXX_MissileSim::InitParams& initial) {
		mp->guide_.nx = initial.time;
		

		//guide_->nx = initial.time;
		//std::cout << "MissileCore 初始化，速度: " << velocity_ << "\n";
    }

    void MissileCore::update(const XXX_MissileSim::UpdateParams& update) {
   
		//aero_->hm = update.time;


        //guide_->computeGuidance(*aero_);
        //aero_->computeAerodynamics();
        //control_->computeControl();
		//position_ += velocity_ * deltaTime;
        //std::cout << "MissileCore 更新完成。新位置: " << position_ << "\n";
    }


    void MissileCore::getState(XXX_MissileSim::OutputParams& out) const {
		out.time = 0.0;
		out.gps[0] = 0.0;
		out.gps[1] = 0.0;
		out.gps[2] = 0.0;
		out.Vn[0] = 0.0;
		out.Vn[1] = 0.0;
		out.Vn[2] = 0.0;
		out.flag_ko = false;
        
		
    }

} // namespace MissileSimInternal
