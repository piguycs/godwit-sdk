_engine_src = [
    'src/engine.cpp',
    'src/renderables.cpp',
]

_engine_headers = [ include_directories('include') ]

deps = [ raylib_dep ]

_engine_lib = static_library(
    'engine', _engine_src,
    dependencies: deps,
    include_directories: _engine_headers,
    install: true,
)

engine_dep = declare_dependency(
    link_with: _engine_lib,
    include_directories: _engine_headers,
    dependencies: deps,
)
