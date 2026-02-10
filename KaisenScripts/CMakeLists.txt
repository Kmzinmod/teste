cmake_minimum_required(VERSION 3.15)
project(KaisenScripts)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurações para Windows
if(WIN32)
    add_definitions(-DUNICODE -D_UNICODE)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Diretório do Dear ImGui (ajuste conforme necessário)
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui" CACHE PATH "Path to Dear ImGui")

# Verificar se o diretório ImGui existe
if(NOT EXISTS ${IMGUI_DIR})
    message(WARNING "ImGui directory not found at ${IMGUI_DIR}")
    message(WARNING "Please download ImGui from https://github.com/ocornut/imgui")
    message(WARNING "And extract it to the 'imgui' folder in the project root")
endif()

# Include directories
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/backends)

# Arquivos do ImGui
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
)

# Arquivo principal
set(SOURCES
    kaisen_scripts.cpp
)

# Criar executável
add_executable(KaisenScripts WIN32 ${SOURCES} ${IMGUI_SOURCES})

# Bibliotecas do Windows
target_link_libraries(KaisenScripts
    d3d11
    dxgi
    d3dcompiler
)

# Definir propriedades
set_target_properties(KaisenScripts PROPERTIES
    OUTPUT_NAME "KaisenScripts"
    WIN32_EXECUTABLE TRUE
)

# Configurações de compilação
if(MSVC)
    target_compile_options(KaisenScripts PRIVATE 
        /W4 
        /WX- 
        /MP
        /permissive-
    )
    
    # Otimizações para Release
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /Oi /Ot /GL")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
else()
    target_compile_options(KaisenScripts PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

# Configurações específicas de Debug/Release
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(KaisenScripts PRIVATE DEBUG_BUILD)
else()
    target_compile_definitions(KaisenScripts PRIVATE RELEASE_BUILD)
endif()

# Instalar executável
install(TARGETS KaisenScripts
    RUNTIME DESTINATION bin
)

# Mensagens de status
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "ImGui directory: ${IMGUI_DIR}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
