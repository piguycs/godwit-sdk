globber = run_command('sh', '-c', 'find . -name "*.cpp" | sort', check: true)
sdk_core_src = globber.stdout().strip().split('\n')

deps = [
    raylib_dep,
]

_sdk_headers = [
    include_directories('include'),
]

_sdk_lib = static_library('sdk', sdk_core_src,
    dependencies: deps,
    include_directories: _sdk_headers,
    install: true,
)

sdk_core_dep = declare_dependency(
    link_with: _sdk_lib,
    include_directories: _sdk_headers,
    dependencies: deps,
)
