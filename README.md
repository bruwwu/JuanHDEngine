# JuanEngineHD

✨ **El motor de juego diseñado para la clase de Arquitectura de Motores.**

## 📌 Descripción
JuanEngineHD es un motor de videojuegos desarrollado en C++ como parte del proyecto académico para el 8vo cuatrimestre de la carrera. Diseñado con una estructura modular y pensado para optimización y escalabilidad, este motor es una excelente base para entender el funcionamiento interno de los motores de juego modernos.

## 🚀 Tecnologías Utilizadas
- **Lenguaje:** C++
- **Entorno de Desarrollo:** Visual Studio Community
- **Gráficos:** DirectX 11
- **SDK:** Autodesk FBX SDK (para FBX)

## 🎯 Objetivo del Proyecto
Este motor fue creado con el propósito de entender, analizar y aplicar los principios de arquitectura de motores de videojuegos. Su estructura permite explorar desde el manejo de memoria y sistemas de renderizado, hasta la integración con shaders y físicas.

## 📂 Organización de Carpetas
- **include/**: Cabeceras (.h)
- **src/**: Código fuente (.cpp)
- **assets/**
  - **models/**: Archivos .fbx y .obj
  - **textures/**: Imágenes .png, .jpg
  - **shaders/**: Archivos .hlsl
- **lib/**: Librerías externas (FBX SDK y dependencias)
- **bin/**: Ejecutable y DLLs

## 📦 Carga de Modelos 3D
Se soportan dos formatos principales:
- **FBX**: Permite jerarquía de escena con nodos anidados (meshes, cámaras, luces, materiales). Requiere el SDK de Autodesk FBX.
- **OBJ**: Mallas estáticas ligeras, ideal para modelos sin jerarquía.

## 🎨 Carga de Texturas
Las texturas se gestionan mediante la clase `Texture`, que inicializa recursos en GPU y se asignan a submeshes en orden.

## 🔧 Configuración de Proyecto
1. Agregar rutas **Include** y **Library** del FBX SDK en las propiedades de Visual Studio.
2. Copiar `libfbxsdk.dll` (y dependencias) a la carpeta `bin/`.
3. Linkear las librerías: `libfbxsdk.lib`, `libxml2.lib`, `zlib.lib`.
4. Compilar en modo Debug o Release y plataforma x64.

## ▶️ Ejecución
Ejecutar `JuanEngineHD.exe` desde la carpeta `bin/`. El motor ofrece controles de cámara con **WASD** y ratón, y panel de inspección con **ImGui**.

---
© 2025 JuanEngineHD Team (yo nada mas XD)

