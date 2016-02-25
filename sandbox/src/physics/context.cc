/// @file context.cc
/// @brief Physics context class definition
/// @author gm
/// @copyright gm 2016
///
/// This file is part of SandBox
///
/// SandBox is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// SandBox is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with SandBox.  If not, see <http://www.gnu.org/licenses/>.

#include "sandbox/src/physics/context.h"
#include "sandbox/src/common.h"

#include "btBulletDynamicsCommon.h"

namespace sandbox {
namespace physics {

Context::Context()
    : collision_configuration_(new btDefaultCollisionConfiguration()),
      collision_dispatcher_(new btCollisionDispatcher(collision_configuration_.get())),
      broadphase_(new btDbvtBroadphase()),
      solver_(new btSequentialImpulseConstraintSolver),
      world_(new btDiscreteDynamicsWorld(collision_dispatcher_.get(),
                                         broadphase_.get(),
                                         solver_.get(),
                                         collision_configuration_.get())) {
  world_->setGravity(btVector3(0, -10, 0));
}

Context::~Context() {
  // Nothing to do here for now
}

}  // namespace context
}  // namespace sandbox
