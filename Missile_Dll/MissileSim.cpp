// MissileSim.cpp
#include "MissileSim.h"
#include "MissileCore.h"

using namespace MissileSimInternal;

namespace XXX_MissileSim {

#ifdef __cplusplus
    extern "C" {
#endif

        MISSILE_SIM_API void* CreateMissile() {
            return new MissileCore();
        }



        MISSILE_SIM_API void InitializeMissile(void* missile, const InitParams* params) {
            if (missile && params) {
                MissileCore* mc = static_cast<MissileCore*>(missile);
                mc->initialize(*params);
            }
        }

        MISSILE_SIM_API void UpdateMissile(void* missile, const UpdateParams* params) {
            if (missile && params) {
                MissileCore* mc = static_cast<MissileCore*>(missile);
                mc->update(*params);
            }
        }

        MISSILE_SIM_API void DestroyMissile(void* missile) {
            if (missile) {
                MissileCore* mc = static_cast<MissileCore*>(missile);
                delete mc;
            }
        }

        MISSILE_SIM_API void GetMissileState(void* missile, OutputParams* output) {
            if (missile && output) {
                MissileCore* mc = static_cast<MissileCore*>(missile);
                mc->getState(*output);
            }
        }

		MISSILE_SIM_API OutputParams GetMissileState_C(void* missile)
		{
			if (missile)
			{
				MissileCore* mc = static_cast<MissileCore*>(missile);
			}
			return  OutputParams();
		}

#ifdef __cplusplus
    }
#endif

} // namespace MissileSim
