#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "WorldView.h"
#include "WormView.h"
#include "client_BulletView.h"
#include "ViewsList.h"
#include "Socket.h"
#include "client_Protocol.h"
#include "client_Player.h"
#include "DataReceiver.h"

int main(int argc, char* argv[]){

	auto app = Gtk::Application::create(argc, argv);
    Gtk::Window window;
    window.resize(1280, 720);

    Socket socket(Socket::Client("127.0.0.1", "7777"));
    ClientProtocol protocol(std::move(socket));
    
    WorldView world;////////////////////////////////////Estos se crean en player despues
    Player player(protocol, world);  ////////////////////////////////////El player despues recibe el protocol
    ViewsList list(world);////////////////////////////////////Estos se crean en player despues

    DataReceiver receiver(list, player, protocol);  ////////////////////////////////////Estos se crean en player despues

    window.add(player.getWindow());
    window.show_all();


    try{
        receiver.start();
        app->run(window);
    } catch (const std::exception& e){}

    try{
        receiver.stop();
    } catch (const std::exception& e){}

    receiver.join();


	return 0;
}
