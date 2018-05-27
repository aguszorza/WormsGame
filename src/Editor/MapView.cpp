
#include <iostream>
#include <fstream>
#include <ObjectSizes.h>
#include "yaml-cpp/yaml.h"
#include "MapView.h"

MapView::MapView(BaseObjectType *cobject,
                 const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Layout(cobject),
          actual_bg(0)
{
    bg_paths.emplace_back("resources/images/editor_toolbox/background1.png");
    bg_paths.emplace_back("resources/images/editor_toolbox/bac.jpg");
    setBackground(bg_paths[actual_bg]);

    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this, &MapView::on_button_clicked));

    std::vector<std::string> worms_imgs;
    worms_imgs.emplace_back("resources/images/right_worm.png");
    worms_imgs.emplace_back("resources/images/left_worm.png");
    pallete.push_back(worms_imgs);


    std::vector<std::string> girder_3_imgs;
    for (int i = 0; i < 180; i = i + 10) {
        girder_3_imgs.emplace_back(
                "resources/images/Girder/girder_3_" + std::to_string(i) +
                ".png");
    }
    pallete.push_back(girder_3_imgs);

    std::vector<std::string> girder_6_imgs;
    for (int i = 0; i < 180; i = i + 10) {
        girder_6_imgs.push_back(
                "resources/images/Girder/girder_6_" + std::to_string(i) +
                ".png");
    }
    pallete.push_back(girder_6_imgs);
}


void MapView::add(unsigned int id, const double &x, const double &y,
                  const int &angle) {
    Gtk::Image new_image(pallete[id - id / 2 - 1][0]);
    const Glib::RefPtr<Gdk::Pixbuf> &img = new_image.get_pixbuf();
    int width= img->get_width();
    int height= img->get_height();
    double x_bound = x - width / 2;
    double y_bound = y - height / 2;

    //if(isIsolated(x_bound,y_bound,id)){ //verifica que no haya colisiones
        put(new_image, x_bound, y_bound);
        new_image.show();
        objects.push_back(std::move(new_image));
        if (angle > 0)
            turn(id, angle, 0);
    //}

}

void MapView::move(const int index, const double &x, const double &y) {
    if (!objects.empty()) {
        Gtk::Image &actual_object = objects[index];
        Gtk::Layout::move(actual_object, x - actual_object.get_width() / 2,
             y - actual_object.get_height() / 2);
        actual_object.show();
    }
}

//TODO: no usar mas el id
void MapView::turn(unsigned int id, int angle, int index) {
    if (!objects.empty()) {
        Gtk::Image &image = objects[index];
        image.set(pallete[id - id / 2 - 1][angle / 10]);
    }
}


bool MapView::on_button_clicked(GdkEventButton *button_event) {
    controller->mapClickedSignal(button_event);
    return true;
}

void MapView::undo() {
    if (!objects.empty())
        objects.pop_back();
}

void MapView::clean() {
    objects.clear();
}

void MapView::linkController(MapController *pController) {
    this->controller = pController;
}

void MapView::setBackground(std::string name) {
    Gtk::Image bg(name);
    int width = bg.get_pixbuf()->get_width();
    int heigth = bg.get_pixbuf()->get_height();
    guint winw,winh;
    this->get_size(winw,winh);
    for(size_t x=0;x<winw;x+=width){
        for(size_t y=0;y<winh;y+=heigth){
            Gtk::Image asd(name);
            asd.show();
            put(asd,x,y);
            back.push_back(std::move(asd));
        }
    }
}

void MapView::changeBackground() {
    back.clear();
    actual_bg=(actual_bg+1)%bg_paths.size();
    setBackground(bg_paths[actual_bg]);
}

bool
MapView::isIsolated(const double &x, double y, const unsigned int &id) {
    int width,height;
    if (id==1){
        height=width=WORM_IMAGE_WIDTH;
    } else {
        y+=78; // espacio en blanco que tiene la imagen, 0 grados
        height = girder_height * SCALE_FACTOR;
        width=180 * ((id-1)/2); //180 es el largo
    }
    std::cout<< x<<"  "<<y <<std::endl;
    Gdk::Rectangle new_object(x,y,width,height);
    bool isolated= true;
    for(size_t i =0;(i<objects.size())&&(isolated);i++){
        const Gtk::Allocation &asd = objects.back().get_allocation();
        int h = asd.get_height();
        int w = asd.get_width();
        if(h>w);
        isolated=!objects[i].intersect(new_object);
    }
    return isolated;
}

int MapView::select(const double &x, const double &y) {
    Gdk::Rectangle new_object(x,y,1,1);
    bool isolated= true;
    for(size_t i=0;(i<objects.size())&&(isolated);i++){
        isolated=!objects[i].intersect(new_object);
        if (!isolated){
            this->actual_selected=i;
        }
    }

    return isolated? -1:actual_selected;
}








