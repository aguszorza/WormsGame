
#include <gtkmm/messagedialog.h>
#include "MapController.h"
#include "InvalidMapError.h"

#define ADD_CMD_ID 0
#define MOVE_CMD_ID 1
#define SELECT_CMD_ID 2


MapController::MapController(Map model,
                             const Glib::RefPtr<Gtk::Builder> &builder)
        : model(std::move(
        model)), actual_item_selected(1), actual_action_id(0), actual_mode(0) {
    builder->get_widget_derived("map", view);
    builder->get_widget_derived("toolbox", toolBox);
    view->linkController(this);
    toolBox->linkController(this);
}

void MapController::addModeSignal(unsigned int id) {
    this->actual_action_id = ADD_CMD_ID;
    this->actual_item_selected = id;
}

void MapController::undo() {
    model.undo(actual_object_selected);
    view->undo(actual_object_selected);
    toolBox->disableMovingItems();
}

void MapController::clean() {
    model.clean();
    view->clean();
    toolBox->disableMovingItems();
}

void MapController::moveSignal() {
    this->actual_action_id = MOVE_CMD_ID;
}

void MapController::changeModeSignal() {
    this->actual_action_id = SELECT_CMD_ID;
}

void MapController::turnCCWSignal() {
    if (model.isGirder(actual_object_selected)) {
        unsigned int id;
        int new_angle = this->model.turnCCWLast(actual_object_selected, id);
        this->view->turn(id, new_angle, actual_object_selected);
    }
}

void MapController::turnCWSignal() {
    if (model.isGirder(actual_object_selected)) {
        unsigned int id;
        int new_angle = this->model.turnCWLast(actual_object_selected, id);
        this->view->turn(id, new_angle, actual_object_selected);
    }
}

void MapController::mapClickedSignal(GdkEventButton *event_button) {
    if (actual_action_id == MOVE_CMD_ID) {
        this->model.move(actual_object_selected, event_button->x,
                         event_button->y);
        this->view->move(actual_object_selected, event_button->x,
                         event_button->y);
    } else if (actual_action_id == SELECT_CMD_ID) {
        this->actual_object_selected = view->select(event_button->x,
                                                    event_button->y);
        if (actual_object_selected > -1) {
            toolBox->enableMovingItems();
        } else toolBox->disableMovingItems();
        actual_action_id = SELECT_CMD_ID; //cambio de estado del toolbox llama a add mode
    } else {
        this->model.add(actual_item_selected, event_button->x, event_button->y);
        this->view->add(actual_item_selected, event_button->x, event_button->y);
    }
}

void MapController::getObjects(std::vector<std::vector<double>> &worms,
                               std::vector<std::vector<double>> &girders) const {
    model.getObjects(worms, girders);
    if (worms.empty()){
        throw InvalidMapError("El mapa actual no contiene worms");
    }
    if (girders.empty()){
        throw InvalidMapError("El mapa actual no contiene vigas");
    }
}

void MapController::loadObjects(std::vector<std::vector<double>> &worms,
                                std::vector<std::vector<double>> &girders) {
    clean();
    for (const auto &worm:worms) {
        this->model.add(1, worm[0], worm[1]);
        this->view->add(1, worm[0], worm[1]);
    }
    for (const auto &girder:girders) {
        this->model.add(girder[0], girder[1], girder[2], girder[3]);
        this->view->add(girder[0], girder[1], girder[2], girder[3]);
    }
}

void MapController::changeBackground() {
    this->view->changeBackground();
}
