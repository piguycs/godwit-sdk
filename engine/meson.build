# important to touch one of the meson.build files whenver I add/remove a file
# still more convinient than manually adding every single .cpp file here
_engine_globber = run_command('sh', '-c', 'find src -name "*.cpp" | sort', check: true)
_engine_src = _engine_globber.stdout().strip().split('\n')

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
