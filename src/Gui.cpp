
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::sort;
using std::move;

#include <imgui.h>
#include "imgui_impl_glfw.h"

#include "Gui.h"

static bool show_file_browser = false;
static void menu();
static void file_menu();
static void file_browser();
static void load_dir_structure(vector<string> &path, string sub, vector<string> &dirs, vector<string> &files);
static void glinfo(const char* status);

bool show_test_window = false;
bool show_another_window = false;
ImVec4 clear_color = (ImVec4)ImColor(114, 144, 154);

Gui::Gui(GLFWwindow *w) {
    
    window = w;
    
    // Setup ImGui binding
    ImGui_ImplGlfw_Init(window, true);
    
    // Load Fonts
    // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
}

Gui::~Gui() {

}

void
Gui::background(){
    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void 
Gui::draw() {
    ImGui_ImplGlfw_NewFrame();
    // 1. Show a simple window
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
    {
        static float f = 0.0f;
        ImGui::Text("Hello, world!");
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::ColorEdit3("clear color", (float*)&clear_color);
        if (ImGui::Button("Test Window")) show_test_window ^= 1;
        if (ImGui::Button("Another Window")) show_another_window ^= 1;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
    glinfo(status.c_str());
    menu();
    if(show_file_browser) file_browser();

    // 2. Show another simple window, this time using an explicit Begin/End pair
    // if (show_another_window)
    // {
    //     ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
    //     ImGui::Begin("Another Window", &show_another_window);
    //     ImGui::Text("Hello");
    //     ImGui::End();
    // }

    // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
    if (show_test_window) {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
        ImGui::ShowTestWindow(&show_test_window);
    }
}

void
Gui::render() {
    ImGui::Render();
}

void 
Gui::shutdown() {
    ImGui_ImplGlfw_Shutdown();
}

static void
glinfo(const char* status) {
    ImGui::Begin("GL Info");
    ImGui::Text(status);
    ImGui::End();
}
// top menu
static void 
menu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            file_menu();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

static void
file_menu() {
    if (ImGui::MenuItem("Open Shape", "Ctrl+O")) show_file_browser ^= 1;
    if (ImGui::MenuItem("Load Data")) {}
    if (ImGui::MenuItem("Save Mesh", "Ctrl+S")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

// file browser panel
static void 
file_browser() {

    // ImGui::SetNextWindowSize(ImVec2(200,0), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Load Shape", &show_file_browser, ImGuiWindowFlags_AlwaysAutoResize);

    static vector<string> files; 
    static vector<string> dirs;
    static vector<string> path = {"."};
    if(dirs.empty()) load_dir_structure(path, "", dirs, files);

    ImGui::Columns(1, "mycolumns"); // 4-ways, with eborder
    // ImGui::Separator();
    // ImGui::Text(path.c_str()); ImGui::NextColumn();
    // ImGui::Separator();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1.0, 4.0));
    int path_s = path.size();
    for(int i=0; i<path_s; i++) {
        if(ImGui::Button(path[i].c_str())){
            path.erase(path.begin()+i+1, path.end());
            load_dir_structure(path, "", dirs, files);
            break;
        }; 
        if(i!=path_s-1) ImGui::SameLine();
    }
    ImGui::PopStyleVar();

    // ImGui::PushStyleVar(ImGuiStyleVar_ChildWindowRounding, 5.0f);
    ImGui::BeginChild("FileList", ImVec2(300, 200), true);
    static int selected = -1;
    int i = 0;
    if(!dirs.empty())
    for (vector<string>::iterator dirs_it=dirs.begin(); dirs_it<dirs.end(); dirs_it++) {
        string dir = *dirs_it;
        if(dir != "..") dir += "/";
        if(ImGui::Selectable(dir.c_str(), selected == i, ImGuiSelectableFlags_AllowDoubleClick)) {
            if (ImGui::IsMouseDoubleClicked(0)) {
                load_dir_structure(path, *dirs_it, dirs, files);
                selected = -1;
                break;
            } else selected = i;
        }
        i++;
    }
    if(!files.empty())
    for (vector<string>::iterator files_it=files.begin(); files_it<files.end(); files_it++) {
        if(ImGui::Selectable(files_it->c_str(), selected == i, ImGuiSelectableFlags_AllowDoubleClick)) {
            selected = i;
        }
        i++;
    }
    
    // ImGui::Separator(); 
    ImGui::EndChild();
    // ImGui::PopStyleVar();

    if (ImGui::Button("cancel")) show_file_browser ^= 1; ImGui::SameLine();
    if (ImGui::Button("ok")    ) show_file_browser ^= 1;
    ImGui::End();
}

// helper dir structure read
static void
load_dir_structure(
    vector<string> &path, 
    string sub, 
    vector<string> &dirs, 
    vector<string> &files) {

    DIR* dir;
    dirent* ent;
    dirs.clear();
    files.clear();
    
    string path_s = "";
    string last = path[path.size()-1];
    bool back = sub==".." && last!=".." && last!=".";
    if(back) path.pop_back();
    else if(sub != "") path.push_back(sub);
    for(size_t i=0; i<path.size(); i++) {
        path_s += path[i]+"/";
    }
    
    printf("LOAD %s\n", path_s.c_str());

    if((dir = opendir(path_s.c_str())) != NULL) {
        while((ent = readdir(dir)) != NULL) {
            string name = ent->d_name;
            if(ent->d_type == DT_DIR) {
                if(name == ".") continue;
                dirs.push_back(name);
            } else if(ent->d_type == DT_REG) {
                files.push_back(name);
            }
        }
        closedir(dir);
    } else {
        // dirs.push_back("ERR");
    }
    sort(dirs.begin(), dirs.end());
    sort(files.begin(), files.end());
}

// TODO: Context info

