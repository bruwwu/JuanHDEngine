#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"
#include "ECS/Component.h"

/**
 * @class MeshComponent
 * @brief Componente que almacena la información de una malla 3D.
 *
 * Extiende la clase base `Component` y se encarga de representar la geometría de un modelo
 * a través de vértices e índices, además de definir cómo se debe actualizar y renderizar.
 */
class MeshComponent : public Component {
public:
  /**
   * @brief Constructor por defecto de MeshComponent.
   *
   * Inicializa el número de vértices e índices a cero y establece el tipo de componente como `MESH`.
   */
  MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

  /**
   * @brief Destructor por defecto de MeshComponent.
   */
  virtual ~MeshComponent() = default;

  /**
   * @brief Actualiza la lógica del componente.
   *
   * En el caso de `MeshComponent`, este método no realiza ninguna acción.
   *
   * @param deltaTime Tiempo transcurrido desde la última actualización.
   */
  void update(float deltaTime) override {}

  /**
   * @brief Renderiza el componente utilizando el contexto de dispositivo.
   *
   * En este nivel, `render` está vacío. Se espera que clases derivadas o instancias especializadas lo implementen si es necesario.
   *
   * @param deviceContext Contexto del dispositivo para operaciones gráficas.
   */
  void render(DeviceContext& deviceContext) override {}

public:
  std::string m_name;                 ///< Nombre identificador de la malla.
  std::vector<SimpleVertex> m_vertex;  ///< Lista de vértices de la malla.
  std::vector<unsigned int> m_index;   ///< Lista de índices que definen las caras de la malla.
  int m_numVertex;                     ///< Número total de vértices.
  int m_numIndex;                      ///< Número total de índices.
};
