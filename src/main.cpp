#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// Función para verificar si el archivo existe
bool file_exists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Función para unir PDFs
void merge_pdfs(const std::string& input1, const std::string& input2, const std::string& output) {
    std::string command = "pdftk " + input1 + " " + input2 + " cat output " + output;
    system(command.c_str());
}

// Función para extraer páginas de un PDF
void extract_pages(const std::string& input, int start_page, int end_page, const std::string& output) {
    std::string command = "pdftk " + input + " cat " + std::to_string(start_page) + "-" + std::to_string(end_page) + " output " + output;
    system(command.c_str());
}

int main() {
    // Inicialización de GLFW y OpenGL
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Interfaz Gráfica con ImGui", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Error al crear la ventana GLFW\n";
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Habilitar V-Sync

    // Inicializar ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Configurar ImGui para GLFW y OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Variables para los nombres de los archivos y la salida
    char input1[128] = "";
    char input2[128] = "";
    char output[128] = "";
    int start_page = 1;
    int end_page = 1;
    int choice = 0;

    // Ciclo principal
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Iniciar nuevo frame de ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Crear ventana ImGui
        ImGui::Begin("Interfaz Gráfica de PDFtk");

        ImGui::Text("Selecciona una opción:");
        if (ImGui::RadioButton("Unir archivos PDF", &choice, 1)) {
            memset(input1, 0, sizeof(input1));
            memset(input2, 0, sizeof(input2));
            memset(output, 0, sizeof(output));
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Extraer páginas de un PDF", &choice, 2)) {
            memset(input1, 0, sizeof(input1));
            memset(output, 0, sizeof(output));
        }

        // Mostrar campos según la opción seleccionada
        if (choice == 1) {
            ImGui::InputText("Archivo PDF 1", input1, IM_ARRAYSIZE(input1));
            ImGui::InputText("Archivo PDF 2", input2, IM_ARRAYSIZE(input2));
            ImGui::InputText("Archivo de salida", output, IM_ARRAYSIZE(output));

            if (ImGui::Button("Unir PDFs") && file_exists(input1) && file_exists(input2)) {
                merge_pdfs(input1, input2, output);
                ImGui::Text("Archivos combinados con éxito.");
            }
            else if (ImGui::Button("Unir PDFs")) {
                ImGui::Text("Verifica que los archivos existan.");
            }
        }
        else if (choice == 2) {
            ImGui::InputText("Archivo PDF de entrada", input1, IM_ARRAYSIZE(input1));
            ImGui::InputInt("Página inicial", &start_page);
            ImGui::InputInt("Página final", &end_page);
            ImGui::InputText("Archivo de salida", output, IM_ARRAYSIZE(output));

            if (ImGui::Button("Extraer páginas") && file_exists(input1)) {
                extract_pages(input1, start_page, end_page, output);
                ImGui::Text("Páginas extraídas con éxito.");
            }
            else if (ImGui::Button("Extraer páginas")) {
                ImGui::Text("Verifica que el archivo exista.");
            }
        }

        ImGui::End();

        // Renderizar la interfaz
        ImGui::Render();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Limpiar recursos
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}