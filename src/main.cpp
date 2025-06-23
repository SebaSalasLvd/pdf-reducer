#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

bool file_exists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void merge_pdfs() {
    std::string input1, input2, output;
    
    do {
        std::cout << "Introduce el primer archivo PDF: ";
        std::cin >> input1;
        if (!file_exists(input1)) {
            std::cout << "El archivo no existe. Intenta de nuevo.\n";
        }
    } while (!file_exists(input1));

    do {
        std::cout << "Introduce el segundo archivo PDF: ";
        std::cin >> input2;
        if (!file_exists(input2)) {
            std::cout << "El archivo no existe. Intenta de nuevo.\n";
        }
    } while (!file_exists(input2));

    std::cout << "Introduce el nombre del archivo de salida: ";
    std::cin >> output;

    std::string command = "pdftk " + input1 + " " + input2 + " cat output " + output;
    system(command.c_str());
    std::cout << "Archivos combinados con éxito.\n";
}

void extract_pages() {
    std::string input, output;
    int start_page, end_page;

    do {
        std::cout << "Introduce el archivo PDF de entrada: ";
        std::cin >> input;
        if (!file_exists(input)) {
            std::cout << "El archivo no existe. Intenta de nuevo.\n";
        }
    } while (!file_exists(input));

    std::cout << "Introduce el rango de páginas para extraer \n";
    std::cout << "Introduce la página inicial del rango: ";
    std::cin >> start_page;
    std::cout << "Introduce la página final del rango (si es una sola página, usa el mismo número): ";
    std::cin >> end_page;

    std::cout << "Introduce el nombre del archivo de salida: ";
    std::cin >> output;

    std::string command = "pdftk " + input + " cat " + std::to_string(start_page) + "-" + std::to_string(end_page) + " output " + output;
    system(command.c_str());
    std::cout << "Páginas extraídas con éxito.\n";
}


int main() {
    int choice;

    std::cout << "¡Bienvenido al programa interactivo de pdftk!\n";
    std::cout << "Selecciona una opción:\n";
    std::cout << "1. Unir archivos PDF\n";
    std::cout << "2. Extraer páginas de un PDF\n";
    std::cout << "Opción: ";
    std::cin >> choice;

    switch(choice) {
        case 1:
            merge_pdfs();
            break;
        case 2:
            extract_pages();
            break;
        default:
            std::cout << "Opción no válida.\n";
    }

    return 0;
}