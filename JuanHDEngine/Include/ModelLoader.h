#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

/**
 * @class ModelLoader
 * @brief Clase encargada de cargar modelos 3D desde archivos FBX y OBJ.
 *
 * Gestiona la carga de geometrías, materiales y texturas asociadas a modelos
 * tridimensionales, procesando la información y almacenándola en MeshComponent.
 */
class ModelLoader {
public:
  /**
   * @brief Constructor por defecto de ModelLoader.
   */
  ModelLoader() = default;

  /**
   * @brief Destructor por defecto de ModelLoader.
   */
  ~ModelLoader() = default;

  /**
   * @brief Inicializa el administrador de FBX (FbxManager).
   *
   * Crea la instancia necesaria para trabajar con archivos FBX.
   * @return `true` si la inicialización fue exitosa, `false` en caso contrario.
   */
  bool InitializeFBXManager();

  /**
   * @brief Carga un modelo 3D desde un archivo FBX.
   *
   * @param filePath Ruta del archivo FBX.
   * @return `true` si el modelo se cargó correctamente, `false` si hubo errores.
   */
  bool LoadFBXModel(const std::string& filePath);

  /**
   * @brief Procesa de manera recursiva todos los nodos de la escena FBX.
   *
   * @param node Nodo actual a procesar.
   */
  void ProcessFBXNode(FbxNode* node);

  /**
   * @brief Procesa un nodo FBX que contiene información de malla (mesh).
   *
   * Extrae los vértices, normales, UVs y genera un MeshComponent.
   *
   * @param node Nodo de tipo malla a procesar.
   */
  void ProcessFBXMesh(FbxNode* node);

  /**
   * @brief Procesa los materiales asociados a una malla FBX.
   *
   * Obtiene las texturas asociadas y las almacena para su uso posterior.
   *
   * @param material Puntero al material de superficie FBX.
   */
  void ProcessFBXMaterials(FbxSurfaceMaterial* material);

  /**
   * @brief Carga un modelo desde un archivo OBJ.
   *
   * Procesa directamente el archivo y llena la lista de `meshes`.
   *
   * @param filePath Ruta del archivo OBJ.
   * @return `true` si el modelo se cargó correctamente, `false` si falló.
   */
  bool LoadOBJ_model(const std::string& filePath);

  /**
   * @brief Obtiene la lista de nombres de archivos de texturas cargadas.
   *
   * @return Vector de strings con los nombres de archivos de texturas.
   */
  std::vector<std::string> GetTextureFileNames() const { return textureFileNames; }

private:
  FbxManager* lSdkManager = nullptr; ///< Gestor principal de FBX SDK.
  FbxScene* lScene = nullptr;        ///< Escena cargada desde un archivo FBX.
  std::vector<std::string> textureFileNames; ///< Nombres de las texturas asociadas al modelo.

public:
  std::string modelName; ///< Nombre del modelo cargado.
  std::vector<MeshComponent> meshes; ///< Lista de mallas obtenidas del modelo.
};
