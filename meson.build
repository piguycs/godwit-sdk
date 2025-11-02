project(
    'gamesdk', 'cpp', 'c',
    default_options: [
        'cpp_std=c++17',
        'c_std=c99',
        'warning_level=3',
    ]
)

cmake = import('cmake')

# setting various options for raylib
_raylib_opts = cmake.subproject_options()
_raylib_opts.set_install(false)
_raylib_opts.add_cmake_defines({
    'BUILD_EXAMPLES': 'OFF',
    'PLATFORM': 'Desktop',
})

# warnings in raylib are not a problem that we can solve
_raylib_opts.set_override_option('werror', 'false')
_raylib_opts.set_override_option('warning_level', '0')

_raylib_proj = cmake.subproject('raylib', options: _raylib_opts)

# the raylib dependency that our code can depend on
raylib_dep = _raylib_proj.dependency('raylib')

subdir('engine')
subdir('games/simulation')
