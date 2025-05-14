source_files = [
    'godwit.cpp'
]

_sdk_headers = include_directories('include')
_sdk_lib = static_library('sdk', source_files,
    include_directories: _sdk_headers,
    install: false,
)

sdk_dep = declare_dependency(
    link_with: _sdk_lib,
    include_directories: _sdk_headers,
)
