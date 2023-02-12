// #pragma once
// #include <functional>
// #include <vector>
// #include <future>
// #include <thread>
// #include <memory>

// typedef int Handle;

// class Dag {

// class DagNode {

// friend class Dag; // 声明friend，从而Dag类能够调用DagNode类的私有方法
// public:
//     DagNode(std::function<void()> f, Handle handle) {
//         this->f = f;
//         this->handle = handle;
//         fut = promise.get_future();
//     }
//     ~DagNode() {
//         // if (thread_ && thread_->joinable()) {
//         //     thread_->join();
//         // }
//     }

//     std::future<int> get_future() {
//         return fut;
//     }

//     void exec() {
//         // thread_.reset(new std::thread([&p, this]{
//         std::this_thread::sleep(std::chrono::millisecond(100));
//         f();
//         promise.set_value(0);
//         // });
//         return;
//     }

//     void add_dependency(Handle handle) {
//         depenencies.push_back(handle);
//     }

//     std::vector<Handle> get_dependencies() {
//         return depenencies;
//     }

//     Handle get_handle() {
//         return handle;
//     }

// private:
//     std::function<void()> f;
//     std::future<int> fut;
//     std::promise<int> promise;
//     std::vector<Handle> depenencies;
//     Handle handle;
//     std::unique_ptr<std::thread> thread_;
// };

// public:

//     ~Dag() {
//         for (auto& ptr : threads_) {
//             if (ptr && ptr->joinable()) {
//                 ptr->join();
//             }
//         }
//     }

//     DagNode& add_node(std::function<void()> f) {
//         Handle handle = nodes.size();
//         nodes.push_back(DagNode(f), handle);
//         return nodes.back();
//     }

//     void add_edge(DagNode& from, DagNode& to) {
//         to.add_dependency(from.get_handle());
//     }

//     void run() {
//         DagNode root_node = add_node([]{});
//         for (auto& node : nodes) {
//             if (node.depenencies.empty()) {
//                 add_edge(root_node, node);
//             }
//         }
//         for (auto& node: nodes) {
//             std::vector<std::future<int>> depend_rets;
//             for (auto handle : node.get_dependencies()) {
//                 depend_rets.push_back(nodes[handle].get_future());
//             }
//             threads_.push_back(new std::thread([&node]{
//                 for (auto fut : depend_rets) {
//                     fut.wait();
//                 }
//                 node.exec();
//             }))
//         }
//         root_node.exec();
//     }


// private:
//     std::vector<DagNode> nodes;
//     std::vector<std::unique_ptr<std::thread>> threads_;
// };