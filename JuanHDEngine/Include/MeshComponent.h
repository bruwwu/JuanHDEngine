#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"

/**
 * @class MeshComponent
 * @brief Representa la geometría de un modelo 3D en la escena.
 *
 * Esta clase almacena los vértices e índices necesarios para representar un modelo en DirectX 11.
 * También incluye información sobre la cantidad de vértices e índices que componen la malla.
 */
class MeshComponent {
public:
  /**
   * @brief Constructor por defecto de MeshComponent.
   *
   * Inicializa el número de vértices e índices a cero.
   */
  MeshComponent() : m_numVertex(0), m_numIndex(0) {}

  /**
   * @brief Destructor por defecto de MeshComponent.
   */
  ~MeshComponent() = default;

public:
  std::string m_name;  ///< Nombre del modelo o malla.

  std::vector<SimpleVertex> m_vertex; ///< Vector de vértices que conforman la malla.
  std::vector<unsigned int> m_index;  ///< Vector de índices para definir las conexiones entre los vértices.

  int m_numVertex; ///< Número total de vértices en la malla.
  int m_numIndex;  ///< Número total de índices en la malla.
};
