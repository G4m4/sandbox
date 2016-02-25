/// @file context.h
/// @brief Physics context class declaration
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

#ifndef SANDBOX_SRC_PHYSICS_CONTEXT_H_
#define SANDBOX_SRC_PHYSICS_CONTEXT_H_

#include <memory>

#include "sandbox/src/common.h"

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

namespace sandbox {
namespace physics {

/// @brief Physics context - interface to the physics engine
class SANDBOX_API Context {
 public:
  Context();
  ~Context();

 private:
  std::unique_ptr<btDefaultCollisionConfiguration> collision_configuration_;
  std::unique_ptr<btCollisionDispatcher> collision_dispatcher_;
  std::unique_ptr<btBroadphaseInterface> broadphase_;
  std::unique_ptr<btSequentialImpulseConstraintSolver> solver_;
  std::unique_ptr<btDiscreteDynamicsWorld> world_;
};

}  // namespace physics
}  // namespace sandbox

#endif  // SANDBOX_SRC_PHYSICS_CONTEXT_H_
