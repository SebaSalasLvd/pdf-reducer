# pdf-reducer, objetivo del proyecto: Desarrollar una aplicación de escritorio para manipular pdfs

### Requisitos:
- Docker
- C++17
## Instrucciones
Desde la raíz del repositorio, creamos un contenedor de docker y lo activamos
`````bash
docker build -t pdf-reducer .
docker run --rm -it -v "$(Get-Location):/workspace" pdf-reducer
`````

Luego de ello  debemos movernos a build y ejecutar cmake para compilar nuestro main

`````bash
cd build
cmake ..
````



