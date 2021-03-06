/**
 *  @autor arssivka
 *  @date 8/26/16
 */

#include <rrc/core/LinearLauncher.h>
#include <rrc/core/Node.h>


rrc::LinearLauncher::LinearLauncher()
        : mFinished(false) { }


rrc::LinearLauncher::~LinearLauncher() {
}


int rrc::LinearLauncher::run() {
    mFinished = false;
    while (this->step());
    return 0;
}


void rrc::LinearLauncher::stop() {
    mFinished = true;
}


void rrc::LinearLauncher::setRootNode(rrc::RootNodePtr node) {
    mRootNode = std::move(node);
}


void rrc::LinearLauncher::addNode(rrc::NodePtr node) {
    mNodesList.emplace_front(std::move(node));
}


void rrc::LinearLauncher::removeNode(rrc::NodePtr node) {
    mNodesList.remove_if([node](const NodeContainer& container) {
        return container.node == node;
    });
}


bool rrc::LinearLauncher::step() {
    if (mFinished) {
        return false;
    }
    mRootNode->entry();
    for (auto&& container : mNodesList) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = now - container.timestamp;
        if (elapsed >= container.node->getMinDuration()) {
            container.node->entry();
            container.timestamp = now;
        }
    }
    return true;
}


rrc::LinearLauncher::NodeContainer::NodeContainer(rrc::NodePtr node)
        : node(node), timestamp() { }
