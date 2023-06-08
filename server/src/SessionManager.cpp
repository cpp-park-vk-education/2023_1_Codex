#include "SessionManager.hpp"

namespace Server {

void SessionManager::Run(SessionSPtr session) {
    Sessions.insert(session);
    session->Run();
}

void SessionManager::DoClose(SessionSPtr session) {
    Sessions.erase(session);
    session->DoClose();
}

}  // namespace Server
