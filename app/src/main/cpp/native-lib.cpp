#include <jni.h>
#include <vector>
#include <string.h>
#include <dobby.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <pthread.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"
#include "Utils.h"
#include "Unity.h"


int  glWidth, glHeight;


#define HOOK(ret, func, ...) \
    ret (*orig##func)(__VA_ARGS__); \
    ret my##func(__VA_ARGS__)

HOOK(void, Input, void *thiz, void *ex_ab, void *ex_ac){
    origInput(thiz, ex_ab, ex_ac);
    ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)thiz);
    return;
}

void SetupImgui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2((float)glWidth, (float)glHeight);

    // Setup Dear ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.3f;
	style.FrameRounding = 2.3f;
	style.ScrollbarRounding = 0;
	
	style.Colors[ImGuiCol_Text]                  = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
	style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_WindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
	style.Colors[ImGuiCol_Border]                = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
	style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
	style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
	style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
	style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
	style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
	style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
	style.Colors[ImGuiCol_Button]                = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
	style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
	style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Header]                = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
	style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
	style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_Button]           = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
	style.Colors[ImGuiCol_ButtonHovered]    = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
	style.Colors[ImGuiCol_ButtonActive]     = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ModalWindowDimBg]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(16,16,16);
    style.Colors[ImGuiCol_ChildBg] = ImColor(24,24,24);
    style.Colors[ImGuiCol_Text] = ImColor(255,255,255);
    style.Colors[ImGuiCol_Header] = ImColor(30,30,30);
    style.Colors[ImGuiCol_HeaderActive] = ImColor(28,28,28);
    style.Colors[ImGuiCol_HeaderHovered] = ImColor(28,28,28);
       
    style.Colors[ImGuiCol_Button] = ImColor(36, 36, 36);
    style.Colors[ImGuiCol_ButtonActive] = ImColor(40, 40, 40);
    style.Colors[ImGuiCol_ButtonHovered] = ImColor(40, 40,40);
       
    style.Colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30);
    style.Colors[ImGuiCol_FrameBgActive] = ImColor(28, 28, 28);
    style.Colors[ImGuiCol_FrameBgHovered] = ImColor(28, 28, 28);

    style.Colors[ImGuiCol_TitleBg] = ImColor(30, 30, 30);
    style.Colors[ImGuiCol_TitleBgActive] = ImColor(28, 28, 28);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(28, 28, 28);

    // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init("#version 100");
    
    // We load the default font with increased size to improve readability on many devices with "high" DPI.
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    io.Fonts->AddFontDefault(&font_cfg);

    // Arbitrary scale-up
    ImGui::GetStyle().ScaleAllSizes(3.0f);
}

bool clearMousePos = true, setup = false;

void Menu(){
	struct game_data {
		const char* name;
        std::string status;
        std::string last_updated;
        bool undetected;
		bool open;
		int id;
	};
    static std::vector<game_data> games = {
		{("Menu 1"),"Undetected","03/15",true,false,1},
        {("Menu 2"),"May Crash ","09/11",false,false,2},
        {("Menu 3"),"Undetected","03/17",true,false,3},
	};
	static int game = 0;
    
	ImGui::SetNextWindowSize(ImVec2(glWidth/2, glHeight/1.5), ImGuiCond_Always);
	
	if(ImGui::Begin(("ImGui Layout By Musk"),0,/*ImGuiWindowFlags_NoTitleBar || */ImGuiWindowFlags_NoResize)){
		ImGui::BeginChild("##leftChild", ImVec2(ImGui::GetWindowSize().x/3, ImGui::GetWindowSize().y*0.85f ));
		{
			for (unsigned int i = 0; i < games.size(); i++) {
				bool selected = (game == i); 
				if (ImGui::Selectable(games[i].name, &selected))
					game = i;
				    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20 );
					if (selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
            }
            ImGui::EndChild();

            {
                ImGui::SameLine(0);
                ImGui::SameLine();
            }
            ImGui::BeginChild("##rightChild", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetWindowSize().y * 0.85f));
            {
                auto& t = games[game];
                auto center = [](float  avail_width, float element_width, float padding = 0)
                {
                    ImGui::SameLine((avail_width / 2)-element_width/2 + padding);
                };

                auto center_text = [&](const char* format,float spacing = 15,ImColor color = ImColor(255,255,255))
                {
                    center(ImGui::GetContentRegionAvail().x, ImGui::CalcTextSize(format).x);
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing );
                    ImGui::TextColored(color.Value,format);
                };

                center_text(t.name,0);
                center_text(t.status.c_str(),28,(t.undetected ? ImColor(0,255,0) : ImColor(255,0,0)));
                center_text(t.last_updated.c_str(), 37);
			    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize , 1);
				
				int i = t.id;
				
				switch(i){
					case 1 :
					    center_text(t.open ? ("Status : Deactivated") : ("Status : Activated"), 46,(t.open ? ImColor(0,255,0) : ImColor(255,0,0)));
					    ImGui::Text("Menu 1");
					break;
					
					case 2 :
						ImGui::Text("Menu 2");
					break;
					
					case 3 :
						ImGui::Text("Menu 3");
					break;
				}
	ImGui::PopStyleVar();  
   }
ImGui::EndChild();
}
ImGui::End();
}


EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
 eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

	if (!setup) {
        SetupImgui();
        setup = true;
    }

    ImGuiIO &io = ImGui::GetIO();


    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // Render ImGui windows here.
    Menu();

    // Rendering
    ImGui::EndFrame();
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (clearMousePos) {
        io.MousePos = ImVec2(-1, -1);
        clearMousePos = false;
    }

    return old_eglSwapBuffers(dpy, surface);
}

void *imgui_go(void *) {
    //We Do Sleep the functions till the game is loaded prperly
    sleep(13);


    address = findLibrary(sofile);

    // Hook eglSwapBuffers
    auto addr = (uintptr_t)dlsym(RTLD_NEXT, "eglSwapBuffers");
    
   /******Lets hook to the egl*****/
    DobbyHook((void *)addr, (void *)hook_eglSwapBuffers, (void **)&old_eglSwapBuffers);
    
    ///exit to prevent more memory usages
    pthread_exit(nullptr);
    return nullptr;


}
__attribute__((constructor))
void lib_main() {
    
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, imgui_go, NULL);
    
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * reserved)
{
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    void *sym_input = DobbySymbolResolver(("/system/lib/libinput.so"), ("_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE"));
    if (NULL != sym_input){
        DobbyHook((void *)sym_input, (void *) myInput, (void **)&origInput);
    }
    return JNI_VERSION_1_6;
}