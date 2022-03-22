#include <iostream>
#include <asio.hpp>
#include <net/basalt_net.hpp>
#include <list>
#include <mutex>
#include <net/Session.hpp>

namespace Basalt
{
    namespace net
    {
        using namespace asio::ip;

        static CallbackMap handlers; // callback functions to call on incoming messages        
        static std::atomic_bool keepGoing = true;
        static uint16_t port;
        static std::mutex mutex;
        static asio::io_context context;

        static tcp::acceptor* acceptor;
        

        static void accept_connections();


        static void on_message(tcp::socket&& peer){
            /* handle incoming message here */
        }

        /* Handle new connected peer */
        void on_connect(asio::error_code ec, tcp::socket peer){
            /* Handle incoming request here */
            new Session(std::move(peer), handlers);
            /* Accept next connections, if any */
            if(keepGoing) accept_connections();
        }
        static void accept_connections(){
            tcp::endpoint ep;
            acceptor->async_accept(context, ep, on_connect);
        }


        void net_init(CallbackMap& callbacks, uint16_t lPort){
            handlers = callbacks;
            port = lPort;
            tcp::endpoint ep(tcp::v4(), port);
            acceptor = new tcp::acceptor(context, ep);

            accept_connections();

            std::thread t([]() { context.run(); });
            t.detach();
        }
        void net_finish(){
            context.stop();
            keepGoing = false;
            delete acceptor;
        }
        
    } // namespace net
    
} // namespace Basalt
