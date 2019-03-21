/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <iostream>

#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/rgb_color.h"
#include "src/entity_type.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
    const struct arena_params *const params,
    Arena * arena, Controller * controller) :
    GraphicsApp(
        params->x_dim + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
        params->y_dim,
        "Robot Simulation"),
    controller_(controller),
    arena_(arena),
    robot_count_(N_ROBOTS),
    light_count_(N_LIGHTS),
    food_exist_(true),
    food_count_(N_FOODS),
    fear_ratio_(RATIO_FEAR),
    sensitivity_(1200) {
  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
      gui->addWindow(
          Eigen::Vector2i(10 + GUI_MENU_GAP, 10),
          "Menu");

  window->setLayout(new nanogui::GroupLayout());

  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Start",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
      gui->addButton("New Game",
        std::bind(&GraphicsArenaViewer::OnResetBtnPressed, this));
  food_button_ = gui->addButton("Food On",
          std::bind(&GraphicsArenaViewer::OnFoodBtnPressed, this));
        gui->addGroup("Arena Configuration");

// Creating a panel impacts the layout. Widgets, sliders, buttons can be
// assigned to either the window or the panel.
nanogui::Widget *panel = new nanogui::Widget(window);

// *************** SLIDER 1 ************************//
new nanogui::Label(panel, "Number of Robots", "sans-bold");
nanogui::Slider *slider = new nanogui::Slider(panel);
// The starting value (range is from 0 to 1)
// Note that below the displayed value is 10* slider value.
slider->setValue(1.0f);
slider->setFixedWidth(100);

// Display the corresponding value of the slider in this textbox
nanogui::TextBox *textBox = new nanogui::TextBox(panel);
textBox->setFixedSize(nanogui::Vector2i(60, 25));
textBox->setFontSize(20);
textBox->setValue("10");

// This is the lambda function called while the user is moving the slider
slider->setCallback(
  [textBox](float value) {
    textBox->setValue(std::to_string(static_cast<int>(value*10)));
  }
);

// This is the lambda function called while the user's done moving the slider
slider->setFinalCallback(
  [&](float value) {
    robot_count_ = static_cast<int>(value*10);
    controller_->updateEntityCount(kRobot, robot_count_);
  }
);

// *************** SLIDER 2 ************************//
new nanogui::Label(panel, "Number of Lights", "sans-bold");
nanogui::Slider *slider2 = new nanogui::Slider(panel);
slider2->setValue(0.75f);
slider2->setFixedWidth(100);

nanogui::TextBox *textBox2 = new nanogui::TextBox(panel);
textBox2->setFixedSize(nanogui::Vector2i(60, 25));
textBox2->setFontSize(20);
textBox2->setValue("4");

slider2->setCallback(
  [textBox2](float value) {
    textBox2->setValue(std::to_string(static_cast<int>(value*6)));
  }
);

slider2->setFinalCallback(
  [&](float value) {
    light_count_ = static_cast<int>(value*6);
    controller_->updateEntityCount(kLight, light_count_);
  }
);

// *************** SLIDER 3 ************************//
new nanogui::Label(panel, "Number of Foods", "sans-bold");
nanogui::Slider *slider3 = new nanogui::Slider(panel);
slider3->setValue(0.75f);
slider3->setFixedWidth(100);

nanogui::TextBox *textBox3 = new nanogui::TextBox(panel);
textBox3->setFixedSize(nanogui::Vector2i(60, 25));
textBox3->setFontSize(20);
textBox3->setValue("4");

slider3->setCallback(
  [textBox3](float value) {
    textBox3->setValue(std::to_string(static_cast<int>(value*6)));
  }
);

slider3->setFinalCallback(
  [&](float value) {
    food_count_ = static_cast<int>(value*6);
    controller_->updateEntityCount(kFood, food_count_);
  }
);

// *************** SLIDER 4 ************************//
new nanogui::Label(panel, "Fear Ratio(%)", "sans-bold");
nanogui::Slider *slider4 = new nanogui::Slider(panel);
slider4->setValue(0.5f);
slider4->setFixedWidth(100);

nanogui::TextBox *textBox4 = new nanogui::TextBox(panel);
textBox4->setFixedSize(nanogui::Vector2i(60, 25));
textBox4->setFontSize(20);
textBox4->setValue("50");

slider4->setCallback(
  [textBox4](float value) {
    textBox4->setValue(std::to_string(static_cast<int>(value*100)));
  }
);

slider4->setFinalCallback(
  [&](float value) {
    fear_ratio_ = static_cast<int>(value*100);
    controller_->updateRobotRatio(fear_ratio_);
  }
);

// *************** SLIDER 5 ************************//
new nanogui::Label(panel, "Sensitivity", "sans-bold");
nanogui::Slider *slider5 = new nanogui::Slider(panel);
slider5->setValue(0.25f);
slider5->setFixedWidth(100);

nanogui::TextBox *textBox5 = new nanogui::TextBox(panel);
textBox5->setFixedSize(nanogui::Vector2i(60, 25));
textBox5->setFontSize(20);
textBox5->setValue("1200");

slider5->setCallback(
  [textBox5](float value) {
    textBox5->setValue(std::to_string(1800 - static_cast<int>(value*1800)));
  }
);

slider5->setFinalCallback(
  [&](float value) {
    sensitivity_ = 1800 - static_cast<int>(value*1800);
    controller_->updateSensitivity(sensitivity_);
  }
);
// **************** End of GUI Elements ************************************

// Lays out all the components with "15" units of inbetween spacing
panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical,
  nanogui::Alignment::Middle, 0, 15));
  screen()->performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (arena_ -> get_game_status() < 2) {
    controller_->AdvanceTime(0);
  } else {
    controller_->AdvanceTime(dt);
  }
}

/*******************************************************************************
 * Handlers for Playing/Resume Button
 ******************************************************************************/
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  paused_ = !paused_;
  if (!paused_) {
    playing_button_->setCaption("Pause");
    controller_ ->AcceptCommunication(kPlay);
  } else {
    playing_button_->setCaption("Play");
    controller_ ->AcceptCommunication(kPause);
  }
}

/*******************************************************************************
 * Handlers for Food Button
 ******************************************************************************/
void GraphicsArenaViewer::OnFoodBtnPressed() {
  food_exist_ = !food_exist_;
  if (food_exist_) {
    food_button_->setCaption("Food On");
    controller_ ->AcceptCommunication(kFoodOn);
  } else {
    food_button_->setCaption("Food Off");
    controller_ ->AcceptCommunication(kFoodOff);
  }
}

/*******************************************************************************
 * Handlers for User New Game button (reset)
 ******************************************************************************/
void GraphicsArenaViewer::OnResetBtnPressed() {
  playing_button_->setCaption("Start");
  paused_ = true;
  controller_->AcceptCommunication(kNewGame);
  arena_ = controller_->get_arena();
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx,
                                     const Robot *const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading of this robot
  nvgSave(ctx);
  nvgTranslate(ctx,
               static_cast<float>(robot->get_pose().x),
               static_cast<float>(robot->get_pose().y));
  nvgRotate(ctx,
            static_cast<float>(robot->get_pose().theta * M_PI / 180.0));

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, static_cast<float>(robot->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(robot->get_color().r, robot->get_color().g,
                       robot->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);


  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, static_cast<float>(M_PI / 2.0));
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, robot->get_name().c_str(), nullptr);
  nvgText(ctx, 0.0, -5.0, robot->get_type_name().c_str(), nullptr);

  // draw sensors
  nvgRotate(ctx, (M_PI));
  nvgRotate(ctx, (-40* M_PI / 180.0));
  nvgText(ctx, 0.0, static_cast<float>(robot->get_radius()), "I", nullptr);
  nvgRotate(ctx, (+80* M_PI / 180.0));
  nvgText(ctx, 0.0, static_cast<float>(robot->get_radius()), "I", nullptr);

  nvgRestore(ctx);
  nvgRestore(ctx);
}
void GraphicsArenaViewer::DrawArena(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  // Creates new rectangle shaped sub-path.
  nvgRect(ctx, 0, 0, arena_->get_x_dim(), arena_->get_y_dim());
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgStroke(ctx);
}

void GraphicsArenaViewer::DrawEntity(NVGcontext *ctx,
                                       const ArenaEntity *const entity) {
  // light's circle
  if (entity->get_type() == kRobot) {return;}
  nvgBeginPath(ctx);
  nvgCircle(ctx,
            static_cast<float>(entity->get_pose().x),
            static_cast<float>(entity->get_pose().y),
            static_cast<float>(entity->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(entity->get_color().r, entity->get_color().g,
                       entity->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // light id text label
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx,
          static_cast<float>(entity->get_pose().x),
          static_cast<float>(entity->get_pose().y),
          entity->get_name().c_str(), nullptr);
}

/*******************************************************************************
 * Drawing the Game Result
 ******************************************************************************/
void GraphicsArenaViewer::DrawGameStatus(NVGcontext *ctx) {
  int a = arena_ -> get_game_status();
  if (a == LOST) {
    nvgFillColor(ctx, nvgRGBA(0, 255, 0, 255));
    nvgFill(ctx);
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgText(ctx, arena_->get_x_dim() / 2,
      arena_->get_y_dim() / 2, "A robot has starved to death!", nullptr);
  }
}

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  DrawArena(ctx);
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  for (auto &entity : entities) {
    DrawEntity(ctx, entity);
    if (entity->get_type() == kRobot) {
      DrawRobot(ctx, dynamic_cast<Robot *>(entity));
    }
  } /* for(i..) */

  nvgFontSize(ctx, 36.0f);
  DrawGameStatus(ctx);
  nvgFontSize(ctx, 18.0f);
}

NAMESPACE_END(csci3081);
