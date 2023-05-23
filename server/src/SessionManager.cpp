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

void SessionManager::DoCloseAll() {
    for (auto& session : Sessions) session->DoClose();
    Sessions.clear();
}

}  // namespace Server
