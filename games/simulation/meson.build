simulation_headers = include_directories('./')
simulation_src = [
    'src/main.cpp',
    'src/grid.cpp',
    'src/systems.cpp',
]

executable('simulation', simulation_src,
    dependencies: engine_dep,
    include_directories: simulation_headers,
    install: true,
    win_subsystem: 'windows',
)
