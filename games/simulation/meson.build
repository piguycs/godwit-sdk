simulation_headers = include_directories('include/')
simulation_src = [
    'src/main.cpp',
]

executable('simulation', simulation_src,
    dependencies: engine_dep,
    include_directories: simulation_headers,
    install: true,
    win_subsystem: 'windows',
)
