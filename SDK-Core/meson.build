sdk_core_src = [
    'src/godwit.cpp',
    'src/event_handler.cpp',
]

deps = [
    raylib_dep,
]

_sdk_headers = [
    include_directories('include'),
]

_sdk_lib = static_library('sdk', sdk_core_src,
    dependencies: deps,
    include_directories: _sdk_headers,
    install: false,
)

sdk_core_dep = declare_dependency(
    link_with: _sdk_lib,
    include_directories: _sdk_headers,
    dependencies: deps,
)
