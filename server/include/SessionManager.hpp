#pragma once

#include <memory>
#include <set>

#include "Session.hpp"

namespace Server {

class SessionManager {
   public:
    void Run(SessionSPtr session);

    void DoClose(SessionSPtr session);

   private:
    std::set<SessionSPtr> Sessions;
};

}  // namespace Server
