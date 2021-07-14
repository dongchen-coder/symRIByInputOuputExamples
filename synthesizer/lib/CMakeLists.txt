add_library(LIB
    bottomUpSearch.cpp
    bottomUpSearch.hpp

    langDef.cpp
    langDef.hpp
    
    sampler.cpp
    sampler.hpp
    
    typeDef.hpp
    
    unification.cpp
    unification.hpp  
)

target_include_directories (LIB PUBLIC ${CMAKE_CUrrENT_SOURCE_DIR})
